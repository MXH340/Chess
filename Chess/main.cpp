#include<SFML/Graphics.hpp>
#include<time.h>
using namespace sf;

void Draw(RenderWindow& app);
void loadPosition();

int size = 56;

Sprite s, bk;
Sprite f[32];

int boards[8][8] = {
	-1, -2, -3, -4,- 5, -3, -2, -1,
	-6, -6, -6, -6, -6, -6, -6, -6,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 6,  6,  6,  6,  6,  6,  6,  6,
	 1,  2,  3,  4,  5,  3,  2,  1
};

int main()
{
	bool isMove = false;
	float dx = 0, dy = 0;
	int n = 0;
	RenderWindow app(VideoMode(453, 453), "Chess");
	app.setFramerateLimit(60);
	Texture t1, t2;
	t1.loadFromFile("images/figures.png");
	t2.loadFromFile("images/board0.png");
	s.setTexture(t1);
	bk.setTexture(t2);

	for (int i = 0; i < 32; i++)
		f[i].setTexture(t1);
	loadPosition();

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
			else if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					for (int i = 0; i < 32; i++)
					{
						if (f[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							isMove = true;
							n = i;
							dx = pos.x - f[i].getPosition().x;
							dy = pos.y - f[i].getPosition().y;
						}
					}
				}
			}
			else if (e.type == Event::MouseButtonReleased)
			{
				if (e.key.code == Mouse::Left)
					isMove = false;
			}
		}
		if (isMove)
			f[n].setPosition(pos.x - dx, pos.y - dy);
		Draw(app);
	}

	return 0;
}

void Draw(RenderWindow& app)
{
	app.clear();
	app.draw(bk);
	for (int i = 0; i < 32; i++)
	{
		app.draw(f[i]);
	}
	app.display();
}


//ÆåÅÌ³õÊ¼»¯
void loadPosition()
{
	int k = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int n = boards[i][j];
			if (!n)
				continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			f[k].setTextureRect(IntRect(size * x, size * y, size, size));
			f[k].setPosition(size * j, size * i);
			k++;
		}
	}
}