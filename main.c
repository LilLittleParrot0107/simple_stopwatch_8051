#include <mcs51/8051.h>
#define SPEAKER_PORT P1_5

#define DELAY_COUNT_DISPLAY 200
#define DELAY_COUNT_SPEED_UP 200
#define DELAY_COUNT_SPEED_DOWN 300
#define DELAY_COUNT_COUNTDOWN 300
#define DELAY_COUNT_FINAL_DISPLAY 1000

void delay(int time)
{
    while(time--);
}

void init_keypad();
unsigned char read_keypad();
int process_key(unsigned char);
void displaySecond(int, int);
void countDown(int);

int speed = 1;
int state = 1;
int currentTime = 0;

void main() {
    init_keypad();
    int res = 0;
    int k;
    currentTime = 0;
    displaySecond(currentTime, DELAY_COUNT_DISPLAY);
    displaySecond(0, 1);


    while(1) {
        unsigned char key = read_keypad();

        
        if(key != 0xFF) { 
            k = process_key(key);


            if (k == 3) {
                speed = speed + 1;
                if (speed > 9) {
                    speed = 9;
                }
                res = speed;
                displaySecond(res, DELAY_COUNT_DISPLAY);
                displaySecond(0, 1);
            }

            else if (k == 7) {
                speed = speed - 1;
                if (speed < 1) {
                    speed = 1;
                }
                res = speed;
                displaySecond(res, DELAY_COUNT_SPEED_DOWN);
                displaySecond(0, 1);
            }
            else if(k == 1) {
                currentTime += 10;
                currentTime = (currentTime + 100) % 100;
                displaySecond(currentTime, DELAY_COUNT_DISPLAY);
                displaySecond(0, 1);
            }

            else if (k == 2) {
                currentTime += 1;
                currentTime = (currentTime + 100) % 100;
                displaySecond(currentTime, DELAY_COUNT_DISPLAY);
                displaySecond(0, 1);
            }

            else if (k == 5) {
                currentTime -= 10;
                currentTime = (currentTime + 100) % 100;
                displaySecond(currentTime, DELAY_COUNT_DISPLAY);
                displaySecond(0, 1);
            }

            else if (k == 6) {
                currentTime -= 1;
                currentTime = (currentTime + 100) % 100;
                displaySecond(currentTime, DELAY_COUNT_DISPLAY);
                displaySecond(0, 1);
            }

            else if (k == 4) {
                countDown(currentTime);
            }


        }
    }
}

void init_keypad() {
    P1 = 0xF0; 
}


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
    int number = key_map[key];
    return number;
}
void displaySecond(int number, int delayCount) {
    unsigned char patterns[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    // Hiển thị chữ số hàng chục
    for (int i = 0; i < 100; i++) {
        P0 = patterns[number / 10];

        // Hiển thị chữ số đơn vị
        if (number >= 0 && number < 10) {
            P0 = patterns[number / 10];
            P2 = (P0 >> 3);
            delay(delayCount);
        }
        else if (number >= 10 && number < 20) {
            P2 = (P0 >> 0);
            delay(delayCount);
        }
        else if (number >= 70 && number < 80) {
            P2 = (P0 >> 0);
            delay(delayCount);
        }
        else {
            P2 = (P0 >> 4);
            delay(delayCount);
        }
        P0 = patterns[number % 10];
        P2 = (P0 >> 4) & 0x01;
        delay(delayCount);
    }
}
void countDown(int number) {
    int st = 1;
    for (int i = number; i >= 0; i--) {
        currentTime = i;
        SPEAKER_PORT = 0x00;
        displaySecond(currentTime, DELAY_COUNT_COUNTDOWN/speed);
        SPEAKER_PORT = 0xFF;
        if (read_keypad() != 0xFF)
        {st = 0;break;}
    }
    for (int i = 0; i<=100; i++){
        if (st==0) break;
        SPEAKER_PORT = 0x00;
        displaySecond(0, 20);
        SPEAKER_PORT = 0xFF;
    }
    displaySecond(currentTime, DELAY_COUNT_FINAL_DISPLAY);
}
