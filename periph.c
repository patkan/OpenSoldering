// Initialisierungsfunktionen für die verschiedenen
// Peripheriekomponenten wie SPI, I2C, SB9, ...


//******************************************************
//	INIT Funktionen für Peripheriekomponenten
//******************************************************

void spiInit (void) {
	DDRB |= 1<<PB2 | 1<<PB3 | 1<<PB5;
	SPCR = 1<<SPE | 1<<MSTR; // SPI Master Mode, clock vollgas
	SPSR = 0;
}

void i2cInit (void) {
	// verwende natürlich auch hier VOLLGAS (400kHz Clockspeed)
	TWBR = 3;
	TWCR = 1<<TWEA | 1<<TWEN; // automatisch ACK
	TWSR = 1<<TWPS0; // prescaler = 4
}

void adcInit(void) {
	ADMUX = 0; // Referenz auf externe Referenz
	ADCSRA = 1<<ADEN | 1<<ADSC | 1<<ADIE | 5<<ADPS0; // ADC an, Interrupt an, Prescaler=128
}

void timerInit(void) {
	// Timer/Counter1 im CTC modus verwenden. alle 10ms ein Interrupt
	TCCR1A = 0; // CTC (mode 4)
	TCCR1B = 1<<WGM12 | 1<<CS11 | 1<<CS10; // CTC (mode 4), Prescaler = 64 -> 4µs pro Timerschritt
	TIMSK = 1<<OCIE1A; // Interrupt on compare match
	OCR1A  = 2500; // TOP und Interrupt alle 10ms bei 16MHz clockspeed
}



//******************************************************
//	Systemfunktionen und HAL
//******************************************************

uint8_t i2cERR = 0;
uint8_t i2cError (void) {
	i2cERR = TWSR;
	TWSR = 1<<TWPS0; // lösche alles außer der ersten beiden Bits
	return i2cERR;
}

void i2cDelay (void) {
	while (!(TWCR & (1<<TWINT))); // Warte, dass sich das TWINT-Bit setzt
}

void i2cStart (void) {
	// Start Condition
	TWCR = 1<<TWINT | 1<<TWSTA | 1<<TWEN;
	i2cDelay ();
	if ((TWSR & 0xF8) != TW_START) {
		i2cError();
	}
}

inline void i2cRestart (void) {
	i2cStart ();
}

void i2cStop (void) {
	// Stop Condition
	TWCR = 1<<TWINT | 1<<TWEN | 1<<TWSTO;
}

void i2cAdrTransmit (uint8_t daten) {
	TWDR = daten;
	TWCR = 1<<TWINT | 1<<TWEN;
	i2cDelay ();
	if ((TWSR & 0xF8) != TW_MT_SLA_ACK) {
		i2cError();
	}
}

void i2cDataTransmit (uint8_t daten) {
	TWDR = daten;
	TWCR = 1<<TWINT | 1<<TWEN;
	i2cDelay ();
	if ((TWSR & 0xF8) != TW_MT_DATA_ACK) {
		i2cError();
	}
}

uint8_t i2cReceive (void) {
	i2cDelay ();
	TWCR = 1<<TWINT | 1<<TWEN;
	i2cDelay ();
	uint8_t temp = TWDR;
	return temp;
}

void i2cTxByte (uint8_t adresse, uint8_t pointerwert, uint8_t daten) {
	i2cStart ();
	// adresse + writeEN-Bit
	i2cAdrTransmit (adresse<<1);
	// RAM-Adresse für Zieldaten senden
	i2cDataTransmit (pointerwert);
	// Daten senden
	i2cDataTransmit (daten);
	i2cStop ();
}

void lm75Init (void) {
	i2cTxByte (0b1001000, 1, 0b01111000);
}

void i2cRxLm75Start (uint8_t adresse) {
	i2cStart ();
	i2cAdrTransmit (adresse<<1);
	i2cDataTransmit (0); // selektiere Datenregister
	i2cStop ();
}

uint16_t i2cRxLm75 (uint8_t adresse) {
	// lesen geht folgendermaßen:
	// start
	// adresse + readbit senden
	// Register auslesen (16 bit)
	uint16_t temp = 0;
	i2cStart ();
	i2cAdrTransmit ((adresse<<1) | 1); // Read == 1. Bit gesetzt
	temp  = ((uint16_t)i2cReceive ()<<4); // obere 8 Bit
	temp |= (i2cReceive ()>>4); // untere 4 Bit
	// bei 12bit entspricht 1 LSB 1/16°C
	i2cStop ();
	return temp;
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

void adcStart(void) {
	ADCSRA |= 1<<ADSC;
}
