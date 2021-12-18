void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  for (int i = 44; i <= 52; i += 2) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
for (int i = 44; i <= 52; i += 2) {
      digitalWrite(i, HIGH);
      delay(100);
   }
   for (int i = 44; i <= 52; i += 2) {
      digitalWrite(i, LOW);
      delay(100);
   }
}
