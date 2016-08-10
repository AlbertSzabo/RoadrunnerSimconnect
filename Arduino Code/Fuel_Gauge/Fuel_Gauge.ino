/*

 * 8-10-16, Matt Cashatt
 * 
 * WHAT IS IT:
 * Simple FSX Fuel Gauge using Simconnect and a 10-segment LED Display from Microtivity.
 * 
 * RELATED HARDWARE:
 * Amazon link: https://www.amazon.com/gp/product/B0085MOT2U/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1
 * 
 * NOTE: Since you need to have an available pin for each "bar" of the readout, I plan to flash an Atmel 328P using it's own internal 8Mhz clock.  I will use one of it's pins to read the value from the master controller, then run the code below for the display.
 * 
 * POSSIBLE IMPROVEMENTS: Right now I send a whole number rounded value to the arduino.  So, if FSX tells me I have 34.5% of fuel left in the tank, we send a value of 30 to Arduino.  If 35.55%, we send 40, etc. In the future, it may be better to send a decimal 
 * over to Arduino and then either fade or blink a bar segment depending on its value.  For example, a value of 34.5% would show 3 solid bars and one blinking bar whereas 35.55% would show four solid bars.
 * 
 * LICENSE: You are free to use this code as you see fit.  No warranties are made.  Use at your own risk.
 * 
 * THANKS: 
 * http://playground.arduino.cc/Csharp/SerialCommsCSharp
 * 
 */
//Setup Output

int p1 = 3;
int p2 = 4;
int p3 = 5;
int p4 = 6;
int p5 = 7;
int p6 = 8;
int p7 = 9;
int p8 = 10;
int p9 = 11;
int p10 = 12;

//Setup message bytes
byte inputByte_0;
byte inputByte_1;
byte inputByte_2;
byte inputByte_3;
byte inputByte_4;

//Setup
void setup() {

  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(p5, OUTPUT);
  pinMode(p6, OUTPUT);
  pinMode(p7, OUTPUT);
  pinMode(p8, OUTPUT);
  pinMode(p9, OUTPUT);
  pinMode(p10, OUTPUT);
  
  Serial.begin(9600);
  digitalWrite(p1, HIGH);//
  delay(250);//
  digitalWrite(p1, LOW);//
  delay(250);//
}

//Main Loop
void loop() {

  //Read Buffer
  if (Serial.available() == 5) 
  {
    //Read buffer
    inputByte_0 = Serial.read();
    delay(100);    
    inputByte_1 = Serial.read();
    delay(100);      
    inputByte_2 = Serial.read();
    delay(100);      
    inputByte_3 = Serial.read();
    delay(100);
    inputByte_4 = Serial.read();   
  }
  //Check for start of Message
  if(inputByte_0 == 16)
  {       
       //Detect Command type
       switch (inputByte_1) 
       {
          case 127:      //"127" is the command for sending data to the pins.  Seems like we can change this to something more friendly.  Came from this tutorial: http://playground.arduino.cc/Csharp/SerialCommsCSharp   
             //Set PIN and value
             switch (inputByte_2)
            {
              case 4:

                  int fuelLevel = inputByte_3;
                  
                  if(fuelLevel >90){
                    digitalWrite(p10, HIGH);
                  }else{
                    digitalWrite(p10, LOW);
                  }

                  if(fuelLevel >80){
                    digitalWrite(p9, HIGH);
                  }else{
                    digitalWrite(p9, LOW);
                  }

                  if(fuelLevel >70){
                    digitalWrite(p8, HIGH);
                  }else{
                    digitalWrite(p8, LOW);
                  }

                  if(fuelLevel >60){
                    digitalWrite(p7, HIGH);
                  }else{
                    digitalWrite(p7, LOW);
                  }

                  if(fuelLevel >50){
                    digitalWrite(p6, HIGH);
                  }else{
                    digitalWrite(p6, LOW);
                  }

                  if(fuelLevel >40){
                    digitalWrite(p5, HIGH);
                  }else{
                    digitalWrite(p5, LOW);
                  }

                  if(fuelLevel >30){
                    digitalWrite(p4, HIGH);
                  }else{
                    digitalWrite(p4, LOW);
                  }

                  if(fuelLevel >20){
                    digitalWrite(p3, HIGH);
                  }else{
                    digitalWrite(p3, LOW);
                  }

                  if(fuelLevel >10){
                    digitalWrite(p2, HIGH);
                  }else{
                    digitalWrite(p2, LOW);
                  }

                  if(fuelLevel >0){
                    digitalWrite(p1, HIGH);
                  }else{
                    digitalWrite(p1, LOW);
                  }

              break;
            } 
            break;
         
        } 
        //Clear Message bytes
        inputByte_0 = 0;
        inputByte_1 = 0;
        inputByte_2 = 0;
        inputByte_3 = 0;
        inputByte_4 = 0;
        
        //Let the PC know we are ready for more data
        Serial.print("-READY TO RECEIVE");
  }
}
