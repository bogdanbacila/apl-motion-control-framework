%{   
Author: Bogdan Bacila 
        Applied Psychoacoustics Lab, University of Huddersfield, UK 

 
 - Class for controlling the APL mic turntable. 

 - Matlab version > R2019b required
 - Make sure the working folder has the “APLMicTurntable.m” library on the same level
 - Make sure that the turntable is connected to the computer via bluetooth. 
 - use the “serialportlist” command to check the available serial ports.
 - Create an instance of the APL Mic Turntable. The first variable in the constructor is the serial port you have to connect to and the second variable is the baud rate (this has to be 9600)

Example:

```
turntable = APLMicTurntable("YOUR_TURNTABLE_SERIAL_PORT", 9600)
```

- Once the object is instantiated you can now try rotating the motor. The `APLMicTurntable.rotate(angle)` allows you to do so. You can use integer and floating point values for rotating to a specific angle. 

Example:

```
turntable.rotate(5) %rotates 5 degrees clockwise
turntable.rotate(-5) %rotates 5 degrees counter-clockwise 
turntable.rotate(2.5) %rotates 2.5 degrees clockwise
turntable.rotate(-2.5) %rotates 2.5 degrees counter-clockwise 
```
%}

classdef APLMicTurntable
   properties
      port = "";
   end
   methods
       function obj = APLMicTurntable(inPort, baudRate)
           obj.port = serialport(inPort, baudRate);
        
       end
       function rotate(obj, angle)
           writeline(obj.port, string(angle))
       end
   end
end
