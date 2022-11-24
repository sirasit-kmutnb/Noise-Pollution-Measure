#define SENSOR_PIN A0
const int sampleWindow = 50;
unsigned int sample;
float db2;
void setup() {

  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  unsigned long startMillis = millis();  // Start of sample window
  float peakToPeak = 0;                  // peak-to-peak level

  unsigned int signalMax = 0;     //minimum value
  unsigned int signalMin = 1024;  //maximum value

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(SENSOR_PIN);  //get reading from microphone
    if (sample < 1024)                // toss out spurious readings
    {
      if (sample > signalMax) {
        signalMax = sample;  // save just the max levels
      } else if (sample < signalMin) {
        signalMin = sample;  // save just the min levels
      }
    }
  }

  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  if (peakToPeak <= 4) {
    db2 = map(peakToPeak,1,4,60.0,70.7);
  }
  else if ((peakToPeak > 4) && (peakToPeak <=7)){
    db2 = map(peakToPeak,4,7,70.7,83.2);
  }   
  else if ((peakToPeak > 7) && (peakToPeak <=10)){
    db2 = map(peakToPeak,7,10,83.2,87.9);
  } 
  else if ((peakToPeak > 10) && (peakToPeak <=16)){
    db2 = map(peakToPeak,10,16,87.9,90.7);
  }  
  else if ((peakToPeak > 16) && (peakToPeak <=18)){
    db2 = map(peakToPeak,16,18,90.7,94.0);
  }  
  else if ((peakToPeak > 18) && (peakToPeak <=23)){
    db2 = map(peakToPeak,18,23,94.0,96.5);
  }   
  else if ((peakToPeak > 23) && (peakToPeak <=31)){
    db2 = map(peakToPeak,23,31,96.5,99.2);
  } 
  else if ((peakToPeak > 31) && (peakToPeak <=46)){
    db2 = map(peakToPeak,31,46,99.2,101.6);
  }
  else if ((peakToPeak > 46) && (peakToPeak <=66)){
    db2 = map(peakToPeak,46,66,101.6,105.1);
  } 
  else if ((peakToPeak > 66) && (peakToPeak <=77)){
    db2 = map(peakToPeak,66,77,105.1,107.0);
  }  
  else if ((peakToPeak > 77) && (peakToPeak <=94)){
    db2 = map(peakToPeak,77,94,107.0,109.3);
  }
  else if ((peakToPeak > 94) && (peakToPeak <=107)){
    db2 = map(peakToPeak,94,107,109.3,110.5);
  }
  else if ((peakToPeak > 107) && (peakToPeak <=120)){
    db2 = map(peakToPeak,107,120,110.5,111.1);
  }     //calibrate for deciBels
  int db = (peakToPeak + 230.66265060241) / 5.77835479850436;  //calibrate for dB using linear regression (beta)
  Serial.print(db);
  Serial.print(" ");
  Serial.print(peakToPeak);
  Serial.print(" ");
  Serial.println(db2);
  delay(100);
}