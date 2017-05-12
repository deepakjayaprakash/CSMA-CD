# CSMA-CD

The project **Carrier Sense Multiple Access with Collision Detection** is a software implementation and show collision detection between any of the station using a common channel to send and receive data through the **Data Link Layer** of the Internet Model. 

This program follows a typical approach to the detect collision, with the Sender uses *non-persistent* method in which,
a station that has a frame to send senses the line. If the line is idle, it sends immediately .If the line is not idle,
it waits for random amount of time and then senses the line again.


## About the code

- The program includes the usual functions of the data link layer like collision, back off time, getting data and making a frame and sending data to the receiving station. 

- The program is designed to **graphically visualize** the sending data and the collision detection. 
- This program is designed such that the user can simulate all the things that can occur while transferring a frame and once a collision is detected the station again retransmits the data using back off time.
- The program is designed such that it is like an interaction between the user and computer. The user has to give the required 
input when prompted by the program. 
- Then the complete **simulation module** takes over including the graphics part in which a typical
sending receiving is accompanied by collision detection. 
