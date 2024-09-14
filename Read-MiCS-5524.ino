//Task intervals
int TASK_HEARTBEAT_INTERVAL = 500;  //Blink on for 500 milliseconds
int TASK_ADC_READ_INTERVAL = 250;  
int SENSOR_WARMUP_INTERVAL = 90000; //90 seconds wait time for sensor to warm up

struct Task {
    unsigned long lastRunTime;  // Last time the task was run
    unsigned long interval;     // Interval at which to run the task
    void (*taskFunction)();     // Pointer to the function to be executed
};

//global variables
int ledHeartbeat = LED_BUILTIN;
int adcInputPin = A2;
boolean BlinkOn = false;
int sensorState;

enum e_sensorState
{
    ssWarmingUp,
    ssDetectingGas,
    ssGasDetected
};


// Function prototypes
void heartbeatTask();
void adcReadTask();

// Task array
Task tasks[] = 
{
    {0, TASK_HEARTBEAT_INTERVAL, heartbeatTask},    // Heartbeat task with 500ms interval
    {0, TASK_ADC_READ_INTERVAL, adcReadTask}      // ADC read task with 250ms interval
};

const int numberOfTasks = sizeof(tasks) / sizeof(tasks[0]);

void setup() {
  //Set up serial port
  Serial.begin(115200);
  delay(3000);
  Serial.println("Read-MiCS-5524 started up!");
  Serial.println("Waiting 90 seconds for sensor to warm up.");
  Serial.println("Gas% delta% Spike");

  // initialize the LED pin as an output.
  pinMode(ledHeartbeat, OUTPUT);
  digitalWrite (ledHeartbeat, false);

  // Set initial task times to current time
  unsigned long currentTime = millis();
  for (int i = 0; i < numberOfTasks; i++) 
  {
    tasks[i].lastRunTime = currentTime;
  }

  //Set the state machine 
  sensorState = ssWarmingUp;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  int sensorValue = 0;
  float percentValue;

  if (timeNow > SENSOR_WARMUP_INTERVAL)
  {
      sensorState = ssDetectingGas;
  }

  // Iterate through tasks
  for (int i = 0; i < numberOfTasks; i++) 
  {
    if (currentTime - tasks[i].lastRunTime >= tasks[i].interval) 
    {
        tasks[i].lastRunTime = currentTime;  // Update last run time
        tasks[i].taskFunction();             // Execute the task function
    }
  }
}

// Task functions

void heartbeatTask() 
{
      if (toggleBlink>0)
      {
        digitalWrite (ledHeartbeat, BlinkOn);
        BlinkOn = !BlinkOn;
        toggleBlink--;  
      }  
}

void adcReadTask() 
{
      //Read from the sensor, calculate new value, calculate delta from last value
      taskTime[tnAdcReadTask] += TASK_ADC_READ_INTERVAL;
      sensorValue = analogRead(adcInputPin);
      newValue = (float)sensorValue/4095.0*100.0;
      if (lastValue > 0)
      {
        delta = (newValue - lastValue ) / lastValue;
      }
      else
      {
        delta = 0;
      }
      //Serial.println("timeNow = " + String(timeNow/1000) + ", newValue  = " + String(newValue) + "%" + ", delta = " + String(delta*100.0) +"%");

      if (sensorState == ssDetectingGas)
      {
          //Check for high gas value, or high delta
          Serial.print (newValue);
          Serial.print (" ");
          Serial.print(delta);
          Serial.print (" ");
  
          //Alert if we drift over 8 or find a spike
          SpikeFound = false;
          if (newValue > 8) {SpikeFound = true;}
          if ((newValue > 3) and (delta>0.3)) {SpikeFound = true;}
          if (SpikeFound)
          {
            toggleBlink=9;
            BlinkOn = false;
            Serial.println(100);
          }
          else
          {
            Serial.println(0);
          }
      }
      lastValue = newValue;
}

