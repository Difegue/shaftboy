#ifndef ZIGO_ANIM
#define ZIGO_ANIM

#include <vector>

#include "Frame.hpp"

// La classe animation n'est qu'un 'vector' de Frame

class Anim
{
    public:

    // par défaut
    Anim();

    // destructeur
    virtual ~Anim();

    // Par copie
    Anim(const Anim& Cpy);

    // Ajouter une Frame
    void PushFrame(const Frame& NewFrame);

    //Ajout de Frames automatisé à partir d'un charset
    void Create(sf::Image* srcImage, sf::Vector2u frmSize, sf::Vector2u nbFrame, sf::Color Color=sf::Color::White, sf::Vector2u origin=sf::Vector2u (0,0));
	//srcImage charset source, frmSize taille d'une frame dans le charset, nbFrame nombre de frames en longueur/largeur,
	//origin origine dans le charset, Color couleur de transparence

	//Version EX de la fonction du dessus: Charge directement l'animation depusi un chemin de fichier
	void Create(std::string srcImage, sf::Vector2u frmSize, sf::Vector2u nbFrame, sf::Color Color=sf::Color::White, sf::Vector2u origin=sf::Vector2u (0,0));

    // Nombre de Frame(s)
    size_t Size() const;

    // Accès a la frame numéro N
    Frame& operator [] (size_t N);

    // Plus tard, nous pourrons ajouter différentes fonctions liées au fait qu'une 'Anim' est une ressource
    // Par exemple : LoadFromFile, SaveToFile etc...

    private:
    std::vector< Frame > myFrame;

};
#endif
