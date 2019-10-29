Student: Henry Van Horik
Student Number: 0966956
Course: INFO6019 - Physics and simulation
Project: MidTerm 2019

I tried to record a video but for some reason OBS is not cooperating.

To build:
	Select Release/x64 target
	right click on project "Master" and hit build

 I have placed searches in the code so you can track down examples for what I am discussing

 Select Search: 
	 Enter the project code. "INFO6019"
	 Pulldown "Entire Solution"
	 Pulldown "Find All"
		- This will find all references to the code that is implmenting specific stuff

Keyboard commands:

X / Shift - X		- Adjust camera in the +/- X position
Y / Shift - Y		- Adjust camera in the +/- Y position
Z / Shift - Z		- Adjust camera in the +/- Z position
L - Turn on/off Laser.

I completed secions 1-4 and made an attempt at #5
It will not shoot astroids outside of the spacestation bounding box
My attempt was to create a two diminsional representation of all of the co-ordinates in the Y/Z plane. 
the velocity X is only on X.
I created a vector of bools in a two dimentional array so that it could just check the array to see if
the objects position overlaps on the Y/Z
It failed and I didn't have time to fix it.
This was similar to the bounding boxes you were just discussing in class.