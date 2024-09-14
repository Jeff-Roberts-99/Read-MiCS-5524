# Read-MiCS-5524

Simple read from the MiCS-5524 breakout board. Reads through A0 once per second.
Reports elapsed time (in seconds) and sensor value from 0-100%.
A0 is a 12-bit ADC (counts range from 0 to 4095).
Also blinks a heartbeat LED twice per second.

Sample output:
Read-MiCS-5524 started up!
timeNow = 4, sensorValue  = 19.88%
timeNow = 5, sensorValue  = 3.52%
timeNow = 6, sensorValue  = 3.64%
timeNow = 7, sensorValue  = 3.25%
timeNow = 8, sensorValue  = 3.81%
timeNow = 9, sensorValue  = 3.88%
