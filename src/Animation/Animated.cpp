#include "Animated.hpp"

// Par Copie
Animated::Animated(const Animated& Cpy) :
	sf::Sprite(Cpy)
{
	myCurrentFrame = Cpy.myCurrentFrame;
	spdAnim = Cpy.spdAnim;
	Paused = Cpy.Paused;
	myAnim = Cpy.myAnim;
	myLoop = Cpy.myLoop;
}

// Par défault
Animated::Animated(bool Play, bool Loop, float Time)
{
	myAnim = NULL;
	myCurrentFrame = 0;
	spdAnim = sf::milliseconds(Time);
	Paused = !Play;
	myLoop = Loop;
}

// Directement avec une Anim
Animated::Animated(Anim* NewAnim, bool Play, bool Loop, float Time)
{
	spdAnim = sf::milliseconds(Time);
	Paused = !Play;
	myLoop = Loop;
	myAnim = NewAnim;
	setFrame(0);
}

// Destructeur
Animated::~Animated()
{

}

// Comme 'SetImage', sauf qu'on lui fournit l'Anim
void Animated::setAnim(Anim* NewAnim)
{
	myAnim = NewAnim;

	setFrame(0);
}

// Retourne un pointeur sur l'anim
Anim* Animated::getAnim()
{
	return myAnim;
}

// Passer à l'image numéro X
void Animated::setFrame(int Frame)
{
	//if ( myAnim != NULL)
	if ((*myAnim).Size() > 0)
	{
		if ((*myAnim)[Frame].Texture.getSize() != sf::Vector2u(0,0))
			setTexture( (*myAnim)[Frame].Texture ); //On change la texture affichée
		myCurrentFrame = Frame;
	}
}

//Retourne La frame courante
int Animated::getCurrentFrame()
{
	return myCurrentFrame;
}

// Fixer le temps entre chaques Frame
void Animated::setFrameTime(float Time)
{
	spdAnim = sf::milliseconds(Time);
}

// retourne le temps entre chaque Frame en tant que millisecondes
float Animated::getFrameTime()
{
	return spdAnim.asMilliseconds();
}

// Jouer en boucle ?
void Animated::setLoop(bool Loop)
{
	myLoop = Loop;
}

// Jouer en boucle ?
bool Animated::isLoop()
{
	return myLoop;
}

// Met en pause la lecture
void Animated::Pause()
{
	Paused = true;
}

// Relance la lecture
void Animated::Play()
{
	zaWarudo.restart();
	Paused = false;
}

// Met en pause la lecture, et 'rembobine'
void Animated::Stop()
{
	setFrame(0);
	Paused = true;
}

//Relance la lecture sans stopper
void Animated::restart()
{
	Stop(); //what's with this lazy solution?
	Play();
}

// Est En pause ?
bool Animated::isPaused()
{
	return Paused;
}

// Est Stoppé ?
bool Animated::isStopped()
{
	return (Paused && (myCurrentFrame == 0));
}

// Fonction à appeler à chaque tours de boucle, prend le temps
// écoulé depuis le dernier appel à la fonction en paramètre
void Animated::update()
{
	int oldFrame(myCurrentFrame);

	// Si il n'est pas en pause et que l'animation est valide
	if (!Paused && myAnim != NULL)
	{
		// Si Le temps entre chaque frame est atteint
		if (zaWarudo.getElapsedTime() >= spdAnim)
		{
			// On réinitialise notre compteur
			zaWarudo.restart();

			// On passe a la frame suivante
			if (myCurrentFrame + 1 < (*myAnim).Size())
				myCurrentFrame++;
			else
				// Ou on a la premiere
				if (myLoop)
					myCurrentFrame = 0;
				else
					// Si le mode Loop est désactivé, on stop l'animation
					Stop();

			// On change la frame
			if (myCurrentFrame!=oldFrame)
				setFrame(myCurrentFrame);
		}
	}
}
