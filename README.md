# Mario-Clone-With-Editor

This is an old project I began working on in 2013/2014 and was later presented as part of my "Matura exam" at ERSŠG (http://www.vegova.si/). 

Later the game was expanded and featured in the schoold presentations at the "Informativa" event. Game has not been updated since then (end of January 2015).

# What is this?

This is a Mario-style game with a working real-time map editor. You can play the game while creating the level at the same time. You can then export your level and load it back later.

It began as a Mario game only, until I hit a major problem - who is going to create the maps? Well, I though hardcoding the maps in the code or a file is too clunky so I made an editor on top of the existing "game".

Made with C++ using SFML graphics library (https://www.sfml-dev.org/) and Qt IDE + forms (https://www.qt.io/).

# Structure

This repository is consists of two folders:
* Code - all the game code + scoreboard built for the Informative event (in Slovenian)
* Executable - out of the box working .exe of the game and the scoreboard; tested in Windows10 x64.

There are 3 executables:
* Mario.exe - main game with editor
* Mario_noSelection.exe - main game with editor; map editiong not possible, use this if you encounter any bugs in the normal version
* Scoreboard.exe - a simple widget for displaying highscores writter in scores.txt file (in Slovenian)

# Features

### Gameplay features:
* The current goal is to collect as many coins as possible without dying and finding the exit in the given time limit. 
* Movement: left, right, jump
* Enemies move in a predetermined way, can be killed by jumping on them, player dies if hit from the side
* 3 lives, upon death you respawn at the start of the level

### Editor features:
* Loading/Exporting maps
* Real-time adding tiles, enemies, coins and exit(s)
* Can select an entity, monitor or change its position or delete it
* Score tracking and exporting to a file (display scores with Scoreboard.exe)
* Allows immediate restart of current level
* Option to set the time limit and map width

# Usage

This is still a really development version of the game/editor, but it should not crash or bug out if you follow these guidelines.

Upon running the game 3 windows will open: console windows (which was used for debug), editor window (form), and a black window. *NEVER CLOSE ANY OF THEM*. 

To start playing, go to the editor window, Import/Export tab, click Refresh and select the desired map. Before importing make sure you have typed your name in the "Player name" box. Upon Importing, the black window will prompt you to press SPACE to begin playing. The "Restart" button in the editor restarts the map, while "Clean" will unload it, turning the screen black again.

To add new things to the map got to the first tab, click the refresh button and select the entity you wish to add, click "Add" and move your cursor over the map. A preview of the entity will follow your cursor. Confirm placement with left mouse click. The placement system works on a grid which you can also enable on this tab.

To select an entity go to the "Selection" (2nd tab) and click "Enable selection mode". Outline determines how the selection border will be displayed. You can now click on any entity in the map and change it's position with the "Entity position" controls on the same tab. You can also delete the entity or check the "Real-time" checkbox to monitor enetity position.

To export the map go to the "Import/Export" tab, type your map name and click export.

You can also put your own textures in the game. Simply put the corrsponding picture in the "res/Textures" folder and name it appropriately ("[TYPE]_myEntity.png").

# Notes

Placing an enemy: Click to set start position and another click to set "patrol waypoint" - enemy will then continiously travel between start point and the waypoint.

Placing coins: First dropdown determines how many coins you want to play in succession - this is to avoid constant siwtching between editior and the game window when placing lots of coins.

Maps are exported in roughly this format:
* 0 PLAYERX PLAYERY MAP_WIDTH  // First line
* TYPE(number) TEXTURE POSITIONX POSITIONY // Other lines
