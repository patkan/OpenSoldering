/*
 *    Filename: loetkobenmodul.c
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
#include "pid.c"


void setKolbenPower (float sollwert) {
	// 16bit Timer1 auf FastPWM, Ausgang OC1A sei Lötkolben.
}

// Der ADC wird interruptgesteuert
volatile uint8_t counter = 0; // für Berechnung von Heizleistung und Temperatur des Lötkolbens
volatile float leistung = 0; // Lötkolbenleistung aktuell
volatile uint16_t spitzentemp = 0, heizstrom = 0, eingangsspannung = 0; // U in mV, I in mA
volatile uint16_t solltemperatur = 0, platinentemperatur = 0;

// PD-Reglerparameter (durch Software veränderlich!!)
volatile float t = 1, tn = 1, kr = 1; // Zeitkonstante und Reglerverstärkung

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


	// PID Regler muss auch hier drin arbeiten, da er mit gleichem Zeitabstand
	// ausgeführt wird, wie der ADC. bzw. mit 1/3 der ADC Frequenz.

	/* Erklärung der Ausgangsübertragungsfunktion und der Regelung:
	*
	* yk	= Ausgang (PWM-Wert)
	* yk1	= vorheriger Ausgangswert
	* kr	= Reglerverstärkung (P)
	* ek	= Eingang (Temperatur)
	* ek1	= vorheriger Eingangswert
	* t	= Zeitkonstante 1 (vmtl. die der Strecke)
	* tn	= Reglerzeitkonstante
	*
	* Die Strecke G(s) muss noch ermittelt werden, sie wandelt ein PWM-Signal
	* in ein Wärmesignal um (Lötkolben incl. MOSFET ist G(s) vmtl. PT1
	*
	* Die Vorsteuerung Gws(s) sorgt dafür, dass die Temperatursprünge, die
	* auf das Sollsignal gegeben werden, nicht direkt in den Regelkreis
	* einwirken.
	*
	* Der Regler Gr(s) = Kr * (1+ (1 / Tns)) ist ein PI Regler mit der Regler-
	* verstärkung Kr und der Zeitkonstante Tn. s ist unbekannt.
	*
	* Die Störung Z(s) wirkt direkt auf die Temperatur der Lötspitze ein, sie
	* ist der Wärmestrom von der Lötspitze in die Luft (Standardfall) oder in
	* die Lötstelle (Regler muss eingreifen)
	*/

	// static float  yk = 0, yk1 = 0; // letzter Reglerausgangswert
	// uint16_t ek = spitzentemp, ek1;
	//
	// Regler (Konzept: PD)
	// yk = yk1 + (kr * (ek - ek1 + (t / tn) * ek1));
	// yk1 = yk;
	// ek1 = ek; // sichere letzten Tempwert



	//das oben ist die alte Implementierung mit Kommentaren, jetzt erstmal eine
	//neue, dann schauen, ob sich noch etwas recyclen lässt.

	yk = pid_compute(spitzentemp, solltemperatur);


	// Weitergabe an Ausgabefunktion:
	setKolbenPower (yk);
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
			// Lötspitzentemperatur wird ausgerechnet
			for(uint8_t i=0; i<MITTELWERTE; i++) {
				temp += tabelle[0 + 3*i];
			}
			// Achtung: die Lötspitze wird kaltstellenkompensiert (daher die Zusatzvariable)
			spitzentemp = (uint16_t)((float)((temp*REFERENZ)<<2)*ABWEICHUNG*SPANNUNG_PRO_GRAD) + platinentemperatur;
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

	uint16_t temp = 0;

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
