
#include<glm.hpp>

#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square
{
public:

	enum DIRECTION
	{
		DIR_RIGHT = 1,
		DIR_LEFT = -1,
		DIR_UP = 2,
		DIR_DOWN = -2

	};
		
	Square(float x,float y,float length);
	
	glm::vec3 getPosition();
	glm::vec4 getColor();
	void setDirection(DIRECTION dir);
	DIRECTION getDirection();
	void move();
private:
	glm::vec4 color;
	glm::vec3 position;
	DIRECTION   direction;

	float length;
};



#endif
