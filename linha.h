#ifndef _LINHA_H_
#define _LINHA_H_

class Coordenada
{
private:
	int x;
	int y;
public:
	Coordenada()
	{
		setX(0);
		setY(0);
	}
	
	Coordenada(int x, int y)
	{
		setX(x);
		setY(y);
	}
	
	inline int getX()
	{
		return x;
	}
	
	inline void setX(int x)
	{
		this->x = x;
	}
	
	inline int getY()
	{
		return y;
	}
	
	inline void setY(int y)
	{
		this->y = y;
	}
};

class Linha
{
private:
	/* cor da linha */
	float r, g, b;
	Coordenada p1;
	Coordenada p2;
public:
	Linha(int x1, int y1, int x2, int y2, float r, float g, float b);

	virtual void render();
	
	inline Coordenada& getP1()
	{
		return p1;
	} 
	
	inline Coordenada& getP2()
	{
		return p2;
	} 

	inline void setColor(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

#endif /* _LINHA_H_ */