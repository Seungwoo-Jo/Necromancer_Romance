#ifndef _COMMON_H_
#define _COMMON_H_

#define NULL					0
#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=NULL; } }

namespace Qusy
{
	struct Position
	{
		int posX, posY, posZ;

		void setPosition(int, int, int);
	};

	struct Point
	{
		int posX, posY;

		void setPoint(int, int);
	};

	
	struct PointF
	{
		float fposX, fposY;

		void setPointF(float, float);
	};
	
	

	struct Rect
	{
		int posX1, posY1;
		int posX2, posY2;

		void setRect(int, int, int, int);
	};

	struct Circle
	{
		Point center;
		float radius;

		void setCircle(Rect);
		void setCircle(float, float);
	};

	// 점과 박스 충돌
	bool Collision(Point, Rect);

	// 점과 원 충돌
	bool Collision(Point, Circle);
}

#endif