Student: Henry Van Horik
Student Number: 0966956
Course: INFO6044 - Framworks & Patterns
Project: MidTerm 2019


To build:
Select Release/x64 target
right click on project "Master" and hit build

I have placed searches in the code so you can track down examples for what I am discussing

Select Search: 
Enter the project code. INFO6044 
Pulldown "Entire Solution"
Pulldown "Find All"
- This will find all references to the code that is implementing specific stuff

Keyboard commands:

X / Shift - X - Adjust camera in the +/- X position
Y / Shift - Y - Adjust camera in the +/- Y position
Z / Shift - Z - Adjust camera in the +/- Z position


I did NOT do any of the physics or most of the special effets. I just hacked around it. Frankly, IMHO it was way
to much for a framworks project. I wasted way too much time f..king around with it and right when I saw your email, it 
angered me. This should have been a simple project.

static bool RobotInSight(const glm::vec3& me, const glm::vec3& them)
{
	// Hack for robot on sight. Just do a random number
	return (randInRange(0, 5) == 0);
}

I also hacked the balistics

 glm::vec3 aHitter(const glm::vec3 target, float damageRadius)
{
	 float farRadius = damageRadius + 1;
	 float randomx = randInRange(-farRadius, +farRadius);
	 float randomz = randInRange(-farRadius, +farRadius);
	 glm::vec3 where = target;
	 where.x += randomx;
	 where.z += randomz;
	 return where;
 }

and I hacked the targeting (lines/balls travelling)

		//   INFO6028 - Hack the flight of balistics
		glm::vec3 colour(1.0f, 1.0f, 0.0f);
		glm::vec3 start = source;
		glm::vec3 end = target;
		start.y += 5;
		end.y += 5;
		gDebugRenderer->addLine(start, end, colour, 1.5f);
