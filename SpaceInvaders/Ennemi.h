#include "Element.h"

class Ennemi : public Element
{
public:
	Ennemi(const sf::Texture&, int, int);
	Ennemi();

	int static tailleSprite;

protected:
};

