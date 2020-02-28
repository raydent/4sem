#include <SFML\Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	sf::CircleShape circle(50);
	sf::Vertex vertex;

	// set its position
	// create an array of 3 vertices that define a triangle primitive
	sf::VertexArray triangle(sf::Triangles, 3);

	// define the position of the triangle's points
	triangle[0].position = sf::Vector2f(10, 10);
	triangle[1].position = sf::Vector2f(100, 10);
	triangle[2].position = sf::Vector2f(100, 100);

	// define the color of the triangle's points
	triangle[0].color = sf::Color::Red;
	triangle[1].color = sf::Color::Blue;
	triangle[2].color = sf::Color::Green;



	std::vector<sf::Vertex> vertices;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event));
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear(sf::Color::White);
		window.draw(triangle);
		window.display();
	}
}