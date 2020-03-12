#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
const float __CHARGE__ = 1;
const int __LINE_NUMBER__ = 8;

struct Charge {
	Charge(sf::Vector2i v, bool b) : pos(v), sign(b) {};
	sf::Vector2i pos;
	bool sign = true;//true is pos
};


class ChargeSystem {
public:
	void insert_pos(sf::Vector2i point) {
		points.push_back(Charge{point, true});
		sf::CircleShape s{ 25 };
		s.setFillColor(sf::Color::Blue);
		s.setPosition(point.x, point.y);
		circles.push_back(s);
		recalc();
	}
	void insert_neg(sf::Vector2i point) {
		points.push_back(Charge{point, false});
		sf::CircleShape s{ 25 };
		s.setFillColor(sf::Color::Blue);
		s.setPosition(point.x, point.y);
		circles.push_back(s);
		recalc();
	}
	void recalc() {
		for (auto it = begin(points); it != end(points); it++) {
			std::vector<std::vector<sf::Vertex>> v(__LINE_NUMBER__);
			sf::Vector2i curpos = it->pos;
			float one_angle = 360 / __LINE_NUMBER__;
			int move = 5;
			for (int i = 0; i < __LINE_NUMBER__; i++) {
				v[i].push_back(sf::Vertex(sf::Vector2f(curpos.x + move * cos(i * one_angle), curpos.y + move * sin(i * one_angle)), sf::Color::Black));
				sf::Vector2f cur_line_pos = v[i].back().position;
				while (cur_line_pos.x >= 0 && cur_line_pos.x <= 1024 
					&& cur_line_pos.y >= 0 && cur_line_pos.y <= 768) {
					float Ex = 0, Ey = 0;
					for (const auto& i : points) {
						int sign = i.sign ? 1 : -1;
						Ex += sign / ((i.pos.x - cur_line_pos.x) * (i.pos.x - cur_line_pos.x));
						Ey += sign / ((i.pos.y - cur_line_pos.y) * (i.pos.y - cur_line_pos.y));
					}
					float mod = sqrt(Ex * Ex + Ey * Ey);
					v[i].push_back(sf::Vertex{ sf::Vector2f{cur_line_pos.x + Ex / mod, cur_line_pos.y + Ey / mod}, sf::Color::Black});
					cur_line_pos = v[i].back().position;
				}
			}
			charges[it->pos] = v;
		}
	}
	auto& get_map() {
		return charges;
	}
private:
	std::map<sf::Vector2i, std::vector<std::vector<sf::Vertex>>> charges;
	std::vector<Charge> points;
	std::vector<sf::CircleShape> circles;
};
int main() {
	sf::RenderWindow window(sf::VideoMode(1024, 768), "My window");
	//std::list<sf::Vector2i> points;
	window.clear(sf::Color::White);
	ChargeSystem cs;
	while (window.isOpen()) {
		sf::Event event;
		window.pollEvent(event);

		switch (event.type) {
		case (sf::Event::Closed):
			window.close();
			break;
		default:
			break;
		}
		window.display();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		auto pos = sf::Mouse::getPosition(window);
		cs.insert_pos(pos);
	}
	for (auto it1 = begin(cs.get_map()); it1 != end(cs.get_map()); it1++) {
		for (auto it2 = begin(it1->second); it2 != end(it1->second); it2++) {
			window.draw(it2, it2->size(), sf::Lines);
		}
	}
}