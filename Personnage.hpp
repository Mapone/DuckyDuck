#ifndef PERSONNAGE_H
#define PERSONNAGE_H

class Personnage
{
public:
	Personnage(Vector2f taille);
	~Personnage();
	Vecor2f getMouvement();


private:
	Vector2f _mouvement;
	RectangleShape _perso;
};


#endif