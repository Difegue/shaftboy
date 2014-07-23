#include "Frame.hpp"
 
// Par défaut
Frame::Frame(const sf::Color& NewColor)
{
    Texture.create(0,0);
    Color = NewColor;
}
 
// Par copie
Frame::Frame(const Frame& Cpy)
{
    Texture = Cpy.Texture;
    Rect = Cpy.Rect;
    Color = Cpy.Color;
}
 
// Image et Rect
Frame::Frame(sf::Image* NewImage, const sf::Rect<int>& NewRect, const sf::Color& NewColor)
{
    Rect = NewRect;
	Color = NewColor;
	//Texture.create(Rect.width, Rect.height);
	(*NewImage).createMaskFromColor(Color);
    Texture.loadFromImage(*NewImage,Rect);
    
}
 
// Image (Le Rect est au dimension de l'image)
Frame::Frame(sf::Image* NewImage, const sf::Color& NewColor)
{
    Rect = sf::Rect<int>(0, 0, (*NewImage).getSize().x, (*NewImage).getSize().y);
	Color = NewColor;
	//Texture.create(Rect.width, Rect.height);
	(*NewImage).createMaskFromColor(Color);
    Texture.loadFromImage(*NewImage,Rect);
}
 
// destructeur
Frame::~Frame()
{
 
}
