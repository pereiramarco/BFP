SDL_FLAG=-lSDL2 -lSDL2_image

run: link
	./jogo

link: texman.o map.o menu.o object.o game.o main.o
	g++ texman.o map.o menu.o object.o game.o main.o $(SDL_FLAG) -o jogo

texman.o: src/TextureManager.cpp
	g++ -o texman.o -c src/TextureManager.cpp

map.o: src/map.cpp
	g++ -o map.o -c src/map.cpp

menu.o: src/GameMenu.cpp
	g++ -o menu.o -c src/GameMenu.cpp

object.o: src/GameObject.cpp
	g++ -o object.o -c src/GameObject.cpp

game.o: src/game.cpp
	g++ -o game.o -c src/game.cpp

main.o: src/main.cpp include/game.hpp include/map.hpp include/TextureManager.hpp
	g++ -o main.o -c src/main.cpp

clean: 
	rm -rf *.o jogo