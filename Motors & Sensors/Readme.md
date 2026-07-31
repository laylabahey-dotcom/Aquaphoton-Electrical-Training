
**TASK 1** 
**Theory Questions**
Question 1) brushed DC Motor vs brushless DC motor
Brushed motors are cost-efficient, easily controlled and have a linear speed-torque relationship, which is why they are used in applications that require high peak torques and run using simple speed controllers. Yet, their mechanical operation has the drawback of wear and tear of the brushes and commutator leading to a shorter lifespan. Their uses are mainly home appliances such as mixers. In a bigger scale they are used in electrical propulsion, cranes, paper machines and steel rolling mills.

On the other hand, brushless DC motors are electronically commutated motors, improving upon brushed motors in life-span due to lack of wear and tear as well higher efficiency and quieter operations. Because of that they are employed in drones, cordless power tools, electric vehicles, and industrial automation robots.
So, based on previous explanation, brushed DC motors should be used in low-cost, academic projects due to low cost, easy wiring and no need for an additional speed control board. Brushless motors will then be used in bigger, costlier projects where brushes don't wear out with time and motor runs colder and faster and battery power is distributed well.

Question 2)
Motor encoders are rotary encoders adapted to provide information about an electric motor shaft's speed and/or position. They are not motors, they are feedback sensor that is attached to the shaft of a motor and is used in a control loop to inform of what the motor is actually doing. They are the 'eyes' of a closed loop which are used to provide feedback to achieve precise control.

Servo motors a highly specialized rotational or translational motor designed for precise control of rotary or linear motion. It employs a feedback mechanism to ensure exact positioning, and paired with an encoder and a control system, it would form a closed loop. It is used for precision objects like robotic arms and pick and place systems.

Stepper motors are a brushless DC motor that rotates in a series of small and discrete angular steps. They can be set to any given step position without needing a position sensor for feedback, so it operates on an open loop control system because each step ooperates on a known angular value. Applications include needing precise, repeatable positioning at low-to-moderate speed with predictable, known loads like 3D printers.

Question 3)
We discussed UARTs first which are asynchronous communication protocols which rely on pre-agreed upon rate of transmission of information, baud rates like 9600 or 115200, so both chips know at which rate to sample. UARTs lack the slave-master protocol that is found in synchronous communication protocols like SPIs and I2Cs, so both chips can receive and transmit at the same time out of their own volition. They are best used if only 2 chips are needed or for debugging because of their parity bits in their data transmission protocol, seeing as wiring any more than 2 causes congestion of the transmission lines and errors down the line. 

SPIs are synchronous and have the master-slave configuration where one master chip can coordinate the communication between several other slave chips. Their pros are that they are very quick. But the drawbacks are that every master-slave pair requires their own select line wiring and that could quickly get messy. They could be used in small quantities so that the wiring doesn't become an issue.

I2Cs are synchronous and have the master-slave protocol but they are different from SPIs because they have only 2 wires for everything. The SDA(data line) and SCL(clock line) connect a master to many slaves. I2Cs have an address protocol where every slave chip has an address the master slave can call upn (2^7 = 128, max possible addresses). Despite so much more efficient, I2Cs are slower than SPIs because their Writing/Reading Transaction is a lengthy process due to the address protocol. They are best used for PCB routing or big projects.

**TASK 2**
**Automated Window Shutter**

TinkerCad link: https://www.tinkercad.com/things/4P4zIkvjSQ9-servo-temp-light/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fcircuits

_Slave Chip Code_
Temperature Sensor: 
The temperature readings and execution is exclusively shown in the slave chip Arduino and is not at all part of the I2C protocol. The temperature is read  by temperature sensor TMP36 and then classified into ranges of cold-medium-hot. Each range has a designated LED and a serial monitor message. When this range is entered, the respective LED blinks at user. 

To get the light intensity, the analogRead() function was used on a photoresistor which has an increasing value with increasing brightness. Since the range of light intensity's range of 0-1023 can come to 2 bytes, the light_reading had to be minced into 2 separate bytes and sent in an array across to the master chip over the SDA.

_Master Chip Code_
All the master chip has to do is receive the two bytes sent by the slave chip and concatenate the values back into one, the light value. After that is done, the light value is multiplied by ratio 180.0/1023.0 that results in a manageable angle for the servomotor which is then reflected in servo fan. Like that, the window shutter closed with increased and opens with decreased light intensity.

Challenges: determining how to send data that is bigger than 1 byte. Solution:  https://forum.arduino.cc/t/i2c-for-value-255/342527
<img width="1486" height="651" alt="Servo - Temp - Light" src="https://github.com/user-attachments/assets/aff1e1d9-abaa-4f58-b863-2b34add1b47a" />



Attempted Bonus: DC MOTOR - unsuccessful, did not have time to really look into encoder today.
(may finish later, if possible)
TinkerCad link: https://www.tinkercad.com/things/9ppvjDCJCa7-dc-motor-bonus/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fcircuits

The slave chip operates exactly the same as with a servo motor, its only the master chip that is changed. I managed to make a range that default sets to specified positions but could not find a way to determine the current position of the motor and how to set it to the position it gauged from the lightvalue.
<img width="1486" height="651" alt="DC Motor Bonus" src="https://github.com/user-attachments/assets/7d8fa17e-1674-422e-bcb3-c1ecd8330e5e" />
