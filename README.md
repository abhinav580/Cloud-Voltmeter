# Cloud-Voltmeter
I have created this project because, sometimes we need to store some data on cloud (MQTT ), like data of temperature sensor, microphone sensor, potentiometer etc, so this program helps in this. In this  Project I have used Thingsio.ai platform which is one of the best IoT platform.
# Lets talk about How this project works:
In this project you need to give a power supply(0 - 3.3 V) in the analog pin of Node Mcu. and the voltage is read in the program by analogRead() function . and this value gets stored in a variable. Now we need to connect the Node Mcu to a WiFi Network so that the value can be passed to the server. after the connection POST method is used to send the data to the thingsio.ai platform.

# How to Access the Data:
Just go the thingsio.ai website and create an account and then create a project. after that create a key on which the value will be stored(This should be same as the key used in Coding. and Now finish that. and then Run the program. You will see that the voltage which is connected to the analog pin will get displayed on the server. 

# About the code
there are few things which you need to change in the code,, First of all Change the Wifi SSID and Wifi password then change the device id(as per your account). and the key name which will be get posted.
and then Upload this program on to your Esp Board.

its done.


# About the Circuit
I have used ESP8266 board (Node MCU) for thsi project. the power supply to run the board is given from the USB port. the power supply which we want to measure is being given in analog pin of the Node MCU board. The Node Mcu has only one Analog PIn (A0) and the VCC of Node Mcu is only 3.3 volt so we can only connect 3.3 Volt maximum in the analog pin.
But it is possible to connect more that 3.3 Volt by using a trick. You can use a Voltage divider by using 3 resistors . By this trick you can even measure up to 220 V easily. But make sure that u make the connections properly.

# thecircuit diagram is uploaded in the repository.
