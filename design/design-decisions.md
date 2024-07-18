# Design Decisions for Kitchen Clock

## Using USB CDC Mode to upload firmware

I decided to skip the standard ESP serial programmer and use USB JTAG/CDC mode for programming and communicating with the microcontroller on board. 

A breakout of RX/TX, GPIO0 and GND is still provded as a fallback if USB does not work.

Programming the firmware can work as described here:
[USB Settings for Logging with the ESP32-S3 in PlatformIO](https://thingpulse.com/usb-settings-for-logging-with-the-esp32-s3-in-platformio/)

**Note:** It can be possible to put the ESP32 into boot mode before it is able to be programmed. I decided not to add a specified Boot button on the board but one can use the breakout of RX/TX/GPI0 instead