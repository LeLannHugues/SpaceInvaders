#include "Element.h"
#include "Vaisseau.h"

#pragma once
class Tir : public Element
{
public:
	Tir(Vaisseau, const sf::Texture&);
	Tir();

	int static tailleSprite;

private:
};

