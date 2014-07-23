#ifndef DEF_TXT
#define DEF_TXT

//#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GBPicture.h"
#include <Animation/Animated.hpp>

/*Le truc qui s'occupe d'afficher du texte.
posX/Y: Position de la boîte
scX/Y: Scale de la boîte
Text: Texte à mettre dedans (défaut rien)
font: police d'écriture (par défaut un tabernacle de .ttf aussi connu sous le nom d'arial)
txtbox: aspect de la textbox (même si je prévois d'utiliser que le défaut, FUTUREPROOFING MOTHERFUCKER
Color: Couleur du texte. ( ¬_¬)

Dérivée de GBPicture pour ne pas avoir à recopier le code de changement de couleurs...
Comme GBPicture, on peut lui appliquer directement setScale, etc.
*/

class Textbox: public GBPicture
{
public:

	Textbox(int posX, int posY, int scX, int scY, std::string text="", std::string font="res/arial.ttf", int size = 24, int spd = 1, std::string txtbox="res/Tx.png", sf::Rect <int> writeRect=sf::Rect <int> (), sf::Color color=sf::Color::Black, sf::Color blk=sf::Color::Black, sf::Color dGr=DarkGray, sf::Color lGr=LiteGray, sf::Color wht=sf::Color::White);

	Textbox(int posX, int posY, std::string text="", std::string font="res/arial.ttf", int spd = 1); //appel simple
	Textbox(){}; //appel vide because

	void setColor(sf::Color newB, sf::Color newDG, sf::Color newLG, sf::Color newW)//OVER-LOAD! Ajoute le changement de couleur du texte.
	{GBPicture::setColor(newB,newLG,newDG,newW); dColor=newB; arrow.setColor(newB);}

	void setPosition(int x, int y)
	{
		sprPic.setPosition(x,y); dText.setPosition(x+20,y+10);
		arrow.setPosition(boxSpace.left+boxSpace.width*sprPic.getScale().x-13*sprPic.getScale().x, boxSpace.top+boxSpace.height*sprPic.getScale().y-10*sprPic.getScale().y);
	}

	void setCharacterSize(int s)
	{dText.setCharacterSize(s);}

	void setScale(float x, float y)
	{GBPicture::setScale(x,y); arrow.setScale(x-1,y-1);}

	void setFont(std::string font)
	{daFont.loadFromFile(font);};

	void setSpeed(int spd)
	{speed=spd;}

	void setString(std::string text) //Change le texte affiché, réinitialise l'affichage
	{rText=text; lText=text[0]; i=1; dText.setString(text[0]); state=false; tbClock.restart();}

	void setWriteRec(sf::Rect <int> writeRect)
	{
		boxSpace=writeRect;
		std::cout << boxSpace.left << std::endl;
		std::cout << std::to_string(boxSpace.top)+"+"+std::to_string(boxSpace.height*sprPic.getScale().y)+"-"+std::to_string(10*sprPic.getScale().y);
		arrow.setPosition(boxSpace.left+boxSpace.width,boxSpace.top+boxSpace.height);
	}

	void update(sf::RenderWindow& window); //OVER-LOAD! voir le .cpp, permet toujours d'updater le schmilblick
	//Update également le texte pour l'affichage et vérifie si l'utilisateur interagit avec la textbox.
	//Demande pour cela la réf. de la fenêtre.

	void draw(sf::RenderTarget& target) const; //override de l'override de GBPicture whee

	std::string getString() const {return rText;}; //just your everyday getters
	sf::Rect <int> getboxSpace() const {return boxSpace;};

	bool userOK(sf::RenderWindow& window); //renvoie TRUE si l'utilisateur a lu tout le texte.

	/*void setchoicefont(std::string font1="res/font/BAARS_.ttf", std::string font2="res/font/BAKESBR.ttf")
	{fonttext.loadFromFile(font1); fontchoice.loadFromFile(font2);};

	int choice(sf::RenderWindow& window, std::string ch1, std::string ch2, sf::Color color=sf::Color::Cyan, std::string ch3="", std::string ch4=""); */
	//Active un choix. Renvoie l'option choisie par l'utilisateur(1/2/3/4).

private:
	std::string rText; //raw texte
	std::string lText; //current line

	sf::Text dText; //Conteneur du texte affiché
	sf::Color dColor; //Conteneur de la couleur du texte.
	sf::Font daFont; //Conteneur de la police

	bool state; // false: texte non affiché en entier - true: texte affiché en entier.
	int speed,i; //Vitesse d'affichage du texte (1/2/3) et compteur d'avancement dans le texte
	sf::Clock tbClock; //Pour mesurer le temps passé depuis la dernière update.

	Anim arrowAnim; // La petite flèche qui incite l'user à passer au message suivant :>
	Animated arrow; // Le sprite animé correspondant

	sf::SoundBuffer buffer; //le buffer du son émis par la textbox
	sf::Sound sound; //Ledit son

	sf::Font fonttext,fontchoice; //polices ecran choix

	//Les assets graphiques viennent de GBPicture: bg,border, picTex, sprPic.
	sf::Rect <int> boxSpace; //Espace de la boîte de texte ou on peut écrire.
};
#endif
