#define X_PIN     A0
#define Y_PIN     A1
#define SW_PIN   7

// RGB LED pin
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup()
{
  Serial.begin(9600);

  // joystick
  pinMode(SW_PIN, INPUT);
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);

  // RGB LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int x=analogRead(X_PIN);
  int y=analogRead(Y_PIN);
  int z=digitalRead(SW_PIN);

  if (x == 0)
  {
    Serial.println("왼쪽");
    setColor(255, 0, 0); // red
  }
  else if (x == 1023)
  {
    Serial.println("오른쪽");
    setColor(0, 0, 255); // blue
  }
  
  if (y == 0)
  {
    Serial.println("위");
    setColor(0, 255, 0); // green
  }
  else if (y == 1023)
  {
    Serial.println("아래");
    setColor(255, 255, 0); // yellow
  }

  delay(100);
}


void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
}
