#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <chrono>
const float __CHARGE__ = 1;
const int __LINE_NUMBER__ = 4;

struct Charge {
	Charge(sf::Vector2i v, bool b) : pos(v), sign(b) {};
	sf::Vector2i pos;
	bool sign = true;//true is pos
};


bool operator<(const sf::Vector2i& lhs, const sf::Vector2i& rhs) {
	//return (lhs.x * lhs.x + lhs.y * lhs.y) < (rhs.x * rhs.x + rhs.y * rhs.y);
	return (lhs.x < rhs.x) && (lhs.y < rhs.y);
}

class ChargeSystem {
public:
	void insert_pos(sf::Vector2i point) {
		points.push_back(Charge{point, true});
		sf::CircleShape s{ 25 };
		s.setFillColor(sf::Color::Red);
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
		auto _zero_it_ = begin(points);
		for (auto it = begin(points); it != end(points); it++) {
			if (it->sign) {
				std::vector<sf::VertexArray> v(__LINE_NUMBER__);
				sf::Vector2i curpos = it->pos;
				float one_angle = 360 / __LINE_NUMBER__;
				int move = 5;
				for (int i = 0; i < __LINE_NUMBER__; i++) {
					v[i].append(sf::Vertex(sf::Vector2f(curpos.x + move * cos(i * one_angle), curpos.y + move * sin(i * one_angle)), sf::Color::Black));
					/*int pos_iter_ = v[i].getVertexCount() - 1;
					if (pos_iter_ < 0)
						pos_iter_ = 0;*/
					sf::Vector2f cur_line_pos = static_cast<sf::Vector2f>(curpos);//v[i].operator[](pos_iter_).position;
					std::cout << cur_line_pos.x << " " << cur_line_pos.y << std::endl;
					while (cur_line_pos.x >= 0 && cur_line_pos.x <= 1024
						&& cur_line_pos.y >= 0 && cur_line_pos.y <= 768) {
						std::cout << "turn " << cur_line_pos.x << " " << cur_line_pos.y << std::endl;
						float Ex = 0, Ey = 0;
						for (const auto& in : points) {
							int sign = in.sign ? 1 : -1;
							/*Ex += sign / ((i.pos.x - cur_line_pos.x) * (i.pos.x - cur_line_pos.x));
							Ey += sign / ((i.pos.y - cur_line_pos.y) * (i.pos.y - cur_line_pos.y));*/
							auto vec = cur_line_pos - static_cast<sf::Vector2f>(in.pos);
							auto mod_ = sqrt(vec.x * vec.x + vec.y * vec.y);
							/*if (1 / mod_ == 0) {
								mod_ = 1;
							}*/
							if (mod_ == 0) {
								mod_ = 0.1;
							}
							auto xsign = signbit(vec.x);
							if (cur_line_pos.x < in.pos.x) {
								xsign = -1;
							}
							else {
								xsign = 1;
							}
							auto ysign = signbit(vec.y);
							if (cur_line_pos.y < in.pos.y) {
								ysign = -1;
							}
							else {
								ysign = 1;
							}
							auto E = sign / mod_ / mod_;
							std::cout << "E = " << E << std::endl;
							Ex += xsign * E * vec.x / mod_;
							Ey += ysign * E * vec.y / mod_;
						}
						float mod = sqrt(Ex * Ex + Ey * Ey);
						if (Ex == 0)
							Ex = 5;
						if (Ey == 0)
							Ey = 5;
						std::cout << "first " << cur_line_pos.x << " " << cur_line_pos.y << std::endl;
						cur_line_pos = sf::Vector2f{cur_line_pos.x + 100 * Ex, cur_line_pos.y + 100 * Ey};
						v[i].append(sf::Vertex{ cur_line_pos, sf::Color::Black });
						cur_line_pos = v[i].operator[](v[i].getVertexCount() - 1).position;
						std::cout << "second " << cur_line_pos.x << " " << cur_line_pos.y << std::endl;
					}
				}
				size_t dif = it - _zero_it_;
				std::cout << dif << std::endl;
				if (charges.size() <= dif) {
					charges.push_back(v);
				}
				else {
					charges[it - _zero_it_] = v;
				}
			}
		}
	}
	auto& get_map() {
		return charges;
	}
	auto& get_circles() {
		return circles;
	}
private:
	//std::map<sf::Vector2i, std::vector<std::vector<sf::Vertex>>> charges;
	std::vector<std::vector<sf::VertexArray>> charges;
	std::vector<Charge> points;
	std::vector<sf::CircleShape> circles;
};
int main() {
	sf::RenderWindow window(sf::VideoMode(1024, 768), "My window");
	//std::list<sf::Vector2i> points;
	window.clear(sf::Color::White);
	ChargeSystem cs;
	auto c = std::chrono::steady_clock::now();
	float time_dif = 100;
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - c).count() > time_dif) {
				auto pos = sf::Mouse::getPosition(window);
				cs.insert_pos(pos);
				c = std::chrono::steady_clock::now();
			}
		}
		for (auto it = begin(cs.get_circles()); it != end(cs.get_circles()); it++) {
			window.draw(*it);
		}
		for (auto it1 = begin(cs.get_map()); it1 != end(cs.get_map()); it1++) {
			for (auto it2 = begin(*it1); it2 != end(*it1); it2++) {
				window.draw(*it2);
			}
		}
		window.display();
	}
}