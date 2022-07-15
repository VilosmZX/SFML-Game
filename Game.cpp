#include "Game.h"
#include <iostream>

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemy();
}

Game::~Game()
{
	// Menghapus Alokasi memory, untuk mencegah memory leak ngab
	delete this->window;
}

void Game::update()
{
	this->updateMousePos();
	this->updateEnemies();
}

void Game::updateMousePos()
{
	// Ini untuk mengetahui posisi cursor kita relative ke window kita 
	// Jadi koordinat (0, 0) itu adalah kiri atas dari window kita bukan dekstop kita
	this->mousePos = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePos);
}



void Game::render()
{ 
	// this->window->clear gunanya untuk menimpa frame lama dengan background RGB yang kita kasih
	this->window->clear(sf::Color(0, 0, 0, 255));

	// Ini bakal render semua enemies yang ada di this->enemies
	this->renderEnemies();

	// Ini bakal menampilkan frame yang ada di buffer.
	this->window->display();
}

void Game::spawnEnemies()
{
	// Ini bakal set posisi enemy secara random dan tidak akan keluar dari map.
	this->enemy.setSize(sf::Vector2f(32, 32));
	float randX = std::rand() % this->window->getSize().x - this->enemy.getSize().x;
	float randY = std::rand() % this->window->getSize().y - this->enemy.getSize().y;
	this->enemy.setPosition(sf::Vector2f(randX, randY));
	this->enemy.setFillColor(sf::Color::Red);
	this->enemies.push_back(this->enemy);
}

void Game::updateEnemies()
{
	// Ini Mastiin kalo enemy nya itu kurang dari this->maxEnemies
	// Jadi dia bakal spawn terus selama enemies yang ada di this->enemies itu kurang dari this->maxEnemies

	if (this->enemies.size() < this->maxEnemies)
	{
		// Ini bakal ngasih delay, jadi enemy nya ga bakal spawn secara instan
		if (this->enemySpawnTimer >= enemySpawnTimer)
		{
			this->spawnEnemies();
			this->enemySpawnTimer = 0;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].move(0.f, 1.f);
		// Ketika musuh di click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				this->enemies.erase(this->enemies.begin() + i);
			}	
		}
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::initVariables()
{
	// Variables ngab gausah dijelasin ini mah
	this->window = nullptr;
	this->points = 0;
	this->maxEnemies = 10;
	this->enemySpawnTimer = 0.f;
	this->maxEnemySpawnTimer = 1000.f;
}

void Game::initWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Close | sf::Style::Titlebar);
	// Ini untuk setframe limit, gunannya apa?
	// Gini, semua pc kan punya spek masing masing.
	// Jadi bisa aja komputer yg bagus bakal berjalan 500frame/second nah itu kan kenceng bgt
	// Bayangin kalian main game online, fps kalian 30 lalu fps musuh kalian 100.
	// Otomatis musuh klean larinya akan cepet banget.
	// Itulah kenapa frame nya kita harus batasi.
	// Rekomendasi nya 60fps
	this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	this->enemy.setFillColor(sf::Color(255, 0, 0, 255));
	this->enemy.setOutlineColor(sf::Color::White);
	this->enemy.setOutlineThickness(1.5f);
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	// Kenapa butuh pollEvents()?
	// Ini untuk menangkap semua event yg terjadi
	// Contoh:
	// - Saat kita memncet keyboard, mouse
	// - Menggerakan mouse
	// - Pencet tombol close, dll
	// itu kita harusnya atasi sendiri.
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}
