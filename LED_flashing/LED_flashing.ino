//ボタンピンとLEDピンの定義
const int buttonPin = 14;
const int ledPin = 15;

//ボタンの状態を追跡する定義
int buttonState = 0;
//直前のボタンの状態を追跡する定義
int lastButtonState = LOW;
//LEDの状態を追跡する定義
int ledState = LOW;
//最後のデバウンス処理の時間を追跡する定義
unsigned long lastDebounceTime = 0;
//デバウンス処理の遅延時間
unsigned long debounceDelay = 50;
//ボタンの押下回数を追跡する定義
int buttonPressCount = 0;
//LEDが点滅中かどうかを追跡する定義
bool isFlashing = false;
//点滅周期を定義する定義
const unsigned long flashInterval = 500; //ミリ秒

// the setup function runs once when you press reset or power the board
void setup(){
  //initialize digital pin as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(115200); //シリアル通信開始
}

//the loop function runs over and again forever
void loop (){
  int reading = digitalRead(buttonPin); //ボタンの状態を読み取る
  //ボタンの状態が変化した場合、最後のデバウンス時間を更新
  if(reading != lastButtonState){
    lastDebounceTime = millis();
  }

  //デバウンス時間が経過したら
  if((millis() - lastDebounceTime) > debounceDelay){
    //ボタンの状態が変化している場合
    if(reading != buttonState){
      //ボタンの状態を更新
      buttonState = reading;

      //ボタンが押された場合
      if(buttonState == HIGH){
        //ボタン押下回数を増加
        buttonPressCount++;

        //押下回数が4で割った余りによってLEDの状態を切り替える
        if(buttonPressCount % 4 == 1){
          ledState = HIGH; // 点灯
        } else if(buttonPressCount % 4 == 3){
          isFlashing = true; // 点滅開始
          lastDebounceTime = millis(); //点滅開始時の時間を記録
        } else {
          ledState = LOW; // 消灯
          isFlashing = false; // 点滅フラグをリセット
        }
      }
    }
  }

  // 点滅中の場合
  if(isFlashing){
    if((millis() - lastDebounceTime) >= flashInterval){
      ledState = !ledState; // LEDの状態を反転
      lastDebounceTime = millis(); // 最後の点滅の時間を更新
    }
  }

  //LEDの状態を更新
  digitalWrite(ledPin, ledState);
  //ボタンの前の状態
  lastButtonState = reading;
}
