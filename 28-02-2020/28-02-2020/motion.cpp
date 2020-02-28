#include <SFML/Graphics.hpp>


int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	//sf::CircleShape circle(50);
	sf::Texture texture;
	texture.loadFromFile("Quake-Live-256.png");
	sf::Sprite circle(texture);
	circle.setScale(0.4, 0.4);
	sf::Clock clock;
	sf::Vector2u circleSize = circle.getTexture()->getSize();
	circle.setOrigin(circleSize.x / 2, circleSize.y / 2);
	const float Pi = 3.14159f;
	while (window.isOpen()) {
		sf::Event event;
		/*(while (window.pollEvent(event));
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}*/
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f center = circle.getPosition();
		sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;
		circle.setRotation(90 + atan2f(d.y, d.x) * 180 / Pi);
		//window.clear(sf::Color::White);
		window.clear(sf::Color::Color(50, 50, 50));
		window.pollEvent(event);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//left mouse button is pressed: shoot
			sf::Vector2f 
		}
		switch (event.type) {
		case (sf::Event::Closed):
			window.close();
			break;
		case(sf::Event::KeyPressed):
			if (event.key.code == sf::Keyboard::Left && circle.getPosition().x > 0) {
				circle.move(-1, 0);
			}
			if (event.key.code == sf::Keyboard::Right && circle.getPosition().x < 700) {
				circle.move(1, 0);
			}
			if (event.key.code == sf::Keyboard::Up && circle.getPosition().y > 0) {
				circle.move(0, -1);
			}
			if (event.key.code == sf::Keyboard::Down && circle.getPosition().y < 500) {
				circle.move(0, 1);
			}
			break;
		default:
			break;
		}
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && circle.getPosition().x > 0) {
			circle.move(-1, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && circle.getPosition().x < 700) {
			circle.move(1, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && circle.getPosition().y > 0) {
			circle.move(0, -1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && circle.getPosition().y < 500) {
			circle.move(0, 1);
		}*/
		window.draw(circle);
		window.display();
	}
}