SDL_FLAG=-lSDL2 -lSDL2_image
COMPONENTS = include/ECS/ECS.hpp include/ECS/Components.hpp include/ECS/TransformComponent.hpp include/ECS/SpriteComponent.hpp include/ECS/KeyboardController.hpp include/ECS/FollowPlayerComponent.hpp

all: link

run: link
	./jogo

link: texman.o vec2d.o assetman.o ECS.o dungeons.o settlements.o lmap.o map.o gamelevelmenu.o gamelevelingame.o gamelevelworld.o gamelevel.o gamedata.o gameengine.o main.o
	g++ -Wall main.o dungeons.o settlements.o lmap.o map.o gameengine.o gamelevelmenu.o gamelevelingame.o gamelevelworld.o gamelevel.o gamedata.o vec2d.o ECS.o texman.o assetman.o $(SDL_FLAG) -o jogo

ECS.o: include/ECS/ECS.hpp
	g++ -o ECS.o -c -g -Wall src/ECS/ECS.cpp

vec2d.o: include/Vector2D.hpp
	g++ -o vec2d.o -c -g -Wall src/Vector2D.cpp

texman.o: include/TextureManager.hpp include/GameData.hpp
	g++ -o texman.o -c -g -Wall src/TextureManager.cpp

assetman.o: include/AssetManager.hpp
	g++ -o assetman.o -c -g -Wall src/AssetManager.cpp

map.o: include/Map.hpp include/TextureManager.hpp include/LocalMap.hpp include/ConstantValues.hpp
	g++ -o map.o -c -Wall -g src/Map.cpp

lmap.o: include/LocalMap.hpp include/TextureManager.hpp include/ConstantValues.hpp
	g++ -o lmap.o -c -Wall -g src/LocalMap.cpp

dungeons.o: include/Dungeon.hpp
	g++ -o dungeons.o -c -Wall -g src/Dungeon.cpp

settlements.o: include/Settlement.hpp
	g++ -o settlements.o -c -Wall -g src/Settlement.cpp

gamelevelmenu.o: include/GameLevelMenu.hpp include/GameLevel.hpp include/GameData.hpp
	g++ -o gamelevelmenu.o -c -Wall -g src/GameLevelMenu.cpp

gamelevelworld.o: include/GameLevelWorld.hpp include/GameLevel.hpp include/GameData.hpp
	g++ -o gamelevelworld.o -c -Wall -g src/GameLevelWorld.cpp

gamelevelingame.o: include/GameLevelIngame.hpp include/GameLevel.hpp include/GameData.hpp
	g++ -o gamelevelingame.o -c -Wall -g src/GameLevelIngame.cpp

gamelevel.o: include/GameLevel.hpp $(COMPONENTS) include/AssetManager.hpp include/Map.hpp include/Groups.hpp include/GameData.hpp
	g++ -o gamelevel.o -c -Wall -g src/GameLevel.cpp

gamedata.o: include/GameData.hpp $(COMPONENTS) include/AssetManager.hpp include/Map.hpp include/Groups.hpp
	g++ -o gamedata.o -c -Wall -g src/GameData.cpp

gameengine.o: include/GameEngine.hpp include/ECS/Components.hpp include/ConstantValues.hpp include/GameData.hpp
	g++ -o gameengine.o -c -Wall -g src/GameEngine.cpp

main.o: include/GameEngine.hpp $(COMPONENTS) include/ConstantValues.hpp
	g++ -o main.o -c -Wall -g src/main.cpp

clean: 
	rm -rf *.o jogo