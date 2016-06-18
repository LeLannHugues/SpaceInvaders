#include <SFML/Graphics.hpp>


#pragma once
class Element
{
public:
	Element(const sf::Texture& texture);
	Element();
	int getVie();
	void setVie(int nouvelleVie);
	sf::Sprite& getSprite();
	void setTexture(const sf::Texture&);


protected:
	int vie;
	sf::Sprite sprite;

};

