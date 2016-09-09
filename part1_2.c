#define F_CPU 16000000UL
#include <avr/interrupt.h>
#define DDRB (*((volatile unsigned char *)0x24))
#define PORTB (*((volatile unsigned char *)0x25))
#define TCCR2 (*((volatile unsigned char *)0xB1))
#define TCNT2 (*((volatile unsigned char *)0xB2))
#define TIMSK (*((volatile unsigned char *)0x70))

// global variable to count the number of overflows
volatile uint8_t tot_overflow;
  
// initialize timer, interrupt and variable
void timer2_init()
{
    // set up timer with prescaler = 256
    TCCR2 |= (1 << 2)|(1 << 1);
  
    // initialize counter
    TCNT2 = 0;
  
    // enable overflow interrupt
    TIMSK |= (1 << 0);
  
    // enable global interrupts
    sei();
  
    // initialize overflow counter variable
    tot_overflow = 0;
}
  
// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER2_OVF_vect)
{
    // keep a track of number of overflows
    tot_overflow++;
}
  
int main(void)
{
    // connect led to pin PC0
    DDRB |= (1 << 0);
  
    // initialize timer
    timer2_init();
  
    // loop forever
    while(1)
    {
        // check if no. of overflows = 12
        if (tot_overflow >= 122)  // NOTE: '>=' is used
        {
            // check if the timer count reaches 53
            if (TCNT2 >= 53)
            {
                PORTB ^= _BV(5);    // toggles the led
                TCNT2 = 0;            // reset counter
                tot_overflow = 0;     // reset overflow counter
            }
        }
    }
}
