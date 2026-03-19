#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

const int NUM_BRANCHES = 6;

enum class Side { LEFT, RIGHT, NONE };

// Branch sprites and their logical positions
Sprite branches[NUM_BRANCHES];
Side branchPositions[NUM_BRANCHES];

void updateBranches(int seed)
{
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
        branchPositions[j] = branchPositions[j - 1];

    int r = rand() % 5;
    switch (r)
    {
    case 0:  branchPositions[0] = Side::LEFT;  break;
    case 1:  branchPositions[0] = Side::RIGHT; break;
    default: branchPositions[0] = Side::NONE;  break;
    }
}

int main()
{
    srand((int)time(0));

    // Window
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Game!!!");
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // Background sprite
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground(textureBackground);

    // Tree sprite
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree(textureTree);
    spriteTree.setPosition(810, 0);

    // Cloud sprites (3 clouds, 1 shared texture)
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1(textureCloud);
    Sprite spriteCloud2(textureCloud);
    Sprite spriteCloud3(textureCloud);
    spriteCloud1.setScale(0.6f, 0.6f);
    spriteCloud2.setScale(0.6f, 0.6f);
    spriteCloud3.setScale(0.6f, 0.6f);

    bool cloudActive1 = false, cloudActive2 = false, cloudActive3 = false;
    float cloudSpeed1 = 0, cloudSpeed2 = 0, cloudSpeed3 = 0;
	 // ---------------- LOG SYSTEM ----------------
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog(textureLog);
    spriteLog.setPosition(810, 720);

    bool logActive = false;
    float logSpeedX = 0;
    float logSpeedY = -1500;
    // ------------------------------------------------
    // Player sprite	
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer(texturePlayer);
    spritePlayer.setPosition(580, 720);

    // Axe sprite
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition(700, 830);

    const float AXE_POSITION_LEFT  = 700;
    const float AXE_POSITION_RIGHT = 1075;

    Side playerSide  = Side::LEFT;
    bool acceptInput = false;

    // RIP gravestone sprite
    Texture textureRip;
    textureRip.loadFromFile("graphics/rip.png");
    Sprite spriteRip(textureRip);
    spriteRip.setPosition(3000, 720);

    // Branch sprites (6 branches, 1 shared texture)
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setOrigin(220, 20);
        branchPositions[i] = Side::NONE;
    }

    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);
    branchPositions[5] = Side::NONE;

    // Bee sprite
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee(textureBee);
    bool  beeActive = false;
    float beeSpeed  = 0;
	
	//Sound Effects
	  SoundBuffer chopBuffer;
  		if (!chopBuffer.loadFromFile("sound/chop.wav"))
    					return -1;
  		Sound chopSound(chopBuffer);

  		SoundBuffer deathBuffer;
  		if (!deathBuffer.loadFromFile("sound/death.wav"))
    					return -1;
  		Sound deathSound(deathBuffer);

  		SoundBuffer outOfTimeBuffer;
  		if (!outOfTimeBuffer.loadFromFile("sound/out_of_time.wav"))
    					return -1;
  		Sound outOfTimeSound(outOfTimeBuffer);
	
    // UI - font, score text, message text
    Font font;
    font.loadFromFile("font/KOMIKAP_.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::Red);
    scoreText.setPosition(20, 20);

    int score = 0;

    Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::Green);
    messageText.setString("Press Enter to Start");

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(
        textRect.left + textRect.width  / 2.0f,
        textRect.top  + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth    = 400;
    float timeBarHeight        = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    float timeRemaining        = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool  paused = true;
    Clock clock;
    Time  dt;

    // Game loop
    while (window.isOpen())
    {
        dt = clock.restart();

        // Input
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Enter && paused)
            {
                paused        = false;
                timeRemaining = 6.0f;
                score         = 0;
                acceptInput   = true;
                messageText.setString("");
                spritePlayer.setPosition(580, 720);
                spriteRip.setPosition(3000, 720);

                for (int i = 0; i < NUM_BRANCHES; i++)
                    branchPositions[i] = Side::NONE;

                updateBranches(1);
                updateBranches(2);
                updateBranches(3);
                updateBranches(4);
                updateBranches(5);
                branchPositions[5] = Side::NONE;
            }

            if (event.type == Event::KeyReleased && !paused)
            {
                acceptInput = true;
                spriteAxe.setPosition(2000, 830);
            }
        }

        // Update
        if (!paused)
        {
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0)
            {
                paused = true;
                messageText.setString("Out of Time!");
				outOfTimeSound.play();
            }

            // Clouds
            if (!cloudActive1)
            {
                cloudSpeed1 = rand() % 200;
                spriteCloud1.setPosition(-200, rand() % 150);
                cloudActive1 = true;
            }
            else
            {
                spriteCloud1.move(cloudSpeed1 * dt.asSeconds(), 0);
                if (spriteCloud1.getPosition().x > 1920) cloudActive1 = false;
            }

            if (!cloudActive2)
            {
                cloudSpeed2 = rand() % 200;
                spriteCloud2.setPosition(-200, (rand() % 300) - 150);
                cloudActive2 = true;
            }
            else
            {
                spriteCloud2.move(cloudSpeed2 * dt.asSeconds(), 0);
                if (spriteCloud2.getPosition().x > 1920) cloudActive2 = false;
            }

            if (!cloudActive3)
            {
                cloudSpeed3 = rand() % 200;
                spriteCloud3.setPosition(-200, (rand() % 450) - 150);
                cloudActive3 = true;
            }
            else
            {
                spriteCloud3.move(cloudSpeed3 * dt.asSeconds(), 0);
                if (spriteCloud3.getPosition().x > 1920) cloudActive3 = false;
            }

            // Chop input
            if (acceptInput)
            {
                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    playerSide = Side::LEFT;
                    spritePlayer.setPosition(580, 720);
                    spriteAxe.setPosition(AXE_POSITION_LEFT, 830);
                    score++;
                    timeRemaining += (2 / score) + .15;
                    updateBranches(score);
					spriteLog.setPosition(810, 720);
                    logSpeedX = 5000;
                    logActive = true;
                    acceptInput = false;
					chopSound.play();
                }

                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    playerSide = Side::RIGHT;
                    spritePlayer.setPosition(1200, 720);
                    spriteAxe.setPosition(AXE_POSITION_RIGHT, 830);
                    score++;
                    timeRemaining += (2 / score) + .15;
                    updateBranches(score);
					spriteLog.setPosition(810, 720);
                    logSpeedX = -5000;
                    logActive = true;
                    acceptInput = false;
					chopSound.play();
                }
            }
			if (logActive)
            {
                spriteLog.move(logSpeedX * dt.asSeconds(),
                               logSpeedY * dt.asSeconds());

                if (spriteLog.getPosition().x < -100 ||
                    spriteLog.getPosition().x > 2000)
                {
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }
            // Death check
            if (branchPositions[5] == playerSide)
            {
                paused      = true;
                acceptInput = false;
                spritePlayer.setPosition(2000, 720);

                if (playerSide == Side::LEFT)
                    spriteRip.setPosition(600, 720);
                else
                    spriteRip.setPosition(1150, 720);

                messageText.setString("SQUISHED!!");
				deathSound.play();
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(
                    textRect.left + textRect.width  / 2.0f,
                    textRect.top  + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            // Bee
            if (!beeActive)
            {
                beeSpeed = (rand() % 200) + 200;
                spriteBee.setPosition(2000, (rand() % 500) + 500);
                beeActive = true;
            }
            else
            {
                spriteBee.move(-beeSpeed * dt.asSeconds(), 0);
                if (spriteBee.getPosition().x < -100) beeActive = false;
            }

            // Score text
            stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        // Sync branch sprites to logical positions
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

        // Render
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        for (int i = 0; i < NUM_BRANCHES; i++)
            window.draw(branches[i]);
        window.draw(spritePlayer);
        window.draw(spriteRip);
        window.draw(spriteAxe);
		window.draw(spriteLog);
        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(timeBar);
        if (paused)
            window.draw(messageText);
        window.display();
    }

    return 0;
}