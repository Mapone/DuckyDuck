NAME=sfml-app

sfml-app: sfmlTest.cpp TileMap.cpp Personnage.cpp
		g++ -std=c++11 -W -Wall -c TileMap.cpp
		g++ -std=c++11 -W -Wall -c Personnage.cpp
		g++ -W -Wall -o $(NAME) sfmlTest.cpp TileMap.o Personnage.o -lsfml-graphics -lsfml-window -lsfml-system


clean:
	@rm *.o $(NAME)
