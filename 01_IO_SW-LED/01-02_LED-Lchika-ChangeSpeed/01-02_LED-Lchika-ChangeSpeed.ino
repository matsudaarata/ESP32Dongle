//Connect SingleLED to OUT connector

#define ledPin 25
#define on HIGH
#define off LOW

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, on); 
  delay(40); //msec (1000msec=1sec)
  digitalWrite(ledPin, off);
  delay(10); //msec (1000msec=1sec)
  digitalWrite(ledPin, on); 
  delay(200); //msec (1000msec=1sec)
  digitalWrite(ledPin, off);
  delay(300); //msec (1000msec=1sec)
  digitalWrite(ledPin, on); 
  delay(16000); //msec (1000msec=1sec)
  digitalWrite(ledPin, off);
  delay(1300); //msec (1000msec=1sec)
}
