// ボタンピンとLEDピンの定義
const int buttonPin = 12;
const int ledPin_red = 13;
const int ledPin_yellow = 14;
const int ledPin_green = 15;

// ボタンの状態を追跡する変数
volatile int buttonState = LOW;
volatile int lastButtonState = LOW;

// LEDの状態を追跡する変数
volatile int ledState = LOW;

// ボタンの押下回数を追跡する変数
volatile int buttonPressCount = 0;

// 前回の割り込み時刻を追跡する変数
volatile unsigned long lastInterruptTime = 0;

void setup() {
  pinMode(ledPin_red, OUTPUT);
  pinMode(ledPin_yellow, OUTPUT);
  pinMode(ledPin_green, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // プルアップ抵抗を使用してボタンを接続
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, FALLING); // ボタン割り込みを設定
  Serial.begin(115200); // シリアル通信開始
}

void loop() {
  // ボタンの状態が変化したときだけ処理を実行
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState; // ボタンの前回の状態を更新
    // ボタンが押された場合
    if (buttonState == LOW) {
      buttonPressCount++; // ボタンの押下回数をインクリメント
      // 偶数回の場合、LEDを消灯する
      if (buttonPressCount % 2 == 0) {
        fadeOut(); // LEDを消灯する関数を呼び出す
      } else {
        // 奇数回の場合、LEDを点灯する
        fadeIn();
      }
    }
  }
}

// ボタンが押されたときの割り込み関数
void buttonPressed() {
  // ボタンの連続押下を防ぐために一定時間の間隔でしか割り込みを処理しない
  if (millis() - lastInterruptTime > 10) {
    buttonState = digitalRead(buttonPin); // ボタンの状態を更新
    lastInterruptTime = millis(); // 前回の割り込み時刻を更新
  }
}

// LEDを徐々に消灯する関数
void fadeOut() {
  for (int value = 255; value >= 0; value--) {
    analogWrite(ledPin_red, value);
    analogWrite(ledPin_yellow, value);
    analogWrite(ledPin_green, value);
    delay(10); // 短い時間待機することで徐々に明るさを下げる
  }
}

// LEDを徐々に点灯する関数
void fadeIn() {
  for (int value = 0; value <= 255; value++) {
    analogWrite(ledPin_red, value);
    analogWrite(ledPin_yellow, value);
    analogWrite(ledPin_green, value);
    delay(10); // 短い時間待機することで徐々に明るさを上げる
  }
}
