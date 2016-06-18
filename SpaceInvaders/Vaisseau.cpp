#include "Vaisseau.h"


int Vaisseau::tailleSprite = 64;

Vaisseau::Vaisseau(const sf::Texture& texture, int tailleMapY) : Element(texture)
{
	sprite.setPosition(sf::Vector2f(10.0f, tailleMapY * 0.4f));
}

Vaisseau::Vaisseau() : Element()
{

}
