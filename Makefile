SDL_FLAG=-lSDL2 -lSDL2_image

run: link
	./jogo

link: map.o game.o main.o
	g++ main.o game.o map.o $(SDL_FLAG) -o jogo

map.o: src/map.cpp
	g++ -o map.o -c src/map.cpp

game.o: src/game.cpp
	g++ -o game.o -c src/game.cpp

main.o: src/main.cpp include/game.hpp include/map.hpp
	g++ -o main.o -c src/main.cpp

clean: 
	rm -rf *.o jogo