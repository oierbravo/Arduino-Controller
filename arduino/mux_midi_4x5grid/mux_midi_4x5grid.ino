/*
* Arduino Controller
* Mux & MIDI version.
* 
* Just takes 20 digital inputs and acts as a MIDI controller sending notes.
* 
* @version 0.0.1
* @author Oier Bravo Urtasun
*/

#define DEBOUNCE
// Debounce time length in milliseconds
#define DEBOUNCE_LENGTH 2

//Give convenient names to the control pins
#define CONTROL0 5    
#define CONTROL1 4
#define CONTROL2 3
#define CONTROL3 2

#define mux0controlPin 14
#define mux1controlPin 15

#define mux0inputNum 16
#define mux1inputNum 4

#define MIDI
//#define DEBUG

byte tempDigitalInput;

int mux0array[mux0inputNum];
int mux1array[mux0inputNum];

int buttonCounter;
int mux0counterArray[mux0inputNum];
int mux1counterArray[mux1inputNum];

int mux0lastValueArray[mux0inputNum];
int mux1lastValueArray[mux1inputNum];

void setup()
{
  //Set MUX control pins to output
  pinMode(CONTROL0, OUTPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);

  #ifdef MIDI
    Serial.begin(31250);
  #endif
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  
  
  //Set analog pins to digital input  
  pinMode(mux0controlPin, INPUT);         
  pinMode(mux1controlPin, INPUT);
  
  //Turn on pullup resistors
  digitalWrite(14, HIGH);       
  digitalWrite(15, HIGH);
}

void loop(){
  processMuxes();
  printOutput();
}
void processMuxes(){
  buttonCounter = 0;
  //First MUX
  proccessMux(mux0array,mux0controlPin,mux0inputNum,mux0counterArray,mux0lastValueArray);
  //Second MUX
  proccessMux(mux1array,mux1controlPin,mux1inputNum,mux1counterArray,mux1lastValueArray);
}
void proccessMux(int *valueArray,int muxControlPin,int arrayLength,int *muxCounterArray,int *muxLastValueArray){
  for (int i=0; i<arrayLength; i++)
  {
   
    
    digitalWrite(CONTROL0, (i&15)>>3); 
    digitalWrite(CONTROL1, (i&7)>>2);  
    digitalWrite(CONTROL2, (i&3)>>1);  
    digitalWrite(CONTROL3, (i&1));

     
    
    //Since internal pullup is on, the pin goes low on changing, so the value needs to be flipped from 0 to 1 (!)
    tempDigitalInput = !digitalRead(muxControlPin);
    #ifdef DEBOUNCE
      // Wait for a short period of time, and then take a second reading from the input pin.
    delay(DEBOUNCE_LENGTH);
      // If the second reading is the same as the initial reading, assume it must be true.
    if (tempDigitalInput == !digitalRead(muxControlPin))
      {
    #endif
    valueArray[i] = tempDigitalInput;
    //Incrase general counter
    muxCounterArray[i] = buttonCounter;
    buttonCounter++;
    #ifdef DEBOUNCE
      }
    #endif
    
  }
}
void printOutput(){
  printMux(mux0array,mux0inputNum,mux0counterArray,mux0lastValueArray);
  printMux(mux1array,mux1inputNum,mux1counterArray,mux1lastValueArray);
}
void printMux(int *valueArray,int arrayLength,int *counterArray,int *lastValueArray){
         
  for (int i=0; i<16; i++)
  {
    if(i < arrayLength){    
      if(lastValueArray[i] != valueArray[i]){
        //Note was off so Play
        if(valueArray[i] == 1){
          noteOn(,counterArray[i]);
        }
        //Note was on so Stop
        if(valueArray[i] == 0){
          noteOff(0x90,counterArray[i]);
        }
        //Update last value
        lastValueArray[i] = valueArray[i];
      }
    }
  }
  
}
/*
*  Plays a MIDI note.
*  @param pitch integer Must be between 0 - 127
*/
void noteOn(int pitch) {
  //Send note MIDI command
  cmd = 0x90;
  //Maximum velocity
  int velocity = 127;
  #ifdef MIDI
    Serial.write(cmd);
    Serial.write(pitch);
    Serial.write(velocity);
  #endif
  #ifdef DEBUG
    Serial.print("Note:");
    Serial.print(pitch);
    Serial.println(" ON");
  #endif
   
}
/*
*  Stops playing a MIDI note.
*  @param pitch integer Must be between 0 - 127
*/
void noteOff(int pitch) {
  //Send note MIDI command
  cmd = 0x90;
  //Minimum velocity
  int velocity = 0x00;
  #ifdef MIDI
    Serial.write(cmd);
    Serial.write(pitch);
    Serial.write(velocity);
    #endif
  #ifdef DEBUG
    Serial.println("Note:");
    Serial.print(pitch);
    Serial.println(" OFF");
  #endif
}
