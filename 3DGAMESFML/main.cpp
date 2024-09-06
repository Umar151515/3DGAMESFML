#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "WorldMap.h"
#include "RayCasting.h"

using namespace sf;

int main() 
{
	RenderWindow window(VideoMode(1200, 800), "3DGAME");
	Clock clock;
	Player player(&window);
	WorldMap worldMap(&player);


	Vector2u windowSize = window.getSize();
	float windowWidth = static_cast<float>(windowSize.x);
	float windowHeight = static_cast<float>(windowSize.y);

	RectangleShape sky(Vector2f(windowWidth, windowHeight / 2));
	sky.setFillColor(Color(135, 206, 235));
	RectangleShape land(Vector2f(windowWidth, windowHeight / 2));
	land.setFillColor(Color(86, 61, 57));
	land.setPosition(0, windowHeight / 2);

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::W) {
					player.w = true;
				}
				else if (event.key.code == Keyboard::S) {
					player.s = true;
				}
				if (event.key.code == Keyboard::A) {
					player.a = true;
				}
				else if (event.key.code == Keyboard::D) {
					player.d = true;
				}
				if (event.key.code == Keyboard::Left) {
					player.left = true;
				}
				else if (event.key.code == Keyboard::Right) {
					player.right = true;
				}
			}
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::W) {
					player.w = false;
				}
				else if (event.key.code == Keyboard::S) {
					player.s = false;
				}
				if (event.key.code == Keyboard::A) {
					player.a = false;
				}
				else if (event.key.code == Keyboard::D) {
					player.d = false;
				}
				if (event.key.code == Keyboard::Left) {
					player.left = false;
				}
				else if (event.key.code == Keyboard::Right) {
					player.right = false;
				}
			}
		}

		sf::Time deltaTime = clock.restart();
		float delta = deltaTime.asSeconds();

		window.clear();
		player.update(delta);
		window.draw(sky);
		window.draw(land);
		RayCasting(&player, &window, &worldMap);
		window.display();
	}
}