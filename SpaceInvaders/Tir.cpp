#include "Tir.h"
#include "Element.h"
#include "Vaisseau.h"

int Tir::tailleSprite = 8;


Tir::Tir(Vaisseau vaisseau, const sf::Texture& texture) : Element(texture)
{
	sprite.setPosition(sf::Vector2f(vaisseau.getSprite().getPosition().x + Vaisseau::tailleSprite, vaisseau.getSprite().getPosition().y + Vaisseau::tailleSprite / 2));
}

Tir::Tir() : Element()
{

}