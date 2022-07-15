#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Game
{
public:
	Game();
	~Game();
	void update();
	void render();
	void pollEvents();
	const bool isRunning() const;
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::RectangleShape enemy;
	sf::Vector2i mousePos;
	sf::Vector2f mousePosView;
	std::vector<sf::RectangleShape> enemies;
	unsigned int points;
	float enemySpawnTimer;
	float maxEnemySpawnTimer;
	unsigned int maxEnemies;
	void spawnEnemies();
	void updateEnemies();
	void renderEnemies();
	void initVariables();
	void initWindow();
	void initEnemy();
	void updateMousePos();
};

