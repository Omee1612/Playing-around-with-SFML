//
// Created by Omee on 8/16/2024.
//
/*
 * Game engine class here!
 *
 */

#ifndef GAME_GAME_H
#define GAME_GAME_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <cstdlib>
class Game {
private:
    //Variables and window
    sf::RenderWindow *window;
    sf::Event event;
    sf::Clock clock;
    sf::Clock defeatClock;
    sf::VideoMode vMode;
    sf::Font font;
    sf::Text pts;
    sf::Text lose;
    std::vector<sf::RectangleShape> enemies;
    //Game logic
    bool buttonPressed;
    bool defeated;
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    // Game Objects
    sf::RectangleShape enemy;
    //mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    //Functions
    void initializeVar();
    void initWindow();
    void initEnemies();
    void initText();
public:
    Game(); // Constructor
    virtual ~Game(); // Destructor
    //Accessors
    bool running() const;
    // Functions
    void displayDefeat();
    void updatePoints();
    void pollEvents();
    void spawnEnemy();
    void update();
    void updateMousePos();
    void render();
    void updateEnemies();
    void renderEnemies();
};
#endif //GAME_GAME_H
