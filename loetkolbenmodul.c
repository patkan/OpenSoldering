/*
 *    Filename: jbcmodul.c
 *     Version: 0.0.4
 * Description: Ansteuerung eines JBC T245A Lötkolbens
 *     License: GPLv3 or later
 *     Depends: global.h, io.h, interrupt.h, sb9, i2c
 *
 *      Author: Copyright (C) Philipp Hörauf
 *        Date: 2014-12-19
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "definitionen.h"


void setKolbenPower (float sollwert) {
	// 16bit Timer1 auf FastPWM, Ausgang OC1A sei Lötkolben.
}

// Der ADC wird interruptgesteuert
volatile uint8_t counter = 0; // für Berechnung von Heizleistung und Temperatur des Lötkolbens
volatile float leistung = 0, rawtemp = 0, spitzentemp = 0;
volatile uint16_t heizstrom = 0, eingangsspannung = 0; // U in mV, I in mA
volatile uint16_t solltemperatur = 0, platinentemperatur = 0;

volatile float ki = 1, kp = 1;

ISR (TIMER0_OVF_vect, ISR_BLOCK) {
	ADMUX = ADMUX & 0b11100000; // lösche selektiv die MUX-Bits
	ADMUX |= (counter%3); // setze ADC-Kanal neu
	ADCSRA |= 1<<ADSC; // start conversion

	// Auslesung der Temperatur des LM75-Sensors
	static uint8_t i2cAuslesung = 0;
	if (i2cAuslesung == 123) { // es sind ca 500 ms vergangen
		platinentemperatur = (i2cRxLm75 (0b1001000)) /16; // erst mal in ganzen °C
		i2cAuslesung = 0;
	} else {
		i2cAuslesung++;
	}
		
	
	// PI Regler muss auch hier drin arbeiten, da er mit gleichem Zeitabstand
	// ausgeführt wird, wie der ADC. bzw. mit 1/3 der ADC Frequenz.
	
	/* Erklärung der Ausgangsübertragungsfunktion und der Regelung:
	* 
	* yk	= Ausgangswert des Integrators
	* ek	= Differenz der Temperatur vom Sollwert (+ => zu kalt)
	* ki	= I-Verstärungswert
	* kr	= Reglerverstärkung
	* 
	* Eine Vorsteuerung hat wegen der stark wechselnden Lastsituationen
	* keinen großen Sinn und wird daher weggelassen.
	*
	* Die Störung Z(s) wirkt direkt auf die Temperatur der Lötspitze ein, sie
	* ist der Wärmestrom von der Lötspitze in die Luft (Standardfall) oder in
	* die Lötstelle (Regler muss eingreifen)
	*/
	
	// Regler (Konzept: PI)
	float ek = solltemperatur - rawtemp;
	static float yk;
	yk += (ki * ek);
	
	// Weitergabe an Ausgabefunktion:
	setKolbenPower (yk + (kp * ek));
}

// ADC Conversion Complete Interrupt
// ADC0 = Temperatur, ADC1 = Heizstrom, ADC2 = Systemspannung
// Die Werte können noch kalibriert werden, allerdings nicht zur Laufzeit.

#define REFERENZ 1			// externe Referenz, 1250mV also 1,2207mV pro STEP
#define ABWEICHUNG 0.220703125		// gemessene Abweichung in %/100 vom exakten Referenzspannungswert
#define MITTELWERTE 4
#define SPANNUNG_PRO_GRAD 1.00000	// Spannung am ADC pro Grad am Lötkolben
#define SPANNUNG_PRO_AMPERE 0.2		// Spannung am ADC pro Ampere das durch die Heizung fließt
#define SPANNUNG_PRO_VOLT 0.04347826	// Spannung am ADC pro Volt der Versorgungsspannung

ISR (ADC_vect, ISR_BLOCK) {
	// 	uartTxStrln("adc");
	// ADC-Auslesungen und Rechnung mit Gleitmittelwert über 4 Werte
	static uint16_t tabelle[3*MITTELWERTE]; // hier kommen die ADC-werte rein.
	uint16_t temp=0;
	tabelle[counter] = ADC; // fülle Tabelle mit ADC-Werten
	
// 	TODO: Formeln anpassen!!
	
	switch (counter%3) {
		case 0:
			// Achtung: die Lötspitze wird kaltstellenkompensiert (daher die Zusatzvariable)
			spitzentemp = spitzentemp*0.95 + (((float)((temp*REFERENZ)<<2)*ABWEICHUNG*SPANNUNG_PRO_GRAD) + platinentemperatur)*0.05;
			rawtemp = ((float)((tabelle[counter]*REFERENZ)<<2)*ABWEICHUNG*SPANNUNG_PRO_GRAD) + platinentemperatur;
			break;
			
		case 1:
			// Heizstrom wird ausgerechnet
			for(uint8_t i=0; i<MITTELWERTE; i++) {
				temp += tabelle[1 + 3*i];
			}
			heizstrom = (uint16_t)((float)((temp*REFERENZ)<<2)*ABWEICHUNG*SPANNUNG_PRO_AMPERE);
			break;
			
		case 2:
			// Eingangsspannung wird ausgerechnet
			for(uint8_t i=0; i<MITTELWERTE; i++) {
				temp += tabelle[2 + 3*i];
			}
			eingangsspannung = (uint16_t)((float)temp*ABWEICHUNG*SPANNUNG_PRO_VOLT);
			break;
	}
	counter++;
	if (counter == 3*MITTELWERTE) { // setze Counter zurück
		counter = 0;
	}
	leistung = ((float)heizstrom * (float)eingangsspannung) / 1000; // Leistung in Watt
}



int main(void) {
	
	// Allgemeine PIN- und PORT-Einstellungen
	DDRB = 1<<PB0 | 1<<PB1 | 1<<PB2 | 1<<PB3 | 1<<PB5;
	DDRD = 1<<PD1 | 1<<PD4 | 1<<PD5; // PD4 ist WS2812B Datenpin
	PORTC = 1<<PC3; // Pullup für Lötkolbenständerschalter
	PORTD = 1<<PD3; // Lötspitzenwechslerschalter
	
	delayms(100);
	
	spiInit();
	i2cInit();
	lm75Init();
// 	timerInit();
// 	uartInit();
	writeSegments(42);
	
	// Initialiserung der WS2812-StatusLED
	struct cRGB led[1];
	led[0].g=128;
	led[0].b=75;
	led[0].b=25;
	ws2812_setleds(led,1);
	
// 	sei(); // und es seien Interrupts :D
	
	delayus(10);
	i2cRxLm75Start(0b1001000);
	
	while(1) {
// 		i2cRxLm75Start(0b1001000);
// 		temp = i2cRxLm75 (0b1001000);
// 		writeSegments (i2cERR & 0xF8);
		writeSegments (platinentemperatur);
		delayms(100);
	}
	return 0;
}
