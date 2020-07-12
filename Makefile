SDL_FLAG=-lSDL2 -lSDL2_image
COMPONENTS = include/ECS/ECS.hpp include/ECS/Components.hpp include/ECS/TransformComponent.hpp include/ECS/SpriteComponent.hpp include/ECS/KeyboardController.hpp

all: link

run: link
	./jogo

link: texman.o vec2d.o assetman.o ECS.o lmap.o map.o game.o main.o
	g++ main.o lmap.o map.o game.o vec2d.o ECS.o texman.o assetman.o $(SDL_FLAG) -o jogo

ECS.o: include/ECS/ECS.hpp
	g++ -o ECS.o -c src/ECS/ECS.cpp

vec2d.o: include/Vector2D.hpp
	g++ -o vec2d.o -c src/Vector2D.cpp

texman.o: include/TextureManager.hpp include/Game.hpp
	g++ -o texman.o -c src/TextureManager.cpp

assetman.o: include/AssetManager.hpp
	g++ -o assetman.o -c src/AssetManager.cpp

map.o: include/Map.hpp include/TextureManager.hpp include/LocalMap.hpp
	g++ -o map.o -c src/Map.cpp

lmap.o: include/LocalMap.hpp include/TextureManager.hpp
	g++ -o lmap.o -c src/LocalMap.cpp

game.o: include/Game.hpp include/ECS/Components.hpp
	g++ -o game.o -c src/Game.cpp

main.o: include/Game.hpp $(COMPONENTS)
	g++ -o main.o -c src/main.cpp

clean: 
	rm -rf *.o jogo