#include "SplashScreen.h"

using namespace std;

SplashScreen::SplashScreen(sf::RenderWindow& window, bool fullscr, sf::Color color, int alpha, string pathbg, sf::Vector2u pos, sf::Vector2u size)
{
bgSpr.setTexture(bgTex);

if (!fullscr)
{//no fullscreen, keep cap of previous state to draw under the splash
//this is screencap machine
scrcap.create(window.getSize().x, window.getSize().y);
scrcap.update(window); //texture contains snapshot of window
scSpr.setTexture(scrcap);

bgTex.create(size.x,size.y);
if (pathbg=="") bgSpr.setColor(color); else
bgTex.loadFromFile(pathbg);
bgSpr.setPosition(pos.x,pos.y);

}
else
{
bgTex.create(window.getSize().x, window.getSize().y);
if (pathbg=="") bgSpr.setColor(color); else
bgTex.loadFromFile(pathbg);
}

bgSpr.setColor(sf::Color(114,65,205,alpha));
};

//OH DE DIEU QU'IL EST CHIANT ET PAS OPTIMISE CE PASSAGE j'aurais pu faire des fonctions génériques mais noooon jouons à TF2 à la place

void SplashScreen::addButton(Clickable Button, std::string id, bool closeOnClick)
{
	buttons.push_back(IdPlus<Clickable>(Button, id));
	buttonid.push_back(closeOnClick);
};

Clickable* SplashScreen::getButton(std::string id)
{
	if (getT(buttons,id)!=-1)
		return buttons[getT(buttons,id)].getElement();
	else return nullptr;
};

void SplashScreen::removeButton(std::string id)
{
	//if (getT(buttons,id).getId()!="-189885454fsdfTOPGUN458745") - pour la posterité
	if (getT(buttons,id)!=-1)
		buttons.erase(buttons.begin()+getT(buttons,id));
};

void SplashScreen::addText(sf::Text text, std::string id)
{
	texts.push_back(IdPlus<sf::Text>(text, id));
};

sf::Text* SplashScreen::getText(std::string id)
{
	if (getT(texts,id)!=-1)
		return texts[getT(texts,id)].getElement();
	else return nullptr;
};

void SplashScreen::removeText(std::string id)
{
	//if (getT(buttons,id).getId()!="-189885454fsdfTOPGUN458745") - pour la posterité
	if (getT(texts,id)!=-1)
		texts.erase(texts.begin()+getT(texts,id));
};

void SplashScreen::addImage(std::string path,std::string id)
{
	sf::Texture welp;
	welp.loadFromFile(path);
	imagetex.push_back(welp);

	sf::Sprite welp2;
	welp2.setTexture(imagetex.back()); //on met en réf la texture qui va rester, pas l'autre ca serait ballot

	images.push_back(IdPlus<sf::Sprite>(welp2, id));
};

sf::Sprite* SplashScreen::getImage(std::string id)
{
	if (getT(images,id)!=-1)
		return images[getT(images,id)].getElement();
	else return nullptr;
};

void SplashScreen::removeImage(std::string id)
{
	if (getT(images,id)!=-1)
	{
		images.erase(images.begin()+getT(images,id));
		imagetex.erase(imagetex.begin()+getT(images,id));
	}
};

//I'm glad it's over

std::string SplashScreen::splash(sf::RenderWindow& target) //Draws splashscreen and polls events.
//if button is clicked, return id of said button.
{

	//on dessine
	target.clear();
	target.draw(scSpr);
	target.draw(bgSpr);
	for (int i(0); i<buttons.size(); i++)
	{
		(*(buttons[i]).getElement()).Update(target);
		(*(buttons[i]).getElement()).draw(target);
	}
	/*sf::Text test (texts[0].getElement());
	for (int i(0); i<texts.size(); i++)
		target.draw(texts[i].getElement());*/
	for (int i(0); i<images.size(); i++)
		target.draw(*(images[i]).getElement());
	target.display();

	sf::Event event;
	while (target.pollEvent(event))
	{
		for (int i(0); i<buttons.size(); i++)
		{
			(*(buttons[i]).getElement()).Update(target);
			if ( (*((buttons[i]).getElement())).clicked() );
				return buttons[i].getId();
		}

	}

	return "-189885454fsdfTOPGUN458745"; //oyea
};

