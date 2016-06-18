#include <SFML/Graphics.hpp>
#include "Vaisseau.h"
#include "Tir.h"
#include "Ennemi.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

#pragma region variables
sf::Texture textVaisseau;
sf::Texture textMissile;
sf::Texture textEnnemi;
sf::Texture imageFond;
sf::Sprite fond;
std::vector<Tir> missiles;
std::vector<Ennemi> invaders;
long aleaApparition;
long aleaPosition;
enum Dir{Up,Left,Down,Right};
#pragma endregion variables

#pragma region constantes
int const speed = 3;
int const tailleMapX = 1200;
int const tailleMapY = 800;
int const tailleSpriteVaisseau = 64;
int const tailleSpriteMissile = 8;
int const tailleSpriteEnnemi = 32;
#pragma endregion constantes

#pragma region prototypes
void gestionClavier(Vaisseau&, sf::Clock&);
void chargerTextures();
void apparition();
void gestionMissiles();
void gestionInvaders();
void gestionCollisions(Vaisseau&);
void draw(sf::RenderWindow&, Vaisseau);
void updateGame(sf::Time);
void impact(Element&, Element&);
#pragma endregion prototypes



int main()
{

	srand(time(0));
	sf::RenderWindow window;
	window.create(sf::VideoMode(tailleMapX, tailleMapY), "SpaceInvaders");
	window.setFramerateLimit(60);

	chargerTextures();
	fond.setTexture(imageFond);

	Vaisseau vaisseau(textVaisseau, tailleMapY);
	
	sf::Clock clock;
	sf::Clock tempsMissiles;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || vaisseau.getVie() == 0)	window.close();
		}

		gestionClavier(vaisseau, tempsMissiles);
		apparition();
		gestionMissiles();
		gestionInvaders();
		gestionCollisions(vaisseau);

		draw(window, vaisseau);

		sf::Time delai = clock.restart();
		updateGame(delai);
	}
	

	return 0;
}

void chargerTextures()
{
	if (!textVaisseau.loadFromFile("Textures\\vaisseau.png", sf::IntRect(128, 128, Vaisseau::tailleSprite, Vaisseau::tailleSprite)))
	{
		std::cout << "Erreur chargement texture vaisseau" << std::endl;
	}
	if (!textMissile.loadFromFile("Textures\\laser.png", sf::IntRect(0, 0, Tir::tailleSprite, Tir::tailleSprite)))
	{
		std::cout << "Erreur chargement texture missile" << std::endl;
	}
	if (!textEnnemi.loadFromFile("Textures\\pierre.png", sf::IntRect(0, 0, Ennemi::tailleSprite, Ennemi::tailleSprite)))
	{
		std::cout << "Erreur chargement texture pierre" << std::endl;
	}
	if (!imageFond.loadFromFile("Textures\\galaxie2.png", sf::IntRect(0, 0, tailleMapX, tailleMapY)))
	{
		std::cout << "Erreur chargement texture image de fond" << std::endl;
	}
}

void gestionClavier(Vaisseau& vaisseau,sf::Clock& clock)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && vaisseau.getSprite().getPosition().y > 0)
	{
		vaisseau.getSprite().move(0, -2*speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && vaisseau.getSprite().getPosition().y < (tailleMapY - Vaisseau::tailleSprite))
	{
		vaisseau.getSprite().move(0, 2*speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && vaisseau.getSprite().getPosition().x < (tailleMapX - Vaisseau::tailleSprite))
	{
		vaisseau.getSprite().move(2*speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && vaisseau.getSprite().getPosition().x > 0)
	{
		vaisseau.getSprite().move(-2*speed, 0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		sf::Time delaiMissiles = clock.getElapsedTime();
		if (delaiMissiles.asMilliseconds() > 200)
		{
			Tir tir(vaisseau, textMissile);
			missiles.push_back(tir);
			clock.restart();
		}
	}
}

void apparition()
{
	aleaApparition = rand() % 100;
	if (aleaApparition == 1)
	{
		aleaPosition = rand() % (tailleMapY-Ennemi::tailleSprite);
		Ennemi ennemi(textEnnemi, tailleMapX, aleaPosition);
		invaders.push_back(ennemi);
	}
}

void gestionMissiles()
{
	int i = 0;
	while (i<missiles.size())
	{
		missiles[i].getSprite().setPosition(sf::Vector2f(missiles[i].getSprite().getPosition().x + speed * 3, missiles[i].getSprite().getPosition().y));

		if (missiles[i].getSprite().getPosition().x >= tailleMapX + Tir::tailleSprite)
		{
			missiles[i].setVie(0);
		}

		if (missiles[i].getVie() == 0)
		{
			missiles.erase(missiles.begin() + i);
		}

		i++;
	}
}

void gestionInvaders()
{
	int i = 0;
	while (i < invaders.size())
	{
		invaders[i].getSprite().setPosition(sf::Vector2f(invaders[i].getSprite().getPosition().x - speed, invaders[i].getSprite().getPosition().y));

		if (invaders[i].getSprite().getPosition().x < -Ennemi::tailleSprite)
		{
			invaders[i].setVie(0);
		}

		if (invaders[i].getVie() == 0)
		{
			invaders.erase(invaders.begin() + i);
		}
		
		i++;
	}
}

void gestionCollisions(Vaisseau& vaisseau)
{
	int i = 0;
	int j;
	int k = 0;
	while (i < missiles.size())
	{
		j = 0;
		while (j < invaders.size())
		{

			if (!	((missiles[i].getSprite().getPosition().x >= invaders[j].getSprite().getPosition().x + Ennemi::tailleSprite)
				||	(missiles[i].getSprite().getPosition().x + Tir::tailleSprite <= invaders[j].getSprite().getPosition().x)
				||	(missiles[i].getSprite().getPosition().y >= invaders[j].getSprite().getPosition().y + Ennemi::tailleSprite)
				||	(missiles[i].getSprite().getPosition().y + Tir::tailleSprite <= invaders[j].getSprite().getPosition().y))		)
			{
				impact(missiles[i], invaders[j]);
			}
			j++;
		}
		i++;
	}

	while (k < invaders.size())
	{
		if (!	((invaders[k].getSprite().getPosition().x >= vaisseau.getSprite().getPosition().x + Vaisseau::tailleSprite)
			||	(invaders[k].getSprite().getPosition().x + Ennemi::tailleSprite <= vaisseau.getSprite().getPosition().x)
			||	(invaders[k].getSprite().getPosition().y >= vaisseau.getSprite().getPosition().y + Vaisseau::tailleSprite)
			||	(invaders[k].getSprite().getPosition().y + Ennemi::tailleSprite <= vaisseau.getSprite().getPosition().y))		)
		{
			impact(invaders[k], vaisseau);
		}
		k++;
	}
}

void draw(sf::RenderWindow& window, Vaisseau vaisseau)
{
	window.clear();
	int i=0;
	window.draw(fond);
	if (vaisseau.getVie() != 0)
	{
		window.draw(vaisseau.getSprite());
	}
	while (i<missiles.size())
	{
		window.draw(missiles[i].getSprite());
		i++;
	}
	i = 0;
	while (i<invaders.size())
	{
		window.draw(invaders[i].getSprite());
		i++;
	}

	window.display();
}

void updateGame(sf::Time delai)
{
	sf::sleep(sf::milliseconds(30 - delai.asMilliseconds()));
}

void impact(Element& element1, Element& element2)
{
	//element1.setVie(element1.getVie() - 1);
	//element2.setVie(element2.getVie() - 1);
	element1.setVie(0);
	element2.setVie(0);
}
