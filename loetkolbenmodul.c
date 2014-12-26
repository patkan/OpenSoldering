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


// Der ADC wird interruptgesteuert
volatile uint8_t counter = 0;
// nötig für Berechnung der Heizleistung und Temperatur des Lötkolbens
volatile float leistung = 0;
volatile uint16_t spitzentemp=0, heizstrom=0, eingangsspannung=0; // U in mV, I in mA
ISR (TIMER1_COMPA_vect, ISR_BLOCK) {
	ADMUX = ADMUX & 0b11100000; // lösche selektiv die MUX-Bits
	ADMUX |= (counter%3); // setze ADC-Kanal neu
	ADCSRA |= 1<<ADSC; // start conversion
}

// ADC Conversion complete Interrupt
// ADC0 = Temperatur, ADC1 = Heizstrom, ADC2 = Systemspannung
// Die Werte können noch kalibriert werden, allerdings nicht zur Laufzeit.

#define REFERENZ 4	// externe Referenz, 4096mV also 4mV pro STEP
#define ABWEICHUNG 1.0  // gemessene Abweichung in % vom exakten Referenzspannungswert
#define MITTELWERTE 4

ISR (ADC_vect, ISR_BLOCK) {
	// 	uartTxStrln("adc");
	// ADC-Auslesungen und Rechnung mit Gleitmittelwert über 4 Werte
	static uint16_t tabelle[3*MITTELWERTE]; // hier kommen die ADC-werte rein.
	uint16_t temp=0;
	tabelle[counter] = ADC; // fülle Tabelle mit ADC-Werten
	
// 	TODO: Formeln anpassen!!
	
	switch (counter%3) {
		case 0:
			// spitzentemp wird ausgerechnet
			for(uint8_t i=0; i<MITTELWERTE; i++) {
				temp += tabelle[0 + 3*i];
			}
			spitzentemp = (uint16_t)((temp*REFERENZ)<<2)*ABWEICHUNG;
			break;
			
		case 1:
			// heizstrom wird ausgerechnet
			for(uint8_t i=0; i<MITTELWERTE; i++) {
				temp += tabelle[1 + 3*i];
			}
			heizstrom = (uint16_t)((temp*REFERENZ)<<2)*ABWEICHUNG;
			break;
			
		case 2:
			// eingangsspannung wird ausgerechnet
			for(uint8_t i=0; i<MITTELWERTE; i++) {
				temp += tabelle[2 + 3*i];
			}
			
			eingangsspannung = (uint16_t)((float)temp*ABWEICHUNG*((float)50/(float)3));
			break;
	}
	counter++;
	if (counter == 3*MITTELWERTE) { // setze Counter zurück
		counter = 0;
	}
	leistung = ((float)heizstrom * (float)eingangsspannung) / 1000; // Leistung in Watt
}


void writeSegments (uint16_t zahl) {
	// Setze die 7-segment-Displays der Lötstation
	SPDR = segEncode(zahl/100); // Zahl darf nicht über 999 sein
	while (!(SPSR & 1<<SPIF));
	SPDR = segEncode((zahl%100)/10);
	while (!(SPSR & 1<<SPIF));
	SPDR = segEncode(zahl%10);
	while (!(SPSR & 1<<SPIF));
	LATCH(1);
	delayus(1);
	LATCH(0);
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
		temp = i2cRxLm75 (0b1001000);
// 		writeSegments (i2cERR & 0xF8);
		writeSegments (temp/16);
		delayms(500);
	}
	return 0;
}
