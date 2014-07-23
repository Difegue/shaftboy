#ifndef ZIGO_FRAME
#define ZIGO_FRAME
 
#include <SFML/Graphics.hpp>
 
// Une Frame est composée d'une texture, d'un SubRect et d'une couleur de transparence.
// La couleur par défaut d'une Frame est le blanc.
// La texture est prédécoupée à partir de l'image et du rect défini par l'utilisateur.
    

class Frame
{
    public:
    // Par défaut
    Frame(const sf::Color& NewColor = sf::Color::White);
 
    // Par copie
    Frame(const Frame& Cpy);
 
    // Image et Rect
    Frame(sf::Image* NewImage, const sf::Rect<int>& NewRect, const sf::Color& Transparency = sf::Color::White);
 
    // Image (Le Rect est au dimension de l'image)
    Frame(sf::Image* NewImage, const sf::Color& Transparency = sf::Color::White);
 
    // destructeur
    virtual ~Frame();
 
    // Accès public à la texture, au Rect et à la couleur
    sf::Texture Texture;
 
    sf::Rect<int> Rect;
 
    sf::Color Color;
};
 
#endif // ZIGO_FRAME
