#ifndef JEU_H
#define JEU_H

class State;
class StateMainMenu;

class Jeu : public sf::Drawable, public sf::Transformable
{
	public:
		Jeu(TileMap &t, Personnage &p);
		~Jeu();
		void addLevel(TileMap t);
		TileMap& getCurrentLevel() const;
		sf::Font & getFont();


	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		std::vector<TileMap> _levels;
		unsigned int _currentLevel;
		Personnage &_heros;
		sf::Font _font;
		State* _actualState;
		StateMainMenu* _stateMainMenu;
};

#endif