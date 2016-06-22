#include "common.h"

void Qusy::Point::setPoint(int x, int y)
{
	posX = x;
	posY = y;
}

void Qusy::PointF::setPointF(float x, float y)
{
	fposX = x;
	fposY = y;
}


void Qusy::Position::setPosition(int X, int Y, int Z)
{
	posX = X;
	posY = Y;
	posZ = Z;
}

void Qusy::Rect::setRect(int x1, int y1, int x2, int y2)
{
	posX1 = x1;
	posY1 = y1;
	posX2 = x2;
	posY2 = y2;
}

void Qusy::Circle::setCircle(Rect rect)
{
	radius = static_cast<float>((rect.posX2 - rect.posX1) * 0.5f);

	center.posX = static_cast<int>(static_cast<float>(rect.posX1) + radius);
	center.posY = static_cast<int>(static_cast<float>(rect.posY1) + radius);
}

bool Qusy::Collision(Point pt, Rect rt)
{
	bool result = true;
	if(pt.posX < rt.posX1) {
		result = false;
	}
	if(pt.posX > rt.posX2) {
		result = false;
	}
	if(pt.posY < rt.posY1) {
		result = false;
	}
	if(pt.posY > rt.posY2) {
		result = false;
	}
	return result;
}

bool Qusy::Collision(Point pt, Circle cc)
{
	float xSquare = static_cast<float>(pt.posX - cc.center.posX);
	float ySquare = static_cast<float>(pt.posY - cc.center.posY);

	if( cc.radius*cc.radius < (xSquare * xSquare) + (ySquare * ySquare) ) {
		return false;
	}

	return true;
}