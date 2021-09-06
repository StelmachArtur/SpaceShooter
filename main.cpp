#include "Game.h"


int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "SpaceShooter");
	Game game(&window);
	
	while (window.isOpen()&& game.active)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
			game.Update();
			game.Draw();
	}
	
	game.Update();
	game.Update();
	game.Draw();

	system("pause");
	return 0;
}