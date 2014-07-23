#include "Anim.hpp"
 
// Par défaut
Anim::Anim()
{
 
}
 
// déstructeur
Anim::~Anim()
{
 
}
 
// Par copie
Anim::Anim(const Anim& Cpy)
{
    myFrame = Cpy.myFrame;
}
 
// Ajouter une frame
void Anim::PushFrame(const Frame& NewFrame)
{
    myFrame.push_back(NewFrame);
}

//Ajout de frame automatisé à partir d'un charset: image source.
//srcImage charset source, frmSize taille d'une frame dans le charset, nbFrame nombre de frames en longueur/largeur
//origin origine dans le charset, Color couleur de transparence
void Anim::Create(sf::Image* srcImage, sf::Vector2u frmSize, sf::Vector2u nbFrame, sf::Color Color, sf::Vector2u origin)
{
int ix, iy;
for (iy=0; iy<nbFrame.x; iy++)
	{

	for (ix=0; ix<nbFrame.y; ix++)
		PushFrame(Frame(srcImage, sf::Rect<int>(ix*frmSize.x+origin.x,iy*frmSize.y+origin.y,frmSize.x,frmSize.y),Color)); 
		//Segmente l'image en rectangles de longueur/largeur frmSize et d'origine relative à nbFrame.
	 };
}
 
//Version EX de la fonction du dessus: Charge directement l'animation depusi un chemin de fichier
void Anim::Create(std::string srcImage, sf::Vector2u frmSize, sf::Vector2u nbFrame, sf::Color Color, sf::Vector2u origin)
{
	sf::Image img;
	img.loadFromFile(srcImage);
	Create(&img,frmSize,nbFrame, Color, origin);
}

// Nombre de frame(s)
size_t Anim::Size() const
{
    return myFrame.size();
}
 
// Accès a la frame numéro N
Frame& Anim::operator [] (size_t N)
{
    return myFrame[N];
}


 
 
// Plus tard, nous pourrons ajouter différentes fonctions liées au fait qu'une 'Anim' est une ressource
// Par exemple : LoadFromFile, SaveToFile etc...
