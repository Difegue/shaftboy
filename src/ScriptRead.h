#ifndef DEF_SCR
#define DEF_SCR

#include "GameState.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include "MusicLoop.h"



class ScriptRead
{
public:
ScriptRead(std::string pathInit, GameState& GState); //démarre la lecture du script: A utiliser pour le premier script seulement.
ScriptRead(std::string pathScript, sf::Image &arrBrd, GameState& GState);
//Si on a déjà défini les paramètres, on les re-passe dans la définition

//void destroyPtr(); //Efface les pointeurs.
int read(); //Démarre la lecture du script.

std::string exec(std::string command); //Execute une commande du script.
void print(std::string toPrint); //Imprime le texte à l'écran. N'est quittée que lorque l'utilisateur a donné son OK.

private: //Les paramètres étant transférées d'une instance de scriptread à une autre, on les relie par pointeurs:

	sf::Image *ptrArrBrd;
	sf::Texture *ptrArrBck;
	GameState *ptrGState;

	//Paramètres pouvant êtres détruits/refaits à chaque instance.
	std::ifstream script;

	std::string toPrint; //Le texte à imprimer dans la boîte à texte
	std::vector <std::streampos> scenepos;
	std::vector <std::string> scenename;

	sf::Color choicingcolor; //couleur du BG des écrans de choix.

	MusicLoop bgm;

};

#endif
