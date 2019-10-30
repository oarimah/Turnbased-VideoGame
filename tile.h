#ifndef TILE_H
#define TILE_H

//will need to know which unit is occupying a given tile, so will need to include the unit.h file

//will also need to know about the graphics to determine what to render on each tile


class Tile {

	public:
		Tile(int x, int y);

		~Tile();

		void clearTile(Tile tile);



	private:
		int positionX, positionY;
		bool isOccupied;


}


#endif
