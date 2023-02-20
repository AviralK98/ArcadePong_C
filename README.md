# ELEC5620M Mini-Project Repository

# ARCADE: TENNIS


# Introduction:-

The duties performed by the DE1-SoC board are handled by the ARM cortex A-9 processor, a 32-bit CPU. This is a fantastic solution for any design that needs exceptional performance in a low-power, cost-sensitive, single processor-based device, such as a mobile phone or tablet. Using the board and LCD screen, a mini-project was presented to help students learn about the basics of embedded systems processing and design. The subject of this mini-project is the arcade tennis game, which highlights the vintage concept while also actively demonstrating the usage of the graphics driver as well as the drivers that are responsible for creating the sound in real-time. 

In order to grasp the project's vast code, which includes IP blocks, blocking and non-blocking parameters, it is best to begin by comprehending the code's flow. The main points of the code are as follows: 

3.1.	When the code is loaded into the board using the debugger, the display drivers configure the LCD screen that will display the following text with a cyan background ‘DE1-SoC Arcade/ ELEC- 5620M’.
3.2.	The introduction screen pauses for a 2 second time interval and the display driver functions are called again and the ‘OPTIONS’ sprites are displayed on the LCD.
3.3.	The options screen is an interactive screen which was achieved using the help of the key and switches. By pressing these keys, the desired option from the ‘Options’ menu can be selected.
3.4.	After selecting ‘Start’, the functions consisting of the game graphics and game physics are called along with the sound drivers and the screen visually transits to the in-game screen, where the rackets are displayed as ‘bars’, a ‘ball’ and the score is displayed using the seven-segment display of the board.
3.5.	In order to go back to the options screen, a switch can be used. From here on a player can reset the score back to zero or continue with the same score.

# VIDEO: -


https://user-images.githubusercontent.com/99490543/168175067-0383d3fb-e91c-446c-8d04-6fe0cd2699ad.mp4



https://user-images.githubusercontent.com/99490543/168175080-4f29f55e-03ff-417b-945a-ee080fd45035.mp4



https://user-images.githubusercontent.com/99490543/168175100-5edc6660-0e29-41fc-bd3d-46f2f8a37b2d.mp4


