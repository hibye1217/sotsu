#include "Rectangle.h"

int main() {
	Shape* s = new Rectangle;
	s->scale();
	delete s;
	Shape* r = new Rectangle;
	r->draw();
	delete r;
}