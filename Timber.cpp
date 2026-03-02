#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>

using namespace sf;
using namespace std;

// ---------------- STEP 5 ADDITIONS ----------------
const int NUM_BRANCHES = 6;
enum class Side { LEFT, RIGHT, NONE };

Sprite branches[NUM_BRANCHES];
Side branchPositions[NUM_BRANCHES];

void updateBranches(int seed)
{    for (int j = NUM_BRANCHES - 1; j > 0; j--)
        branchPositions[j] = branchPositions[j - 1];

    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r)
    {
    case 0:
        branchPositions[0] = Side::LEFT;
        break;
    case 1:
        branchPositions[0] = Side::RIGHT;
        break;
    default:
        branchPositions[0] = Side::NONE;
        break;
    }
}
// ---------------------------------------------------

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Game!!!");

    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground(textureBackground);

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree(textureTree);
    spriteTree.setPosition(810, 0);

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 500); // 800
    bool beeActive = false;
    float beeSpeed = 0.0f;

    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer(texturePlayer);
    spritePlayer.setPosition(580, 720);

    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition(700, 830);

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // ---------------- BRANCH TEXTURE INIT ----------------
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
        branchPositions[i] = Side::NONE;
    }
    // ------------------------------------------------------
    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);

    branchPositions[5] = Side::NONE;
    // -----------------------------------------------------

    
    Font font;
    font.loadFromFile("font/KOMIKAP_.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::Red);
    scoreText.setPosition(20, 20);

    int score = 0;
    stringstream ss;
    ss << "Score = " << score;
    scoreText.setString(ss.str());

    Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::Green);
    messageText.setString("Press Enter to Start");

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f
    );
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused = true;

    Clock clock;
    Time dt;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Enter)
            {
                paused = false;
                timeRemaining = 6.0f;      // reset timer
                clock.restart();           // reset clock
                messageText.setString(""); // remove start text
            }
        }

        // -------- TIME SYSTEM --------
        if (!paused)
        {
            dt = clock.restart();

            timeRemaining -= dt.asSeconds();

            timeBar.setSize(
                Vector2f(timeBarWidthPerSecond * timeRemaining,
                         timeBarHeight)
            );

            if (timeRemaining <= 0.0f)
            {
                paused = true;
                messageText.setString("Out of Time!");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(
                    textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f
                );
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }
            if (!beeActive) {
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;

                srand((int)time(0) * 10);
                float height = (rand() % 200) + 300;
                spriteBee.setPosition(2000, height);

                beeActive = true;
            }
            else {
                spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
                if (spriteBee.getPosition().x < -100){
                    beeActive = false;
                }
            }

        }
        // -----------------------------

        // -------- Branch Rendering --------
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            float height = i * 150;

            if (branchPositions[i] == Side::LEFT)
            {
                branches[i].setPosition(610, height);
                branches[i].setRotation(180);
            }
            else if (branchPositions[i] == Side::RIGHT)
            {
                branches[i].setPosition(1330, height);
                branches[i].setRotation(0);
            }
            else
            {
                branches[i].setPosition(3000, height);
            }
        }

        // -----------------------------------

        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteTree);

        for (int i = 0; i < NUM_BRANCHES; i++)
            window.draw(branches[i]);

        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(timeBar);

        if (paused)
            window.draw(messageText);

        window.display();
    }
}
