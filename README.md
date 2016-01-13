# pm25arduino
This application shows how to measure air quality in terms of particle density using a Sharp GP2Y1010AU0F Dust Sensor and an Arduino Uno.

## Components
The following components are needed to measure air quality:
* Ardunio or equivalent (~10€)
* Breadboard (~5€)
* Sharp GP2Y1010AU0F Dust Sensor (~8€)
* 150 Ohm Resistor & 220 µF Capacitor if not included in Sharp Sensor package

## Setup
The setup is based on the [Sharp GP2Y1010AU0F Datasheet](http://www.sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y1010au_appl_e.pdf) which results in the following wiring:

| Sharp Sensor  | Arduino Uno |
| ------------- | ------------- |
| 1 V-LED  | 5V Pin + 150 Ohm resistor  |
| 2 LED-GND | GND Pin  |
| 3 LED | Digital Pin 2  |
| 4 S-GND | GND Pin  |
| 5 Vo | Analog Pin A0  |
| 6 Vcc | 5V Pin  |

See the figure below for the wiring using an Arduino Uno and the Sharp GP2Y1010AU0F Dust Sensor.
![Setup](https://drive.google.com/open?id=0BzlX-a_DzYB2c05weWRRYXhSUG8)
Figure 1: Wiring


## Code

As shown in the Sharp datasheet the output pulse can be sampled after 280 µs the IR LED was turned on. After another 40 µs the LED is turned off, then the sequence is delayed for 9680 µs.
![Sampling](https://drive.google.com/open?id=0BzlX-a_DzYB2RFhzRWxTbDRYNWs)
Figure 2: Sampling example
![Wave](https://drive.google.com/open?id=0BzlX-a_DzYB2RGpKVExKVXNhZW8)
Figure 3: Wave

To calculate the particle density given the output voltage of Sharp pin 3 the graph in figure 4 was transposed and linearized as shown in figure 5.
This results in the following equation: y= 0,1648 * x - 0,0923.

![VoltageDensity](https://drive.google.com/uc?export=download&id=0BzlX-a_DzYB2U2xmTnBEeGNib28)
Figure 4: Output voltage vs. particle density

![Linear](https://drive.google.com/open?id=0BzlX-a_DzYB2NVJ2ZEJFQkM2Rkk)
Figure 5: Linearized graph

```
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
```
