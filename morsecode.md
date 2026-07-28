My morse code display approach:

User is prompted to enter the encrypted sentence/word/character into the serial monitor. 
The string is taken and processed as an array of characters, where through iteration every char is being evaluted for being either a dot, slash or a dash[.,-,/]. 
The ground rules state that dots are short (0.3s) and dashes are longer (0.9s), spaces are also (0.9s) and slashes are longest (2.1s). 
But seeing as there are already pauses between each [.,-] character for (0.3s), the actual pauses seen as spaces or slashes are each reduced to respectively (0.6s) delay and (1.8s) in coding, but will be seen as true value all compiled together.
The LED is then lit up for every evaluated character.

Tinkercad: https://www.tinkercad.com/things/hlkAnNTT2NQ-morse-code
Video: https://drive.google.com/file/d/1Hlt4D6Vl4cRsoWfSdZzSWFBJsj3D1MTc/view?usp=sharing
