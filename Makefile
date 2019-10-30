COMP = g++
COMPFLAGS = -w
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

testgraphics: Main.o Button.o EraseButtonHandler.o InfoButtonHandler.o TextDisplay.o ImageHandler.o
	$(COMP) -o testgraphics Main.o Button.o EraseButtonHandler.o InfoButtonHandler.o TextDisplay.o ImageHandler.o $(COMPFLAGS) $(LIBS)   

Main.o: Main.cpp Button.h EraseButtonHandler.h InfoButtonHandler.h TextDisplay.h	
	$(COMP) -c Main.cpp $(COMPFLAGS) $(LIBS) 

Button.o: Button.cpp ImageHandler.h ButtonEventHandler.h GameObject.h
	$(COMP) -c Button.cpp $(COMPFLAGS) $(LIBS)

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

