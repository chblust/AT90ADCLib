#include "adc.h"

#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * Configure AT90 ADC controller for general operation.
 * @param[in] prescale - prescale value selection bits. Only 3 LSBs used.
 *
 */
void initADC( uint8_t prescale )
{
	uint8_t adcsra = ADCSRA;

	// Ensure interrupts are enabled on the AT90
	sei();

	// Set the reference voltage to VCC
	uint8_t admux = ADMUX;

	admux &= ~(3 << REFS0);
	admux |= (1 << REFS0);
	ADMUX = admux;

	adcsra |= (1 << ADEN); // enable all of the ADC
	adcsra |= (1 << ADIE); // enable ADC interrupts
	adcsra |= (prescale & 0x3); // set the prescaler to the first 3 bits of prescale

	ADCSRA = adcsra;
}

/**
 * Put the ADC into "free running mode".
 *
 */
void startADCAutoTrigger()
{
	// Set auto trigger source to free running mode
	ADCSRB &= ~(0x07);

	// Enable Auto triggering
	ADCSRA |= (1 << ADATE);
}

/**
 * Synchronously read a specified channel of the ADC.
 * @param[in] channel - the specified channel, 0-7
 * @return 10 bit adc value
 *
 */
uint16_t adcRead( uint8_t channel )
{
	// Ensure channel value is only 3 bits
	channel &= 0x7;

	uint8_t admux = ADMUX;

	// Clear mux select bits
	admux &= (~0x7);
	// Set the mux select to the desired channel
	admux |= (channel);

	ADMUX = admux;

	// Initiate the conversion
	ADCSRA |= (1 << ADSC);

	// Wait for the conversion to finish
	while( ADCSRA & (1 << ADSC) );

	return ADC;
}


















