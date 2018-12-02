// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GfxSprite.h"
#include "GfxWindow.h"
#include "GfxTextbox.h"

// Make code easier to type with "using namespace"
using namespace sf;
// Function declaration
void updateBranches(int seed);

const int NUM_CLOUDS = 6;
const int NUM_BRANCHES = 6;
GfxSprite branches[NUM_BRANCHES];

// Where is the player/branch? 
// Left or Right
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

// Line the axe up with the tree
const float AXE_POSITION_LEFT = 850;
const float AXE_POSITION_RIGHT = 1075;
const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;
const float OUT_SCREEN_X = 2200;
const float INFO_POS_Y = SCREEN_HEIGHT - 120;
const float FPS_WIDTH = 300;
const float FPS_HEIGHT = 50;
const float SCORE_WIDTH = 600;
const float SCORE_HEIGHT = 80;

int main()
{
	// Create a video mode object
	GfxWindow _window("Timber!!!", SCREEN_WIDTH, SCREEN_HEIGHT);

	// Create background
	GfxSprite spriteBackground("resources/graphics/background.png");
	spriteBackground.setPosition(0,0);
	_window.addSprite(spriteBackground);

	// Make a tree sprite
	GfxSprite spriteTree("resources/graphics/tree.png");
	spriteTree.setPosition(810, 0);
	_window.addSprite(spriteTree);

	// Background trees
	GfxSprite spriteTree2("resources/graphics/tree2.png");
	spriteTree2.setPosition(20, 0);
	_window.addSprite(spriteTree2);
	GfxSprite spriteTree3(spriteTree2.getTexture());
	spriteTree3.setPosition(300, -400);
	_window.addSprite(spriteTree3);
	GfxSprite spriteTree4(spriteTree2.getTexture());
	spriteTree4.setPosition(1300, -400);
	_window.addSprite(spriteTree4);
	GfxSprite spriteTree5(spriteTree2.getTexture());
	spriteTree5.setPosition(1500, -500);
	_window.addSprite(spriteTree5);
	GfxSprite spriteTree6(spriteTree2.getTexture());
	spriteTree6.setPosition(1900, 0);
	_window.addSprite(spriteTree6);

	// Prepare the bee
	GfxSprite spriteBee("resources/graphics/bee.png");
	spriteBee.setPosition(20, 0);
	_window.addSprite(spriteBee);

	// Background clouds
	GfxSprite clouds[NUM_CLOUDS];
	int cloudSpeeds[NUM_CLOUDS];
	bool cloudsActive[NUM_CLOUDS];

	auto _cloudTexture = std::make_shared<sf::Texture>();
	// Load a graphic into the texture
	_cloudTexture->loadFromFile("resources/graphics/cloud.png");

	for (int i = 1; i < NUM_CLOUDS; i++)
	{
		clouds[i] = GfxSprite(_cloudTexture);
		clouds[i].setPosition(-300, i * 150);
		cloudsActive[i] = false;
		cloudSpeeds[i] = 0;
		_window.addSprite(clouds[i]);
	}

	// Prepare 5 branches
	// Set the texture for each branch sprite
	auto _branchTexture = std::make_shared<sf::Texture>();
	// Load a graphic into the texture
	_branchTexture->loadFromFile("resources/graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i] = GfxSprite(_branchTexture);
		branches[i].setPosition(-OUT_SCREEN_X, -OUT_SCREEN_X);
		// Set the sprite's origin to dead center
		// We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
		_window.addSprite(branches[i]);
	}

	// Prepare the player
	GfxSprite spritePlayer("resources/graphics/player.png");
	spritePlayer.setPosition(OUT_SCREEN_X, 720);
	_window.addSprite(spritePlayer);

	// Prepare the axe
	GfxSprite spriteAxe("resources/graphics/axe.png");
	spriteAxe.setPosition(OUT_SCREEN_X, 830);
	_window.addSprite(spriteAxe);

	// Prepare the gravestone
	GfxSprite spriteRIP("resources/graphics/rip.png");
	spriteRIP.setPosition(OUT_SCREEN_X, 750);
	_window.addSprite(spriteRIP);

	// Prepare the flying log
	GfxSprite spriteLog("resources/graphics/log.png");
	spriteLog.setPosition(OUT_SCREEN_X, 720);
	_window.addSprite(spriteLog);

	// Prepare FPS information
	GfxTextbox textboxFps(sf::Vector2f(FPS_WIDTH,FPS_HEIGHT), "resources/fonts/KOMIKAP_.ttf", 20);
	textboxFps.setForeColor(sf::Color::Magenta);
	textboxFps.setBackColor(sf::Color(0, 0, 0, 150));
	textboxFps.setPosition(SCREEN_WIDTH - FPS_WIDTH - 50, INFO_POS_Y);
	_window.addSprite(&textboxFps);

	// Prepare Score Information
	GfxTextbox textboxScore(sf::Vector2f(SCORE_WIDTH, SCORE_HEIGHT), "resources/fonts/KOMIKAP_.ttf", 60);
	textboxScore.setForeColor(sf::Color::Yellow);
	textboxScore.setBackColor(sf::Color(0, 0, 0, 150));
	textboxScore.setPosition(50, INFO_POS_Y);
	_window.addSprite(&textboxScore);

	// Prepare Game Information popup
	GfxTextbox textboxPopup(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT), "resources/fonts/KOMIKAP_.ttf", 140);
	textboxPopup.setForeColor(sf::Color::Cyan);
	textboxPopup.setBackColor(sf::Color(0, 0, 0, 150));
	textboxPopup.setPosition(0, 0);
	textboxPopup.enableBackground(false);
	textboxPopup.hide(true);
	_window.addSprite(&textboxPopup);


	// The player starts on the left
	side playerSide = side::LEFT;

	// Is the bee currently moving?
	bool beeActive = false;

	// How fast can the bee fly
	float beeSpeed = 0.0f;


	
	// Variables to control time itself
	Clock clock;
	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((SCREEN_WIDTH / 2) - timeBarStartWidth / 2, INFO_POS_Y);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused = true;
	// Draw some text
	int score = 0;

	// Some other useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	// Control the player input
	bool acceptInput = false;

	// Prepare the sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("resources/sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("resources/sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	// Out of time
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("resources/sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	// control the drawing of the score
	int lastDrawn = 0;

	while (_window.isOpen())
	{
		// score ++;
		Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;

				// hide the axe
				spriteAxe.setPosition(OUT_SCREEN_X, spriteAxe.getPosition().y);
				spriteAxe.setRotation(0);
			}
		}

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			_window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			// hide popup message
			textboxPopup.hide(true);

			// Reset the time and the score
			score = 0;
			timeRemaining = 6;

			// Make all the branches disappear
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			// Make sure the gravestone is hidden
			spriteRIP.setPosition(OUT_SCREEN_X, spriteRIP.getPosition().y);

			// Move the player into position
			spritePlayer.setPosition(580, 720);

			acceptInput = true;
		}

		// Wrap the player controls to
		// Make sure we are accepting input
		if (acceptInput)
		{
			// More code here next...
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				playerSide = side::RIGHT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);
				spriteAxe.setRotation(0);

				spritePlayer.setPosition(1200, 720);

				// update the branches
				updateBranches(score);

				// set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				// Play a chop sound
				//chop.play();
			}

			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Make sure the player is on the left
				playerSide = side::LEFT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_LEFT,
					spriteAxe.getPosition().y);
				spriteAxe.setRotation(180);

				spritePlayer.setPosition(580, 720);

				// update the branches
				updateBranches(score);

				// set the log flying
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;


				acceptInput = false;

				// Play a chop sound
				//chop.play();
			}
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!paused)
		{

			// Measure time
			Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			// size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {

				// Pause the game
				paused = true;

				// Change the message shown to the player
				textboxPopup.setText("Out of time!!");
				textboxPopup.hide(false);

				// Play the out of time sound
				//outOfTime.play();
			}


			// Setup the bee
			if (!beeActive)
			{
				// How fast is the bee
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;

				// How high is the bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(OUT_SCREEN_X, height);
				beeActive = true;
			}
			else
				// Move the bee
			{
				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);

				// Has the bee reached the right hand edge of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					// Set it up ready to be a whole new cloud next frame
					beeActive = false;
				}
			}

			// Manage the clouds with arrays
			for (int i = 0; i < NUM_CLOUDS; i++)
			{
				if (!cloudsActive[i])
				{
					// How fast is the cloud
					srand((int)time(0) * i);
					cloudSpeeds[i] = (rand() % 200);

					// How high is the cloud
					srand((int)time(0) * i);
					float height = (rand() % 150);
					clouds[i].setPosition(-200, height);
					cloudsActive[i] = true;
				}
				else
				{
					// Set the new position
					clouds[i].setPosition(
						clouds[i].getPosition().x +
						(cloudSpeeds[i] * dt.asSeconds()),
						clouds[i].getPosition().y);

					// Has the cloud reached the right hand edge of the screen?
					if (clouds[i].getPosition().x > SCREEN_WIDTH)
					{
						// Set it up ready to be a whole new cloud next frame
						cloudsActive[i] = false;
					}
				}
			}
			
			// Draw the score and the frame rate once every 100 frames
			lastDrawn++;
			if (lastDrawn == 100) {
				// Update the score text
				std::stringstream ss;
				ss << "Score = " << score;
				textboxScore.setText(ss.str());

				// Draw the fps
				std::stringstream ss2;
				ss2 << "FPS = " << 1/dt.asSeconds();
				textboxFps.setText(ss2.str());
				lastDrawn = 0;
			}

			// update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;

				if (branchPositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					branches[i].setPosition(610, height);
					// Flip the sprite round the other way
					branches[i].setOrigin(220, 40);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					branches[i].setPosition(1330, height);
					// Set the sprite rotation to normal
					branches[i].setOrigin(220, 40);
					branches[i].setRotation(0);

				}
				else
				{
					// Hide the branch
					branches[i].setPosition(OUT_SCREEN_X, height);
				}
			}

			// Handle a flying log				
			if (logActive)
			{
				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				// Has the insect reached the right hand edge of the screen?
				if (spriteLog.getPosition().x < -100 ||
					spriteLog.getPosition().x > OUT_SCREEN_X)
				{
					// Set it up ready to be a whole new cloud next frame
					logActive = false;
					spriteLog.setPosition(OUT_SCREEN_X, 720);
				}
			}

			// has the player been squished by a branch?
			if (branchPositions[5] == playerSide)
			{
				// death
				paused = true;
				acceptInput = false;

				// Draw the gravestone
				spriteRIP.setPosition(spritePlayer.getPosition().x, spriteRIP.getPosition().y);

				// hide the player
				spritePlayer.setPosition(OUT_SCREEN_X, spritePlayer.getPosition().y);

				// hide the axe
				spriteAxe.setPosition(OUT_SCREEN_X, spriteAxe.getPosition().y);
				spriteAxe.setRotation(0);

				// hide log
				spriteLog.setPosition(OUT_SCREEN_X, 720);

				// Change the text of the message
				textboxPopup.setText("SQUISHED!!");
				textboxPopup.hide(false);

				// Play the death sound
				//death.play();
			}


		}// End if(!paused)

		 /*
		 ****************************************
		 Draw the scene
		 ****************************************
		 */

		 // Clear everything from the last frame
		_window.clear();

		// Draw our game scene here
		_window.drawSprites();

		// Draw the timebar
		_window.draw(timeBar);

		// Show everything we just drew
		_window.display();
	}

	return 0;
}

// Function definition
void updateBranches(int seed)
{
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}

	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;

	case 1:
		branchPositions[0] = side::RIGHT;
		break;

	default:
		branchPositions[0] = side::NONE;
		break;
	}


}



