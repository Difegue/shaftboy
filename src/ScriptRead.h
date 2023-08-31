#ifndef DEF_SCR
#define DEF_SCR

#include "GameState.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include "MusicLoop.h"



class ScriptRead
{
public:
ScriptRead(std::string pathInit, GameState& GState); //d�marre la lecture du script: A utiliser pour le premier script seulement.
ScriptRead(std::string pathScript, sf::Image &arrBrd, GameState& GState);
//Si on a d�j� d�fini les param�tres, on les re-passe dans la d�finition

//void destroyPtr(); //Efface les pointeurs.
int read(); //D�marre la lecture du script.

std::string exec(std::string command); //Execute une commande du script.
void print(std::string toPrint); //Imprime le texte � l'�cran. N'est quitt�e que lorque l'utilisateur a donn� son OK.

private: //Les param�tres �tant transf�r�es d'une instance de scriptread � une autre, on les relie par pointeurs:

	sf::Image *ptrArrBrd;
	sf::Texture *ptrArrBck;
	GameState *ptrGState;

	//Param�tres pouvant �tres d�truits/refaits � chaque instance.
	std::ifstream script;

	std::string toPrint; //Le texte � imprimer dans la bo�te � texte
	std::vector <std::streampos> scenepos;
	std::vector <std::string> scenename;

	sf::Color choicingcolor; //couleur du BG des �crans de choix.

	MusicLoop bgm;

};

#endif
