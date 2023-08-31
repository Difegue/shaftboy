#ifndef DEF_BTN
#define DEF_BTN

/*Class which represents every clickable item. Mainly buttons.
Can be drawn by SFML through xxx.draw(window)

sprite:Item's sprite. sf::Image.
m_texn, m_texc: two textures for the sprite, texn for normal button, texc for clicked button.
hitbox: rectangle symbolizing the sprite's hitbox. Default is the full image, located at (0,0).

*/
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Clickable// : public sf::Drawable
{
public :

	Clickable(std::string img, std::string imgc, sf::IntRect& rect, sf::Vector2u orig=sf::Vector2u(0,0)); //origine (0,0)
	Clickable(std::string img, std::string imgc, sf::Vector2u& orig); //origine orig et hitbox par d�faut
	Clickable(std::string img, std::string imgc); //le rect par d�faut est calcul� via img
	Clickable(sf::Text text); //construire depuis un texte existant.
	Clickable(){}; //empty constructor.
	void Update(sf::RenderWindow& window); //Doit �tre lanc�e pendant le gameloop, update le bouton selon la souris etc. N�cessite une r�f�rence � la fen�tre de jeu.
	bool clicked(); //Combinaison de state et statePrev. V�rifie si le bouton est cliqu�.
	void changeTexture(std::string img); //change m_texn
	void changeTexture2(std::string img); //change m_texc
	void draw(sf::RenderTarget& target) const
	{target.draw(m_sprite);};	//overriding the draw function by... drawing the sprite included in the item. woop


protected:
	sf::Texture m_texn, m_texc; //Permet de changer les textures facilement pour les classes perso sans passer par l'accesseur changeTexture.

private :

	sf::Sprite m_sprite;
	sf::IntRect hitbox;
	bool state; //Etat du bouton. TRUE=Bouton activ� FALSE=Bouton non activ�.
	bool statePrev; //Etat du bouton � l'it�ration pr�c�dente. Sert � voir si le bouton n'a pas d�j� �t� activ�.
};


#endif