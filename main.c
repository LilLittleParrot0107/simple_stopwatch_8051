#include <mcs51/8051.h>
const int dupCount = 10;
// Chân loa
#define SPEAKER_PORT P1_5

// Sleep function
void delay(int time)
{
    while(time--);
}


void init_keypad();
unsigned char read_keypad();
int process_key(unsigned char);
void displaySecond(int, int);
void countDown(int);



void main() {
    init_keypad(); 
    int res = 0;
    int k;
    while(1) {


        unsigned char key = read_keypad(); 
        if(key != 0xFF) { 
            k = process_key(key);
            if(k ==1) {res += 10;
            res = (res+100)%100;
            displaySecond(res,200);
            displaySecond(0,10);}

            if (k == 2) {res+= 1;
            res = (res+100)%100;
            displaySecond(res,200);
            displaySecond(0,10);
            }

            if (k == 5) {res -= 10;
            res = (res+100)%100;
            displaySecond(res,200);
            displaySecond(0,10);
            }

            if (k == 6) {res -= 1;
            res = (res+100)%100;
            displaySecond(res,200);
            displaySecond(0,10);
            }

            if (k ==3)
                {countDown(res);
                    res = 0;}
                    }

           
        }
    }


void init_keypad() {
    P1 = 0xF0; 
}

// Function to read the keypad state
unsigned char read_keypad() {
    unsigned char row, col, key = 0xFF;
    for(row = 0; row < 4; row++) {
        P1 = (P1 | 0x0F) & ~(1 << row); 
        for(col = 0; col < 4; col++) {
            if(!(P1 & (0x10 << col))) { 
                key = (row * 4) + col; 
                break;
            }
        }
        if(key != 0xFF) break; 
    }
    return key; 
}


int process_key(unsigned char key) {
    int key_map[16] = {16,12,8,4,15,11,7,3,14,10,6,2,13,9,5,1};
    int number = key_map[key] ; 
    return number;
}


void displaySecond(int number, int delayCount)
{
    unsigned char patterns[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    // Display units digit
    for (int i = 0; i < 100; i++){
        P0 = patterns[number / 10];
        // Display tens digit
        if (number >= 0 && number < 10)
        {
            P0 = patterns[number / 10];
            P2 = (P0 >> 3);
            delay(delayCount);
        }
        else if (number >= 10 && number < 20)
        {
            P2 = (P0 >> 0);
            delay(delayCount);
        }
        else if (number >= 70 && number < 80)
        {
            P2 = (P0 >> 0);
            delay(delayCount);
        }
        else
        {
            P2 = (P0 >> 4);
            delay(delayCount);
        }
        P0 = patterns[number % 10];
        P2 = (P0 >> 4) & 0x01;
        delay(delayCount);
    }
}

void countDown(int number)
{
    for (int i=number;i>=1;i--)
    {
        SPEAKER_PORT = 0x00;
        displaySecond(i,300);
        SPEAKER_PORT = 0xFF;
    }
    SPEAKER_PORT = 0x00;
    displaySecond(0,300);


}


