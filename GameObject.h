#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <string>

class GameObject {

	virtual void render() = 0;
	virtual const std::string getType() = 0;

};

#endif