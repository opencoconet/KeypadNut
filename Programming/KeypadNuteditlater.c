// code for 4x3 membrane keypad
// ROW1-PA0, ROW2-PA1, ROW3-PA2,ROW4-PA3, COL1-PA4(SCK), COL2-PA5(MISO), COL3-PA6(MOSI)
//For Keypad RX - PB2,TX - PA7


#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set

// For Serial Communicaiton
#define bit_delay_time 8.5 // bit delay for 115200 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay
#define char_delay() _delay_ms(10) // char delay
#define serial_port_out PORTA
#define serial_port_in PORTB
#define serial_direction_out DDRA
#define serial_direction_in DDRB
#define serial_pins_out PINA
#define serial_pins_in PINB
#define serial_pin_out (1 << PA7)
#define serial_pin_in (1 << PB2)
#define max_buffer 25

// For LED
#define led (1 << PA6)
#define led_port PORTA
#define led_direction DDRA

// For Keypad
#define row1 (1 << PA0)
#define row2 (1 << PA1)
#define row3 (1 << PA2)
#define row4 (1 << PA3)
#define col1 (1 << PA4)
#define col2 (1 << PA5)
#define col3 (1 << PA6)
#define keypad_port PORTA
#define keypad_direction DDRA
#define keypad_input PINA

#define KEYPAD A  //KEYPAD IS ATTACHED ON PORTA
81
82    //Don't Touch the lines below
83    //*******************************
84    #define KEYPAD_PORT PORT(KEYPAD)
85    #define KEYPAD_DDR   DDR(KEYPAD)
86    #define KEYPAD_PIN   PIN(KEYPAD)
87    //*******************************


uint8_t GetKeyPressed()
114   {
115      uint8_t r,c;
116
117      KEYPAD_PORT|= 0X0F;
118
119      for(c=0;c<3;c++)
120      {
121         KEYPAD_DDR&=~(0X7F);
122
123         KEYPAD_DDR|=(0X40>>c);
124         for(r=0;r<4;r++)
125         {
126            if(!(KEYPAD_PIN & (0X08>>r)))
127            {
128               return (r*3+c);
129            }
130         }
131      }
132
133      return 0XFF;//Indicate No key pressed
134   }


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


int main(void)
{



int keypressed=0;//integer for storing matrix value

//Set raw as output pin
output(DDRA,(1 << PA0));
output(DDRA,(1 << PA1));
output(DDRA,(1 << PA2));
output(DDRA,(1 << PA3));
//Set col as input pin
input(DDRA,(1 << PA4));
input(DDRA,(1 << PA5));
input(DDRA,(1 << PA6));
//Set PA7 as serial outupt pin
output(DDRA,(1 << PA7));

_delay_ms(1);

//Powering the Row
set(PORTA,(1 << PA0));
set(PORTA,(1 << PA1));
set(PORTA,(1 << PA2));
set(PORTA,(1 << PA3));
clear(PORTA,(1 << PA4));
clear(PORTA,(1 << PA5));
clear(PORTA,(1 << PA6));

_delay_ms(1);


/*
while (1) {
set(PORTA,(1 << PA7));
_delay_ms(10);
clear(PORTA,(1 << PA7));
_delay_ms(10);
}
*/


while(1)
{

    key=GetKeyPressed(); //Get the keycode of pressed key

    if ((pin_test(PINA,(1 << PA4))) || (pin_test(PINA,(1 << PA5))))//in any of column pins goes high execute the loop
    {

        set(PORTA,(1 << PA7));
        _delay_ms(10);
        clear(PORTA,(1 << PA7));
        _delay_ms(10);

        _delay_ms(5);
        keypressed = PINA;//taking the column value into integer

        if ((keypressed==0b11111000)||(keypressed==0b11111001)) {
        }

        else if ((keypressed==0b11110100)||(keypressed==0b11110101))
        {

        }
                       DDRA ^=0b11110000;//making rows as inputs and columns as ouput (Rx flag)
                                                _delay_ms(1);
                                                PORTA ^= 0b00001111;//powering columns
                                                _delay_ms(1);

                                                keypressed |=PINA; //taking row value and OR ing it to column value

                                                if (keypressed==0b00010001)
                                                {



                                                }
                                                if (keypressed==0b00010010)
                                                {

                                                }
                                                if (keypressed==0b00010100)
                                                {

                                                }
                                                if (keypressed==0b00011000)
                                                {

                                                }

                                                if (keypressed==0b00100001)
                                                {

                                                }
                                                if (keypressed==0b00100010)
                                                {

                                                }
                                                if (keypressed==0b00100100)
                                                {

                                                }
                                                if (keypressed==0b00101000)
                                                {




                                                if (keypressed==0b01000001)
                                                {

                                                }
                                                if (keypressed==0b01000010)
                                                {

                                                }
                                                if (keypressed==0b01000100)
                                                {

                                                }
                                                if (keypressed==0b01001000)
                                                {

                                                }



                                                if (keypressed==0b10000001)
                                                {

                                                }
                                                if (keypressed==0b10000010)
                                                {

                                                }
                                                if (keypressed==0b10000100)
                                                {

                                                }
                                                if (keypressed==0b10001000)
                                                {

                                                keypressed=0;//after showing integer erasing the row column memory
                                                DDRA ^=0b11111111;//shifting input and power port
                                                _delay_ms(1);
                                                PORTA ^= 0b11111111;//powering row pins of keypad
                                                _delay_ms(220);

                                }

                }

                }





}

}




