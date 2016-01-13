// pin mapping
int particleInputPin = 0;
int ledPin = 2;

// timing variables
int delayTimeOutputPulse = 280;
int delayTimePulseWaveEnd = 40;
float waitTime = 9680;


float voMeasured = 0;
float ppm = 0;
float voltage = 0;
float dustDensity = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  ppm = 0;
}

void loop() {
  digitalWrite(ledPin, LOW); // power on the LED
  delayMicroseconds(delayTimeOutputPulse);
  voMeasured = analogRead(particleInputPin); // read the dust value
  delayMicroseconds(delayTimePulseWaveEnd);
  digitalWrite(ledPin, HIGH); // turn the LED off
  delayMicroseconds(waitTime);
  voltage = voMeasured * (5.0/1024);
  //Serial.println(voltage);
  dustDensity = ((0.1648 * voMeasured * (5.0/1024)) - 0.0923)*1000;
  if(dustDensity < 0){
    dustDensity = 0;
  }
  String dataString = "";
  //dataString += String(voltage,2);
  //dataString += ",";
  dataString += String(dustDensity,4);
  dataString += "µg/m³";
  ppm = 0;
  Serial.println(dataString);
  delay(10000);
  
}
