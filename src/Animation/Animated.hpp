#ifndef ZIGO_ANIMATED
#define ZIGO_ANIMATED
 
#include "Anim.hpp"
/*An animated sf::Sprite.

It is made up of two things. First the time between each Frames. And a pointer to the Animation that will be drawn.
This special sf::Sprite provide some features like Play, Pause, Stop or Loop. 

tl;dr what's displayed on the screen and whose animation can be changed on the fly.*/ 

class Animated : public sf::Sprite
{
    public:
 
    // Par Copie
    Animated(const Animated& Cpy);
 
    // Par défault
    Animated(bool Play = false, bool Loop = true, float Time = 450);
 
    // Directement avec une Anim
    Animated(Anim* NewAnim, bool Play = false, bool Loop = true, float Time = 450);
 
    // Destructeur
    virtual ~Animated();
 
    // Comme 'SetImage', sauf qu'on lui fournit l'Anim
    void setAnim(Anim* NewAnim);
 
    // Retourne un pointeur sur l'anim
    Anim* getAnim();
 
    // Passer à l'image numéro X
    void setFrame(int Frame);
 
    // Retourne la Frame courante
    int getCurrentFrame();
 
    // Fixer le temps entre chaques Frame
    void setFrameTime(float Time);
 
    // Retourne le temps entre chaques Frame
    float getFrameTime();
 
    // Jouer en boucle ?
    void setLoop(bool Loop);
 
    // Jouer en boucle ?
    bool isLoop();
 
    // Met en pause la lecture
    void Pause();
 
    // Relance la lecture
    void Play();
 
    // Met en pause la lecture, et 'rembobine'
    void Stop();

	//Relance la lecture sans stopper
	void restart();
 
    // Est en pause ?
    bool isPaused();
 
    // Est stoppé ?
    bool isStopped();
 
    // Fonction à appeler à chaque tour de boucle, prend le temps
    // écoulé depuis le dernier appel à la fonction en paramètre
    void update();


    private:
    bool Paused;
    bool myLoop;
    Anim* myAnim;
    int myCurrentFrame;
    sf::Time spdAnim;
    sf::Clock zaWarudo;
};
 
#endif
