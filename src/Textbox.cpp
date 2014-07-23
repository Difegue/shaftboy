#include "Textbox.h"
#include <iostream>

using namespace std;

string wordwrap(string str, int i=0) //takes a string at a specific position and returns the next full word
{
	if (i> str.length() || str[i]==*" " || str[i]==*"\n" ) return "";
	else return str[i]+wordwrap(str, i+1);
};

int widthInPixels(string str, sf::Font font, int size) //Donne la largeur d'une ligne de texte en pique-sels
{ //On reprend notre string, on crée un text rien qu'avec lui puis on en récupère la taille
	sf::Text text(str, font, size);
	return text.getGlobalBounds().width;
};

Textbox::Textbox(int posX, int posY, int scX, int scY, string text, string font, int size, int spd, string txtbox, sf::Rect <int> writeRect, sf::Color color, sf::Color blk, sf::Color dGr, sf::Color lGr, sf::Color wht) : GBPicture(txtbox, blk, dGr, lGr, wht)
{
	state=false;
	speed=spd;
	rText=text;
	lText=rText[0];

	setPosition(posX,posY);
	setScale(scX,scY);
	dColor=color;

	daFont.loadFromFile(font);
	dText.setFont(daFont);
	dText.setString(text[0]); //setup compteur
	i=1;
	dText.setColor(dColor);
	dText.setPosition(posX+20,posY+10);
	dText.setCharacterSize(size);

	arrowAnim.Create("res/arrow.png", sf::Vector2u (30,28), sf::Vector2u (1,5));
	arrow.setAnim(&arrowAnim);
	arrow.setLoop(true);
	arrow.setPosition(writeRect.left+writeRect.width-10, writeRect.top+writeRect.height-10);
	arrow.setScale(scX-1,scY-1);
	arrow.Stop();

	buffer.loadFromFile("res/sfx/TextboxBloop8-Bit.ogg");
	sound.setBuffer(buffer);

	if (writeRect == sf::Rect <int> (0,0,0,0)) //si l'user n'a pas défini de rectangle
		boxSpace = sf::Rect <int> (posX+5,posY+4,244,50); //défaut
};


Textbox::Textbox(int posX, int posY, string text, string font, int spd) : GBPicture("res/Tx.png", sf::Color::Black, DarkGray, LiteGray, sf::Color::White)
{
	state=false;
	speed=spd;
	rText=text;
	lText=rText[0];

	setPosition(posX,posY);
	setScale(3,3);
	dColor=sf::Color::Black;

	daFont.loadFromFile(font);
	dText.setFont(daFont);
	dText.setString(text[0]); //setup compteur
	i=1;
	dText.setColor(dColor);
	dText.setPosition(posX+20,posY+10);
	dText.setCharacterSize(24);

	boxSpace = sf::Rect <int> (posX+5,posY+4,244,50); //défaut

	arrowAnim.Create("res/arrow.png", sf::Vector2u (30,28), sf::Vector2u (1,5));
	arrow.setAnim(&arrowAnim);
	arrow.setLoop(true);
	arrow.setPosition(boxSpace.left+boxSpace.width-10, boxSpace.top+boxSpace.height-10);
	arrow.setScale(2,2);
	arrow.Stop();

	buffer.loadFromFile("res/sfx/TextboxBloop8-Bit.ogg"); //Son Textbox ici
	sound.setBuffer(buffer);


};


void Textbox::update(sf::RenderWindow& window)
{
	int Tx(sf::Mouse::getPosition(window).x),Ty(sf::Mouse::getPosition(window).y);
	sf::Vector2f cCoor;
	cCoor=window.mapPixelToCoords(sf::Vector2i(Tx,Ty)); //Position souris

	string wWrap("");
	int maxLineSize(boxSpace.width*sprPic.getScale().x);
	int checka;
	bool usercheck;
	usercheck=(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sprPic.getGlobalBounds().contains(cCoor)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space); //Intervention de l'utilisateur?

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && (!state))
		//Si skip, on affiche tout sans itération
	{
		do
		{
			size_t next1 = rText.find( "/n", i+1 ); //on récupère la position de la prochaine fin de ligne
			size_t next2 = rText.find( " ", i+1 ); //on récupère la position du prochain espace
			size_t next;
			if (next1>next2 && next2<=rText.length()) next=next2; else if (next1<=rText.length()) next=next1; else next=rText.length();
			//On prend le plus proche, itt le plus petit

			string left = rText.substr(i,next-i);//tout ce qui reste entre i et next

			//wWrap=wordwrap(rText, next+1);
			checka=widthInPixels(lText + left,daFont,dText.getCharacterSize());
			if(checka >= maxLineSize) //si la ligne courante ne peut être contenue dans une ligne
				{
					dText.setString(dText.getString()+'\n'+left.substr(1));
					lText="";
				}
			else
				{
					dText.setString(dText.getString()+left);
					if (next==next1) lText=""; else lText=lText+left;
				}
			i=next;
		}
		while (i<rText.length());

		state=true;
		arrow.Play();


	}
	else
		if (tbClock.getElapsedTime().asMilliseconds()>=75*speed || usercheck )
			//si le joueur skippe, on dit fakiou au temps et on update le plus vite possible pour tout afficher
				//sinon, affichage caractère par caractère selon la vitesse
					if (!state)
					{
						arrow.Stop();
						tbClock.restart();
						if (i==rText.length()) //On démarre l'animation, et on met state=true
						{
							state=true;
							arrow.Play();
						}
						else
						{
							//WORDWRAPPING HERE NIGGAS
							if (rText[i]==*" " || rText[i]==*"\n")
							{
								wWrap=wordwrap(rText, i+1);
								checka=widthInPixels(lText +" "+ wWrap,daFont,dText.getCharacterSize());
								if(checka >= maxLineSize && rText[i]==*" ") //si la ligne courante ne peut être contenue dans une ligne
								{
									dText.setString(dText.getString()+'\n');
									lText="";
								}
								else
								{
									dText.setString(dText.getString()+rText[i]);
									if (rText[i]==*"\n") lText=""; else lText=lText+rText[i];
								}
							}
							else {
								dText.setString(dText.getString()+rText[i]);
								lText=lText+rText[i];
							}


							if (/*rText[i]==*" " ||*/ rText[i]==*"\n") sound.stop();
							else sound.play(); //On ne joue pas de son si on a un retour à la ligne
							i++;

						}
					}

					dText.setFont(daFont);
					dText.setColor(dColor);
					picTex.update(bg);

					if (state)
						{
							arrow.update(); //On active la flèche animée
							//std::cout << lText << std::endl; //print laid dans la console pour debugay
							if (arrow.getCurrentFrame()==
						}

};

bool Textbox::userOK(sf::RenderWindow& window)
{
	window.setKeyRepeatEnabled(false); //Pour éviter que tout le texte soit bouffé si l'utilisateur garde la touche appuyée
	int Tx(sf::Mouse::getPosition(window).x),Ty(sf::Mouse::getPosition(window).y);
	sf::Vector2f cCoor;
	cCoor=window.mapPixelToCoords(sf::Vector2i(Tx,Ty)); //Position souris

	bool user(false);
	sf::Event event;
	while (window.pollEvent(event))
	if (event.type == sf::Event::Closed) //mandatory
		{
		window.close();
		return true;
		}

	user = (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && sprPic.getGlobalBounds().contains(cCoor))
		|| event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl); //Intervention de l'utilisateur?

	//std::cout << (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space);
	window.setKeyRepeatEnabled(true);
	return (state && user && );
};


void Textbox::draw(sf::RenderTarget& target) const
{
	target.draw(sprPic);
	target.draw(dText);
	if (state)
		target.draw(arrow);
};

/*sf::Text settingUp(string text, sf::Font font, int charSize, sf::Vector2u pos)
{
	sf::Text res;

	res.setFont(font);
	res.setString(text);
	res.setCharacterSize(charSize);
	res.setPosition(pos.x,pos.y);

	return res;
};

int Textbox::choice(sf::RenderWindow& window, string ch1, string ch2, sf::Color color, string ch3, string ch4)
{
srand (time(NULL));
SplashScreen choosing(window, true, color);

//add collision checking...

sf::Text ch1_t,ch2_t,ch3_t,ch4_t, textmisc;
string b1_1("res/clicky1.png"),b1_2("res/clicky2.png");

ch1_t= settingUp(ch1,fontchoice,18, sf::Vector2u (rand() % window.getSize().x, rand() % window.getSize().y));
choosing.addText(ch1_t,"ch1");
choosing.addButton( Clickable(b1_1,b1_2),"ch1b",true);

ch2_t= settingUp(ch2,fontchoice,18, sf::Vector2u (rand() % window.getSize().x,rand() % window.getSize().y));
choosing.addText(ch2_t,"ch2");
choosing.addButton( Clickable(b1_1,b1_2),"ch2b",true);

textmisc=settingUp("What will you choose?",fonttext,32, sf::Vector2u (window.getSize().x/2,window.getSize().y/2));
choosing.addText(textmisc,"txtc");

if (ch3!=""){
				ch3_t= settingUp(ch3,fontchoice,18, sf::Vector2u (rand() % window.getSize().x,rand() % window.getSize().y));
				choosing.addText(ch3_t,"ch3");
				choosing.addButton( Clickable(ch3_t),"ch3b",true);
			}

if (ch4!=""){
				ch4_t= settingUp(ch4,fontchoice,18, sf::Vector2u (rand() % window.getSize().x,rand() % window.getSize().y));
				choosing.addText(ch4_t,"ch4");
				choosing.addButton( Clickable(ch4_t),"ch4b",true);
			}


while (true)
{
	string oyea(choosing.splash(window));

	if (oyea!="-189885454fsdfTOPGUN458745")
		if (oyea=="ch1_b") return 1;
		else if (oyea=="ch2_b") return 2;
		else if (oyea=="ch3_b") return 3;
		else if (oyea=="ch4_b") return 4;

}
}
*/

