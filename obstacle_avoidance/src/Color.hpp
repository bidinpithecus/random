#ifndef _COLOR_HPP_
#define _COLOR_HPP_

class Color {
	public:
		Color();
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);
		Color(unsigned char r, unsigned char g, unsigned char b);
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		Color(int hexColor);

		float getRed();
		float getGreen();
		float getBlue();
		float getSaturation();
		void setRed(float r);
		void setGreen(float g);
		void setBlue(float b);
		void setSaturation(float a);

		void paint();

	private:
		float r;
		float g;
		float b;
		float a;
};

#endif
