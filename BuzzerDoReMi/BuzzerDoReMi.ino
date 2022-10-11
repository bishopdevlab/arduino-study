const int C_4 = 261;   // 도
const int D_4 = 294;   // 레
const int E_4 = 330;   // 미
const int F_4 = 349;   // 파
const int G_4 = 392;   // 솔
const int A_4 = 440;   // 라
const int B_4 = 494;   // 시
const int C_5 = 540;   // 도

int BUZZER_PIN = 8;

void setup() {
}

void loop() {
  tone(BUZZER_PIN, C_4);
  delay(1000);
 
  tone(BUZZER_PIN, D_4);
  delay(1000);
 
  tone(BUZZER_PIN, E_4);
  delay(1000);
 
  tone(BUZZER_PIN, F_4);
  delay(1000);
 
  tone(BUZZER_PIN, G_4);
  delay(1000);
 
  tone(BUZZER_PIN, A_4);
  delay(1000);
 
  tone(BUZZER_PIN, B_4);
  delay(1000);

  tone(BUZZER_PIN, C_5);
  delay(1000);
 
  noTone(BUZZER_PIN);
  delay(1000);
}
