// ボタンピンとLEDピンの定義
const int buttonPin = 12;
const int ledPin_red = 13;
const int ledPin_yellow = 14;
const int ledPin_green = 15;

// ボタンの状態を追跡する変数
int buttonState = 0;
int lastButtonState = LOW;

// LEDの状態を追跡する変数
int ledState = LOW;

// デバウンス処理の時間を追跡する変数
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// ボタンの押下回数を追跡する変数
int buttonPressCount = 0;

void setup() {
  pinMode(ledPin_red, OUTPUT);
  pinMode(ledPin_yellow, OUTPUT);
  pinMode(ledPin_green, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(115200); // シリアル通信開始
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        buttonPressCount++;

        if (buttonPressCount % 4 == 1) {
          // 1回目の押下で赤を点灯
          digitalWrite(ledPin_red, HIGH);
          digitalWrite(ledPin_yellow, LOW);
          digitalWrite(ledPin_green, LOW);
        } else if (buttonPressCount % 4 == 2) {
          // 2回目の押下で黄色を点灯
          digitalWrite(ledPin_red, LOW);
          digitalWrite(ledPin_yellow, HIGH);
          digitalWrite(ledPin_green, LOW);
        } else if (buttonPressCount % 4 == 3) {
          // 3回目の押下で緑を点灯
          digitalWrite(ledPin_red, LOW);
          digitalWrite(ledPin_yellow, LOW);
          digitalWrite(ledPin_green, HIGH);
        } else if (buttonPressCount % 4 == 0) {
          // 4回目の押下で赤、黄、緑が順番に点灯
          //5回目押すまで繰り返したい
          digitalWrite(ledPin_green, LOW);
          delay(500);
          digitalWrite(ledPin_red, HIGH);
          delay(500);
          digitalWrite(ledPin_red, LOW);
          delay(500);
          digitalWrite(ledPin_yellow, HIGH);
          delay(500);
          digitalWrite(ledPin_yellow, LOW);
          delay(500);
          digitalWrite(ledPin_green, HIGH);
          delay(500);
          digitalWrite(ledPin_green, LOW);
        }
      }
    }
  }

  lastButtonState = reading;
}
