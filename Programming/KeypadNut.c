// ROW - PA0, PA1, PA2,PA3, PA4 and COL - PA5, PA6 and TX - PA7 and RX - PB2

#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set

// For Serial Communication
#define bit_delay_time 8.5 // bit delay for 115200 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay
#define char_delay() _delay_ms(10) // char delay


/*******************************************

Function return keycode map

    [0x0B] [0x0A] [0x09]
    [0x08] [0x07] [0x06]
    [0x05] [0x04] [0x03]
    [0x02] [0x01] [0x00]

255 (hex 0xFF) if NO keypressed.
*******************************************/


uint8_t GetKeyPressed()
{
    uint8_t r,c;

    PORTA|= 0X0F;

    for(c=0;c<3;c++)
    {
        DDRA&=~(0X7F);

        DDRA|=(0X40>>c);

        for(r=0;r<4;r++)
        {
            if(!(PINA & (0X08>>r)))
            {
                return (r*3+c);
            }
         }
      }

      return 0XFF;//Indicate No key pressed
}


void put_char(volatile unsigned char *port, unsigned char pin, char txchar) {
   //
   // send character in txchar on port pin
   //    assumes line driver (inverts bits)
   //
   // start bit
   //
   clear(*port,pin);
   bit_delay();
   //
   // unrolled loop to write data bits
   //
   if bit_test(txchar,0)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,1)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,2)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,3)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,4)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,5)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,6)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,7)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   //
   // stop bit
   //
   set(*port,pin);
   bit_delay();
   //
   // char delay
   //
   bit_delay();

}


void flash() {
    output(DDRA,(1 << PA6));
    clear(PORTA, (1 << PA6));
    _delay_ms(50);
    set(PORTA, (1 << PA6));
    _delay_ms(50);
    clear(PORTA, (1 << PA6));
}


int main()
{

    static char chr = 'P';
    uint8_t key;

    // set clock divider to /1
    CLKPR = (1 << CLKPCE);
    CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);

    // Set PA7 as serial port output pin
    output(DDRA,(1 << PA7));

    while(1)
    {
    key=GetKeyPressed(); //Get the keycode of pressed key

        if (key == 0X0B)
        {
            put_char(&PORTA, (1 << PA7),0x31);
            flash();
        }
        else if (key == 0X0A)
        {
            put_char(&PORTA, (1 << PA7),0x32);
        }
        else if (key == 0X09)
        {
            put_char(&PORTA, (1 << PA7),0x33);
        }
        else if (key == 0X08)
        {
            put_char(&PORTA, (1 << PA7),0x34);
        }
        else if (key == 0X07)
        {
            put_char(&PORTA, (1 << PA7),0x35);
        }
        else if (key == 0X06)
        {
            put_char(&PORTA, (1 << PA7),0x36);
        }
        else if (key == 0X05)
        {
            put_char(&PORTA, (1 << PA7),0x37);
        }
        else if (key == 0X04)
        {
            put_char(&PORTA, (1 << PA7),0x38);
        }
        else if (key == 0X03)
        {
            put_char(&PORTA, (1 << PA7),0x39);
        }
        else if (key == 0X02)
        {
            put_char(&PORTA, (1 << PA7),0x2A);
        }
        else if (key == 0X01)
        {
            put_char(&PORTA, (1 << PA7),0x30);
        }
        else if (key == 0X00)
        {
            put_char(&PORTA, (1 << PA7),0x23);
        }
      }

}

