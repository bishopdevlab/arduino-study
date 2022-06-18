# 아두이노 DIY (arduino-study)
Arduino study and DIY

아두이노를 이용하여 이것 저것 만들어 본 것들을 기록합니다. 주로 아이와 함께 즐기기 위한 프로젝트들입니다.

---

## 목차

1. [피에조 부저 (piezo buzzer)](#피에조-부저-(piezo-buzzer))
2. [초음파 센서 (HC-SR04)](#초음파-센서-(HC-SR04))
3. [LED를 이용한 신호등](#LED를-이용한-신호등)
4. [조도센서와 RGB LED 제어하기](#조도센서와-RGB-LED-제어하기)

---

## 피에조 부저 (piezo buzzer)

PiezoBuzzer 프로젝트

Beep 또는 LED는 간단하게 동작 확인 등 디버깅에 자주 사용됩니다. 피에조 부저를 이용하여 간단히 beep를 발생시키는 예제입니다.

![피에조 부저](/PiezoBuzzer/assets/Beep_피에조부저.jpeg)

![회로도](/PiezoBuzzer/assets/Beep_회로도.jpeg)

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

---

## 초음파 센서 (HC-SR04)

초음파 센서 중 입문자가 사용하기 쉽고 보편적인 모델로 초음파를 발신/수신하여 물체와의 거리를 측정할 수 있습니다.

전원, 발신, 수신, 접지 4개의 핀으로 구성되어 있어 쉽게 사용할 수 있습니다.

![초음파 센서](/DistanceRobotBasic/assets/초음파센서.PNG)

### 기본 활용

DistanceRobotBasic 프로젝트

#### 회로도

초음파 센서는 다음과 같이 회로를 구성합니다.

* VCC 전원 핀은 5V와 연결
* Trig 핀은 Tx 2번와 연결 (임의의 Tx 핀 가능)
* Echo 핀은 Tx 3번와 연결 (임의의 Tx 핀 가능)
* GND 핀은 GND 접지와 연결

![회로도](/DistanceRobotBasic/assets/초음파센서_기본_회로도.PNG)

#### 제작

회로도를 참고하여 센서와 아두이노를 연결합니다.

![제작](/DistanceRobotBasic/assets/초음파센서_기본_제작.JPG)

#### 코드

아두이노 스케치에서 아래와 같이 코드를 작성합니다.

![코드](/DistanceRobotBasic/assets/초음파센서_기본_코드.PNG)

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

![동작](/DistanceRobotBasic/assets/초음파센서_기본_동작.PNG)


### 응용 1 - 부저로 근접 알림

DistanceRobotBuzzer 프로젝트

#### 피에조 부저

피에조 부저를 연결하여 10cm 이내로 근접하면 beep 음을 발생시키도록 알리도록 합니다.

![피에조부저](/DistanceRobotBuzzer/assets/피에조부저.jpeg)

#### 회로도

+가 Tx 핀에 연결되고, -가 접지에 연결됩니다.

![회로도](/DistanceRobotBuzzer/assets/초음파센서_회로도_부저.jpeg)

#### 제작

회로도를 참고하여 피에조 부저를 아두이노를 연결합니다.

![제작](/DistanceRobotBuzzer/assets/초음파센서_제작_부저.jpg)

#### 코드

아두이노 스케치에서 아래와 같이 코드를 작성합니다.

![코드](/DistanceRobotBuzzer/assets/초음파센서_코드_부저.PNG)

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

![동작](/DistanceRobotBuzzer/assets/초음파센서_동작_응용1_부저.PNG)


### 응용 2 - LED로 물체의 거리 알리기

DistanceRobotLED 프로젝트

#### LED

아두이노에 초록, 노랑, 빨강 LED를 연결하여 물체와의 거리에 따라 LED를 켜도록 합니다.

#### 회로도

다리가 긴 핀이 +이고, 짧은 핀이 -입니다.

+에 Tx를 연결하고, -에는 저항을 연결한 후 GND(접지)에 연결합니다.

![LED 극](/DistanceRobotLED/assets/초음파센서_회로도_LED1.jpeg)

![회로도](/DistanceRobotLED/assets/초음파센서_회로도_LED2.PNG)

실제 구현 시 LED 핀 위치는 Green(9), Yellow(10), Red(11)에 연결했습니다.

#### 제작

회로도를 참고하여 3개의 LED를 아두이노에 연결합니다.

![제작](/DistanceRobotLED/assets/초음파센서_제작_LED.jpg)

#### 코드

아두이노 스케치에서 아래와 같이 코드를 작성합니다.

![코드](/DistanceRobotLED/assets/초음파센서_코드_LED1.PNG)

![코드](/DistanceRobotLED/assets/초음파센서_코드_LED2.PNG)

```cpp

int trigPin = 2; // trigger pin 설정 (초음파 발생)
int echoPin = 3; // echo pin 설정 (초음파 수신)

int green = 9;    // LED Green pin 설정
int yellow = 10;  // LED Yellow pin 설정
int red = 11;     // LED Red pin 설정

void setup() {
  Serial.begin(9600);       // 시리얼 모니터 속도 설정
  // 초음파 센서
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

![동작](/DistanceRobotLED/assets/초음파센서_동작_LED.PNG)

---

## LED를 이용한 신호등

SignalLight 프로젝트

Green -> Yellow -> Red 순서로 일정 시간동안 LED를 켜는 동작을 반복하는 예제입니다. LED를 어떻게 사용하는지 간단히 익힐 수 있습니다.

![LED 극](/SignalLight/assets/LED신호등_회로도.jpeg)

![회로도](/SignalLight/assets/LED신호등_회로도.PNG)

LED 핀 위치는 Green(9), Yellow(10), Red(11)에 연결했습니다.

![코드](/SignalLight/assets/LED신호등_코드.png)

```cpp
// 신호등 - 일정 간격으로 LED 변경

int green = 9;          // LED Green pin 설정
int yellow = 10;         // LED Yellow pin 설정
int red = 11;           // LED Red pin 설정
int speakerPin = 12;    // 피에조 부저 pin 설정

void setup() {
  Serial.begin(9600);   // 시리얼 모니터 속도 설정
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  Serial.println("GREEN");
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  Serial.println("Sound!!");
  tone(speakerPin, 500, 500);  // 500 음 높이(주파수), 500: 지속시간
  delay(1000);

  Serial.println("YELLOW");
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
  Serial.println("Sound!!");
  tone(speakerPin, 800, 500);  // 500 음 높이(주파수), 500: 지속시간
  delay(500);

  Serial.println("RED");
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  Serial.println("Sound!!");
  tone(speakerPin, 1000, 500);  // 500 음 높이(주파수), 500: 지속시간
  delay(1000);
}

```

---

## 조도센서와 RGB LED 제어하기

LightRobot 프로젝트

조도센서를 이용하여 획득된 밝기값에 따라 색상을 변경하는 RGB LED 불빛 색상을 변경하는 예제입니다.

조도센서 주변 밝기를 변경하여 LED의 불빛이 변경되는지 확인해 보면 재미 있습니다.

### 조도센서

조도센서(Photo Resistor)는 주변의 밝기를 측정하는 센서로 광에너지를 받으면 내부에 움직이는 전자가 발생하여 전도율이 변하는 광전효과를 가지는 소자인 황화카드뮴(Cds)을 사용하여 CdS 센서라고도 합니다.

![조도센서](/LightRobot/assets/조도센서.PNG)

조도센서는 빛의 양이 많아질 수록 전도율이 높아져 저항이 낮아집니다. 그러나 전도율 변화가 선형적이지 않기 때문에 단순 밝고 어두운 정도만 판별하는 것에 적합합니다.

조도센서도 일종의 저항이나 빛의 양이 매우 많은 경우 저항이 매우 작아져서 과전류가 흐를 수 있는데 CdS 조도센서는 대략 10KΩ의 저항을 갖기 때문에 10KΩ 저항이 함께 사용합니다.

![10K 옴 저항](/LightRobot/assets/조도센서_10K옴저항.PNG)

LED의 컬러를 표현하기 위해 3색 LED를 사용합니다. 3색 LED는 빨강, 초록, 파랑색을 하나로 합친 LED로 3개의 LED를 각각 제어하여 색상을 표현할 수 있습니다.

![RGB LED](/LightRobot/assets/RGBLED.png)

### 회로도

#### 조도센서

조도센서의 2핀 중 하나에 저항을 연결하고 그 저항은 아두이노의 접지(GND)에 연결됩니다.

저항에 연결된 조도센서 핀은 아두이노의 입력핀에 연결합니다. (예제에서는 A0에 연결)

조도센서의 나머지 핀은 전압 5V에 연결합니다.

![조도센서 회로도](/LightRobot/assets/조도센서_회로도.PNG)

#### RGB LED

RGB LED는 4개의 다리가 있습니다. 각각의 LED에는 양극 리드가 연결되어 있고,3개의 LED의 음극리드는 하나로 묶여서 한개의 음극리드로 나와 있습니다.

공통으로 사용하는 음극핀은 LED의평평한 면으로부터 2번째 핀이며, 가장 길이가 긴 핀입니다. 이 리드는 접지(GND)에 연결합니다.

![RGBLED 회로도](/LightRobot/assets/RGBLED_회로도1.PNG)

내부의 각 LED는 너무 많은 전류가 LED로 흘러와 LED가 망가지는 것을 방지하기 위해서 270Ω을 각각 필요합니다. 이 저항은 3개의 양극 리드와 아두이노 출력핀 사이에 위치해야 합니다.

![RGBLED 회로도](/LightRobot/assets/RGBLED_회로도2.jpg)

### 제작

회로도를 참고하여 조도센서와 RGB LED를 아두이노에 연결합니다.

![제작](/LightRobot/assets/조도센서_RGBLED_제작.jpg)

### 코드

아두이노 스케치에서 아래와 같이 코드를 작성합니다.

LED의 밝기는 공급되는 전원의 양에 의해 제어되므로 analogWrite 함수를 사용해야 합니다.

먼저 주변 밝기를 변경하여 조도센서의 밝기값을 시리얼 모니터로 확인하고 적당한 범주의 값을 설정하여 RGB LED 색상을 설정합니다.

![코드](/LightRobot/assets/조도센서_코드1.png)

![코드](/LightRobot/assets/조도센서_코드2.png)

```cpp

// 조도센서를 이용하여 밝기에 따라 RGB LED에 다른 색상의 등을 켜는 예제

// RGB LED pin
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

// 조도센서 pin
int cds = A0;

void setup()
{
  Serial.begin(9600); // 시리얼 모니터 속도 설정
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  // 조도센서로부터 측정된 밝기값 읽기 (전압의 크기(0~5V)에 따라 0 ~ 1023 범위의 값)
  int cdsValue = analogRead(cds);

  Serial.print("Light: ");
  Serial.println(cdsValue);

  if (cdsValue < 50)
  {
    setColor(255, 0, 0); // red
  }
  else if (cdsValue >= 50 && cdsValue < 100)
  {
    setColor(0, 0, 255); // blue
  }
  else if (cdsValue >= 100 && cdsValue < 200)
  {
    setColor(80, 0, 80); // purple
  }
  else if (cdsValue >= 200 && cdsValue < 500)
  {
    setColor(0, 255, 0); // green
  }
  else if (cdsValue >= 500 && cdsValue < 700)
  {
    setColor(255, 255, 0); // yellow
  }
  else
  {
    setColor(0, 255, 255); // aqua
  }

  delay(1000);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
}

```

### 동작

조도센서 주변의 밝기를 조절하여 RGB LED 생삭이 정상적으로 변경되는 것을 확인할 수 있습니다.

