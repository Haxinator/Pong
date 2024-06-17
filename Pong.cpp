#include "Bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	//create video mode object
	VideoMode vm(1920, 1080);\

	//create and open window for the game
	RenderWindow window(vm, "Pong", Style::Fullscreen);

	// Low res code
	View view(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(view);

	int score = 0;
	int lives = 3;

	//Create a bat at the bottom center of the screen
	Bat bat(1920 / 2, 1080 - 20);

	//Add ball later

	//Create a text object called HUD
	Text hud;

	//load cool retro font
	Font font;
	font.loadFromFile("fonts/PressStartRegular-ay8E.ttf");

	//set the hud font to loaded style
	hud.setFont(font);

	//make it big
	hud.setCharacterSize(40);

	//Choose a colour
	hud.setFillColor(Color::White);

	hud.setPosition(20, 20);

	//Clock for timing
	Clock clock;

	while (window.isOpen())
	{
		/*
		Handle player input
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				//quit the game when the window is closed
				window.close();
			}
		}

		//handle player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//hanlde pressing and releasing arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else {
			bat.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else {
			bat.stopRight();
		}

		/*
		Update the bat, ball and HUD
		*/
		//update the delta time
		Time dt = clock.restart();
		bat.update(dt);
		//Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << " Lives:" << lives;
		hud.setString(ss.str());

		/*
		Draw the bat, the ball and HUD
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.display();
	}

	return 0;
}