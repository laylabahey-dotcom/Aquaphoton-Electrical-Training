My Simon Game Approach:
The game starts by asking for difficulty level (mode) the user wishes to play at. [easy - medium - hard]. The level is displayed on an RGB LED that stays on for the entirety of the round.
Easy, the pause between each flare is 3s and the sequence shown is shorter (4 flares) -- RGB color: green
Medium, the pause between each flare is 1.5s and the sequence shown is slightly longer (6 flares) -- RGB color: blue
Hard, the pause between each flare is 0.75s and the sequence shown is longest (8 flares) -- RGB color: red
It functions as if 3 LEDs connected to a single ground, but the colors depend on which pin you set to HIGH. (RCGB)

There is a set sequence that is shown on the 4 LEDs, the corresponding LED and Pushbuttons digital pins/
0 = Red, 1 = Yellow, 2 = Green, 3 = Blue
int ledseq[] = {0, 3, 2, 1, 0, 2, 3, 1};
int ledPins[] = {7, 8, 9, 10};
                0   1  2   3
int buttonPins[] = {3, 4, 5, 6};
                    0  1  2  3
This is for 
1) displaying pattern on the LEDs for the player at the start of the game
2) anticipating which buttons are to be pressed and in which sequence, also knowing when the pattern is entered wrong.
3) making corresponding LEDs light up when button is pressed.

NEW: learning to wait for button to be pushed. I set a certain value (-1) to a variable I named 'pushedbutton' and made a while loop. While pushedbutton remained -1, aka unpressed, there are several scenarios inside:
1) Millis() operation measures up until 5s have passed without a button being pressed (correctly, wrong input ends the game).
2) If the 5 seconds are exceeded, the game is over and restarts again with cleared RGB and no addition to score.
3) If a button is pressed, its value is saved to 'pressedbutton' which is later compared with the 'expectedbutton' variable. If it does not match, a failure is recorded and loop is broken. If it is correct, !failure is recorded and loop is ended.

With this recorded 'fail' value, the game outcome is decided with the help of a buzzer as follows:
A buzzer is also inserted for alerting the user of 3 scenarios:
1) User exceeds 5s to enter pattern using the buttons
   If that happens, the RGB clears out and the game starts over with the return command
   
  Game Results desplayed on Serial Monitor + Score along with:  
2) Letting out a long tone upon failure to enter right pattern
3) Letting out multiple short tones upon succes to enter right pattern


TinkerCad Simulation: https://www.tinkercad.com/things/lBPzs74HDK7-simon-game
Video: https://drive.google.com/file/d/1zMgsDUxCIWrNXhFw7u8QJdbyP1F9MZdV/view?usp=sharing
