#ifndef DEF_GST
#define DEF_GST

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Textbox.h"

class GBPicture; //GbPicture est inclue dans Textbox.

//Classe stockant toutes les variables définies lors de la lecture du script. Peut aussi servir à sauvegarder/charger.
//Gère l'affichage en fonction du fichier configuration.

class GameState
{
public:
GameState();

void add(std::string name, int value=0); //ajouter variable
bool change(std::string name, int value); //changer etat variable
int check(std::string name); //regarde état variables

void save(std::string path);
void load(std::string path);

void display()
{
	gameWindow.clear();
	gameWindow.draw(gameBck);
	gameWindow.draw(gbSpr);
	gameGBP.draw(gameWindow);
	gameText.update(gameWindow);
	gameText.draw(gameWindow);
	gameWindow.display();

}

sf::RenderWindow gameWindow;
GBPicture gameGBP;
Textbox gameText;
sf::Sprite gameBck;

int getRatio(){return ratio;}

private:
	std::vector <int> flags;
	std::vector <std::string> flagnames;

	int width,height,ratio,speed;
	sf::Texture gb;
	sf::Sprite gbSpr;
};

#endif
