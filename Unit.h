#ifndef UNIT_H
#define UNIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ImageHandler.h"
#include <iostream>
#include "GameObject.h"
#include "SpecialAbilities.h"

class Unit: public GameObject {

private:
	SDL_Rect position;
	SDL_Texture* image;
	bool clicked;
	ImageHandler* imageHandler;
	int maxHealth;
	int curHealth;
	int offense;
	int defense;
	int numOfAttacksPerTurn;
	int numberOfAttacksForTurn;
	int rangeBegins;
	int rangeEnds;
	int maxSpeed;
	int curSpeed;
	bool used;
	SpecialAbilities* sa;
	std::string name;


public:
	Unit(int xPos, int yPos, int height, int width,
		 const std::string& imageFile, ImageHandler *imgHandler, int health,
		 int offense, int defense, int numOfAttacks, int rangeBegins,
		 int rangeEnds, int speed,SpecialAbilities* sa, std::string name);

	~Unit();
	const SDL_Rect* getPosition();
	void changePosition(int newX, int newY);
	const bool isClicked();
	void changeImage(const std::string& imageFile);
	void render();
	const std::string getType();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	void changeClicked(bool value);
	int getMaxHealth();
	int getCurHealth();
	void setHealth(int damage);
	int getAttack();
	int getDefense();
	int getMaxNumOfAttacks();
	int getCurNumOfAttacks();
	void attack();
	int getRangeBegins();
	int getRangeEnds();
	int getMaxSpeed();
	int getCurSpeed();
	void speedUsed(int speedUsed);
	bool isUsed();
	void reset();
	bool isDead();
	void activateAbility();
	const std::string getName();
	SpecialAbilities* getSpecAbil();
	void deactivateAbility();

};

#endif
