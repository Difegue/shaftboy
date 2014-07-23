#include "ScriptRead.h"

using namespace std;

ScriptRead::ScriptRead(string pathInit, GameState& GState):script(pathInit.c_str())
{
	//Let's go resource init
	ptrGState = &GState;
	choicingcolor = sf::Color::Cyan;


}

ScriptRead::ScriptRead(string pathScript, sf::Image &arrBrd, GameState& GState):script(pathScript.c_str())
{
	ptrGState = &GState;
	ptrArrBrd = &arrBrd;

}

int ScriptRead::read()
{
	bool killswitch(true),wait(false),zawa;
	string line;

	while (killswitch) //my loop is augmented
	{
		if (!(*ptrGState).gameWindow.isOpen()) //retour au main si la fenêtre est ded
		{
			killswitch=false;
			break;
		}

		zawa=(*ptrGState).gameText.userOK((*ptrGState).gameWindow);

		if ( wait && !zawa ) //On attend l'input de l'utilisateur avant de continuer.
			(*ptrGState).display();
		else
			if (getline(script, line))
			{
				if (line.size()!=0)
				{
					wait=false;
					switch ( line[0]+line[1] ) //I love doing this so much holy shit
					{
					case '>'+'>' : {
									if (toPrint!="") wait = true;
									print(toPrint); toPrint="";
									string command=exec(line.substr(2));
									if (command!="")
										if (command[0]+command[1]!=':'+':')
										do getline(script, line); while (line!=command); //advances to specified command/scene
										else
										for (int i(0); i<scenename.size(); i++)
											if (scenename[i]==command.substr(2)) script.seekg(scenepos[i]);
									if (command=="DIE")
										return 0;

									break;
								   }
					case '/'+'/' : { if (toPrint!="") {wait = true; print(toPrint); toPrint=""; break;}}
					case ':'+':' : { if (toPrint!="") {wait = true; print(toPrint); toPrint="";} scenepos.push_back(script.tellg()); scenename.push_back(line.substr(2)); break;}
					default  : if (toPrint!="") toPrint = toPrint+'\n'+line; else toPrint=line;
					}
				}
			}
			else killswitch=false;
	}
}

void ScriptRead::print(string toPrint)
{
	if (toPrint=="") exit;
	else
	{
		(*ptrGState).gameText.setString(toPrint);
		(*ptrGState).display();
	}
}

vector <string> tokenize(string s, string delimit) //shamelessly stolen, returns words split by delimit as vector
{
	vector <string> benis; //fug
	size_t next=-1;
	size_t i;

	do
	{
		i=next+1; //next+1 nous donne le prochain mot si next a déjà pris un f_first_of, sinon on a 0, le début du string. (-1+1...)
		if (s[i]=='"') //Cas spécifique: si on a des mots entre guillemets on va jusqu'à la fin des guillemets.
		{
			next = s.find_first_of( '"', i+1 );
			benis.push_back(s.substr(i+1, next-(i+1))); // on l'ajoute

		}
		else
		{
			next = s.find_first_of( delimit, i ); //on récupère la position de la prochaine itération de delimit
			benis.push_back(s.substr(i, next-i)); // on l'ajoute
		}
		if (benis.back()=="") benis.pop_back(); //ABSOLUTELY DISGUSTING
	}
	while (next != string::npos);
	return benis;
}

int cv(string s) //brother in arms of tokenize, gives ints for strings of numbers
{
	return atoi(s.c_str());
}

string ScriptRead::exec(string s) //Returns "" if the script must keep on being parsed, otherwise the name of the thing to jump to
{
	//tokenize by space to get the command name. s is split by whitespace
	vector <string> command=tokenize(s, " ");

	//all the different command interpretations go here

	if (command[0]=="title") //set window title
		(*ptrGState).gameWindow.setTitle(s.substr(6));

	if (command[0]=="framenum") //set number of frames
	{
		ptrArrBrd = new sf::Image [cv(command[1])]; //Tableau contenant toutes les bordures
		string ein("./res/frames/"),zwei(".png");
		for (int i(0); i<cv(command[1]); i++)
		{
			ptrArrBrd[i].loadFromFile(ein+to_string(i)+zwei);
		};
	}

	if (command[0]=="bcknum") //set number of backgrounds
	{
		ptrArrBck = new sf::Texture [cv(command[1])]; //Tableau contenant tous les backgrounds
		string ein("./res/bck/"),zwei(".png");
		for (int i(0); i<cv(command[1]); i++)
		{
			ptrArrBck[i].loadFromFile(ein+to_string(i)+zwei);
		};
	}

	if (command[0]=="gbp") //set gameboy picture
	{
		sf::Image benis;
		benis.loadFromFile(command[1]);
		(*ptrGState).gameGBP.setPic(benis);

		if (command[2]!="")
		{
			(*ptrGState).gameGBP.setBorder(ptrArrBrd[cv(command[2])]);
		}
	(*ptrGState).gameGBP.update();
	}

	if (command[0]=="brd") //set gbpic border
		(*ptrGState).gameGBP.setBorder(ptrArrBrd[cv(command[1])]);

	if (command[0]=="color") //change colors
	{
		//On définit les couleurs en lisant les chiffres de la commande les uns après les autres.
		sf::Color newB(cv(command[1]),cv(command[2]),cv(command[3])),
			newDG(cv(command[4].c_str()),cv(command[5].c_str()),cv(command[6].c_str())),
			newLG(cv(command[7]),cv(command[8]),cv(command[9])),
			newW(cv(command[10]),cv(command[11]),cv(command[12]));

		(*ptrGState).gameGBP.setColor(newB,newDG,newLG,newW);
		(*ptrGState).gameGBP.update();
	}

		if (command[0]=="textcolor") //change textbox colors
	{
		//On définit les couleurs en lisant les chiffres de la commande les uns après les autres.
		sf::Color newB(cv(command[1]),cv(command[2]),cv(command[3])),
			newDG(cv(command[4].c_str()),cv(command[5].c_str()),cv(command[6].c_str())),
			newLG(cv(command[7]),cv(command[8]),cv(command[9])),
			newW(cv(command[10]),cv(command[11]),cv(command[12]));

		(*ptrGState).gameText.setColor(newB,newDG,newLG,newW);
		(*ptrGState).gameText.update((*ptrGState).gameWindow);
	}

	if (command[0]=="bg") //set background
		(*ptrGState).gameBck.setTexture(ptrArrBck[cv(command[1])]);

	if (command[0]=="musicp") //play music with or without looping.
	{
		bgm.openFromFile(command[1]);

		if (command.size()==4)
		{
			int begin(cv(command[2])), end(cv(command[3]));
			bgm.setStart(begin);
			bgm.setEnd(end);
		}
		bgm.play();
	}

	if (command[0]=="musics") //stop music
		bgm.stop();

	if (command[0]=="soundp") //play sound
	{
		sf::SoundBuffer Sound;
		Sound.loadFromFile(command[1]);

		sf::Sound SFX(Sound);
		SFX.play();

	 while(SFX.getStatus() == sf::Sound::Playing)
		{
		}


	}

	if (command[0]=="speed") //set textbox speed
		(*ptrGState).gameText.setSpeed(atoi(command[1].c_str()));

	if (command[0]=="font") //set textbox font
		(*ptrGState).gameText.setFont(command[1]);

	if (command[0]=="textsize") //set font size
    {
        if ((*ptrGState).getRatio()==169)
            (*ptrGState).gameText.setCharacterSize(atoi(command[1].c_str()));
        else
            (*ptrGState).gameText.setCharacterSize(atoi(command[1].c_str())/2);
    }

	//serious shit starts here

	if (command[0]=="var") //define and change variable
	{
		if ( !(*ptrGState).change(command[1], cv(command[2])) ) //si la var existe déjà on la change
			(*ptrGState).add(command[1], cv(command[2])); //sinon on l'ajoute
	}

	if (command[0]=="var+") //increment variable by x
		(*ptrGState).change(command[1], (*ptrGState).check(command[1])+cv(command[2]));

	if (command[0]=="var-") //decrement variable by x
		(*ptrGState).change(command[1], (*ptrGState).check(command[1])-cv(command[2]));

	if (command[0]=="if") //checks whether variable is equal to value indicated, jumps reading to corresponding point
		if ((*ptrGState).check(command[1])==cv(command[2]))
			return "";
		else
			return ">>else";

	if (command[0]=="else") //encountered only when on a if that passed. In this case, we skip everything past the else until encountering <endif>.
		return ">>endif";

	//if (command[0]=="endif") //encountered only when on a if that didn't pass.(straight jump to else block.) We just go past it.
	//unnecessary.

	if (command[0]=="choicecolor")
		choicingcolor = sf::Color (cv(command[1]),cv(command[2]),cv(command[3]));

	if (command[0]=="choice") //choice implementation here
	{
		string ch1_s(command[1]),ch1_t(command[2]), ch2_s(command[3]),ch2_t(command[4]),ch3_s,ch4_s;
		int choiced(0);

		switch(command.size())
		{ //On appelle gameText.choice, qui retourne un int correspondant à la réponse de l'utilisateur.
			case 6: {
					string ch3_s(command[5]),ch3_t(command[6]);
					//int choiced = (*ptrGState).gameText.choice((*ptrGState).gameWindow,ch1_t,ch2_t,choicingcolor,ch3_t);
					}
			case 7: {
					string ch3_s(command[5]),ch3_t(command[6]);
					string ch4_s(command[7]),ch4_t(command[8]);
					//int choiced = (*ptrGState).gameText.choice((*ptrGState).gameWindow,ch1_t,ch2_t,choicingcolor,ch3_t,ch4_t);
					}
			//default:int choiced = (*ptrGState).gameText.choice((*ptrGState).gameWindow,ch1_t,ch2_t,choicingcolor);
		}

		switch (choiced)
		{
		case 1: return "::"+ch1_s;
		case 2: return "::"+ch2_s;
		case 3: return "::"+ch3_s;
		case 4: return "::"+ch4_s;
		default  : return "";
		}

	}

	if (command[0]=="display") //jump to another scene within the script
	return "::"+s.substr(8);

	if (command[0]=="open") //change script file*/
	{ //Transfer pointer contents, destroy non-pointer elements, create new ScriptRead and activate his open before destructing this ScriptRead.
		ScriptRead *tabernacle = new ScriptRead("script/"+command[1],*ptrArrBrd,*ptrGState);
		(*tabernacle).read();
		//delete this; //As long as you're careful, it's OK for an object to commit suicide! (In this case it isn't)
	}


	return "";
}
