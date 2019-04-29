CPPFLAGS=-Wall -g 
OBJECTS=main.o Menu.o Slider.o Button.o   Engine.o  Game.o 

.GP: all
all: Jihyo

Jihyo: $(OBJECTS)
	g++ $(CPPFLAGS) *.o -o Jihyo -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lSDL2main -lSDL2 

main.o: main.cpp
	g++ -c $(CPPFLAGS) main.cpp

Menu.o: Menu.cpp
	g++ -c $(CPPFLAGS) Menu.cpp

Slider.o: Slider.cpp
	g++ -c $(CPPFLAGS) Slider.cpp

Button.o: Button.cpp
	g++ -c $(CPPFLAGS) Button.cpp

Engine.o: Engine.cpp
	g++ -c $(CPPFLAGS) Engine.cpp

Game.o: Game.cpp
	g++ -c $(CPPFLAGS) Game.cpp

run: Jihyo
	rm *.o && ./Jihyo