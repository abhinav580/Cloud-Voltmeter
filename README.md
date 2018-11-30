# Cloud-Voltmeter
I have created this project because, sometimes we need to store some data on cloud (MQTT ), like data of temperature sensor, microphone sensor, potentiometer etc, so this program helps in this. In this  Project I have used Thingsio.ai platform which is one of the best IoT platform.
Lets talk about How this project works:
In this project you need to give a power supply(0 - 3.3 V) in the analog pin of Node Mcu. and the voltage is read in the program by analogRead() function . and this value gets stored in a variable. Now we need to connect the Node Mcu to a WiFi Network so that the value can be passed to the server. after the connection POST method is used to send the data to the thingsio.ai platform.

How to Access the Data:
Just go the thingsio.ai website and create an account and then create a project. after that create a key on which the value will be stored(This should be same as the key used in Coding. and Now finish that. and then Run the program. You will see that the voltage which is connected to the analog pin will get displayed on the server. 

