#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <chrono>
const float Pi = 3.14159f;

class Bullet {
public:
	Bullet(sf::Sprite hero, sf::Vector2f d) : bullet(10), curpos(hero.getPosition()),
		x(d.x / sqrt(d.x * d.x + d.y * d.y)), y(d.y / sqrt(d.x * d.x + d.y * d.y))
	{
		bullet.setPosition(curpos);
		//c.getElapsedTime();
		timer = time(nullptr);
		//std::cout << c.getElapsedTime().asMicroseconds() << std::endl;
	}
	bool if_time() {
		if (static_cast<float>(time(nullptr) - timer) >= timedif) {
			timer = time(nullptr);
			return true;
		}
		return false;
	}
	void move() {
		bullet.move(x, y);
	}
	bool to_erase() {
		if (bullet.getPosition().x <= 0 || bullet.getPosition().y <= 0 || bullet.getPosition().x >= 800 || bullet.getPosition().y >= 600) {
			return true;
		}
		return false;
	}
	sf::CircleShape get_bullet() {
		return bullet;
	}
private:
	float timedif = 0.1;
	time_t timer;
	sf::CircleShape bullet;
	sf::Vector2f curpos;
	float x = 0;
	float y = 0;
};

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	sf::Texture texture;
	texture.loadFromFile("Quake-Live-256.png");
	sf::Sprite circle(texture);
	circle.setScale(0.4, 0.4);
	sf::Clock clock;
	sf::Vector2u circleSize = circle.getTexture()->getSize();
	circle.setOrigin(circleSize.x / 2, circleSize.y / 2);
	std::list<Bullet> bullets;
	auto last_bullet_time = std::chrono::steady_clock::now();
	while (window.isOpen()) {
		sf::Event event;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f center = circle.getPosition();
		sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;
		circle.setRotation(90 + atan2f(d.y, d.x) * 180 / Pi);
		window.clear(sf::Color::Color(50, 50, 50));
		float timedif = 100;
		for (auto it = begin(bullets); it != end(bullets); it++) {
			window.draw(it->get_bullet());
			it->move();
			if (it->to_erase()) {
				auto tempit = next(it);
				bullets.erase(it);
				it = tempit;
			}
		}
		window.pollEvent(event);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			auto dist = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_bullet_time).count();
			if (dist >= timedif) {
				bullets.push_back({ circle, d });
				last_bullet_time = std::chrono::steady_clock::now();
			}
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
		window.draw(circle);
		window.display();
	}
}