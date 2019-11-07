COMP = g++
COMPFLAGS = -w
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

testgraphics: Main.o Button.o Game.o Tile.o backgroundMap.o Player.o Unit.o EraseButtonHandler.o InfoButtonHandler.o TextDisplay.o ImageHandler.o
	$(COMP) -o testgraphics Main.o Button.o Game.o Tile.o backgroundMap.o Player.o Unit.o EraseButtonHandler.o InfoButtonHandler.o TextDisplay.o ImageHandler.o $(COMPFLAGS) $(LIBS)   

Main.o: Main.cpp Button.h EraseButtonHandler.h InfoButtonHandler.h TextDisplay.h	
	$(COMP) -c Main.cpp $(COMPFLAGS) $(LIBS) 

Button.o: Button.cpp ImageHandler.h ButtonEventHandler.h GameObject.h
	$(COMP) -c Button.cpp $(COMPFLAGS) $(LIBS)

Game.o: Game.cpp ImageHandler.h ButtonEventHandler.h GameObject.h
	$(COMP) -c Game.cpp $(COMPFLAGS) $(LIBS)

Tile.o: Tile.cpp ImageHandler.h GameObject.h
	$(COMP) -c Tile.cpp $(COMPFLAGS) $(LIBS)

backgroundMap.o: backgroundMap.cpp ImageHandler.h GameObject.h
	$(COMP) -c backgroundMap.cpp $(COMPFLAGS) $(LIBS)

Player.o: Player.cpp Unit.h ImageHandler.h GameObject.h
	$(COMP) -c Player.cpp $(COMPFLAGS) $(LIBS)

Unit.o: Unit.cpp ImageHandler.h GameObject.h
	$(COMP) -c Unit.cpp $(COMPFLAGS) $(LIBS)

EraseButtonHandler.o: EraseButtonHandler.cpp ButtonEventHandler.h GameObject.h
	$(COMP) -c EraseButtonHandler.cpp $(COMPFLAGS) $(LIBS) 

InfoButtonHandler.o: InfoButtonHandler.cpp ButtonEventHandler.h TextDisplay.h
	$(COMP) -c InfoButtonHandler.cpp $(COMPFLAGS) $(LIBS) 

TextDisplay.o: TextDisplay.cpp ImageHandler.h
	$(COMP) -c TextDisplay.cpp $(COMPFLAGS) $(LIBS) 

ImageHandler.o: ImageHandler.cpp 
	$(COMP) -c ImageHandler.cpp $(COMPFLAGS) $(LIBS) 

clean: 
	rm testgraphics *.o

