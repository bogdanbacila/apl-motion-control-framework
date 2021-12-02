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
