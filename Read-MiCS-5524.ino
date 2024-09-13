struct Task {
    unsigned long lastRunTime;  // Last time the task was run
    unsigned long interval;     // Interval at which to run the task
    void (*taskFunction)();     // Pointer to the function to be executed
};

//global variables
int ledHeartbeat = LED_BUILTIN;
int adcInputPin = A0;
boolean BlinkOn = false;

// Function prototypes
void heartbeatTask();
void adcReadTask();

// Task array
Task tasks[] = 
{
    {0, 500, heartbeatTask},    // Heartbeat task with 500ms interval
    {0, 1000, adcReadTask}      // ADC read task with 1000ms interval
};

const int numberOfTasks = sizeof(tasks) / sizeof(tasks[0]);

void setup() {
  //Set up serial port
  Serial.begin(115200);
  delay(3000);
  Serial.println("Read-MiCS-5524 started up!");

  // initialize the LED pin as an output.
  pinMode(ledHeartbeat, OUTPUT);

  // Set initial task times to current time
  unsigned long currentTime = millis();
  for (int i = 0; i < numberOfTasks; i++) 
  {
    tasks[i].lastRunTime = currentTime;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  int sensorValue = 0;
  float percentValue;


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
    digitalWrite (ledHeartbeat, BlinkOn);
    BlinkOn = !BlinkOn;
}

void adcReadTask() 
{
    int sensorValue = analogRead(adcInputPin);
    float percentValue = (float)sensorValue / 4095.0 * 100.0;
    Serial.println("Sensor Value = " + String(percentValue) + "%");
}

