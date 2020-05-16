
int counter = 0 ;

static const double up = 1.9;
static const double down = 1.2;

bool flag = false;

int previousValue = 0;

double diffValue =0;
double movingAverageValue =0;
double movingAverageValue2 =0;

static const double alphaDiff = 0.9;
static const double alphaValue = 0.8;
static const double alphaValue2 = 0.99;

#ifndef  PLOTTER_OUTPUT_ENABLE
#define PLOTTER_OUTPUT_ENABLE 1
#endif

void setup() {
  // initialize serial communication at 230400 bits per second:
  
#if PLOTTER_OUTPUT_ENABLE
  Serial.begin(230400);
#endif
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);   
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  movingAverageValue2 = alphaValue2*movingAverageValue2 +(1.0-alphaValue2)*sensorValue;
  movingAverageValue = alphaValue*movingAverageValue +(1.0-alphaValue)*sensorValue;

  diffValue =  diffValue*alphaDiff + fabs((1.0-alphaDiff)*(movingAverageValue-previousValue));

  if ((diffValue > up) && flag == false)
  {
    flag = true;
    counter++;
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(12, LOW);   
  }  
  else if ((diffValue < down) && flag == true)
  {
    flag = false;
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(12, HIGH);   
  }
  
previousValue = movingAverageValue;

 #if PLOTTER_OUTPUT_ENABLE
  Serial.print(diffValue*10);
  Serial.print(",");
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.print(movingAverageValue-100);
  Serial.print(",");
  Serial.print(abs(movingAverageValue2-movingAverageValue) );
  Serial.print(",");
  Serial.println(flag ? 1024/2 : 0);
 #endif
  
  delay(2);        // delay in between reads for stability
}
