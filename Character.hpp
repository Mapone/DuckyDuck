/**
 * @file Character.cpp
 * @author P. Raballand & N. Guittonneau
 * @date 09/30/2015
 * @brief Création une classe Character contrôlable par l'utilisateur dans le projet DuckyDuck
**/

/**
 * @brief Classe Character
 *
 * @param :-
 *
 * @b Role : Définit une classe Character.
 *
 * @b Cadre : -
 *
 * @pre : -
 * @post : -
 *
**/
class Character()
{
	private:
		State _stateDeath;
		State _stateNormal;
		State _stateBig;
		State _statePowerUp;

		State _state; 


	public:
		/**
 		 * @brief Constrcteur Character
 		 *
 		 * @param :-
		 *
 		 * @b Role : Définit une classe Character.
		 *
		 * @b Cadre : -
		 *
		 * @pre : -
		 * @post : Créer le Character.
 		 *
		**/
		Character()
		{
			_stateDeath= new StateDeath();
			_stateNormal= new StateNormal();
			_stateBig= new StateBig();
			_statePowerUp= new StatePowerUp();

			_state = _stateNormal;
		}

		/**
 		 * @brief Procédure moveCharacter
 		 *
 		 * @param : movement la touche correspondant au mouvement
		 *
 		 * @b Role : Fait bouger le Character en fonciton de l'entrée (grâce à SFML)
		 *
		 * @b Cadre : -
		 *
		 * @pre : -
		 * @post : -
 		 *
		**/
		void moveCharacter(int movement)
		{
			// EXECUTION DU MOUVEMENT PAR LA BIBLIOTHEQUE SFML;
		}


}