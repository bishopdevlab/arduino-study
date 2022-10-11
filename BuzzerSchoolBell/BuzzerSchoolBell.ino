const int BUZZER_PIN = 8;
 
const int C_4 = 261;   // 도
const int D_4 = 294;   // 레
const int E_4 = 330;   // 미
const int F_4 = 349;   // 파
const int G_4 = 392;   // 솔
const int A_4 = 440;   // 라
const int B_4 = 494;   // 시
 
typedef struct  { 
  int tone;
  unsigned long delay;
} TAD;//Tone And Delay
 
TAD music[] =
  {
    {G_4, 100}, {G_4, 100}, {A_4, 100}, {A_4, 100}, {G_4, 100}, {G_4, 100}, {E_4, 200},
    {G_4, 100}, {G_4, 100}, {E_4, 100}, {E_4, 100}, {D_4, 200}, {G_4, 100}, {G_4, 100},
    {A_4, 100}, {A_4, 100}, {G_4, 100}, {G_4, 100}, {E_4, 200}, {G_4, 100}, {E_4, 100},
    {D_4, 100}, {E_4, 100}, {C_4, 200}
  };
 
int musicLen;
 
void setup() {
  musicLen = sizeof(music) / sizeof(TAD);
}
 
void loop() {
  for(int i = 0; i < musicLen; i++) {
    tone(BUZZER_PIN, music[i].tone);
    delay(music[i].delay * 5);
 
    noTone(BUZZER_PIN);
    delay(30);
  }
 
  noTone(BUZZER_PIN);
  delay(1000);
}
