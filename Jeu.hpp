#ifndef JEU_H
#define JEU_H

#include <SFML/Graphics.hpp>
class TileMap;
class Personnage;
class State;
class StateMainMenu;
class StateLevel;

class Jeu : public sf::Drawable, public sf::Transformable
{
	public:
		Jeu(TileMap &t, Personnage &p);
		~Jeu();
		void update();
		void addLevel(TileMap t);
		TileMap* getCurrentLevel() const;
		const sf::Font& getFont() const;
		Personnage getHero() const;
		void setState(State* s);
		StateLevel* getStateLevel() const;


	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void processInput();
		void checkCollision();
		std::vector<TileMap*> _levels;
		unsigned int _currentLevel;
		Personnage &_heros;
		sf::Font _font;
		State* _currentState;
		StateMainMenu* _stateMainMenu;
		StateLevel* _stateLevel;
};

#endif