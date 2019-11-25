COMP = g++
COMPFLAGS = -w
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

game: Main.o Button.o Game.o Tile.o backgroundMap.o foregroundMap.o Player.o Unit.o EraseButtonHandler.o InfoButtonHandler.o TextDisplay.o ControlPoint.o ImageHandler.o UnitFactory.o 
	$(COMP) -o game Main.o Button.o Game.o Tile.o backgroundMap.o foregroundMap.o Player.o Unit.o EraseButtonHandler.o InfoButtonHandler.o TextDisplay.o ControlPoint.o ImageHandler.o UnitFactory.o $(COMPFLAGS) $(LIBS)   

Main.o: Main.cpp Game.h Button.h EraseButtonHandler.h InfoButtonHandler.h TextDisplay.h	
	$(COMP) -c Main.cpp $(COMPFLAGS) $(LIBS) 

Button.o: Button.cpp ImageHandler.h ButtonEventHandler.h GameObject.h
	$(COMP) -c Button.cpp $(COMPFLAGS) $(LIBS)

Game.o: Game.cpp ImageHandler.h Player.h TextDisplay.h InfoButtonHandler.h backgroundMap.h foregroundMap.h Button.h 
	$(COMP) -c Game.cpp $(COMPFLAGS) $(LIBS)

Tile.o: Tile.cpp ImageHandler.h GameObject.h
	$(COMP) -c Tile.cpp $(COMPFLAGS) $(LIBS)

backgroundMap.o: backgroundMap.cpp ImageHandler.h GameObject.h Tile.h
	$(COMP) -c backgroundMap.cpp $(COMPFLAGS) $(LIBS)

foregroundMap.o: foregroundMap.cpp ImageHandler.h Tile.h Unit.h TextDisplay.h Player.h
	$(COMP) -c foregroundMap.cpp $(COMPFLAGS) $(LIBS)

Player.o: Player.cpp UnitFactory.h Unit.h ControlPoint.h
	$(COMP) -c Player.cpp $(COMPFLAGS) $(LIBS)

ControlPoint.o: ControlPoint.cpp Player.h GameObject.h ImageHandler.h
	$(COMP) -c ControlPoint.cpp $(COMPFLAGS) $(LIBS)

UnitFactory.o: UnitFactory.cpp UnitFactory.h
	$(COMP) -c UnitFactory.cpp $(COMPFLAGS) $(LIBS)

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
	rm game *.o

