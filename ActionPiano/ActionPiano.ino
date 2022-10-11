const int C_4 = 261;   // 도
const int D_4 = 294;   // 레
const int E_4 = 330;   // 미
const int F_4 = 349;   // 파
const int G_4 = 392;   // 솔
const int A_4 = 440;   // 라
const int B_4 = 494;   // 시

int BUZZER_PIN = 8;

int Tact1 = 4;
int Tact2 = 5;
int Tact3 = 6;
int Tact4 = 7;

void setup() {
  Serial.begin(9600); // 시리얼 모니터 속도 설정
  
  pinMode(BUZZER_PIN, OUTPUT);

  // 저항을 사용하는 경우는 INPUT, 저항을 사용하지 않는 경우는 INPUT_PULLUP으로 설정
  pinMode(Tact1, INPUT_PULLUP);
  pinMode(Tact2, INPUT_PULLUP);
  pinMode(Tact3, INPUT_PULLUP);
  pinMode(Tact4, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(Tact1));
  Serial.println(digitalRead(Tact2));
  Serial.println(digitalRead(Tact3));
  Serial.println(digitalRead(Tact4));
  Serial.println("----------------");
  for (int i = 0; i < 4; i++)
  {
    if (digitalRead(Tact1) == HIGH)
    {
      tone(BUZZER_PIN, C_4);
      delay(1);
    }
    else if (digitalRead(Tact2) == HIGH)
    {
      tone(BUZZER_PIN, D_4);
      delay(1);
    }
    else if (digitalRead(Tact3) == HIGH)
    {
      tone(BUZZER_PIN, E_4);
      delay(1);
    }
    else if (digitalRead(Tact4) == HIGH)
    {
      tone(BUZZER_PIN, F_4);
      delay(1);
    }
  }

  noTone(BUZZER_PIN);
}
