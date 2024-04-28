// 初期設定
const int ledPin_Red = 15;
const int ledPin_Yellow = 14;
const int buttonPin = 12;

bool ledState = false; // LED の状態を保持する変数
bool buttonState = false;
bool lastButtonState = false;

int buttonPressCount = 0;
bool isBlinking = false;

void led_on_red(void)
{
  ledState = true;
  digitalWrite(ledPin_Red, HIGH);
  digitalWrite(ledPin_Yellow, LOW);
}
void led_on_yellow(void)
{
  ledState = true;
  digitalWrite(ledPin_Yellow, HIGH);
  digitalWrite(ledPin_Red, LOW);
}

void led_off(void)
{
  ledState = false;
  digitalWrite(ledPin_Red, LOW);
  digitalWrite(ledPin_Yellow, LOW);
}

void led_blink(void)
{
while(1){

//ボタンの状態を取得
    buttonState = digitalRead(buttonPin);
    if(buttonState == HIGH){
      //ボタンが押されたら点滅中断して消灯
      led_off();
      isBlinking = false;
      return;
    }
    led_on_red();
    delay(500);
    led_on_yellow();
    delay(500);
    led_off();
  }
  return;

  #if 0
  for(int i = 0; i < 10; i++){

      //ボタンの状態を取得
    buttonState = digitalRead(buttonPin);
    if(buttonState == HIGH){
      //ボタンが押されたら点滅中断して消灯
      led_off();
      isBlinking = false;
      return;
    }
    digitalWrite(ledPin_Red, HIGH);
    delay(500);
    digitalWrite(ledPin_Red, LOW);
    delay(500);
  }
  return;
  #endif

}

void setup() {
  pinMode(ledPin_Red, OUTPUT);
  pinMode(ledPin_Yellow, OUTPUT);
  pinMode(buttonPin, INPUT); // 内部プルアップ抵抗を使用
  
  // 最初に LED を消灯する
  led_off();
}

void loop() {
  // ボタンの状態を読み取る
  buttonState = digitalRead(buttonPin);

  if(buttonState != lastButtonState){
    if(buttonState == LOW){
    buttonPressCount++;
    if (buttonPressCount % 4 == 1) {
        // 1回目の押下でLEDを点灯
        led_on_red();
      } else if (buttonPressCount % 4 == 2) {
        // 2回目の押下でLEDを消灯
        led_on_yellow();
      } else if (buttonPressCount % 4 == 3) {
        // 3回目の押下でLEDを点滅
        led_blink();
         isBlinking = true; // 点滅中フラグを設定
      } else if (buttonPressCount % 4 == 0) {
        // 4回目の押下でLEDを消灯
        led_off();
        buttonPressCount = 0; // カウントをリセット
        isBlinking = false;
      }
    }

   // ボタンの状態を更新
    lastButtonState = buttonState;
  }
}
