#define outputA 6
 #define outputB 7
 int diff = 0; 
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
       diff ++;
     } else {
       diff --;
     }
     if (diff >= 8) {
      diff = 8;
     } else if (diff <= 0) {
      diff = 0;
     }
     Serial.print("Position: ");
     Serial.println(diff);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state

   for (int i = 44; i <= 52; i += 2) {
    if (diff == (i - 44) || diff == (i - 45)) {
      for (int j = 44; j <= i; j += 2) {
        digitalWrite(j, HIGH); 
        digitalWrite(j+2, LOW);
      }      
    }
   }
   
}
