#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

/*This class alters graphics. Use its components to change game logic or place and edit graphics.*/
class Transform
{
public:
	Transform();
	~Transform();

	/*Holds the value of where in the screen it's located.*/
	class Position
	{
	public:
		Position(){};
		Position(int posX, int posY)
		{
			x = posX;
			y = posY;
		}
		~Position(){};

		int x, y;
		
		Position Zero()
		{
			Position v = Position(0, 0);
			return v;
		};
		
		Position One()
		{
			Position v = Position(1, 1);
			return v;
		};
	};

	/*Used to manipulate Position's values.*/
	class Velocity
	{
	public:
		Velocity(){};
		Velocity(int velX, int velY)
		{
			x = velX;
			y = velY;
		}
		~Velocity(){};

		int x, y;
		
		Velocity Zero()
		{
			Velocity v = Velocity(0, 0);
			return v;
		};
		
		Velocity One()
		{
			Velocity v = Velocity(1, 1);
			return v;
		};
	};

	/*Use to manipulate size of the object.*/
	class Size
	{
	public:
		Size(){};
		Size(int width, int height)
		{
			w = width;
			h = height;
		}
		~Size(){};

		int w, h;
		
		Size Zero()
		{
			Size s = Size(0, 0);
			return s;
		};
		
		Size One()
		{
			Size s = Size(1, 1);
			return s;
		};
	};

	/*Use to manipulate the color of the object. A list of common colors are already pre-defined.*/
	class Color
	{
	public:
		Color() {};
		Color(int red, int green, int blue)
		{
			LimitAllColors(red, green, blue);
			r = red; g = green; b = blue;
		}
		~Color(){};

		int r, g, b;

		bool GetDifference(Color c1, Color c2)
		{
			return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
		}
		
		Color Black(int modifier = 0)
		{
			Color c = Color(0, 0, 0);
			ColorModifier(c, true, true, true, modifier);
			LimitAllColors(c.r, c.g, c.b);
			return c;
		};
		
		Color White(int modifier = 255)
		{
			Color c = Color(255, 255, 255);
			ColorModifier(c, true, true, true, modifier);
			LimitAllColors(c.r, c.g, c.b);
			return c;
		};
		
		Color Red(int modifier = 255)
		{
			Color c = Color(255, 0, 0);
			ColorModifier(c, true, false, false, modifier);
			ColorLimit(c.r);
			return c;
		};
		
		Color Green(int modifier = 255)
		{
			Color c = Color(0, 255, 0);
			ColorModifier(c, false, true, false, modifier);
			ColorLimit(c.g);
			return c;
		};
		
		Color Blue(int modifier = 255)
		{
			Color c = Color(0, 0, 255);
			ColorModifier(c, false, false, true, modifier);
			ColorLimit(c.b);
			return c;
		};

		Color Yellow(int modifier = 255)
		{
			Color c = Color(255, 255, 0);
			ColorModifier(c, true, true, false, modifier);
			ColorLimit(c.r); ColorLimit(c.g);
			return c;
		};

		Color Turquoise(int modifier = 255)
		{
			Color c = Color(0, 255, 255);
			ColorModifier(c, false, true, true, modifier);
			ColorLimit(c.g); ColorLimit(c.b);
			return c;
		};

		Color Purple(int modifier = 255)
		{
			Color c = Color(255, 0, 255);
			ColorModifier(c, true, false, true, modifier);
			ColorLimit(c.r); ColorLimit(c.b);
			return c;
		};

		Color Orange(int modifier = 165)
		{
			Color c = Color(255, 0, 0);
			ColorModifier(c, false, true, false, modifier);
			ColorLimit(c.g);
			return c;
		};

		Color Gray(int modifier = 100)
		{
			Color c = Color(0, 0, 0);
			ColorModifier(c, true, true, true, modifier);
			LimitAllColors(c.r, c.g, c.b);
			return c;
		};
	private:
		void ColorLimit(int& value)
		{
			if(value > 255)
				value = 255;
			else if(value < 0)
				value = 0;
		}

		void LimitAllColors(int& r, int& g, int& b)
		{
			ColorLimit(r); ColorLimit(g); ColorLimit(b);
		}

		void ColorModifier(Color& c, bool changeRed, bool changeGreen, bool changeBlue, int modifier)
		{
			if(changeRed) c.r += modifier; 
			if(changeGreen) c.g += modifier; 
			if(changeBlue) c.b += modifier;
		}
	};
	
	//Use these functions to move an object based on its position.
	virtual void Move(int x, int y, float delta);
	virtual void Move(Velocity velocity, float delta);
	virtual void MoveUp(float delta);
	virtual void MoveDown(float delta);
	virtual void MoveLeft(float delta);
	virtual void MoveRight(float delta);

	//Use these functions to set a new or get current position/velocity/size of the object.
	virtual void SetPosition(int x, int y);
	virtual void SetPosition(Position position);
	virtual void SetVelocity(int x, int y);
	virtual void SetVelocity(Velocity velocity);
	virtual void SetSize(int w, int h);
	virtual void SetSize(Size size);
	virtual void SetColor(int r, int g, int b);
	virtual void SetColor(Color color);
	virtual Position GetPosition();
	virtual Velocity GetVelocity();
	virtual Size GetSize();
	virtual Color GetColor();
	
	//Use these to manipulate current velocity based on its current values.
	virtual void AddVelocity(int x, int y);
	virtual void AddVelocity(Velocity velocity);
	virtual void SubVelocity(int x, int y);
	virtual void SubVelocity(Velocity velocity);
	virtual void InvertVelocityX();
	virtual void InvertVelocityY();

	//Sets new individual value of position/velocity/size.
	virtual void SetPositionX(int x);
	virtual void SetPositionY(int y);
	virtual void SetVelocityX(int x);
	virtual void SetVelocityY(int y);
	virtual void SetSizeW(int w);
	virtual void SetSizeH(int h);

private:
	Position _position;
	Velocity _velocity;
	Size _size;
	Color _color;
};

#endif