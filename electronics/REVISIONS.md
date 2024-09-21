# Board revisions

## v1.1 - Power Management

### Issue 1: USB light on when device is powered only from battery

**Issue:**
The USB power LED get's driven by the remaining voltage that is on the charging IC's VIN pin when only the battery is providing power

**Fix**:
Introduce a low drop (e.g. a Shotky diode) between VBUS and VIN of the charging IC

**Status**: Implemented in Schematic


### Issue 2: No Ready and charging leds

**Issue:**
The active low charging and ready pins of the charging IC are only provided to the microcontroller so far. It would be good to have also leds on the board which indicate the charging process and its ready state also when the microcontroller is off

**Fix**:
- Add to LEDs to the charging and ready pin respectively
- Move all the LEDs (charging, ready, usb powered and system on to one place on the edge of the pcb)
- change the LEDs to PHTs so that we can bring them through the case of the project

**Status**: In Progress

### Issue 3: Add an I2C port

‚

### Issue 4: Switching 5V rail to USB VBUS if available putting load of the battery while loading