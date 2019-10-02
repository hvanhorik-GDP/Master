INFO-6025-01-19F - Project 2 
Author: Henry Van Horik
Student Number: 0966956

Solution name: Project2
Target solution: Project2
Target selection: Any Debug/Release x64 (x86 has issues due to rapidxml project errors that I need to fix)

Data input: gamedata.xml (is overwritten on exit/end)
Data backup: gamedata_backup.xml (start xml file saved to backup)

Valid Commands are:
     help - This message
     language - Set Language to {Value}
     hit - Hit Player {Player}						- Only player name is henry
     info - Get information on player {player}		- Only player name is henry
     talk - Say something profane
     end - End Game

Valid Languages are: english, french, pig, spanish, yoda

What is does based on the project specifications:

Creates xml with 20+ settings
Reads and displays the xml
loads 4+ languages
Allows the user to select the language
Saves language selection to the xml file for the next startup
Bonus - single file with languages

XML file format:
	<Player name="henry">
		<Property id="1" name="Player" value="Henry Van Horik"/>

Note - the id of the entry is used for translation purposes

	<Language name="english">
		<Translation id="1" name="Player Name"/>
	<Language name="french">
		<Translation id="1" name="Nom de joueur"/>

All strings used in the application are looked up via the id="nn"
if it can't find the string in the language it uses the english version
if it also can't find the english version it defaults to an error message

Bugs - There are probably issues if the xml has been manually edited and is corrupted. I didn't test all of these
senarios

Issues - rapidxml does not store strings passed into it when you set a value or create a new pool. I used the internal
pool avaiable from the xml_document<>

Wasted huge amounts of time trying to get the windows console to print french characters. "Capacités maximales"
Every suggestion i found online failed. Piece of junk.
	