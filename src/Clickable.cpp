#include "Clickable.h"
using namespace std; 



Clickable::Clickable(std::string img, std::string imgc)
{
	//on stocke tous les paramètres
	m_texn.loadFromFile(img);
	m_texc.loadFromFile(imgc);
	hitbox=sf::IntRect(0,0,m_texn.getSize().x, m_texn.getSize().y);
	state=false;
	statePrev=false;

	//on configure le sprite
	m_sprite.setTexture(m_texn);

}

Clickable::Clickable(std::string img, std::string imgc, sf::Vector2u& orig)
{
	//on stocke tous les paramètres
	m_texn.loadFromFile(img);
	m_texc.loadFromFile(imgc);
	hitbox=sf::IntRect(orig.x,orig.y,m_texn.getSize().x, m_texn.getSize().y); //on utilise orig pour définir la hitbox
	state=false;
	statePrev=false;

	//on configure le sprite
	m_sprite.setTexture(m_texn);
	m_sprite.setPosition(orig.x,orig.y);

}

Clickable::Clickable(std::string img, std::string imgc, sf::IntRect& rect, sf::Vector2u orig)
{
	//on stocke tous les paramètres
	m_texn.loadFromFile(img);
	m_texc.loadFromFile(imgc);
	hitbox=rect;
	state=false;
	statePrev=false;

	//on configure le sprite
	m_sprite.setTexture(m_texn);
	m_sprite.setPosition(orig.x,orig.y);

}

Clickable::Clickable(sf::Text text) //construire depuis un texte
{
	//on stocke tous les paramètres

	sf::IntRect rekt(text.getGlobalBounds());
	hitbox=rekt;

	state=false;
	statePrev=false;

	//on configure le sprite
	m_sprite.setTexture(m_texn);


}

void Clickable::Update(sf::RenderWindow& window)
{
	statePrev=state;

	if (hitbox.contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_sprite.setTexture(m_texc);
		state=true; //ACTIVATE IT
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && m_sprite.getTexture()==&m_texc )
	{
		state=false; 
		m_sprite.setTexture(m_texn);

	}
}

bool Clickable::clicked(){
	if (!(state) && statePrev) 
		return true;
	else return false;
}

void Clickable::changeTexture(std::string img) //change m_texn
{ 
	m_texn.loadFromFile(img);	
} 

void Clickable::changeTexture2(std::string img) //change m_texc
{ 
	m_texc.loadFromFile(img);	
} 
