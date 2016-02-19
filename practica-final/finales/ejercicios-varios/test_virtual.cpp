#include <iostream>

#define WITH_VIRTUAL 0

#if WITH_VIRTUAL
#define VIRTUAL virtual
#else
#define VIRTUAL
#endif

namespace
{
	bool fillMode = false;
}

bool setFillMode(bool fm)
{
	bool ofm = fillMode;
	fillMode = fm;
	return ofm;
}

class Shape
{
	VIRTUAL void llDraw() const
	{
		std::cout << "Draws a(n) " << (fillMode ? "filled" : "empty")
			<< " 'shape'.\n";
	}

public:
	void drawEmpty() const
	{
		bool oldFillMode = ::setFillMode(false);
		llDraw();
		::setFillMode(oldFillMode);
	}
	void drawFilled() const
	{
		bool oldFillMode = ::setFillMode(true);
		llDraw();
		::setFillMode(oldFillMode);
	}
};

class Triangle : public Shape
{
	virtual void llDraw() const
	{
		std::cout << "Draws a(n) " << (fillMode ? "filled" : "empty")
			<< " triangle.\n";
	}
};

class Square : public Shape
{
	virtual void llDraw() const
	{
		std::cout << "Draws a(n) " << (fillMode ? "filled" : "empty")
			<< " square.\n";
	}
};

int main()
{
	Square s;
	Triangle t;

	s.drawEmpty();
	s.drawFilled();
	t.drawEmpty();
	t.drawFilled();

	return 0;
}
