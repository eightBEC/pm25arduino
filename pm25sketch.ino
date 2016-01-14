// pin mapping
int particleInputPin = 0;
int ledPin = 2;

// timing variables
int delayTimeOutputPulse = 280;
int delayTimePulseWaveEnd = 40;
float waitTime = 9680;
int i = 0;


float voMeasured = 0;
float voltage = 0;
float dustDensity = 0;
float dustDensityAvg = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, LOW); // power on the LED
  delayMicroseconds(delayTimeOutputPulse);
  voMeasured = analogRead(particleInputPin); // read the dust value
  delayMicroseconds(delayTimePulseWaveEnd);
  digitalWrite(ledPin, HIGH); // turn the LED off
  delayMicroseconds(waitTime);
  voltage = voMeasured * (5.0/1024);
  // µg/m³
  dustDensity = ((0.1648 * voMeasured * (5.0/1024)) - 0.0923)*1000;
  if(dustDensity < 0){
    dustDensity = 0;
  }
  dustDensityAvg += dustDensity;
  delay(10000);
  i++;
  if(i%6==0){
    char avgDustStr[25];
    //avg dust density (µg/m³) / min
    sprintf(avgDustStr,"%f",(dustDensityAvg / (i*1.0)));
    Serial.println(avgDustStr);
    i=0;
    dustDensityAvg=0;
  }
}