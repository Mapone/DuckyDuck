NAME=sfml-app

sfml-app: sfmlTest.cpp TileMap.cpp
		g++ -std=c++11 -W -Wall -c TileMap.cpp
		g++ -W -Wall -o $(NAME) sfmlTest.cpp TileMap.o -lsfml-graphics -lsfml-window -lsfml-system


clean:
	@rm *.o $(NAME)
