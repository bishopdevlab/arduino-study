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
