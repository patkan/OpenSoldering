/*
 *    Filename: jbcmodul.c
 *     Version: 0.0.1
 * Description: Ansteuerung eines JBC T245A Lötkolbens
 *     License: GPLv3 or later
 *     Depends: global.h, io.h, interrupt.h, uart, i2c
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

#include "../../AtmelLib/global.h"
#include "../../AtmelLib/io/io.h"
#include <avr/interrupt.h>


#define LATCH(x) out(PORTB, PB2,0,x)

void spiInit (void) {
	DDRB |= 1<<PB2 | 1<<PB3 | 1<<PB5;
	SPCR = 1<<SPE | 1<<MSTR; // SPI Master Mode, clock vollgas
	SPSR = 0;
}


// Anordnung der Segmente: DP, C, B, A, G, F, E, D
#define A (1<<4)
#define B (1<<5)
#define C (1<<6)
#define D (1<<0)
#define E (1<<1)
#define F (1<<2)
#define G (1<<3)
#define DP (1<<7)

uint8_t segEncode(uint8_t ziffer) {
	// einfach eine große Switch-case Kaskade
	switch (ziffer) {
		case 0: // ABCDEF
		return ~(A | B | C | D | E | F);
		break;
		case 1: // FE
		return ~(B | C);
		break;
		case 2: // ABGED
		return ~(A | B | G | E | D);
		break;
		case 3: // ABGCD
		return ~(A | B | G | C | D);
		break;
		case 4: // FGBC
		return ~(F | G | B | C);
		break;
		case 5: // AFGCD
		return ~(A | F | G | C | D);
		break;
		case 6: // ACDEFG
		return ~(A | C | D | E | F | G);
		break;
		case 7: // ABC
		return ~(A | B | C);
		break;
		case 8: // ABCDEFG
		return ~(A | B | C | D | E | F | G);
		break;
		case 9: // GFABCD
		return ~(G | F | A | B | C | D);
		break;
		default:
		return 0xFF;
	}
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
	delayms(100);
	
	DDRB = 1<<PB0 | 1<<PB1 | 1<<PB2 | 1<<PB3 | 1<<PB5;
	DDRD = 1<<PD1 | 1<<PD4 | 1<<PD5; // WS2812B Datenpin
	PORTC = 1<<PC4; // Pullup für Lötkolbenständerschalter
	PORTD = 1<<PD3; // Lötspitzenwechslerschalter
	
	spiInit();
// 	lm75Init();
// 	timerInit();
// 	uartInit();
	
// 	sei(); // und es seien Interrupts :D
	
	while(1) {
		for (uint16_t i=0; i<1000; i++) {
			writeSegments(i);
			delayms(100);
		}
	}
	return 0;
}
