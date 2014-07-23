#include <iostream> //i/o stream
#include <fstream> //file stream
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Clickable.h"
//#include "Textbox.h"
//#include "GameState.h"
#include "ScriptRead.h"

//#include "GBPicture.h" remplacé par :
class GBPicture; //GbPicture est inclue dans Textbox.
class Textbox;
class GameState;

using namespace std;


int main()
{
	srand((unsigned)time(0));

	GameState GS;
	ScriptRead firstSR("./script/Init.sfs", GS);

	while (GS.gameWindow.isOpen())
	{
		sf::Event event;

		while ((GS.gameWindow).pollEvent(event))
		{
			//Check if user quits
			if (event.type == sf::Event::Closed)
				{
					(GS.gameWindow).close();
					return 0;
				}

			firstSR.read();

		}

	}
	return 0;
}
