#include "Ennemi.h"

int Ennemi::tailleSprite = 32;


Ennemi::Ennemi(const sf::Texture& texture, int tailleMapX, int posY) : Element(texture)
{
	sprite.setPosition(sf::Vector2f(tailleMapX - 10.0f, posY*1.0f));
}

Ennemi::Ennemi() : Element()
{

}