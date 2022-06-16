int speakerPin = 12;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  tone(speakerPin, 500, 1000);  // 500 음 높이(주파수), 1000: 지속시간
  delay(2000);
}
