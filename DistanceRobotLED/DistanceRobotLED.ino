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
