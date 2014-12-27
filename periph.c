// Initialisierungsfunktionen für die verschiedenen
// Peripheriekomponenten wie SPI, I2C, ADC, SB9, ...


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
	// Der ADC läuft mit 16e6 / 128 = 125kHz
	// bei 13 Zyklen pro Wandlung sind das 9,615ksps 
	ADMUX = 0; // Referenz auf externe Referenz
	ADCSRA = 1<<ADEN | 1<<ADSC | 1<<ADIE | 5<<ADPS0; // ADC an, Interrupt an, Prescaler=128
}

void timerInit(void) {
	// Timer/Counter0 kann nur Overflow-Interrupt. daher Prescaler auf 256
	// heißt: alle 4,08ms kommt ein Interrupt rein.
	TCCR0 = 1<<CS02; // Prescaler = 256
	TIMSK |= 1<<TOIE0; // Overflow Interrupt aktiv
	
	// Timer/Counter1 im PhaseCorrectPWM Modus verwenden. (Heizung an OC1A)
	TCCR1A = 1<<COM1A1 | 1<<WGM11 | 1<<WGM10; // PhaseCorrectPWM 10 Bit
	TCCR1B = 1<<CS11 | 1<<CS10; // Prescaler = 64
	OCR1A  = 0; // Lötkolben erst mal aus.
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

void adcStart(void) {
	ADCSRA |= 1<<ADSC;
}
