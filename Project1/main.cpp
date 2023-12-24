#include <SFML/Graphics.hpp>
#include <cstdlib>

int main()
{   
    //INITIALIZE
    sf::RenderWindow win(sf::VideoMode(800, 600), "mywin");
    bool gemOut = false;
    int score = 0;

    //LOAD
    sf::Image grass;

    grass.loadFromFile("assets/terrain/grass,png");
    

    sf::Texture gemTexture;
    sf::Texture playerTextureUp;
    sf::Texture playerTextureDown;
    sf::Texture playerTextureLeft;
    sf::Texture playerTextureRight;

    sf::Sprite playerSprite;
    sf::Sprite gemSprite;
    
    sf::Text text;
    sf::Font opensans;

    playerTextureUp.loadFromFile("assets/player/textures/link.png", sf::IntRect(0, 208, 96, 104));
    playerTextureDown.loadFromFile("assets/player/textures/link.png", sf::IntRect(0, 0, 96, 104));
    playerTextureLeft.loadFromFile("assets/player/textures/link.png", sf::IntRect(0, 104, 96, 104));
    playerTextureRight.loadFromFile("assets/player/textures/link.png", sf::IntRect(0, 312, 96, 104));
    gemTexture.loadFromFile("assets/gems/textures/gems.png", sf::IntRect(125, 125, 125, 125));

    playerSprite.setTexture(playerTextureDown);
    gemSprite.setTexture(gemTexture);

    //Text
    opensans.loadFromFile("assets/font/opensans.ttf");
    text.setFont(opensans);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    std::string txt = "Diamonds:";

    //Terrain


    //Game loop
    while (win.isOpen()) {


        //UPDATE
        sf::Event event;
        while (win.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                win.close();
            }           
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            playerSprite.move(0, 0.02);
            
            if (playerSprite.getTexture() != &playerTextureDown) {
                playerSprite.setTexture(playerTextureDown);
            }
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            playerSprite.move(0, -0.02);

            if (playerSprite.getTexture() != &playerTextureUp) {
                playerSprite.setTexture(playerTextureUp);
            }
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerSprite.move(0.02, 0);

            if (playerSprite.getTexture() != &playerTextureRight) {
                playerSprite.setTexture(playerTextureRight);
            }
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerSprite.move(-0.02, 0);

            if (playerSprite.getTexture() != &playerTextureLeft) {
                playerSprite.setTexture(playerTextureLeft);
            }
        }

        //collision
        sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
        sf::FloatRect gemBounds = gemSprite.getGlobalBounds();
        if (playerBounds.intersects(gemBounds)) {
            ++score;
            gemOut = false;
        }


        //respawning gem
        if (gemOut == false) {
            int x = rand() % 675;
            int y = rand() % 475;

            gemSprite.setPosition(sf::Vector2f(x, y));
            gemOut = true;
        }

        //text
        std::string value = std::to_string(score);
        std::string fullstring = txt + " " + value;
        text.setString(fullstring);

        

        //DRAW
        win.clear(sf::Color::Black);
        win.draw(playerSprite);
        win.draw(gemSprite);
        win.draw(text);
        win.display();


    }


    return 0;
}