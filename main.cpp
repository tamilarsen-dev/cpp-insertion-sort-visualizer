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
constexpr int BAR_COUNT = 20;

// maximum and minimum height for bar
constexpr float MAX_BAR_HEIGHT = WINDOW_HEIGHT - TOP_MARGIN;
constexpr float MIN_BAR_HEIGHT = 30.f;

// now, we calculate useable window size after margin apply on both side
constexpr float USEABLE_WINDOW = WINDOW_WIDTH - (2.f * MARGIN_SIDE);

// next we calculate bar width;
constexpr float BAR_WIDTH = (USEABLE_WINDOW - (BAR_COUNT - 1) * GAP) / BAR_COUNT;

// after all we calculate total window width used by all element we want rendered
constexpr float TOTAL_USED_WINDOW_WIDTH = BAR_COUNT * BAR_WIDTH + (BAR_COUNT - 1) * GAP;

// this is starting point of x for each item we want rendered
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
	sf::Clock stepClock;
	constexpr float STEP_INTERVAL = 0.1f;
	

	std::vector<float> heights;
	heights.reserve(BAR_COUNT);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> height_dist(MIN_BAR_HEIGHT, MAX_BAR_HEIGHT);

	for (std::size_t i = 0; i < BAR_COUNT; ++i)
	{
		heights.push_back(height_dist(gen));
	}

	bool inserting = false;
	bool sortingFinished = heights.size() < 2;
	float key = 0.f;
	int j = -1;
	std::size_t m = 1;

	// BATCH INSERTION SORT ALGORITHM
	/*for (int k = 1; k < heights.size(); ++k)
	{


		while (j >= 0 && heights[j] > key)
		{
			heights[j + 1] = heights[j];
			--j;
		}
		heights[j + 1] = key;
	}*/

	while (window.isOpen())
	{
		// 1. handle events
		while (auto events = window.pollEvent())
		{
			if (events->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		// 2. update data
		if (!sortingFinished && stepClock.getElapsedTime().asSeconds() >= STEP_INTERVAL)
		{
			stepClock.restart();
			if (!inserting)
			{
				key = heights[m];
				j = m - 1;

				inserting = true;
			}
			else if (j >= 0 && heights[j] > key)
			{
				heights[j + 1] = heights[j];
				--j;
			}
			else
			{
				heights[j + 1] = key;

				++m;
				inserting = false;

				if (m >= heights.size())
				{
					sortingFinished = true;
				}
			}
		}

		//3. render
		window.clear(sf::Color::Black);

		for (std::size_t i = 0; i < BAR_COUNT; ++i)
		{
			const float x_pos = START_X + i * (BAR_WIDTH + GAP);
			const float height = heights[i];
			const float y_pos = WINDOW_HEIGHT - height;

			/*print(i+1);
			print(x_pos);
			print(y_pos);

			if (i == 1) break;*/

			sf::Color color = sf::Color::Yellow; // warna default

			if (inserting && i == m)
			{
				color = sf::Color(168, 85, 247); // ungu
			}
			else if (inserting && j >= 0 &&
				i == static_cast<std::size_t>(j))
			{
				color = sf::Color(56, 189, 248); // biru
			}

			sf::RectangleShape bar;
			bar.setFillColor(color);
			bar.setSize({ BAR_WIDTH, height });
			bar.setPosition({ x_pos, y_pos });

			window.draw(bar);
		}
		
		window.display();
	}
	
	return 0;
}