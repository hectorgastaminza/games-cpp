// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GfxSprite.h"
#include "GfxSpriteSliding.h"
#include "GfxWindow.h"
#include "GfxTextbox.h"
#include "GfxBar.h"

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
const float AXE_POSITION_Y = 830;
const float RIP_POSITION_Y = 750;
const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;
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
	_window.addSprite(&spriteBackground);

	// Prepare the bee
	GfxSpriteSliding spriteBee("resources/graphics/bee.png");
	spriteBee.configureSlide(slidingDirection::SLIDE_LEFT, SCREEN_WIDTH, SCREEN_HEIGHT-500, SCREEN_HEIGHT-300, 10);
	spriteBee.hide(true);
	_window.addSprite(&spriteBee);

	// Background clouds
	std::list<std::shared_ptr<GfxSpriteSliding>> clouds;
	// Load a graphic into the texture
	auto _cloudTexture = std::make_shared<sf::Texture>();
	_cloudTexture->loadFromFile("resources/graphics/cloud.png");
	// Create clouds
	for (int idx = 0 ; idx < NUM_CLOUDS ; idx++)
	{
		clouds.emplace_back(std::make_shared<GfxSpriteSliding>(_cloudTexture));
		auto ptr = clouds.back();
		ptr->configureSlide(slidingDirection::SLIDE_RIGHT, SCREEN_WIDTH, 0, 300, 10);
		ptr->hide(true);
		_window.addSprite(ptr.get());
	}

	// Make a tree sprite
	GfxSprite spriteTree("resources/graphics/tree.png");
	spriteTree.setPosition(810, 0);
	_window.addSprite(&spriteTree);

	// Background trees
	GfxSprite spriteTree2("resources/graphics/tree2.png");
	spriteTree2.setPosition(20, 0);
	_window.addSprite(&spriteTree2);
	GfxSprite spriteTree3(spriteTree2.getTexture());
	spriteTree3.setPosition(300, -400);
	_window.addSprite(&spriteTree3);
	GfxSprite spriteTree4(spriteTree2.getTexture());
	spriteTree4.setPosition(1300, -400);
	_window.addSprite(&spriteTree4);
	GfxSprite spriteTree5(spriteTree2.getTexture());
	spriteTree5.setPosition(1500, -500);
	_window.addSprite(&spriteTree5);
	GfxSprite spriteTree6(spriteTree2.getTexture());
	spriteTree6.setPosition(1900, 0);
	_window.addSprite(&spriteTree6);

	// Prepare 5 branches
	// Set the texture for each branch sprite
	auto _branchTexture = std::make_shared<sf::Texture>();
	// Load a graphic into the texture
	_branchTexture->loadFromFile("resources/graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i] = GfxSprite(_branchTexture);
		branches[i].hide(true);
		// Set the sprite's origin to dead center
		// We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
		_window.addSprite(&branches[i]);
	}

	// Prepare the flying log
	GfxSprite spriteLog("resources/graphics/log.png");
	spriteLog.hide(true);
	_window.addSprite(&spriteLog);

	// Prepare the player
	GfxSprite spritePlayer("resources/graphics/player.png");
	spritePlayer.hide(true);
	_window.addSprite(&spritePlayer);

	// Prepare the axe
	GfxSprite spriteAxe("resources/graphics/axe.png");
	spriteAxe.hide(true);
	_window.addSprite(&spriteAxe);

	// Prepare the gravestone
	GfxSprite spriteRIP("resources/graphics/rip.png");
	spriteRIP.hide(true);
	_window.addSprite(&spriteRIP);

	// Prepare FPS information
	GfxTextbox textboxFps(sf::Vector2f(FPS_WIDTH,FPS_HEIGHT), "resources/fonts/KOMIKAP_.ttf", 20);
	textboxFps.setForeColor(sf::Color::Magenta);
	textboxFps.setBackColor(sf::Color(0, 0, 0, 150));
	textboxFps.setPosition(SCREEN_WIDTH - FPS_WIDTH - 50, INFO_POS_Y);
	textboxFps.hide(true);
	_window.addSprite(&textboxFps);

	// Prepare Score Information
	GfxTextbox textboxScore(sf::Vector2f(SCORE_WIDTH, SCORE_HEIGHT), "resources/fonts/KOMIKAP_.ttf", 60);
	textboxScore.setForeColor(sf::Color::Yellow);
	textboxScore.setBackColor(sf::Color(0, 0, 0, 150));
	textboxScore.setPosition(50, INFO_POS_Y);
	textboxScore.hide(true);
	_window.addSprite(&textboxScore);

	// Time bar
	const float maxTime = 6.0f;
	GfxBar timeBar(maxTime, maxTime, 400, 80);
	timeBar.setPosition((SCREEN_WIDTH / 2) - 400 / 2, INFO_POS_Y);
	timeBar.setForeColor(Color::Red);
	timeBar.setBackColor(sf::Color(Color::Red.r, Color::Red.g, Color::Red.b, 150));
	timeBar.hide(true);
	_window.addSprite(&timeBar);

	// Prepare Game Information popup
	GfxTextbox textboxPopup(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT), "resources/fonts/KOMIKAP_.ttf", 140);
	textboxPopup.setForeColor(sf::Color::Cyan);
	textboxPopup.setPosition(0, 0);
	textboxPopup.enableBackground(false);
	textboxPopup.hide(true);
	_window.addSprite(&textboxPopup);



	// The player starts on the left
	side playerSide = side::LEFT;
	
	// Variables to control time itself
	Clock clock;

	Time gameTimeTotal;

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
				spriteAxe.hide(true);
			}
		}

		/* ****************************************
			Handle the players input
		**************************************** */

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			_window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			acceptInput = true;

			// Reset the time and the score
			score = 0;
			timeBar.setValue(maxTime);

			// hide popup message
			textboxPopup.hide(true);

			// Make all the branches disappear
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			// Make sure the gravestone is hidden
			spriteRIP.hide(true);

			// Move the player into position
			playerSide = side::LEFT;
			spritePlayer.setPosition(580, 720);
			spritePlayer.hide(false);

			textboxScore.hide(false);
			textboxFps.hide(false);
			timeBar.hide(false);
		}

		// Wrap the player controls to
		// Make sure we are accepting input
		if (acceptInput)
		{
			// More code here next...
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				acceptInput = false;
				score++;

				// Add to the amount of time remaining
				timeBar.addValue((2 / score) + .15);

				spriteAxe.setPosition(AXE_POSITION_RIGHT, AXE_POSITION_Y);
				spriteAxe.setRotation(0);
				spriteAxe.hide(false);

				// Make sure the player is on the right
				playerSide = side::RIGHT;
				spritePlayer.setPosition(1200, 720);
				spritePlayer.hide(false);

				// update the branches
				updateBranches(score);

				// set the log flying to the left
				spriteLog.setPosition(810, 720);
				spriteLog.hide(false);
				logSpeedX = -5000;
				logActive = true;

				// Play a chop sound
				//chop.play();
			}

			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				acceptInput = false;

				score++;
				// Add to the amount of time remaining
				timeBar.addValue((2 / score) + .15);

				spriteAxe.setPosition(AXE_POSITION_LEFT, AXE_POSITION_Y);
				spriteAxe.setRotation(180);
				spriteAxe.hide(false);

				// Make sure the player is on the left
				playerSide = side::LEFT;
				spritePlayer.setPosition(580, 720);
				spritePlayer.hide(false);

				// update the branches
				updateBranches(score);

				// set the log flying
				spriteLog.setPosition(810, 720);
				spriteLog.hide(false);
				logSpeedX = 5000;
				logActive = true;

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
			timeBar.addValue((dt.asSeconds() * -1.0));

			if (timeBar.getValue() <= 0.0f) {

				// Pause the game
				paused = true;

				// Change the message shown to the player
				textboxPopup.setText("Out of time!!");
				textboxPopup.hide(false);

				// Play the out of time sound
				//outOfTime.play();
			}

			// Move the bee
			spriteBee.slide(dt.asSeconds());

			// Manage the clouds with arrays
			for (auto it : clouds)
			{
				it->slide(dt.asSeconds());
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
				branches[i].hide(false);

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
					branches[i].hide(true);
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
					spriteLog.getPosition().x > SCREEN_WIDTH)
				{
					// Set it up ready to be a whole new cloud next frame
					logActive = false;
					spriteLog.hide(true);
				}
			}

			// has the player been squished by a branch?
			if (branchPositions[5] == playerSide)
			{
				// death
				paused = true;
				acceptInput = false;

				// Draw the gravestone
				spriteRIP.setPosition(spritePlayer.getPosition().x, RIP_POSITION_Y);
				spriteRIP.hide(false);

				// hide the player
				spritePlayer.hide(true);

				// hide the axe
				spriteAxe.hide(true);

				// hide log
				spriteLog.hide(true);

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



