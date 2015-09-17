#include "Color.h"


Color::Color(float r,float g,float b,float a) : a(a),b(b),r(r),g(g)
{

}

Color::Color()
{

}

Color Color::Black()
{
	return Color(0.0f,0.0f,0.0f,1.0f);
}

Color Color::White()
{
	return Color(1.0f,1.0f,1.0f,1.0f);
}

Color Color::Red()
{
	return Color(1.0f,0.0f,0.0f,1.0f);
}

Color Color::Blue()
{
	return Color(0.0f,0.0f,1.0f,1.0f);
}
