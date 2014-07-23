#include "GBPicture.h"
using namespace std;

GBPicture::GBPicture(string img, sf::Color blk, sf::Color dGr, sf::Color lGr, sf::Color wht)
{
	//Définition des paramètres de base
	bg.loadFromFile(img);
	black=blk;
	lGray=lGr;
	dGray=dGr;
	white=wht;


	//On parse l'image et on stocke les pixels colorés dans 4 tableaux
	int imx(0), imy(0);
	sf::Vector2u size(bg.getSize());
    picTex.create(size.x,size.y);

	sprPic.setTexture(picTex);

	for (imx; imx<size.x; imx++)
	{
		for (imy; imy<size.y; imy++)
		{

			if ((bg.getPixel(imx,imy) == DarkGray) || (bg.getPixel(imx,imy) == EmuDG)){
				dG.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if ((bg.getPixel(imx,imy) == LiteGray) || (bg.getPixel(imx,imy) == EmuLG)){
				lG.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if (bg.getPixel(imx,imy) == sf::Color::White){
				w.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if ((bg.getPixel(imx,imy) == sf::Color::Black) || (bg.getPixel(imx,imy) == EmuBlack)){
				b.push_back(sf::Vector2i(imx,imy));
				continue;
			}
		}
		imy=0;
	}

	setColor(sf::Color::Black,DarkGray,LiteGray,sf::Color::White);
	//au cas ou les couleurs de l'image originale sont des couleurs d'émulateur, on remet les couleurs pures.

	//Les couleurs sont-elles différentes du standard? Si oui, on les change.
	if (black!=sf::Color::Black){
		for(unsigned int i(0); i<b.size(); i++){
			bg.setPixel(b[i].x,b[i].y, black);
		};

		for(unsigned int i(0); i<b_b.size(); i++){
			border.setPixel(b_b[i].x,b_b[i].y, black);
		};
	};

	if (lGray!=LiteGray){
		for(unsigned int i(0); i<lG.size(); i++){
			bg.setPixel(lG[i].x,lG[i].y, lGray);
		};

		for(unsigned int i(0); i<lG_b.size(); i++){
			border.setPixel(lG_b[i].x,lG_b[i].y, lGray);
		};
	};

	if (dGray!=DarkGray){
		for(unsigned int i(0); i<dG.size(); i++){
			bg.setPixel(dG[i].x,dG[i].y, dGray);
		};

		for(unsigned int i(0); i<dG_b.size(); i++){
			border.setPixel(dG_b[i].x,dG_b[i].y, dGray);
		};
	};

	if (white!=sf::Color::White){
		for(unsigned int i(0); i<w.size(); i++){
			bg.setPixel(w[i].x,w[i].y, white);
		};

		for(unsigned int i(0); i<w_b.size(); i++){
			border.setPixel(w_b[i].x,w_b[i].y, white);
		};
	};

}

GBPicture::GBPicture(string img, string brd, sf::Color blk, sf::Color dGr, sf::Color lGr, sf::Color wht)
{
	bg.loadFromFile(img);
	border.loadFromFile(brd);
	black=blk;
	lGray=lGr;
	dGray=dGr;
	white=wht;

	//On parse l'image et on stocke les pixels colorés dans 4 tableaux
	int imx(0), imy(0);
	sf::Vector2u size(bg.getSize());

	picTex.create(160,144);
    sprPic.setTexture(picTex);

	for (imx; imx<size.x; imx++)
	{
		for (imy; imy<size.y; imy++)
		{

			if ((bg.getPixel(imx,imy) == DarkGray) || (bg.getPixel(imx,imy) == EmuDG)){
				dG.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if ((bg.getPixel(imx,imy) == LiteGray) || (bg.getPixel(imx,imy) == EmuLG)){
				lG.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if (bg.getPixel(imx,imy) == sf::Color::White){
				w.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if ((bg.getPixel(imx,imy) == sf::Color::Black) || (bg.getPixel(imx,imy) == EmuBlack)){
				b.push_back(sf::Vector2i(imx,imy));
				continue;
			}
		}
		imy=0;
	}
		//On réinitialise pour parser la bordure!
		imx=0;
		size=border.getSize();

    for (imx; imx<size.x; imx++)
    {
        for (imy; imy<size.y; imy++)
        {
            if (border.getPixel(imx,imy) == sf::Color(192,220,192)) //si la couleur fait partie de celles du milieu(les transparentes) on skippe!
                continue;

            if (border.getPixel(imx,imy) == DarkGray){
                dG_b.push_back(sf::Vector2i(imx,imy));
                continue;
            }

            if (border.getPixel(imx,imy) == LiteGray){
                lG_b.push_back(sf::Vector2i(imx,imy));
                continue;
            }

            if (border.getPixel(imx,imy) == sf::Color::White){
                w_b.push_back(sf::Vector2i(imx,imy));
                continue;
            }

            if (border.getPixel(imx,imy) == sf::Color::Black){
                b_b.push_back(sf::Vector2i(imx,imy));
                continue;
            }
        }
        imy=0;
    }

	setColor(sf::Color::Black,DarkGray,LiteGray,sf::Color::White);
	//au cas ou les couleurs de l'image originale sont des couleurs d'émulateur, on remet les couleurs pures.

	//Les couleurs sont-elles différentes du standard? Si oui, on les change.
	if (black!=sf::Color::Black){
		for(unsigned int i(0); i<b.size(); i++){
			bg.setPixel(b[i].x,b[i].y, black);
		};

		for(unsigned int i(0); i<b_b.size(); i++){
			border.setPixel(b_b[i].x,b_b[i].y, black);
		};
	};

	if (lGray!=LiteGray){
		for(unsigned int i(0); i<lG.size(); i++){
			bg.setPixel(lG[i].x,lG[i].y, lGray);
		};

		for(unsigned int i(0); i<lG_b.size(); i++){
			border.setPixel(lG_b[i].x,lG_b[i].y, lGray);
		};
	};

	if (dGray!=DarkGray){
		for(unsigned int i(0); i<dG.size(); i++){
			bg.setPixel(dG[i].x,dG[i].y, dGray);
		};

		for(unsigned int i(0); i<dG_b.size(); i++){
			border.setPixel(dG_b[i].x,dG_b[i].y, dGray);
		};
	};

	if (white!=sf::Color::White){
		for(unsigned int i(0); i<w.size(); i++){
			bg.setPixel(w[i].x,w[i].y, white);
		};

		for(unsigned int i(0); i<w_b.size(); i++){
			border.setPixel(w_b[i].x,w_b[i].y, white);
		};
	};


}

void GBPicture::setPic(sf::Image& pic)
{
	bg=pic;
	//On vide les couleurs de l'image précédente.
	dG.clear();
	lG.clear();
	w.clear();
	b.clear();
	//On parse l'image et on stocke les pixels colorés dans 4 tableaux
	int imx(0), imy(0);
	sf::Vector2u size(bg.getSize());

	for (imx; imx<size.x; imx++)
	{
		for (imy; imy<size.y; imy++)
		{

			if ((bg.getPixel(imx,imy) == DarkGray) || (bg.getPixel(imx,imy) == EmuDG)){
				dG.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if ((bg.getPixel(imx,imy) == LiteGray) || (bg.getPixel(imx,imy) == EmuLG)){
				lG.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if (bg.getPixel(imx,imy) == sf::Color::White){
				w.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if ((bg.getPixel(imx,imy) == sf::Color::Black) || (bg.getPixel(imx,imy) == EmuBlack)){
				b.push_back(sf::Vector2i(imx,imy));
				continue;
			}
		}
		imy=0;
	}

	setColor(sf::Color::Black,DarkGray,LiteGray,sf::Color::White);
	//au cas ou les couleurs de l'image originale sont des couleurs d'émulateur, on remet les couleurs pures.

}

void GBPicture::setColor(sf::Color newB, sf::Color newDG, sf::Color newLG, sf::Color newW) //Change les 4 couleurs.
{
	//Si la nouvelle couleur est différente de la couleur actuelle, on la change. Sinon, on laisse tel quel, économie mémoire etc
	if (newB!=black){
		black=newB;
		for(unsigned int i(0); i<b.size(); i++)
			bg.setPixel(b[i].x,b[i].y, newB);

		for(unsigned int i(0); i<b_b.size(); i++){
			border.setPixel(b_b[i].x,b_b[i].y, black);
		};
	};

	if (newLG!=lGray){
		lGray=newLG;
		for(unsigned int i(0); i<lG.size(); i++)
			bg.setPixel(lG[i].x,lG[i].y, newLG);

		for(unsigned int i(0); i<lG_b.size(); i++){
			border.setPixel(lG_b[i].x,lG_b[i].y, lGray);
		};
	};

	if (newDG!=dGray){
		dGray=newDG;
		for(unsigned int i(0); i<dG.size(); i++)
			bg.setPixel(dG[i].x,dG[i].y, newDG);

		for(unsigned int i(0); i<dG_b.size(); i++){
			border.setPixel(dG_b[i].x,dG_b[i].y, dGray);
		};
	};

	if (newW!=white){
		white=newW;
		for(unsigned int i(0); i<w.size(); i++)
			bg.setPixel(w[i].x,w[i].y, newW);

		for(unsigned int i(0); i<w_b.size(); i++){
			border.setPixel(w_b[i].x,w_b[i].y, white);
		};
	};

}

void GBPicture::setBorder(sf::Image& brd) //Change la bordure.
{
	border=brd;
	//On vide les coordonnées de la bordure précédente pour pas avoir un mix horrible des 2 bordures.
	dG_b.clear();
	lG_b.clear();
	w_b.clear();
	b_b.clear();

	int imx(0), imy(0);
	sf::Vector2u size(border.getSize());

	for (imx; imx<size.x; imx++)
	{
		for (imy; imy<size.y; imy++)
		{

			if (border.getPixel(imx,imy) == DarkGray){
				dG_b.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if (border.getPixel(imx,imy) == LiteGray){
				lG_b.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if (border.getPixel(imx,imy) == sf::Color::White){
				w_b.push_back(sf::Vector2i(imx,imy));
				continue;
			}

			if (border.getPixel(imx,imy) == sf::Color::Black){
				b_b.push_back(sf::Vector2i(imx,imy));
				continue;
			}
		}
		imy=0;
	}

	//kopipe: On swappe les couleurs
	for(unsigned int i(0); i<b_b.size(); i++){
		border.setPixel(b_b[i].x,b_b[i].y, black);
	};
	for(unsigned int i(0); i<lG_b.size(); i++){
		border.setPixel(lG_b[i].x,lG_b[i].y, lGray);
	};
	for(unsigned int i(0); i<dG_b.size(); i++){
		border.setPixel(dG_b[i].x,dG_b[i].y, dGray);
	};
	for(unsigned int i(0); i<w_b.size(); i++){
		border.setPixel(w_b[i].x,w_b[i].y, white);
	};

}

void GBPicture::update()
{
	sf::Image render(border);
	render.copy(bg,16,16);
	//render.saveToFile("test2.png"); //This werks
	picTex.update(render);
}

GBPicture::~GBPicture(){

	//destructeur? idk

}
