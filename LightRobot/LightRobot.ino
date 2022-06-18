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
