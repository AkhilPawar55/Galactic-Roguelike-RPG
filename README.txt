  ________    _____  .____       _____  ____________________.____________  
 /  _____/   /  _  \ |    |     /  _  \ \_   ___ \__    ___/|   \_   ___ \ 
/   \  ___  /  /_\  \|    |    /  /_\  \/    \  \/ |    |   |   /    \  \/ 
\    \_\  \/    |    \    |___/    |    \     \____|    |   |   \     \____
 \______  /\____|__  /_______ \____|__  /\______  /|____|   |___|\______  /
        \/         \/        \/       \/        \/                      \/ 
                                                                           

------------------------------------------------------------------------
			INTRODUCTION
------------------------------------------------------------------------
Space themed RPG. Players goal is to destroy as many aliens as possible to protect his spacestation.
-------------------------------------------------------------------------
			CONTROLS
-------------------------------------------------------------------------
KEYBOARD:
Left, Right, Up, Down		- walk, navigate through space
g				- pick up items
i				- display inventory
s 				- output info.

Player performs a melee attack by standing next to the enemy and pressing an arrow key in the direction of the enemy.
Blue rectangle healing area in the center heals the player by one health point every time he moves on it.

Pickups:
Healing potion - heals player.
Air strike - attack closest player within specified radius.

--------------------------------------------------------------------------
			INSTALLATION
--------------------------------------------------------------------------
1) Download and install Microsoft Visual Studio 2015 Enterprise.
2) Download libtcod. The libtcod folder is already added in the project folder.
3) Unzip libtcod to a directory.

4) Open the project in Visual Studio 2015 Eneterprise.
5) Go to Project > Properties > Configuration Properties > VC++ Directories and 
add the following folders that are inside of the unzipped libtcod folder:


Include Directories: add the "include" folder
Library Directories: add the "lib" folder
Source Directories: add the "source" folder
In each case, to add a directory, click inside of the textbox to the right of 
the label, click the down arrow, and click <Edit...>. Then double click near 
the top of the whitespace and your cursor should be inside a textbox, click the
button that appeared to the right of the text box with an ellipse (...) as the 
text. This should open a folder browser dialog in which you can now browse to 
the appropriate folder to add.

6) Under Project > Properties > Configuration Properties > Linker > Input add 
libtcod-VS.lib under "Additional Dependencies".

7) Copy libtcod-VS.dll, SDL.dll, and terminal.png from the unzipped libtcod 
folder to the "Debug" folder in your project's root directory (i.e. the 
directory in windows explorer, this is not done through Visual Studio).

8) Under Project > Properties > Configuration Properties > Linker > General add the "lib" 
and root folder of the unzipped libtcod directory to "Additional Library 
Directories".

9) Under Project > Properties > Configuration Properties > Debugging change the 
"Working Directory" to the "Debug" folder in the root folder of your visual 
studio project.

