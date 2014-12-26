// Defines-Datei

// Hier werden Einstellungen für das Lötkolbenprojekt,
// bzw. für die Software vorgenommen.


// Allgemeiner Teil
#include "../AtmelLib/global.h"
#include "../AtmelLib/io/io.h"
#include <avr/interrupt.h>
#include <util/twi.h>
#include <avr/pgmspace.h>

#include "periph.c"
#include "light_ws2812/light_ws2812.c"

// Einstellung, welcher Lötkolben gerade angeschlossen ist
#define JBC
// #define WELLER_WXMP
// #define WELLER_LEGACY

#define LATCH(x) out(PORTB, PB2,0,x)

// Anordnung der Segmente: DP, C, B, A, G, F, E, D
// MSB ist hiermit der Punkt (üblich)
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
