#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	//get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//create video mode object
	VideoMode vm(resolution.x, resolution.y);
	//VideoMode vm(960, 540);

	//create and open window for the game
	RenderWindow window(vm, "Pong", Style::Fullscreen);

	// Low res code
	//View view(sf::FloatRect(0, 0, 1920, 1080));
	//window.setView(view);

	int score = 0;
	int lives = 3;

	//Create a bat at the bottom center of the screen
	Bat bat(resolution.x / 2, resolution.y - 20);

	//create a ball
	Ball ball(resolution.x / 2, 0);

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
		ball.update(dt);

		//Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << " Lives:" << lives;
		hud.setString(ss.str());

		//Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			//reverse ball direction
			ball.reboundBottom();

			//remove life
			lives--;

			//check for zero lives
			if (lives < 1) {
				//reset score
				score = 0;
				//reset lives
				lives = 3;
			}
		}

		//Handle ball hitting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();

			//add point to score;
			score++;
		}

		//Handle ball hitting sides
		if (ball.getPosition().left < 0 ||
			ball.getPosition().left + ball.getPosition().width >
			window.getSize().x)
		{
			ball.reboundSides();
		}

		//Handle ball hitting bat
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			//hit detected so reverse ball
			ball.reboundBatOrTop();
		}


		/*
		Draw the bat, the ball and HUD
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}