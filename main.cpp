#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>

constexpr int W_WIDTH = 1600;
constexpr int W_HEIGHT = 800;
constexpr float REC_WIDTH_MAX = W_WIDTH - 465;
constexpr float REC_HEIGHT_MAX = W_HEIGHT - 280;
constexpr float REC_WIDTH_MIN = W_WIDTH / 80;
constexpr float REC_HEIGHT_MIN = W_HEIGHT / 16;


int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution height_dist(REC_HEIGHT_MIN, REC_HEIGHT_MAX);

	std::vector<sf::RectangleShape> rectangles = {};

	sf::RenderWindow window(sf::VideoMode({ W_WIDTH, W_HEIGHT }), "Insertion Sort Visualize", sf::Style::Default, sf::State::Windowed);

	std::cout << "data -n: w h\n";

	for (size_t i = 0; i < 100; i++)
	{
		auto width_gen = 20.0f;
		auto height_gen = std::round(height_dist(gen));

		auto rec = sf::RectangleShape({ width_gen, height_gen });
		rec.setFillColor(sf::Color::Green);
		rec.setPosition(sf::Vector2f(width_gen + (width_gen * i), W_HEIGHT - height_gen));

		std::cout << "data -" << i + 1 << ": " << width_gen << ' ' << height_gen << '\n';
		rectangles.push_back(rec);
	}

	while (window.isOpen())
	{
		while (auto events = window.pollEvent())
		{
			if (events->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);

		for (size_t i = 1; i < rectangles.size(); i++) {
			window.draw(rectangles[i]);

			float key = rectangles[i].getSize().y;
			float j = i - 1;
			while (j >= 0 && rectangles[j].getSize().y > key)
			{
				rectangles[j + 1] = rectangles[j];
				j = j - 1;
			}
			rectangles[j + 1] = rectangles[i];

		}

		window.display();
	}

	return 0;
}