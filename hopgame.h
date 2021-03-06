#ifndef HOPGAME_H
#define HOPGAME_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "config.h" // configures the games values and constants and such

/* Macros for determining keys pressed */
#define ISPRESSED(k) sf::Keyboard::isKeyPressed(k)
#define KEY_JUMP (ISPRESSED(sf::Keyboard::Space) || ISPRESSED(sf::Keyboard::Up))
#define KEY_DUCK ISPRESSED(sf::Keyboard::Down)
#define KEY_RESTART ISPRESSED(sf::Keyboard::Return)
#define KEY_PAUSE (ISPRESSED(sf::Keyboard::Escape) || ISPRESSED(sf::Keyboard::P))

sf::RectangleShape playerCollisionBox(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
sf::RectangleShape playerDuckCollisionBox(sf::Vector2f(PLAYER_WIDTH_DUCK, PLAYER_HEIGHT_DUCK));
sf::RectangleShape ground(sf::Vector2f(WIDTH, 2.0f));
sf::Font scoreFont;
sf::Text scoreText;
sf::Text gameOverText;
sf::Text gameOverSubtitle;
sf::Text pauseText;

sf::RectangleShape pauseBar(sf::Vector2f(45.0f, 150.0f));
sf::RectangleShape pauseBar2(sf::Vector2f(45.0f, 150.0f));

sf::Texture spritesheet;

const sf::Vector2f smallObstacleSize(OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
const sf::Vector2f flyingObstacleSize(FLYING_OBSTACLE_WIDTH, FLYING_OBSTACLE_HEIGHT);

bool pausekeydown = false; // used to make it so the pause key doens't make the game freak out

namespace hopgame {
	class gameobject;
	class player;
	class obstacle;
};

enum GameState {
	PLAYING = 0,
	PAUSED = 1,
	OVER = 2
};

using namespace hopgame;

static float obstacleSpeed = SPEED;
static int score = 0; // will be counted by number of enemies that leave the screen
static unsigned long long ticks = 0;

static std::vector<obstacle*> obstacles;
static GameState gamestate = PLAYING;

static gameobject* _player;

static void addObstacle(obstacle* ob) {
	obstacles.push_back(ob);
};

template<class T, class U, class V>
T clamp(T num, U min, V max) {
	if (num < (T)min)
		return (T)min;
	else if (num > (T)max)
		return (T)max;
	else
		return num;
};

void centerTextHorizontal(sf::Text& text, float offset = 0.0f) {
	sf::FloatRect bounds = text.getGlobalBounds();
	text.setPosition(((WIDTH/2.0f) + offset) - (bounds.width/2.0f), text.getPosition().y);
};

void centerTextVertical(sf::Text& text, float offset = 0.0f) {
	sf::FloatRect bounds = text.getGlobalBounds();
	text.setPosition(text.getPosition().x, ((HEIGHT/2.0f) + offset) - (bounds.height/2.0f));
};

void centerText(sf::Text& text) {
	centerTextHorizontal(text);
	centerTextVertical(text);
};

#endif
