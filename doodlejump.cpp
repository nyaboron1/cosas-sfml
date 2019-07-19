#include <SFML/Graphics.hpp>

#include <time.h>

using namespace sf;

#define ancho 481
#define alto 850
#define plataformas 11

struct Point
{
  int x [plataformas];
  int y [plataformas];
};


int main()
{
  srand(time(0));
  
  RenderWindow app (VideoMode(ancho, alto), "Doodle Game");
  app.setFramerateLimit (60);

  Texture t1;
  Texture t2;
  Texture t3;
  t1.loadFromFile ("images/background.png");
  t2.loadFromFile ("images/platform.png");
  t3.loadFromFile ("images/doodle.png");

  Sprite sBackground (t1);
  Sprite sPlat (t2);
  Sprite sPers (t3);


  Point plat;

  for (int i = 0; i < plataformas; ++i)
    {
      plat.x[i] = rand() % ancho;
      plat.y[i] = rand() % alto;
    }

  // posición inicial
  int x = ancho / 2;
  int y = alto - 100;
  // altura a actualizar las plataformas
  int h = 100;
  
  float dy = 0;

  
  while (app.isOpen())
    {
      
      Event e;
      while (app.pollEvent(e))
	{
	  if (e.type == Event::Closed)
	    {
	      app.close();
	    }
	}

      //********************************************************* Eventos teclado
      if (Keyboard::isKeyPressed (Keyboard::Right) && x < ancho-80)
	{
	  x += 3;
	}
      else if (Keyboard::isKeyPressed (Keyboard::Left) && x > 0)
	{
	  x -= 3;
	}

      //******************************************************** Nuevas posiciones
      dy += 0.2;
      y += dy;
      
      if (y>500)
	dy =- 10;
      
      if (y < h)
	{
	  for (int i = 0; i < plataformas; i++)
	    {
	      y = h;
	      plat.y[i] = plat.y[i] - dy;

	      if (plat.y[i] > alto)
		{
		  plat.y[i] = 0;
		  plat.x[i] = rand() % ancho;
		}
	    }
	}

      
      //******************************************************** colisión
      for (int i = 0; i < plataformas; i++)
      {
	if ((x + 50 > plat.x[i]) && (x + 20 < plat.x[i] + 68)
	    && (y + 70 > plat.y[i]) && (y + 70 < plat.y[i] + 14) && (dy > 0))
	    {
	    	dy=-10;
	    }
      }
      
      //*++++++++++++++++++++++++++++++++++++++++++++++++++++ Dibujar
      sPers.setPosition (x, y);
      app.draw (sBackground);
      app.draw (sPers);

      for (int i = 0; i < plataformas; ++i)
	{
	  sPlat.setPosition (plat.x[i], plat.y[i]);
	  app.draw (sPlat);
	}
      
      app.display();
    }
}
