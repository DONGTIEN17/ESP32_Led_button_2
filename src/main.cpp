#include <Arduino.h>
#include <OneButton.h>

// OneButton: dùng nút BTN_PIN, hoạt động theo mức BTN_ACT
OneButton button(BTN_PIN, true, BTN_ACT);

bool ledState = false;         // trạng thái LED hiện tại
bool blinkMode = false;        // chế độ nhấp nháy
unsigned long lastBlink = 0;
const int blinkInterval = 200; // 200ms

int activeLed = 1;             // 1 = LED1, 2 = LED2

// ----- Xử lý sự kiện nút -----
void btnClick() {
  // single click -> bật/tắt LED đang điều khiển
  blinkMode = false;
  ledState = !ledState;
  if (activeLed == 1) {
    digitalWrite(LED1_PIN, ledState ? LED1_ACT : !LED1_ACT);
    Serial.println(ledState ? "LED1 ON" : "LED1 OFF");
  } else {
    digitalWrite(LED2_PIN, ledState ? LED2_ACT : !LED2_ACT);
    Serial.println(ledState ? "LED2 ON" : "LED2 OFF");
  }
}

void btnDoubleClick() {
  // double click -> đổi LED điều khiển
  blinkMode = false;
  activeLed = (activeLed == 1) ? 2 : 1;
  Serial.printf("Switched control to LED%d\n", activeLed);
}

void btnLongPressStart() {
  // giữ nút -> bật chế độ blink
  blinkMode = true;
  Serial.printf("Blink mode ON for LED%d\n", activeLed);
}

// ----- Setup -----
void setup() {
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, !LED1_ACT); // tắt LED1
  digitalWrite(LED2_PIN, !LED2_ACT); // tắt LED2

  button.attachClick(btnClick);
  button.attachDoubleClick(btnDoubleClick);
  button.attachLongPressStart(btnLongPressStart);

  Serial.println("System ready.");
}

// ----- Loop -----
void loop() {
  button.tick();

  if (blinkMode) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastBlink >= blinkInterval) {
      lastBlink = currentMillis;
      ledState = !ledState;
      if (activeLed == 1) {
        digitalWrite(LED1_PIN, ledState ? LED1_ACT : !LED1_ACT);
      } else {
        digitalWrite(LED2_PIN, ledState ? LED2_ACT : !LED2_ACT);
      }
    }
  }
}
