COMP = g++
COMPFLAGS = -w
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

testgraphics: Main.o Button.o EraseButtonHandler.o InfoButtonHandler.o TextDisplay.o ImageHandler.o
	$ (COMP) Main.o Button.o EraseButtonHandler.o InfoButtonHandler.o TextDisplay.o ImageHandler.o $ (COMPFLAGS) $ (LIBS) -o testgraphics  

Main.o: Main.cpp Button.h ContinueHandler.h EraseButtonHandler.h InfoButtonHandler.h SelectButtonHandler.h TextDisplay.h	
	$ (COMP) Main.cpp $ (COMPFLAGS) $ (LIBS) -c Main.o

Button.o: Button.cpp ImageHandler.h ButtonEventHandler.h GameObject.h
	$ (COMP) Button.cpp $ (COMPFLAGS) $ (LIBS) -c Button.o

EraseButtonHandler.o: EraseButtonHandler.cpp ButtonEventHandler.h GameObject.h
	$ (COMP) EraseButtonHandler.cpp $ (COMPFLAGS) $ (LIBS) -c EraseButtonHandler.o

InfoButtonHandler.o: InfoButtonHandler.cpp ButtonEventHandler.h TextDisplay.h
	$ (COMP) InfoButtonHandler.cpp $ (COMPFLAGS) $ (LIBS) -c InfoButtonHandler.o

TextDisplay.o: TextDisplay.cpp ImageHandler.h
	$ (COMP) TextDisplay.cpp $ (COMPFLAGS) $ (LIBS) -c TextDisplay.o

ImageHandler.o: ImageHandler.cpp 
	$ (COMP) ImageHandler.cpp $ (COMPFLAGS) $ (LIBS) -c ImageHandler.o


