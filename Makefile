SDL_FLAG=-lSDL2 -lSDL2_image

run: link
	./jogo

link: map.o game.o texman.o main.o
	g++ main.o game.o map.o texman.o $(SDL_FLAG) -o jogo

map.o: src/map.cpp
	g++ -o map.o -c src/map.cpp

game.o: src/game.cpp
	g++ -o game.o -c src/game.cpp

texman.o: src/TextureManager.cpp
	g++ -o texman.o -c src/TextureManager.cpp

main.o: src/main.cpp include/game.hpp include/map.hpp include/TextureManager.hpp
	g++ -o main.o -c src/main.cpp

clean: 
	rm -rf *.o jogo