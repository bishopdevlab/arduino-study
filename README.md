# arduino-study
Arduino study and DIY

## 피에조 부저 (piezo buzzer)

Beep 또는 LED는 간단하게 동작 확인 등 디버깅에 자주 사용됩니다. 피에조 부저를 이용하여 간단히 beep를 발생시키는 예제입니다.

![피에조 부저](/assets/images/Beep/Beep_피에조부저.jpeg)

![회로도](/assets/images/Beep/Beep_회로도.jpeg)

```cpp
int speakerPin = 12;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  tone(speakerPin, 500, 1000);  // 500 음 높이(주파수), 1000: 지속시간
  delay(2000);
}

```

## 초음파 센서 (HC-SR04)

초음파 센서 중 입문자가 사용하기 쉽고 보편적인 모델로 초음파를 발신/수신하여 물체와의 거리를 측정할 수 있습니다.

전원, 발신, 수신, 접지 4개의 핀으로 구성되어 있어 쉽게 사용할 수 있습니다.

![초음파 센서](/assets/images/Distance_Robot/센서_초음파센서.PNG)

### 기본 활용

#### 회로도

초음파 센서는 다음과 같이 회로를 구성합니다.

* VCC 전원 핀은 5V와 연결
* Trig 핀은 Tx 2번와 연결 (임의의 Tx 핀 가능)
* Echo 핀은 Tx 3번와 연결 (임의의 Tx 핀 가능)
* GND 핀은 GND 접지와 연결

![회로도](/assets/images/Distance_Robot/초음파센서_회로도.PNG)

#### 제작

회로도를 참고하여 센서와 아두이노를 연결합니다.

![제작](/assets/images/Distance_Robot/초음파센서_제작_기본.JPG)

#### 코드

아두이노 스케치에서 아래와 같이 코드를 작성합니다.

![코드](/assets/images/Distance_Robot/초음파센서_코드_기본.PNG)

```cpp

int trigPin = 2; // trigger pin 설정 (초음파 발생)
int echoPin = 3; // echo pin 설정 (초음파 수신)

void setup() {
  Serial.begin(9600);       // 시리얼 속도 설정
  pinMode(echoPin, INPUT);  // echoPin 입력
  pinMode(trigPin, OUTPUT); // trigPin 출력
}

void loop() {
  float duration, distanceMm;

  digitalWrite(trigPin, HIGH);  // 초음파 발신
  delayMicroseconds(10);        // 10us 동안 신호 유지
  digitalWrite(trigPin, LOW);   // 초음파 발신 off

  if (digitalRead(echoPin) == LOW)
  {
    // 초음파 속도: 340m/s
    // 단위 변환: m/s -> mm/us. m -> mm: 1/1000000, s -> us: 1000. 즉 1/1000이 됨
    // 왕복거리로 측정되므로 2로 나눔
    duration = pulseIn(echoPin, HIGH);
    distanceMm = ((float)(340 * duration) / 1000) / 2;

    Serial.print("Distance: ");
    Serial.print((float)distanceMm / 10);
    Serial.println(" cm");
  }
  else
  {
    Serial.println("Echo: High");

    // 초음파 신호가 돌아오지 않을 때 Echo를 LOW로 강제 전환
    pinMode(echoPin, OUTPUT);
    digitalWrite(echoPin, LOW);
    pinMode(echoPin, INPUT);
  }
  delay(500);
}

```

#### 동작

실행한 후 시리얼 모니터로 확인해 보면 거리가 비교적 잘 측정되는 것을 확인할 수 있습니다.

![동작](/assets/images/Distance_Robot/초음파센서_동작_기본.PNG)


### 응용 1 - 부저로 근접 알림

#### 피에조 부저

피에조 부저를 연결하여 10cm 이내로 근접하면 beep 음을 발생시키도록 알리도록 합니다.

![피에조부저](/assets/images/Distance_Robot/센서_피에조부저.jpeg)

#### 회로도

+가 Tx 핀에 연결되고, -가 접지에 연결됩니다.

![회로도](/assets/images/Distance_Robot/초음파센서_회로도_부저.jpeg)

#### 제작

회로도를 참고하여 피에조 부저를 아두이노를 연결합니다.

![제작](/assets/images/Distance_Robot/초음파센서_제작_응용1_부저.jpg)

#### 코드

아두이노 스케치에서 아래와 같이 코드를 작성합니다.

![코드](/assets/images/Distance_Robot/초음파센서_코드_응용1.PNG)

```cpp

int trigPin = 2; // trigger pin 설정 (초음파 발생)
int echoPin = 3; // echo pin 설정 (초음파 수신)

int speakerPin = 12;  // 피에조 부저 pin 설정

void setup() {
  Serial.begin(9600);       // 시리얼 속도 설정
  pinMode(echoPin, INPUT);  // echoPin 입력
  pinMode(trigPin, OUTPUT); // trigPin 출력
}

void loop() {
  float duration, distanceMm;

  digitalWrite(trigPin, HIGH);  // 초음파 발신
  delayMicroseconds(10);        // 10us 동안 신호 유지
  digitalWrite(trigPin, LOW);   // 초음파 발신 off

  if (digitalRead(echoPin) == LOW)
  {
    // 초음파 속도: 340m/s
    // 단위 변환: m/s -> mm/us. m -> mm: 1/1000000, s -> us: 1000. 즉 1/1000이 됨
    // 왕복거리로 측정되므로 2로 나눔
    duration = pulseIn(echoPin, HIGH);
    distanceMm = ((float)(340 * duration) / 1000) / 2;

    Serial.print("Distance: ");
    Serial.print((float)distanceMm / 10);
    Serial.println(" cm");

    // 부저로 근접 알림
    if (distanceMm < 100)
    {
      Serial.println("Sound!!");
      tone(speakerPin, 500, 500);  // 500 음 높이(주파수), 1000: 지속시간
      delay(1000);
    }
  }
  else
  {
    Serial.println("Echo: High");

    // 초음파 신호가 돌아오지 않을 때 Echo를 LOW로 강제 전환
    pinMode(echoPin, OUTPUT);
    digitalWrite(echoPin, LOW);
    pinMode(echoPin, INPUT);
  }
  delay(500);
}

```

#### 동작

실행한 후 시리얼 모니터에서 출력을 확인하고 물건을 10cm 이내로 근접했을 경우 Beep 음이 발생하는 것을 확인할 수 있습니다.

![동작](/assets/images/Distance_Robot/초음파센서_동작_응용1_부저.PNG)


### 응용 2 - LED로 물체의 거리 알리기

#### LED

아두이노에 초록, 노랑, 빨강 LED를 연결하여 물체와의 거리에 따라 LED를 켜도록 합니다.

#### 회로도

다리가 긴 핀이 +이고, 짧은 핀이 -입니다.

+에 Tx를 연결하고, -에는 저항을 연결한 후 GND(접지)에 연결합니다.

![LED 극](/assets/images/Distance_Robot/초음파센서_회로도_LED2.jpeg)

![회로도](/assets/images/Distance_Robot/초음파센서_회로도_LED.PNG)

#### 제작

회로도를 참고하여 3개의 LED를 아두이노에 연결합니다.

![제작](/assets/images/Distance_Robot/초음파센서_제작_응용2_LED.jpg)

#### 코드

아두이노 스케치에서 아래와 같이 코드를 작성합니다.

![코드](/assets/images/Distance_Robot/초음파센서_코드_응용2_1.PNG)

![코드](/assets/images/Distance_Robot/초음파센서_코드_응용2_2.PNG)

```cpp

int trigPin = 2; // trigger pin 설정 (초음파 발생)
int echoPin = 3; // echo pin 설정 (초음파 수신)

int green = 8;          // LED Green pin 설정
int yellow = 9;         // LED Yellow pin 설정
int red = 10;           // LED Red pin 설정

void setup() {
  Serial.begin(9600);       // 시리얼 속도 설정
  pinMode(echoPin, INPUT);  // echoPin 입력
  pinMode(trigPin, OUTPUT); // trigPin 출력

  // LED
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  float duration, distanceMm;

  digitalWrite(trigPin, HIGH);  // 초음파 발신
  delayMicroseconds(10);        // 10us 동안 신호 유지
  digitalWrite(trigPin, LOW);   // 초음파 발신 off

  if (digitalRead(echoPin) == LOW)
  {
    // 초음파 속도: 340m/s
    // 단위 변환: m/s -> mm/us. m -> mm: 1/1000000, s -> us: 1000. 즉 1/1000이 됨
    // 왕복거리로 측정되므로 2로 나눔
    duration = pulseIn(echoPin, HIGH);
    distanceMm = ((float)(340 * duration) / 1000) / 2;

    Serial.print("Distance: ");
    Serial.print((float)distanceMm / 10);
    Serial.println(" cm");

    // LED 초기화 (off)
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    delay(50);

    // LED로 근접 알림
    if (distanceMm < 100)
    {
      Serial.println("RED!!");
      digitalWrite(red, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
      delay(500);
    }
    else if (distanceMm >= 100 && distanceMm < 200)
    {
      Serial.println("YELLOW!!");
      digitalWrite(red, LOW);
      digitalWrite(yellow, HIGH);
      digitalWrite(green, LOW);
      delay(500);
    }
    else
    {
      Serial.println("GREEN!!");
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
      delay(500);
    }
  }
  else
  {
    Serial.println("Echo: High");

    // 초음파 신호가 돌아오지 않을 때 Echo를 LOW로 강제 전환
    pinMode(echoPin, OUTPUT);
    digitalWrite(echoPin, LOW);
    pinMode(echoPin, INPUT);
  }
  delay(500);
}

```

#### 동작

실행한 후 시리얼 모니터에서 출력을 확인하고 물건을 10cm 이내, 20cm 이내, 20cm 밖으로 움직였을 때 LED등이 잘 켜지지 확인할 수 있습니다.

![동작](/assets/images/Distance_Robot/초음파센서_동작_응용2_LED.PNG)

실제 제작 후 동작 시 초록 LED가 비정상적으로 동작되는 문제가 있었습니다. 추후 어떤 문제가 있는지 확인할 예정입니다.
