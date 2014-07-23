#include "GameState.h"

using namespace std;
GameState::GameState():gameWindow(sf::VideoMode(1280,720), "SHAFTBoy Engine"), gameGBP("res/GBP/A/test.png","res/frames/0.png"), gameText(240,530,"-189885454fsdfTOPGUN458745","res/font/karen2mono.ttf")
{
	string w,h,r,s;

	//Ici lecture du fichier config: définition résolution, taille textbox etc
	ifstream config("Res.cfg");

	if (config.is_open())
	{
		getline(config,w);
		getline(config,h);
		getline(config,r);
		getline(config,s);
	}
	config.close();

	width = atoi(w.c_str());
	height= atoi(h.c_str());
	ratio = atoi(r.c_str());
	speed = atoi(s.c_str());

	//on remplace les constructeurs vides par THE REAL THING
	gameWindow.create(sf::VideoMode(width, height),"SHAFTBoy Engine");
	gameGBP.update();

	gb.loadFromFile("res/GB.png");
	gbSpr.setTexture(gb);

	//Shit calculations for aspect ratio management.
	if (ratio==169)
		{

			gameGBP.setPosition(width*496/1280,height*144/720);
			gameGBP.setScale(width*2/1280,height*2/720);

            sf::Image welp;
			welp.loadFromFile("res/Tx.png");
            gameText.setPic(welp);

			gameText.setPosition(width/5.33, height/1.358);
			gameText.setSize(width*68/100,height*25/100);
			gameText.setWriteRec(sf::Rect <int> (width/5.33+5,height/1.35+4,width*68/100+width/5.33,height*25/100+height/1.358));



			gbSpr.setPosition(width*354/1280,height*10/720);
			gbSpr.setScale(width*0.5/1280,height*0.5/720);


		}
	if (ratio==43)
		{
			gameGBP.setPosition(width/3,height/5.6);
			gameGBP.setScale(width*1.5/640,height*1.5/480);

            sf::Image welp;
			welp.loadFromFile("res/Tx43.png");
			gameText.setPic(welp);

			gameText.setPosition(width/5.66, height/1.358);
			gameText.setSize(width*64/100,height*25/100);
			gameText.setCharacterSize(12);
			gameText.setWriteRec(sf::Rect <int> ((width/5.33)+5,(height/1.358)+4,width*64/100+(width/5.33)+5,height*25/100+(height/1.358)+4));


			gbSpr.setPosition(width*354/1280,height*10/720);
			gbSpr.setScale(width*0.5/1280,height*0.5/720);
		}

}

void GameState::add(string name, int value)
{
	flagnames.push_back(name);
	flags.push_back(value);
}

int GameState::check(string name)
{
	for (int i(0); i<flagnames.size(); i++) //on vérifie si la valeur existe
		if (flagnames[i].compare(name)==0) return flags[i]; //si oui on la retourne

	return 0; //si non le retour défaut est FALSE
}

bool GameState::change(string name, int value)
{
	for (int i(0); i<flagnames.size(); i++) //on vérifie si la valeur existe
		if (flagnames[i].compare(name)==0)
		{
			flags[i]=value; //si oui on la change et on retourne true
			return true;
		}

		return false; //si non le retour défaut est FALSE

}

void GameState::save(string path)
{
	ofstream myfile;
	myfile.open (path.c_str(), ios::trunc);

	if (myfile.is_open())
	{
		for (int i(0); i<flagnames.size(); i++)
		{
			myfile << flagnames[i] + " ";
			myfile << flags[i] + "\n";
		}

		myfile.close();
	}
}

void GameState::load(string path)
{
	string line;
	int flag;
	ifstream myfile(path.c_str());

	flags.clear();
	flagnames.clear();

	if (myfile.is_open())
	{
		while (myfile >> line >> flag)
		{
			flagnames.push_back(line);
			flags.push_back(flag);
		}
		myfile.close();
	}

}
