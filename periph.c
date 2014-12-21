// Initialisierungsfunktionen für die verschiedenen
// Peripheriekomponenten wie SPI, I2C, SB9, ...



void spiInit (void) {
	DDRB |= 1<<PB2 | 1<<PB3 | 1<<PB5;
	SPCR = 1<<SPE | 1<<MSTR; // SPI Master Mode, clock vollgas
	SPSR = 0;
}

void i2cInit (void) {
	// verwende natürlich auch hier VOLLGAS (400kHz Clockspeed)
	TWBR = 3;
	TWCR |= 1<<TWEA | 1<<TWEN; // automatisch ACK
	TWSR |= 1<<TWPS0; // prescaler = 4
}

void i2cStart (void) {
	// Start Condition
	sbi (TWCR, TWSTA);
	sbi (TWCR, TWINT); // clear Interrupt flag
	while (TWCR & 1<<TWINT); // Warte, dass START gesendet wurde
	// eigendlich: prüfen ob TWSR = 0x08 ist.
}

inline void i2cRestart (void) {
	i2cStart ();
}

void i2cStop (void) {
	// Stop Condition
	sbi(TWCR, TWSTO);
	sbi(TWCR, TWINT);
}

void i2cTransmit (uint8_t daten) {
	TWDR = daten;
	sbi (TWCR, TWINT);
	while (TWCR & 1<<TWINT);
}

uint8_t i2cReceive (void) {
	while (TWCR & 1<<TWINT);
	uint8_t temp = TWDR;
	return temp;
}

void i2cTxByte (uint8_t adresse, uint8_t pointerwert, uint8_t daten) {
	// TODO: Statusbits überprüfen und Errorbehandlung schreiben
	i2cStart ();
	// adresse + writeEN-Bit
	i2cTransmit (adresse | 1<<7);
	// RAM-Adresse für Zieldaten senden
	i2cTransmit (pointerwert);
	// Daten senden
	i2cTransmit (daten);
	i2cStop ();
}

// uint8_t i2cRxByte (uint8_t adresse, uint8_t pointerwert) {
// 	// Lese ein bestimmtes Byte aus dem Target
// 	i2cStart ();
// 	// Lesen: daher kein Schreib-Bit senden
// 	i2cTransmit (adresse);
// 	i2cTransmit (pointerwert);
// 	
// }

void lm75Init (void) {
	i2cTxByte (0b1001000, 0x01, 0b01100000);
}

// hier 0b1001000 dauerhaft
uint16_t i2cRxLm75 (uint8_t adresse) {
	// lesen geht folgendermaßen:
	// Pointer setzen (write mode)
	// restart senden
	// Register auslesen
	uint16_t temp = 0;
	i2cStart ();
	i2cTransmit (adresse | 1<<7);
	i2cTransmit (0); // selektiere Datenregister
	i2cStart (); // i2c restart
	i2cTransmit (adresse);
	temp  = i2cReceive () << 4; 
	temp |= i2cReceive () >> 4;
	// bei 12bit entspricht 1 LSB 1/16°C
	return temp;
}