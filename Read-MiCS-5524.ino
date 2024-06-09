//global variables
int ledHeartbeat = LED_BUILTIN;
int HEARTBEAT_INTERVAL = 500;  //Blink on for 500 milliseconds

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
  Serial.begin(9600);
  delay(500);
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

  timeNow = millis();

  //Blink a heartbeat LED so we know we're operating.
  if (timeNow > taskTime[tnHeartbeatTask] + HEARTBEAT_INTERVAL)
  {
      Serial.println("timeNow  = " + String(timeNow));
      taskTime[tnHeartbeatTask] += HEARTBEAT_INTERVAL;
      digitalWrite (ledHeartbeat, BlinkOn);
      BlinkOn = !BlinkOn;
  }

}
