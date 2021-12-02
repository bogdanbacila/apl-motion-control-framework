# APL motion control framework

Basic framework which can be used for building different rotating devices used for 
audio research. 


TODO 

- [ ] add STL files
- [ ] define structure of the repo
- [ ] create requirements, roadmap and product description (mission statement)

TMP - Old instructions - to transfer to readme
---
- Screenshots of the connection and control process are available in the “Screenshots folder”
- Pictures of the connected device and possible mounting configurations are available in the “Photos” folder
- The Matlab library in in the “Matlab” folder
- The Arduino script used for controlling the motor is in the “Arduino” folder

Powering the device:

- Connect the motor cable to the controller box and fasten the screw.
!!IMPORTANT!! Do not power on the device without connecting the motor cable to the controller box.
- Plug in the power supply to the controller box. 

Connecting to the device:

- Go to System preferences -> Bluetooth.
- Find the “APLMicTurntable” device and click Connect.
- The device might not connect from the first try, click on Options, and change the passcode to “1234” and click Connect.
- Now the device should appear as connected.

Controlling the device:

- Open Matlab (required > R2019b)
- Make sure the working folder has the “APLMicTurntable.m” library on the same level
- use the “serialportlist” command to check the available serial ports. You are looking for the “/dev/cu.APLMicTurntable-DevB” port. 
- Create an instance of the APL Mic Turntable. The first variable in the constructor is the serial port you have to connect to and the second variable is the baud rate (this has to be 9600)

Example:

```
turntable = APLMicTurntable("/dev/cu.APLMicTurntable-DevB", 9600)
```

- Once the object is instantiated you can now try rotating the motor. The APLMicTurntable.rotate(angle) allows you to do so. You can use integer and floating point values for rotating to a specific angle. 

Example:

```
turntable.rotate(5) %rotates 5 degrees clockwise
turntable.rotate(-5) %rotates 5 degrees counter-clockwise 
turntable.rotate(2.5) %rotates 2.5 degrees clockwise
turntable.rotate(-2.5) %rotates 2.5 degrees counter-clockwise 
```
