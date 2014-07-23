#ifndef DEF_GBP
#define DEF_GBP

/* Allow me to explain!
The GBPicture class is made for handling GameBoy Camera pictures.

bg:The main image(in string form: path to image.) Can't be changed because it's a pain and unpractical anyway.
border:The image's border. CAN be changed.
black,lGray,dGray,white: The colors of the picture. Defaults to the original GBCam colors.
PicTex: The texture matching the combo border+image+colors. Is public and if associated with a sprite, updating it with automatically update the SFML window.
MAGIC!

setColor: Changes the picture's colors. Changes won't be visible until the end texture is re-declared.
setBorder: Changes the picture's border and auto-updates its colors. Changes won't etc etc
getTex: Updates the texture. Self-explanatory, no?
*/

#include <SFML/Graphics.hpp>
//#include <vector>
#include <iostream>

const sf::Color DarkGray(128,128,128), LiteGray(192,192,192); //Les deux gris d'une photo GBCam. Les autres couleurs dont sf::Color Black/White.
const sf::Color EmuBlack(24,24,32), EmuDG(88,88,104), EmuLG(168,168,176); //bullshit colors used by most GB emulators and pictures obtained through ROM dumpers
/*







Insérér d'autres constantes de couleurs au fur et à mesure du dev ici
*/

const sf::Image dmy; //bordure vide just in case


//Définition classe et attributs
class GBPicture
{
public:
	//Une photo GBCamera est définie par son background, le bord du background et les 4 couleurs de base(par défaut les nuances de gris)
	GBPicture(){}; //constructeur vide
	//borderless constructor
	GBPicture(std::string img, sf::Color blk=sf::Color::Black, sf::Color dGr=DarkGray, sf::Color lGr=LiteGray, sf::Color wht=sf::Color::White);
	//constructor with border
	GBPicture(std::string img, std::string brd, sf::Color blk=sf::Color::Black, sf::Color dGr=DarkGray, sf::Color lGr=LiteGray, sf::Color wht=sf::Color::White);
	void setColor(sf::Color newB, sf::Color newDG, sf::Color newLG, sf::Color newW); //Change les 4 couleurs, pour la photo et la bordure.
	void setBorder(sf::Image& brd); //Change la bordure.
	void setPic(sf::Image& pic); //Changes picture. Resets all colors.
	void update(); //Update la texture de l'objet.
	void draw(sf::RenderTarget& target) const
	{target.draw(sprPic);};	//overriding the draw function by... drawing the sprite included in the item. woop

	void setScale(float x, float y)
	{sprPic.setScale(x,y);};
	void setPosition(int x, int y)
	{sprPic.setPosition(x,y);};
	void setSize(int x, int y)
	{
	    std::cout << std::to_string(x)+" "+std::to_string(y) << std::endl;
        std::cout << std::to_string(picTex.getSize().x);
	    sprPic.setScale((float)x/picTex.getSize().x,(float)y/picTex.getSize().y);
	    };


	~GBPicture(); //DESTROY

protected:
	sf::Image bg,border;
	sf::Texture picTex;
	sf::Sprite sprPic;

private:
	sf::Color black,lGray,dGray,white; //couleurs. De base, noir/grisc/grisf/blanc
	std::vector<sf::Vector2i> lG,dG,w,b; //Tableaux contenant les coordonnées pour la photo
	std::vector<sf::Vector2i> lG_b,dG_b,w_b,b_b; //Tableaux contenant les coordonnées pour la photo
};

#endif
