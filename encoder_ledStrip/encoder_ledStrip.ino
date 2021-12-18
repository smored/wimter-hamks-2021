#define outputA 6
 #define outputB 7
 int counter = 0; 
 int aState;
 int aLastState;  

void setup() {
  // put your setup code here, to run once:
  for (int i = 44; i <= 52; i += 2) {
    pinMode(i, OUTPUT);
  }

  Serial.begin(115200);
// Reads the initial state of the outputA
   aLastState = digitalRead(outputA);  
   pinMode (outputA,INPUT_PULLUP);
   pinMode (outputB,INPUT_PULLUP);

   
}

void loop() {
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     if (counter >= 8) {
      counter = 8;
     } else if (counter <= 0) {
      counter = 0;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state

   for (int i = 44; i <= 52; i += 2) {
    if (counter == (i - 44) || counter == (i - 45)) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
   }
}
