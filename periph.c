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
	TWSR = 1<<TWPS0; // prescaler = 4
}

uint8_t i2cError (void) {
	return TWSR;
}

void i2cDelay (void) {
	while (!(TWCR & (1<<TWINT))); // Warte, dass START gesendet wurde
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
// 	i2cDelay ();
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
	uint8_t temp = TWDR;
	return temp;
}

void i2cTxByte (uint8_t adresse, uint8_t pointerwert, uint8_t daten) {
	// TODO: Statusbits überprüfen und Errorbehandlung schreiben
	i2cStart ();
	// adresse + writeEN-Bit
	i2cAdrTransmit ((adresse<<1) + 1);
	// RAM-Adresse für Zieldaten senden
	i2cDataTransmit (pointerwert);
	// Daten senden
	i2cDataTransmit (daten);
	i2cStop ();
}

void lm75Init (void) {
	i2cTxByte (0b01001000, 1, 0b01100000);
}

void i2cRxLm75Start (uint8_t adresse) {
	i2cStart ();
	i2cAdrTransmit ((adresse<<1) + 1);
	i2cDataTransmit (0); // selektiere Datenregister
	i2cStop ();
}

// hier 0b1001000 dauerhaft
uint16_t i2cRxLm75 (uint8_t adresse) {
	// lesen geht folgendermaßen:
	// Pointer setzen (write mode)
	// restart senden
	// Register auslesen
	uint16_t temp = 0;
	i2cStart ();
	i2cAdrTransmit (adresse<<1);
	temp  = ((uint16_t)i2cReceive ()<<4); // obere 8 Bit
	temp |= (i2cReceive ()>>4); // untere 4 Bit
	// bei 12bit entspricht 1 LSB 1/16°C
	i2cStop ();
	return temp;
}
