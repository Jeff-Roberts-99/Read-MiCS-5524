//global variables
int ledHeartbeat = LED_BUILTIN;
int HEARTBEAT_INTERVAL = 500;  //Blink on for 500 milliseconds
int ADC_READ_INTERVAL = 1000;  
int adcInputPin = A0;

//Global task information
enum taskNumbers {
  tnHeartbeatTask,
  tnAdcReadTask,
  tnNumberOfTasks, 
};
unsigned long taskTime[tnNumberOfTasks];

void setup() {
  // put your setup code here, to run once:
  //Set up serial port
  Serial.begin(115200);
  delay(3000);
  Serial.println("Read-MiCS-5524 started up!");

  // initialize the LED pin as an output.
  pinMode(ledHeartbeat, OUTPUT);

  //Set timers to current time.
  taskTime[tnHeartbeatTask] = millis();
  taskTime[tnAdcReadTask] = millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long timeNow = 0;
  static boolean BlinkOn;
  int sensorValue = 0;
  float percentValue;

  timeNow = millis();

  //Blink a heartbeat LED so we know we're operating.
  if (timeNow > taskTime[tnHeartbeatTask] + HEARTBEAT_INTERVAL)
  {
      taskTime[tnHeartbeatTask] += HEARTBEAT_INTERVAL;
      digitalWrite (ledHeartbeat, BlinkOn);
      BlinkOn = !BlinkOn;
  }

  if (timeNow > taskTime[tnAdcReadTask] + ADC_READ_INTERVAL)
  {
      //Read from the sensor
      taskTime[tnAdcReadTask] += ADC_READ_INTERVAL;
      sensorValue = analogRead(adcInputPin);
      percentValue = (float)sensorValue/4095.0*100.0;
      Serial.println("timeNow = " + String(timeNow/1000) + ", sensorValue  = " + String(percentValue) + "%");
  }

}
