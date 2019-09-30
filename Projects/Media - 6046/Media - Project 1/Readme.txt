
Here are the available keyboard commands:
  (space) or (tab) - Move between speakers or people
     u/d             - volume up/down by 5%
     i/o             - pitch up/down by 5%
     b/v             - balance left/right by .05
                        *** NOTE - Pan does not work in speaker mode
     0, 1, 2, 3, 4   - Get a response from active person
     r               - replay track
     ?               - Information on current track
Character interactions: (Case sensitive)
     S               - Seduce
     J               - Tell Joke
     W               - Go for a walk
     D               - Walk the dog
     M               - Watch Monty Python
     (esc)           - To Exit

	 1) There are 4 music assets that can be played. Tab or space between them.
	 2) There are people in the game (An old Man and two old women). You scan their dialogs via the space bar followed by the
	     number keys.
     3) There is an XML file called GameLibary.xml which controls all of the files to input into the game. If you edit the file the
	    program will probably crash since I did not do extensive error checking.
	 3a) This will be my generic asset handler 
     4) On startup you can select between raw(.wav) files or mpeg files.
	 5) I've added a bunch of extra controls for the files. the Balance/Pan did not work on my system.
	 6) All of the Audio controls are in the file "cAudioAssetManager.cpp" - they belong in "cAudioObjectManager.cpp" but
	    I did not have time to move them.
     7) The game is based on the old game "Doom", but far in the future when all of the characters have aged. So it's in a 
	    nursing home. It is my plan to actually implement this and have all of the characters well aged and moving with walkers
		and wheelchairs. Everything in slow motion and have them struggling to handle the weapons. I figure I'm the senior of the
		class so this seems apropo.
      8) so the simulation is very primitive
	  9) No openGL - didn't have the time. I've been busy working on the Asset and Object manager so I can connect up all
	     of the objects, audio and lights in the game.
	  10) I borrowed some of your code and didn't have time to refactor it into proper classes. 
	  11) It works for all targets including x64


