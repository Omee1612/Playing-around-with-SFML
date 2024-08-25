#include "game.h"
// These are private functions

void Game::initializeVar() {
    this->window = nullptr;
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    clock.restart();
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    defeated=false;
}

void Game::spawnEnemy() {
    //Spawns enemy,sets color and pos
    // Random position random color
    this->enemy.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
    this->enemy.setPosition(
            static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y)));
    this->enemies.push_back(this->enemy);
}

void Game::initWindow() {
    this->vMode.height = 1080;
    this->vMode.width = 1920;
    this->window = new sf::RenderWindow(this->vMode, "my 2nd game",
                                        sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(75);
}

void Game::initEnemies() {
    enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setScale(sf::Vector2f(0.5, 0.5));
    //this->enemy.setOutlineColor(sf::Color::Green);
    //this->enemy.setOutlineThickness(1.f);
    this->initText();
}

//These are public functions
Game::Game() {
    this->initializeVar();
    this->initWindow();
    this->initEnemies();
    this->buttonPressed = false;
}

Game::~Game() {
    delete this->window;
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->event)) {
        switch (event.type) {
            case sf::Event::Closed :
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

bool Game::running() const {
    return this->window->isOpen();
}

// Updates mouse position in window
void Game::updateMousePos() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update() { //updating game logic

        this->pollEvents();
        //Mouse positions
        //Relative to screen
        this->updateMousePos();
        //Updating enemies
        this->updateEnemies();
    }

void Game::initText() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font!";
        return;
    }
    pts.setFont(font);
    pts.setString("Points: " + std::to_string(points));
    pts.setFillColor(sf::Color::Green);
    pts.setPosition(540.f, 10.f);
}

void Game::displayDefeat() {
    lose.setFont(font);
    lose.setString("You lose!");
    lose.setFillColor(sf::Color::Red);
    lose.setPosition(540.f,990.f);
    defeated = true;
}
void Game::updatePoints() {
    pts.setString("Points: " + std::to_string(points));
}

void Game::render() { //rendering
    // clear old frame
    // render new object
    // shows new frame in window
    this->window->clear(sf::Color(0, 0, 0, 255));
    if (defeated) window->draw(lose);
    else {
        //rendering enemies
        this->renderEnemies();
        this->updatePoints();
        this->window->draw(pts);
    }
    this->window->display();
}


void Game::updateEnemies() {
    //Updates the game logic, so it spawns enemies when the enemies are lower than the max amount
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
    }
    this->enemySpawnTimer += 1.f; // Use a smaller increment
    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    //Should also remove enemies at edge of the screen
    //Move enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        bool deleted = false;
        it->move(0.f, 3.f);

        if (!buttonPressed && mousePressed) {
            if (it->getGlobalBounds().contains(this->mousePosView)) {
                deleted = true;
                this->points += 10;
            }
        }

        if (it->getPosition().y > this->window->getSize().y) {
            deleted = true;
            this->points -= 10;
        }
        if (deleted) {
            it = this->enemies.erase(it);
        } else {
            ++it;
        }
        if (points > 0) clock.restart();
        if (clock.getElapsedTime().asSeconds() > 4 && !defeated) {
            displayDefeat();
            defeatClock.restart();
            //enemies.clear();
            std::cout << "Defeat conditions met \n";
        }
    }
    if (defeated && defeatClock.getElapsedTime().asSeconds() > 3){
        window->close(); }
    buttonPressed = mousePressed;
}

void Game::renderEnemies() {
    for (auto &e: this->enemies) {
        this->window->draw(e);
    }
}