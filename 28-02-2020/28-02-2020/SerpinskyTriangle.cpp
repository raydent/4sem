#include <SFML\Graphics.hpp>
#include <algorithm>
#include <vector>

void draw_serpinskiy(std::vector<sf::Vertex>& vertices, int n, sf::RenderWindow & window) {
	n--;
	sf::Vertex lefttop{ {(vertices[0].position.x + vertices[1].position.x) / 2, (vertices[0].position.y + vertices[1].position.y) / 2 }, sf::Color::White};
	sf::Vertex righttop{ {(vertices[1].position.x + vertices[2].position.x) / 2, (vertices[1].position.y + vertices[2].position.y) / 2 }, sf::Color::White };
	sf::Vertex bot{ {(vertices[2].position.x + vertices[0].position.x) / 2, (vertices[2].position.y + vertices[0].position.y) / 2 }, sf::Color::White };
	sf::VertexArray triangle(sf::Triangles, 3);
	triangle[0] = lefttop;
	triangle[1] = righttop;
	triangle[2] = bot;
	window.draw(triangle);
	if (n > 0) {
		std::vector<sf::Vertex> first{vertices[0], lefttop, bot};
		draw_serpinskiy(first, n, window);
		std::vector<sf::Vertex> second{lefttop, vertices[1], righttop };
		draw_serpinskiy(second, n, window);
		std::vector<sf::Vertex> third{ righttop, vertices[2], bot };
		draw_serpinskiy(third, n, window);
	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	std::vector<sf::Vertex> vertices;
	sf::VertexArray triangle(sf::Triangles, 3);
	
	triangle[0].position = sf::Vector2f(0, 200);
	triangle[1].position = sf::Vector2f(200 , 0);
	triangle[2].position = sf::Vector2f(400, 200);
	vertices.push_back(triangle[0].position);
	vertices.push_back(triangle[1].position);
	vertices.push_back(triangle[2].position);
	triangle[0].color = sf::Color::Black;
	triangle[1].color = sf::Color::Black;
	triangle[2].color = sf::Color::Black;
	
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
		int n = 5;
		draw_serpinskiy(vertices, n, window);
		//window.draw(triangle);
		//window.draw(&vertices[0], vertices.size(), sf::Triangles);
		window.display();
	}
}