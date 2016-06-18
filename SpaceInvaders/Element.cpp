#include <SFML/Graphics.hpp>
#include "Element.h"
#include <iostream>

using namespace std;


Element::Element(const sf::Texture& texture)
{
	vie = 1;
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(30, 30));

}

Element::Element()
{
	vie = 1;
	sprite.setPosition(sf::Vector2f(30, 30));
}

int Element::getVie()
{
	return vie;
}

void Element::setVie(int nouvelleVie)
{
	vie = nouvelleVie;
}

sf::Sprite& Element::getSprite()
{
	return sprite;
}

void Element::setTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

