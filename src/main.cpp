#include <Arduino.h>
#include "LED.h"
#include <OneButton.h>

// Tạo đối tượng LED
LED led1(LED1_PIN, LED1_ACT);
LED led2(LED2_PIN, LED2_ACT);

// Biến theo dõi LED nào đang điều khiển
int currentLed = 1;

// Tạo đối tượng OneButton
OneButton button(BTN_PIN, !BTN_ACT);

// Prototype
void btnClick();
void btnDoubleClick();
void btnLongPress();

void setup() {
    led1.off();
    led2.off();

    // Gán callback cho button
    button.attachClick(btnClick);
    button.attachDoubleClick(btnDoubleClick);
    button.attachLongPressStart(btnLongPress);
}

void loop() {
    led1.loop();
    led2.loop();
    button.tick();
}

// Single click → Bật/tắt LED hiện tại
void btnClick() {
    if (currentLed == 1) {
        led1.flip();
    } else {
        led2.flip();
    }
}

// Double click → Chuyển chế độ điều khiển giữa LED1 và LED2
void btnDoubleClick() {
    currentLed = (currentLed == 1) ? 2 : 1;
}

// Long press → LED hiện tại nhấp nháy 200ms
void btnLongPress() {
    if (currentLed == 1) {
        led1.blink(200);
    } else {
        led2.blink(200);
    }
}
