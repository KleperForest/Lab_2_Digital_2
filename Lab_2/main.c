#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB5
#define DELAY_TIME 1000 // 1000 ms = 1 segundo

void setup() {
    // Configura el pin LED_PIN como salida
    DDRB |= (1 << LED_PIN);
}

void loop() {
    // Enciende el LED
    PORTB |= (1 << LED_PIN);
    _delay_ms(DELAY_TIME);
    
    // Apaga el LED
    PORTB &= ~(1 << LED_PIN);
    _delay_ms(DELAY_TIME);
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
    
    return 0;
}
