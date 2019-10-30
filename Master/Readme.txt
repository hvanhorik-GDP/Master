Student: Henry Van Horik
Student Number: 0966956
Course: INFO6019 - Physics and simulation
Project: MidTerm 2019

I tried to record a video but for some reason, OBS is not cooperating.

To build:
Select Release/x64 target
right click on project "Master" and hit build

I have placed searches in the code so you can track down examples for what I am discussing

Select Search: 
Enter the project code. "INFO6019"
Pulldown "Entire Solution"
Pulldown "Find All"
- This will find all references to the code that is implementing specific stuff

Keyboard commands:

X / Shift - X - Adjust camera in the +/- X position
Y / Shift - Y - Adjust camera in the +/- Y position
Z / Shift - Z - Adjust camera in the +/- Z position
L - Turn on/off Laser.

I completed sections 1-4 and made an attempt at #5
It will not shoot asteroids outside of the space station bounding box
My attempt was to create a two-dimensional representation of all of the co-ordinates in the Y/Z plane. 
the velocity X is only on X.
I created a vector of bools in a two-dimensional array so that it could just check the array to see if
the object's position overlaps on the Y/Z
It failed and I didn't have time to fix it.
This was similar to the bounding boxes you were just discussing in class.

I noticed in your notes that you do not allow "auto" for midterms, but this was not stated for the initial projects. I use
auto a lot, (welcome to RSI where you need to minimize typing). There is no way I can undo all of the changes. All of my projects are set to use: ISO C++17 Standard (std:c++17) so there should be no problems with compilation.

We're almost at 2020. I think it's time to ring in the 2011 specs.

for (auto itMap : myMap)
{ }
vs.
for (std::map<std::string, std::string>::iterator itMap = myMap.begin();
itMap != myMap.end(); // 1 past the end of the vector
itMap++, )
{
}