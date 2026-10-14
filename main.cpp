#include <iostream>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

#define print(item) std::cout << item << '\n';

// window size
constexpr unsigned int WINDOW_WIDTH = 1600;
constexpr unsigned int WINDOW_HEIGHT = 800;

// margin size both on right and left side will be 20
constexpr float MARGIN_SIDE = 20.f;

// top margin
constexpr float TOP_MARGIN = 40.f;

// gap between bar
constexpr float GAP = 5.f; 

// total bar we want rendered
constexpr int BAR_COUNT = 50;

// maximum and minimum height for bar
constexpr float MAX_BAR_HEIGHT = WINDOW_HEIGHT - TOP_MARGIN;
constexpr float MIN_BAR_HEIGHT = 30.f;

// now, we calculate useable window size after margin apply on both side
constexpr float USEABLE_WINDOW = WINDOW_WIDTH - (2.f * MARGIN_SIDE);

// next we calculate bar width;
constexpr float BAR_WIDTH = (USEABLE_WINDOW - (BAR_COUNT - 1) * GAP) / BAR_COUNT;

// after all we calculate total window width used by all element we want rendered
constexpr float TOTAL_USED_WINDOW_WIDTH = BAR_COUNT * BAR_WIDTH + (BAR_COUNT - 1) * GAP;

// 
constexpr float START_X = (WINDOW_WIDTH - TOTAL_USED_WINDOW_WIDTH) / 2.f;


int main()
{
	/*print(MIN_BAR_HEIGHT);
	print(MAX_BAR_HEIGHT);
	print(USEABLE_WINDOW);
	print(BAR_WIDTH);
	print(TOTAL_USED_WINDOW_WIDTH);
	print(START_X);
	print("--------------------------------------------------------------------------------");*/

	auto window = sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Insertion Sort Visualize", sf::Style::Default, sf::State::Windowed);
	
	window.setFramerateLimit(30);

	bool running = true;

	std::vector<float> heights;
	heights.reserve(BAR_COUNT);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> height_dist(MIN_BAR_HEIGHT, MAX_BAR_HEIGHT);

	for (std::size_t i = 0; i < BAR_COUNT; ++i)
	{
		heights.push_back(height_dist(gen));
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

		for (std::size_t i = 0; i < BAR_COUNT; ++i)
		{
			const float x_pos = START_X + i * (BAR_WIDTH + GAP);
			const float height = heights[i];
			const float y_pos = WINDOW_HEIGHT - height;

			float key = heights[i];
			int j = i - 1;
			int current = j + 1;
			/*print(i+1);
			print(x_pos);
			print(y_pos);

			if (i == 1) break;*/

			sf::RectangleShape bar;
			bar.setFillColor(sf::Color::Yellow);
			bar.setSize({ BAR_WIDTH, height });
			bar.setPosition({ x_pos, y_pos });

			window.draw(bar);

			if (j >= 0 && heights[j] > key)
			{
				heights[current] = heights[j];
				--j;
			}
			heights[j + 1] = key;
			sf::sleep(sf::milliseconds(1.900));
		}
		
		window.display();
	}
	
	return 0;
}