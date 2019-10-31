
#ifndef UNIT_H
#define UNIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ImageHandler.h"
#include <iostream>
#include "GameObject.h"

class Unit: public GameObject{

    private:
        SDL_Rect position;
        SDL_Texture* image;
        bool clicked;
        ImageHandler* imageHandler;
        int health;
        int offense;
        int defense;
        int numOfAttacks;
        int rangeBegins;
        int rangeEnds;
        int speed;

    public:
        Unit(int xPos, int yPos, int height, int width, const std::string& imageFile, ImageHandler *imgHandler, int health, int offense, int defense, int numOfAttacks, int rangeBegins, int rangeEnds, int speed); 
        ~Unit();
        const SDL_Rect* getPosition();
        void changePosition(int newX, int newY);
        const bool isClicked();
        void changeImage(const std::string& imageFile);
        void render();
        const std::string getType();
        void changeClicked(bool value);
        int getHealth();
        void setHealth(int damage); 
        int getAttack();
        int getDefense();
        int getNumOfAttacks();
        int getRangeBegins();
        int getRangeEnds();
        int getSpeed();
        bool isDead();
};

#endif

