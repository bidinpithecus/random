#ifndef _COORDINATE_HPP_
#define _COORDINATE_HPP_

class Coordinate {
	public:
		Coordinate();
		Coordinate(float x, float y, float z);
		Coordinate(float same);
		~Coordinate();
		float getX();
		float getY();
		float getZ();
		void setX(float x);
		void setY(float y);
		void setZ(float z);

		bool operator==(Coordinate coordinate);
		bool operator!=(Coordinate coordinate);

		Coordinate operator+(Coordinate coordinate);
		Coordinate operator-(Coordinate coordinate);
		Coordinate operator*(float num);
		Coordinate operator/(float num);

		void operator +=(Coordinate coordinate);
		void operator -=(Coordinate coordinate);
		void operator *=(float num);
		void operator /=(float num);

		float distance(Coordinate coordinate);

	private:
		float x;
		float y;
		float z;
};

#endif
