// Ejemplo de led parpadeante PB5 Arduino Nano atmega 328p
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB5  // El pin PB5 corresponde al pin digital 13 en el Arduino Nano

void setup() {
	// Configurar el pin del LED como salida
	DDRB |= (1 << LED_PIN);
}

void loop() {
	// Encender el LED
	PORTB |= (1 << LED_PIN);
	_delay_ms(500);
	// Apagar el LED
	PORTB &= ~(1 << LED_PIN);
	_delay_ms(500);
}

int main(void) {
	setup();
	while (1) {
		loop();
	}
	return 0;
}
