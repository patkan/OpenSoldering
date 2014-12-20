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
	TWCR = 1<<TWEA | 1<<TWEN; // automatisch ACK
	TWSR |= 1<<TWPS0; // prescaler = 4
}

void i2cTxByte (uint8_t adresse, uint8_t pointerwert, uint8_t daten) {
	// TODO: Statusbits überprüfen und Errorbehandlung schreiben
	// Start Condition
	sbi (TWCR, TWSTA);
	sbi (TWCR, TWINT); // clear Interrupt flag
	while (TWCR & 1<<TWINT); // Warte, dass START gesendet wurde
	// eigendlich: prüfen ob TWSR = 0x08 ist.
	
	TWDR = adresse | 1<<7; // adresse + writeEN-Bit
	sbi (TWCR, TWINT);
	while (TWCR & 1<<TWINT);
	
	// RAM-Adresse für Zieldaten senden
	TWDR = pointerwert;
	sbi (TWCR, TWINT);
	while (TWCR & 1<<TWINT);
	
	// Daten senden
	TWDR = daten;
	sbi (TWCR, TWINT);
	while (TWCR & 1<<TWINT);
	
	// Stop Condition
	sbi(TWCR, TWSTO);
	sbi(TWCR, TWINT);
}
