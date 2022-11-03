
#define SENSOR_PIN A0
const int sampleWindow = 50; 
unsigned int sample;
void setup() {

  Serial.begin(9600);
  pinMode (SENSOR_PIN, INPUT);
  
}

void loop() { 
   unsigned long startMillis= millis();                   // Start of sample window
   float peakToPeak = 0;                                  // peak-to-peak level
 
   unsigned int signalMax = 0;                            //minimum value
   unsigned int signalMin = 1024;                         //maximum value
 
                                                          // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(SENSOR_PIN);                    //get reading from microphone
      if (sample < 1024)                                  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;                           // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;                           // save just the min levels
         }
      }
   }
 
   peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
  //  float db = map(peakToPeak,20,900,49.5,90);             //calibrate for deciBels   
  int db = (peakToPeak+230.66265060241)/5.77835479850436 ; //calibrate for dB using linear regression (beta)
  Serial.print(db);
  Serial.print(" ");
  Serial.println(peakToPeak);   
}