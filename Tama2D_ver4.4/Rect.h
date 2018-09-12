#ifndef RECTANGLE_H
#define RECTANGLE_H

#include"Space/Vector2.h"

	class Rect
	{
	public:
		Rect();

		bool isIntersect(const Rect& r)const;
		void setPosition(const Vector2&);
		void setPosition(float, float);
		void setSize(const Vector2&);
		void setSize(float, float);
		void setOffset(const Vector2&);
		void setOffset(float, float);
		void setSizeRate(const Vector2&);
		void setSizeRate(float, float);

		//ãÍì˜ÇÃçÙÇÃvelocity.Å@è’ìÀÇ∑ÇÈÇ»ÇÁtrue
		void restrictMove(
			Vector2* moveVectorInOut,
			const Rect& r,
			const Vector2& playerPrevMove = Vector2(0.f, 0.f))const;

		float offsetX()const;
		float offsetY()const;
		float sizeRateX()const;
		float sizeRateY()const;
	private:
		int m_x;
		int m_y;
		int m_sizeX;
		int m_sizeY;
		int m_offsetX;
		int m_offsetY;
		float m_sizeRateX;
		float m_sizeRateY;
	};

#endif