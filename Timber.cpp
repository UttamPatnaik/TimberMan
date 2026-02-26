/*To execute this program, we must run the command: g++ Timber.cpp -o Timber -lsfml-graphics -lsfml-window -lsfml-system && ./Timber*/

#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;
using namespace std;

int main()
{
    // Window
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Game");

    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // ================= BACKGROUND =================
    Texture textureBackground;
    if (!textureBackground.loadFromFile("graphics/background.png"))
        return -1;

    Sprite spriteBackground(textureBackground);

    // ================= TREE =================
    Texture textureTree;
    if (!textureTree.loadFromFile("graphics/tree.png"))
        return -1;

    Sprite spriteTree(textureTree);
    spriteTree.setPosition(800, 0);

    // ================= PLAYER =================
    Texture texturePlayer;
    if (!texturePlayer.loadFromFile("graphics/player.png"))
        return -1;

    Sprite spritePlayer(texturePlayer);
    spritePlayer.setPosition(580, 720);

    enum class side { LEFT, RIGHT };
    side playerSide = side::LEFT;

    // ================= AXE =================
    Texture textureAxe;
    if (!textureAxe.loadFromFile("graphics/axe.png"))
        return -1;

    Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition(700, 830);

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // ================= FONT =================
    Font font;
    if (!font.loadFromFile("font/KOMIKAP_.ttf"))
        return -1;

    // ================= SCORE TEXT =================
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::Red);
    scoreText.setPosition(20, 20);

    int score = 0;
    stringstream ss;
    ss << "Score = " << score;
    scoreText.setString(ss.str());

    // ================= MESSAGE TEXT =================
    Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::Green);
    messageText.setString("Press Enter to Start!");

    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f
    );

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    // ================= TIME BAR =================
    RectangleShape timeBar;

    float timeBarStartWidth = 400;
    float timeBarHeight = 80;

    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(
        (1920 / 2.0f) - (timeBarStartWidth / 2.0f),
        980
    );

    // ================= GAME LOOP =================
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // PLAYER MOVEMENT
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            playerSide = side::LEFT;
            spritePlayer.setPosition(580, 720);
            spriteAxe.setPosition(AXE_POSITION_LEFT, 830);
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            playerSide = side::RIGHT;
            spritePlayer.setPosition(1200, 720);
            spriteAxe.setPosition(AXE_POSITION_RIGHT, 830);
        }

        // ================= DRAW =================
        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(timeBar);
        window.draw(scoreText);
        window.draw(messageText);

        window.display();
    }

    return 0;
}