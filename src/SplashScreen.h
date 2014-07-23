#ifndef DEF_SS
#define DEF_SS

#include <vector>
#include <SFML/Graphics.hpp>
#include "Clickable.h"
//Generates a screen that when called, will appear pausing the rest of the game and asking the user for action. 
//Good for menus. 
//PIECE O' SHIT CODE TO BE BURIED AWAY AND FORGOTTEN

template<class T>
class IdPlus
{
public:
IdPlus(T element2, std::string id2)
	{element=element2; id=id2;};

T* getElement()
	{return &element;};

std::string getId()
	{return id;};

private:
T element;
std::string id;
};

template<class T>
int getT(std::vector<IdPlus<T>> vect, std::string tofind)
{
		for (int i(0); i<vect.size(); i++) //on vérifie si la valeur existe
		if (vect[i].getId()==tofind) return i; //si oui on retourne son index

	return -1; //si non le retour défaut est FALSE

};

class SplashScreen
{
public:
SplashScreen(sf::RenderWindow& window, bool fullscr=false, sf::Color color=sf::Color::Transparent, int alpha=255, std::string pathbg="", sf::Vector2u pos = sf::Vector2u(0,0), sf::Vector2u size = sf::Vector2u(0,0)); 
//fenêtre ou rendre et si plein écran ou non.

void changeColor(sf::Color color)
{bgSpr.setColor(color);};

void addButton(Clickable Button, std::string id, bool closeOnClick=false); //la position est relative à l'origine du splashscreen.
Clickable* getButton(std::string id);
void removeButton(std::string id);

void addText(sf::Text text, std::string id);
sf::Text* getText(std::string id);
void removeText(std::string id);

void addImage(std::string path,std::string id);
sf::Sprite* getImage(std::string id);
void removeImage(std::string id);

std::string splash(sf::RenderWindow& target); //Activates splash screen, ends when screen is closed
//Returns id of matching button

private:
std::vector<IdPlus<Clickable>> buttons;
std::vector<bool> buttonid;

std::vector<IdPlus<sf::Text>> texts;

std::vector<IdPlus<sf::Sprite>> images;
std::vector<sf::Texture> imagetex;

sf::Texture bgTex;
sf::Sprite bgSpr;
sf::Texture scrcap;
sf::Sprite scSpr;

};

#endif