# Galactic Empires 2
Galactic Empires

## How to Play
Your world has finally obtained interstellar travel and it is now time to spread your culture and ways, by force if necessary.

You must travel the galaxy and conquer all known worlds in the star map, currently under the control of the mysterious empire known only as 65535. Upon sending your fleet to each world a battle will ensue to determine who controls that world afterwards. There is no element of surprise, so the defending fleet always attacks first! Each world can build ships for the protecting fleet, which means your enemy will be building ships as well. 

## Player Commands
H: Prints the help message, listing all available commands in the game

M: Display the world map

S: Display known controlled worlds

C: Create mission. The mission sub-menu will walk you through creating a diplomatic mission to take over another world


## TODO:

* Reinforcements: Ships sent to a world already owned by the player will not have the fleets merged, and will likely result in the traveling fleet being lost forever. 
* Multi-player:	The game only assumes there is one player, need to allow for multiple players to join
* Internet Multi-Player: The multi-player system should just buffer all of the needed commands for all of the players, which should enable network play pretty easily. Still need to implement sockets in the game and a proper data exchange system. Maybe copy [Space Shuttle](https://history.nasa.gov/computers/Ch4-4.html) method?
* Graphics: Everything is text based right now, should really make this with graphics
