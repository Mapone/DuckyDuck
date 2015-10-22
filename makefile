NAME=sfml-app

sfml-app: sfmlTest.cpp TileMap.cpp Personnage.cpp Jeu.cpp State.cpp StateMainMenu.cpp
		g++ -std=c++11 -W -Wall -c TileMap.cpp
		g++ -std=c++11 -W -Wall -c Personnage.cpp
		g++ -std=c++11 -W -Wall -c Jeu.cpp
		g++ -std=c++11 -W -Wall -c State.cpp
		g++ -std=c++11 -W -Wall -c StateMainMenu.cpp
		g++ -W -Wall -o $(NAME) sfmlTest.cpp TileMap.o Personnage.o -lsfml-graphics -lsfml-window -lsfml-system -g


clean:
	@rm *.o $(NAME)
