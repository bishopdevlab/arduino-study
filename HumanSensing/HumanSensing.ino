int pirPin = 12;
int speakerPin = 13;

void setup() {
  Serial.begin(9600); // 시리얼 모니터 속도 설정
  pinMode(pirPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // 인체감지센서 값 읽기
  int sensor = digitalRead(pirPin);
  Serial.print("sensor: ");
  Serial.println(sensor);

  if (sensor == HIGH)
  {
    Serial.println("앗 사람이다");
    tone(speakerPin, 300, 500);  // 음높이, 지속시간
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
  }
  else
  {
    Serial.println("사람이 없다.");
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000); 
  }
}
