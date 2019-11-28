#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <string>


/**@brief Template for generic game object parent class
@author Carolyn Owen
details This class defines required functions for all subclasses of game objects. All must be able to render and return their type.
	
*/
class GameObject {

	virtual void render() = 0;
	virtual const std::string getType() = 0;

};

#endif