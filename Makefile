SDL_FLAG=-lSDL2 -lSDL2_image
COMPONENTS = include/ECS/ECS.hpp include/ECS/Components.hpp include/ECS/PositionComponent.hpp include/ECS/SpeedComponent.hpp include/ECS/SpriteComponent.hpp

run: link
	./jogo

link: texman.o map.o menu.o object.o game.o main.o
	g++ main.o map.o menu.o object.o game.o texman.o $(SDL_FLAG) -o jogo

texman.o: src/TextureManager.cpp include/TextureManager.hpp
	g++ -o texman.o -c src/TextureManager.cpp

map.o: src/Map.cpp include/Map.hpp include/TextureManager.hpp src/TextureManager.cpp
	g++ -o map.o -c src/Map.cpp

menu.o: src/GameMenu.cpp include/GameMenu.hpp include/TextureManager.hpp texman.o
	g++ -o menu.o -c src/GameMenu.cpp

object.o: src/GameObject.cpp include/GameObject.hpp include/TextureManager.hpp texman.o
	g++ -o object.o -c src/GameObject.cpp

game.o: src/Game.cpp include/Game.hpp
	g++ -o game.o -c src/Game.cpp

main.o: src/main.cpp include/Game.hpp $(COMPONENTS)
	g++ -o main.o -c src/main.cpp

clean: 
	rm -rf *.o jogo