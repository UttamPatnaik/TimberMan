#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>

using namespace sf;
using namespace std;

/* ===================== CONSTANTS & TYPES ===================== */

const int NUM_BRANCHES = 6;
const float AXE_POSITION_LEFT = 700;
const float AXE_POSITION_RIGHT = 1075;

enum class Side { LEFT, RIGHT, NONE };

/* ===================== GLOBAL OBJECTS ===================== */

Sprite branches[NUM_BRANCHES];
Side branchPositions[NUM_BRANCHES];

Texture textureCloud;
Sprite spriteCloud1, spriteCloud2, spriteCloud3;

bool cloudActive1 = false;
bool cloudActive2 = false;
bool cloudActive3 = false;

float cloudSpeed1 = 0.0f;
float cloudSpeed2 = 0.0f;
float cloudSpeed3 = 0.0f;

/* ===================== FUNCTIONS ===================== */

void updateBranches(int seed)
{
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
        branchPositions[j] = branchPositions[j - 1];

    srand((int)time(0) + seed);
    int r = rand() % 5;

    if (r == 0) branchPositions[0] = Side::LEFT;
    else if (r == 1) branchPositions[0] = Side::RIGHT;
    else branchPositions[0] = Side::NONE;
}

/* ===================== MAIN ===================== */

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Game!!!");
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    /* -------- Textures & Sprites -------- */

    Texture textureBackground, textureTree, textureBee, texturePlayer, textureAxe, textureBranch, textureRIP;
    textureBackground.loadFromFile("graphics/background.png");
    textureTree.loadFromFile("graphics/tree.png");
    textureBee.loadFromFile("graphics/bee.png");
    texturePlayer.loadFromFile("graphics/player.png");
    textureAxe.loadFromFile("graphics/axe.png");
    textureBranch.loadFromFile("graphics/branch.png");
    textureCloud.loadFromFile("graphics/cloud.png");
    textureRIP.loadFromFile("graphics/rip.png");

    Sprite spriteBackground(textureBackground);
    Sprite spriteTree(textureTree);
    Sprite spriteBee(textureBee);
    Sprite spritePlayer(texturePlayer);
    Sprite spriteAxe(textureAxe);
    Sprite spriteRIP(textureRIP);

    spriteTree.setPosition(810, 0);
    spriteBee.setPosition(0, 500);
    spritePlayer.setPosition(580, 720);
    spriteAxe.setPosition(700, 830);
    spriteRIP.setPosition(860, 600);

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    /* -------- Branch Init -------- */

    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
        branchPositions[i] = Side::NONE;
    }

    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);
    branchPositions[5] = Side::NONE;

    /* -------- UI -------- */

    Font font;
    font.loadFromFile("font/KOMIKAP_.ttf");

    Text scoreText, messageText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::Red);
    scoreText.setPosition(20, 20);

    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::Green);
    messageText.setString("Press Enter to Start");
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(960, 540);

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(960 - timeBarStartWidth / 2, 980);

    /* -------- Game State -------- */

    int score = 0;
    bool paused = true;
    bool beeActive = false;
    bool showRIP = false;
    bool acceptInput = false;

    float beeSpeed = 0.0f;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    Side playerSide = Side::LEFT;

    Clock clock;
    Time dt;

    /* ===================== GAME LOOP ===================== */

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                paused = false;
                score = 0;
                timeRemaining = 6.0f;
                acceptInput = true;
                showRIP = false;
                messageText.setString("");
                spritePlayer.setPosition(580, 720);
            }

            if (event.type == Event::KeyReleased && !paused)
            {
                acceptInput = true;
                spriteAxe.setPosition(2000, 830);
            }

            if (acceptInput)
            {
                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    playerSide = Side::LEFT;
                    spritePlayer.setPosition(580, 720);
                    spriteAxe.setPosition(AXE_POSITION_LEFT, 830);
                    score++;
                    timeRemaining += (2.0f / score) + .15f;
                    updateBranches(score);
                    acceptInput = false;
                }

                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    playerSide = Side::RIGHT;
                    spritePlayer.setPosition(1200, 720);
                    spriteAxe.setPosition(AXE_POSITION_RIGHT, 830);
                    score++;
                    timeRemaining += (2.0f / score) + .15f;
                    updateBranches(score);
                    acceptInput = false;
                }

                if (branchPositions[5] == playerSide)
                {
                    paused = true;
                    acceptInput = false;
                    showRIP = true;
                    messageText.setString("SQUISHED!!!");

                    FloatRect tr = messageText.getLocalBounds();
                    messageText.setOrigin(tr.left + tr.width / 2.0f, tr.top + tr.height / 2.0f);
                    messageText.setPosition(960, 540);
                }
            }
        }

        if (!paused)
        {
            dt = clock.restart();
            timeRemaining -= dt.asSeconds();

            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                paused = true;
                messageText.setString("Out of Time!");
                FloatRect tr = messageText.getLocalBounds();
                messageText.setOrigin(tr.left + tr.width / 2.0f, tr.top + tr.height / 2.0f);
                messageText.setPosition(960, 540);
            }

            if (!beeActive)
            {
                beeSpeed = (rand() % 200) + 200;
                float height = (rand() % 200) + 300;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                spriteBee.move(-beeSpeed * dt.asSeconds(), 0);
                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            if(!cloudActive1){
                cloudSpeed1 = (rand()%200)+50;
                spriteCloud1.setPosition(-200, rand()%300);
                cloudActive1 = true;
            } else {
                spriteCloud1.move(cloudSpeed1 * dt.asSeconds(), 0);
                if(spriteCloud1.getPosition().x > 1920) cloudActive1 = false;
            }

            if(!cloudActive2){
                cloudSpeed2 = (rand()%200)+50;
                spriteCloud2.setPosition(-200, (rand()%300)-150);
                cloudActive2 = true;
            } else {
                spriteCloud2.move(cloudSpeed2 * dt.asSeconds(), 0);
                if(spriteCloud2.getPosition().x > 1920) cloudActive2 = false;
            }

            if(!cloudActive3){
                cloudSpeed3 = (rand()%200)+50;
                spriteCloud3.setPosition(-200, (rand()%450)-150);
                cloudActive3 = true;
            } else {
                spriteCloud3.move(cloudSpeed3 * dt.asSeconds(), 0);
                if(spriteCloud3.getPosition().x > 1920) cloudActive3 = false;
            }
        }

        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            float height = i * 150;

            if (branchPositions[i] == Side::LEFT){
                branches[i].setPosition(610, height);
                branches[i].setRotation(180);
            }
            else if (branchPositions[i] == Side::RIGHT){
                branches[i].setPosition(1330, height);
                branches[i].setRotation(0);
            }
            else{
                branches[i].setPosition(3000, height);
            }
        }

        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);

        for (int i = 0; i < NUM_BRANCHES; i++)
            window.draw(branches[i]);

        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(timeBar);

        if (paused)
        {
            window.draw(messageText);
            if(showRIP) window.draw(spriteRIP);
        }

        window.display();
    }
}
