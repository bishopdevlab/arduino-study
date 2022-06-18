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