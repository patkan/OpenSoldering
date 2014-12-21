/*
 *    Filename: jbcmodul.c
 *     Version: 0.0.1
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
#include "periph.c"


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
	PORTC = 1<<PC3 | 1<<PC4 | 1<<PC5; // Pullup für Lötkolbenständerschalter
	PORTD = 1<<PD3; // Lötspitzenwechslerschalter
	
	delayms(100);
	
	spiInit();
	i2cInit();
	lm75Init();
// 	timerInit();
// 	uartInit();
	writeSegments(42);
	
// 	sei(); // und es seien Interrupts :D
	
	uint16_t temp = 0;
	uint8_t i = 0;
	
	while(1) {
// 		lm75Init();
		temp = i2cRxLm75 (0b1001000);
		
		writeSegments (i++);
		delayms(500);
	}
	return 0;
}
