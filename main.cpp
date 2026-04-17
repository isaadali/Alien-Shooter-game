#include <iostream>
#include <fstream>
#include <string>
#include "help.h"
using namespace std;

const int bgC = 12; //bg Color
void enableFullScreen() {
	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_MAXIMIZE); //maximize the console window
}

void drawStar(int x, int y, int R, int G, int B) {
	// Small dot to represent the star
	myEllipse(x - 2, y - 2, x + 2, y + 2, R, G, B, R, G, B);
}

void clearStar(int x, int y, int bgc) {
	// Clear the star by drawing a background-colored dot
	myEllipse(x - 2, y - 2, x + 2, y + 2, bgc, bgc, bgc, bgc, bgc, bgc);
}

void drawShip(int x, int y, int R, int G, int B) {
	//body of the spaceship
	myRect(x - 20, y - 10, x + 20, y + 10, R, G, B, R / 2, G / 2, B / 2);

	//front of the spaceship
	myLine(x + 20, y - 10, x + 40, y, R, G, B);
	myLine(x + 20, y + 10, x + 40, y, R, G, B);

	//thruster of the spaceship
	myLine(x - 20, y - 5, x - 40, y - 15, 255, 69, 0);
	myLine(x - 20, y + 5, x - 40, y + 15, 255, 69, 0);

	//flame at the back
	myEllipse(x - 60, y + 7, x - 20, y - 7, 255, 69, 0, 255, 165, 0);
}

void removeShip(int initial_x, int initial_y, int bgc) {
	//body of the spaceship
	myRect(initial_x - 20, initial_y - 10, initial_x + 20, initial_y + 10, bgc, bgc, bgc, bgc, bgc, bgc);

	//front of the spaceship
	myLine(initial_x + 20, initial_y - 10, initial_x + 40, initial_y, bgc, bgc, bgc);
	myLine(initial_x + 20, initial_y + 10, initial_x + 40, initial_y, bgc, bgc, bgc);

	//thruster of the spaceship
	myLine(initial_x - 20, initial_y - 5, initial_x - 40, initial_y - 15, bgc, bgc, bgc);
	myLine(initial_x - 20, initial_y + 5, initial_x - 40, initial_y + 15, bgc, bgc, bgc);

	//flame at the back
	myEllipse(initial_x - 60, initial_y + 7, initial_x - 20, initial_y - 7, bgc, bgc, bgc, bgc, bgc, bgc);
}

void drawAlien(int x, int y, int R, int G, int B) {
	//head
	myEllipse(x - 15, y - 15, x + 15, y + 15, R, G, B, R / 2, G / 2, B / 2);
	//eyes
	myEllipse(x - 8, y - 5, x - 4, y + 5, 0, 0, 0, 0, 255, 0); //left Eye
	myEllipse(x + 4, y - 5, x + 8, y + 5, 0, 0, 0, 0, 255, 0); //right Eye
	//pupils
	myEllipse(x - 5, y, x - 4, y + 3, 255, 255, 255, 255, 255, 255);  // Left Pupil
	myEllipse(x + 5, y, x + 4, y + 3, 255, 255, 255, 255, 255, 255);  // Right Pupil
	//mouth
	myLine(x - 10, y + 10, x + 10, y + 10, 255, 255, 255);
	//antennae
	myLine(x - 10, y - 15, x - 20, y - 30, 255, 0, 0);
	myLine(x + 10, y - 15, x + 20, y - 30, 255, 0, 0);
}

void removeAlien(int x, int y, int bgc) {
	//remove the head
	myEllipse(x - 15, y - 15, x + 15, y + 15, bgc, bgc, bgc, bgc, bgc, bgc);
	//remove the eyes
	myEllipse(x - 8, y - 5, x - 4, y + 5, bgc, bgc, bgc, bgc, bgc, bgc); // Left Eye
	myEllipse(x + 4, y - 5, x + 8, y + 5, bgc, bgc, bgc, bgc, bgc, bgc); // Right Eye
	//remove the mouth
	myLine(x - 10, y + 10, x + 10, y + 10, bgc, bgc, bgc);
	//remove the antennae
	myLine(x - 10, y - 15, x - 20, y - 30, bgc, bgc, bgc);
	myLine(x + 10, y - 15, x + 20, y - 30, bgc, bgc, bgc);
}

void drawSadAlien(int x, int y, int r, int g, int b) {
	//Head
	myEllipse(x - 15, y - 15, x + 15, y + 15, r, g, b, r / 2, g / 2, b / 2);  // Head with green color

	//Eyes
	myEllipse(x - 8, y - 5, x - 4, y + 5, 255, 255, 255, 255, 255, 255);  // Left Eye
	myEllipse(x + 4, y - 5, x + 8, y + 5, 255, 255, 255, 255, 255, 255);  // Right Eye

	//Mouth
	myLine(x - 10, y + 10, x + 10, y + 10, 0, 0, 0);
	myLine(x - 10, y + 10, x - 7, y + 12, 0, 0, 0);
	myLine(x + 10, y + 10, x + 7, y + 12, 0, 0, 0);

	//Antennae
	myLine(x - 10, y - 15, x - 20, y - 30, 255, 255, 0);  // Left Antenna
	myLine(x + 10, y - 15, x + 20, y - 30, 255, 255, 0);  // Right Antenna
}

void drawBullet(int x, int y, int R, int G, int B) {
	//bullet
	myEllipse(x - 5, y - 5, x + 5, y + 5, R, G, B, R, G / 2, B / 2);
}

void removeBullet(int prevX, int prevY, int bgc) {
	myEllipse(prevX - 5, prevY - 5, prevX + 5, prevY + 5, bgc, bgc, bgc, bgc, bgc, bgc);
}

//bullets state global variables
const int MAX_BULLETS = 10;
int bulletX[MAX_BULLETS] = { 0 }; //bullets x-y coords array
int bulletY[MAX_BULLETS] = { 0 };
bool bulletActive[MAX_BULLETS] = { false };
int bulletCooldown = 0;

void fireBullet(int shipX, int shipY, int alienx[][10], int alieny[][10], int bullethit[][10], int rows, int cols, int& score) {
	if (bulletCooldown == 0) {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!bulletActive[i]) {
				//initialize bullet
				bulletX[i] = shipX + 45;
				bulletY[i] = shipY;
				bulletActive[i] = true;

				drawBullet(bulletX[i], bulletY[i], 255, 165, 0);
				//cooldown so not all bullets are fired at once
				bulletCooldown = 3; //firing rate
				break;
			}
		}
	}
}

int bullet_speed = 10;

void updateScoreNdbullet(int alienx[][10], int alieny[][10], int bullethit[][10], int rows, int cols, int& score) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bulletActive[i]) {
			//remove the previous bullet
			removeBullet(bulletX[i], bulletY[i], bgC);

			bulletX[i] += bullet_speed;

			//check if the bullet goes off-screen
			if (bulletX[i] >= 1440) {
				bulletActive[i] = false;
			}
			else {
				//draw the bullet
				drawBullet(bulletX[i], bulletY[i], 255, 165, 0);

				//check bullethit with aliens
				for (int r = 0; r < rows; r++) {
					for (int c = 0; c < cols; c++) {
						//if bullet hits with an alien
						if (bullethit[r][c] == 1 &&
							bulletX[i] >= alienx[r][c] - 15 && bulletX[i] <= alienx[r][c] + 15 &&
							bulletY[i] >= alieny[r][c] - 30 && bulletY[i] <= alieny[r][c] + 15) {

							removeAlien(alienx[r][c], alieny[r][c], bgC);
							removeBullet(bulletX[i], bulletY[i], bgC);

							//update state
							bullethit[r][c] = 0;   // alien is dead
							bulletActive[i] = false;
							drawText(20, 20, 10, 0, 0, 0, "Score: ", true, score);
							score += 10;
							drawText(20, 20, 10, 255, 255, 255, "Score: ", true, score);
							break;
						}
					}
				}
			}
		}
	}
}

void initializeAliens(int alienx[][10], int alieny[][10], int aliens_inrow, int aliens_incol) {
	int startX = 720;  //x-pos of the first alien
	int startY = 300;  //y-pos of the first alien
	const int xspace = 70; //x-spacing btw aliens
	const int yspace = 50; //y-spacing btw rows

	for (int i = 0; i < aliens_inrow; i++) {
		for (int j = 0; j < aliens_incol; j++) {
			alienx[i][j] = startX + j * xspace;
			alieny[i][j] = startY + i * yspace;
			drawAlien(alienx[i][j], alieny[i][j], 255, 0, 0);
		}
	}
}

bool moveAliens(int alienx[][10], int alieny[][10], int bullethit[][10], int aliens_inrow, int aliens_incol, double a_speed) {
	const int left_edge = 0;
	bool gameOver = false;

	for (int i = 0; i < aliens_inrow; i++) {
		for (int j = 0; j < aliens_incol; j++) {
			if (bullethit[i][j] == 1) {
				removeAlien(alienx[i][j], alieny[i][j], bgC);
				alienx[i][j] -= a_speed;
				drawAlien(alienx[i][j], alieny[i][j], 255, 0, 0);

				//if alien reaches left edge of the screen, game-over
				if (alienx[i][j] <= left_edge) {
					gameOver = true;
				}
			}
		}
	}

	return gameOver;
}

void writeScore(int score) {
	std::fstream file("highscore.txt", std::ios::out | std::ios::app);
	if (file.is_open()) {
		file << score << std::endl;
		file.close();
	}
	else {
		drawText(20, 20, 50, 255, 0, 0, "Error: Could not write to highscore.txt", 0);
	}
}

void displayTopScores() {
	fstream file("highscore.txt", ios::in);
	if (!file.is_open()) {
	//	cout << "Unable to open highscore.txt" << endl;
		return;

	}

	const int MAX_SCORES = 100;
	int scores[MAX_SCORES];
	int i = 0;

	//read all scores from the file into the array
	while (file >> scores[i] && i < MAX_SCORES) {
		i++;
	}

	//sort the scores in descending order
	for (int j = 0; j < i - 1; ++j) {
		for (int k = j + 1; k < i; ++k) {
			if (scores[j] < scores[k]) {
				int temp = scores[j];
				scores[j] = scores[k];
				scores[k] = temp;
			}
		}
	}


	//display the top scores
	int yPos = 80; //starting position for the first rank
	drawText(20, 520, 20, 255, 169, 0, "Top 5 High Scores: ", 0);

	//if scores are less then 5 in the file then only access the scores present in the file
	int displayCount = 5;
	if (i < 5) {
		displayCount = i;
	}

	//gold color
	int R = 255;
	int G = 223;
	int B = 0;
	int decreaseRate = 30;  //rate at which the intensity decreases

	for (int i = 0; i < displayCount; i++) {
		if (R - decreaseRate >= 0)
			R -= decreaseRate;
		if (G - decreaseRate >= 0)
			G -= decreaseRate;
		if (B - decreaseRate >= 0)
			B -= decreaseRate;

		// Display rank
		drawText(20, 620, yPos, R, G, B, "Rank ", 0);
		drawText(20, 620 + 50, yPos, R, G, B, "  ", true, i + 1);
		yPos += 60;

		// Display score
		drawText(20, 600, yPos, 255, 255, 255, "Score: ", 0);
		drawText(20, 600 + 50, yPos, 255, 255, 255, "   ", true, scores[i]);
		yPos += 60;
	}
}

void saveGameState(int alienx[][10], int alieny[][10], int bullethit[][10], int rows, int cols,
	int spaceshipX, int spaceshipY, int score, int lives, int level) {
	ofstream file;
	file.open("saved_game.txt");
	if (file.is_open()) {
		file << spaceshipX << " " << spaceshipY << "\n";
		file << score << " " << lives << " " << level << "\n";
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				file << alienx[i][j] << " " << alieny[i][j] << " " << bullethit[i][j] << " ";
			}
			file << "\n";
		}
		file.close();
	}
	//else {
	////	cout << "Error: Could not save the game state!" << endl;
	//}
}

bool loadGameState(int alienx[][10], int alieny[][10], int bullethit[][10], int rows, int cols,
	int& spaceshipX, int& spaceshipY, int& score, int& lives, int& level) {
	ifstream file;
	file.open("saved_game.txt");
	if (file.is_open()) {
		file >> spaceshipX >> spaceshipY;
		file >> score >> lives >> level;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				file >> alienx[i][j] >> alieny[i][j] >> bullethit[i][j];
			}
		}
		file.close();
		return true;
	}
	else {
		//cout << "Error: No saved game found!" << endl;
		return false;
	}
}

bool checkSavedGame(const string& filename = "saved_game.txt") {
	ifstream file(filename);
	return file.is_open();
}

void displayMenu(int selectedIndex, int bulletX, int bulletY) {
	bool save_game = checkSavedGame();
	const char* options[5] = { "Start Game", "Leaderboard", "Instructions", "Exit" };
	int size = 4;
	int numOptions = 4;

	if (save_game) {
		for (int i = numOptions; i > 0; i--) {
			options[i] = options[i - 1];
		}
		options[0] = "Resume";
		options[1] = "New Game";

		numOptions++;
	}

	//positions for menu items
	int menuX = 610;  //x position of menu text
	int menuY = 420;  //y position of the first menu option
	int menuSpacing = 60;  //space between each option
	static int prevAlienY = menuY;  //store previous alien Y position

	//remove the previous alien
	removeAlien(570, prevAlienY, bgC);

	// Update alien position based on selected menu option
	int alienY = menuY + (selectedIndex * menuSpacing);

	if (selectedIndex == numOptions - 1) {
		drawSadAlien(570, alienY, 255, 0, 0);
	}
	else {
		drawAlien(570, alienY, 255, 255, 0);  // Normal selected option
	}

	//store the current alien position for the next iteration
	prevAlienY = alienY;

	drawShip(200, 325, 0, 255, 255);
	drawAlien(400, 125, 255, 0, 255);
	drawAlien(1040, 125, 0, 255, 0);
	drawAlien(1200, 325, 255, 69, 0);

	drawBullet(bulletX, bulletY, 255, 165, 0);

	for (int i = 0; i < numOptions; i++) {
		if (i == selectedIndex) {
			//highlight selected option with yellow color
			drawText(18, 600, 400 + (i * 60), 255, 255, 0, options[i], 0);
		}
		else {
			drawText(18, 600, 400 + (i * 60), 255, 255, 255, options[i], 0);
		}
	}
}

int gameMenu(int numOptions) {
	int selectedIndex = 0; //current selected menu option
	int bulletX = 240;  //initial bullet position
	int bulletY = 325;  //vertical position
	int prevBulletX = bulletX; //store previous bullet position
	int prevBulletY = bulletY; //store previous bullet position
	int intensity = 255;       //start intensity for the glow
	bool increasing = true;    //direction of intensity change
	bool menuRunning = true;
	bool save_game = checkSavedGame();

	const int numStars = 20;
	int starX[numStars] = { 321, 90, 30, 130, 230, 50, 150, 300, 450, 600, 750, 900, 1050, 1200, 1350, 200, 800, 400, 1000, 500 };
	int starY[numStars] = { 0, 420, 470, 510, 380, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800 };
	const int screenWidth = 1200;

	//Menu Loop
	while (menuRunning) {
		//animate stars
		for (int i = 0; i < numStars; i++) {
			clearStar(starX[i], starY[i], bgC);

			//update star position
			starX[i] += 1;
			if (starX[i] > screenWidth) {
				starX[i] = (i * 100) % screenWidth; //reset position
			}

			drawStar(starX[i], starY[i], 255, 255, 255);
		}

		removeBullet(prevBulletX, prevBulletY, bgC);

		//Update bullet position
		bulletX += 2;
		if (bulletX > 1180) { //reset when reached max bound
			bulletX = 240;
		}

		//store current bullet position
		prevBulletX = bulletX;
		prevBulletY = bulletY;

		displayMenu(selectedIndex, bulletX, bulletY);

		drawText(40, 440, 80, intensity, 0, 0, "SPACE INVADERS", 0);
		drawText(18, 330, 220, 255, 255, 0, "Are You Ready to Battle against the Invaders?", 0);

		//intensity for glowing effect
		if (increasing) {
			intensity += 5;
			if (intensity >= 255) {
				increasing = false; //Reverse direction when max is reached
			}
		}
		//decrease intensity
		else {
			intensity -= 5;
			if (intensity <= 100) {
				increasing = true; //Reverse direction when min is reached
			}
		}
		int whichKey = 0;
		if (isKeyPressed(whichKey)) {
			if (whichKey == 2) { //Up arrow
				selectedIndex = (selectedIndex - 1 + numOptions) % numOptions; //move up
			}
			else if (whichKey == 4) { //Down arrow
				selectedIndex = (selectedIndex + 1) % numOptions; //Move down
			}
			else if (whichKey == 5) { //Enter key
				system("cls");

				if (numOptions == 5) {
					if (selectedIndex == 0) {  //Handle resume logic
						return 1;
						//Load the saved game and resume
					}
					else if (selectedIndex == 1) {  //Start new game
						return 0;
					}
					else if (selectedIndex == 2) { //Leaderboard
						system("cls");

						//Open file
						ifstream ihighscore("highscore.txt");
						string line;
						bool isEmpty = true;

						//check if the file is empty
						if (ihighscore) {
							while (getline(ihighscore, line)) {
								isEmpty = false;
								break;
							}
						}

						if (isEmpty) {
							drawText(20, 330, 350, 255, 165, 0, "No high scores, play to show high score...", 0);
						}
						else {
							displayTopScores();
						}

						drawText(15, 20, 800, 255, 165, 0, "Press Escape to return to the menu...", 0);

						//Escape key
						int key;
						while (true) {
							if (isKeyPressed(key)) {
								if (key == 7) {
									break;
								}
							}
						}
						system("cls");
					}
					else if (selectedIndex == 3) { //Instructions
						system("cls");

						//display instructions
						drawText(20, 330, 300, 0, 255, 0, "Use arrow keys to navigate", 0);
						drawText(20, 330, 350, 0, 255, 0, "Space to fire.", 0);
						drawText(15, 20, 800, 0, 255, 0, "Press Escape to return to the menu.", 0);

						//Escape key
						int key;
						while (true) {
							if (isKeyPressed(key)) {
								if (key == 7) {
									break;
								}
							}
						}
						system("cls");
					}
					else if (selectedIndex == 4) { //Exit
						return 2;
					}
				}
				else if (numOptions == 4) {
					//Menu options
					if (selectedIndex == 0) {  //start game
						menuRunning = false;
						return 0;
					}
					else if (selectedIndex == 1) { //Leaderboard
						system("cls");

						//Open file
						ifstream ihighscore("highscore.txt");
						string line;
						bool isEmpty = true;

						//check if the file is empty
						if (ihighscore) {
							while (getline(ihighscore, line)) {
								isEmpty = false;
								break;
							}
						}

						if (isEmpty) {
							drawText(20, 330, 350, 255, 165, 0, "No high scores, play to show high score...", 0);
						}
						else {
							displayTopScores();
						}

						drawText(15, 20, 800, 255, 165, 0, "Press Escape to return to the menu...", 0);

						//Escape key
						int key;
						while (true) {
							if (isKeyPressed(key)) {
								if (key == 7) {
									break;
								}
							}
						}
						system("cls");
					}
					else if (selectedIndex == 2) { //Instructions
						system("cls");

						//display instructions
						drawText(20, 330, 300, 0, 255, 0, "Use arrow keys to navigate", 0);
						drawText(20, 330, 350, 0, 255, 0, "Space to fire.", 0);
						drawText(15, 20, 800, 0, 255, 0, "Press Escape to return to the menu.", 0);

						//Escape key
						int key;
						while (true) {
							if (isKeyPressed(key)) {
								if (key == 7) {
									break;
								}
							}
						}
						system("cls");
					}
					else if (selectedIndex == 3) { //Exit
						return 2;
					}
				}
			}
		}
	}
	return -1;
}

bool isPaused = false;

void initializeGame(int alienx[][10], int alieny[][10], int bullethit[][10], int rows, int cols,
	int& spaceshipX, int& spaceshipY, int& lives, int& score, int& level, bool& gameOver, bool is_gamesave) {

	//for resuming
	if (is_gamesave) {

		system("cls");  

		// Display spaceship
		drawShip(spaceshipX, spaceshipY, 0, 255, 255);  

		// Display score and lives
		drawText(20, 20, 10, 255, 255, 255, "Score: ", true, score);  
		drawText(20, 850, 10, 255, 255, 255, "Lives: ", true, lives);  
		drawText(20, 450, 10, 255, 255, 0, "Level: ", true, level);  

		// Display aliens
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (bullethit[i][j] == 1) {  // If the alien is alive 
					drawAlien(alienx[i][j], alieny[i][j], 255, 0, 0); 
				}
			}
		}
	}
	else if (!is_gamesave) {

		//if new or restart
		//reset aliens
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				bullethit[i][j] = 1;
			}
		}

		//initialize alien positions
		initializeAliens(alienx, alieny, rows, cols);

		//reset spaceship position
		spaceshipX = 100;
		spaceshipY = 450;

		//if restarted
		if (isPaused) {
			lives = 3;
			score = 0;
			level = 1;
			for (int i = 0; i < MAX_BULLETS; i++) {
				bulletX[i] = 0;
				bulletY[i] = 0;
				bulletActive[i] = false;  // Deactivate all bullets
			}
		}

		gameOver = false;

		system("cls");

		//draw initial spaceship
		drawShip(spaceshipX, spaceshipY, 0, 255, 255);

		//draw initial score and lives
		drawText(20, 20, 10, 255, 255, 255, "Score: ", true, score);
		drawText(20, 850, 10, 255, 255, 255, "Lives: ", true, lives);
		drawText(20, 450, 10, 255, 255, 0, "Level: ", true, level);  // Display the level
	}
}

bool levelOver(int bullethit[][10], int alien_rows, int alien_cols) {

	//check if all aliens are destroyed
	for (int i = 0; i < alien_rows; ++i) {
		for (int j = 0; j < alien_cols; ++j) {
			if (bullethit[i][j] == 1) {
				return false;
			}
		}
	}

	//if no aliens are alive the game is over
	return true;
}

void spaceshiphit(int& spaceshipx, int& spaceshipy, int alienx[][10], int alieny[][10], int& lives, int bullethit[][10], int rows, int cols) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (bullethit[i][j] == 1) {
				//if alien and ship collides
				if (spaceshipx >= alienx[i][j] - 45 && spaceshipx <= alienx[i][j] + 50 &&
					spaceshipy >= alieny[i][j] - 40 && spaceshipy <= alieny[i][j] + 25) {

					//change game-state
					bullethit[i][j] = 0;
					removeShip(spaceshipx, spaceshipy, bgC);
					removeAlien(alienx[i][j], alieny[i][j], bgC);

					//flashing effect 3 times upon hit
					for (int i = 0; i < 6; i++) {
						if (i % 2 == 0) {
							removeShip(spaceshipx, spaceshipy, bgC);
						}
						else {
							drawShip(spaceshipx, spaceshipy, 0, 255, 255);
						}
						Sleep(100);
					}
					removeShip(spaceshipx, spaceshipy, bgC);

					//respawn spaceship at
					spaceshipx = 100;
					spaceshipy = 450;
					drawShip(spaceshipx, spaceshipy, 0, 255, 255);

					//update lives
					drawText(20, 850, 10, 0, 0, 0, "       ", true, lives); //clear old display
					lives--;
					drawText(20, 850, 10, 255, 255, 255, "       ", true, lives); //show new lives count


				}
			}
		}
	}
}

//game-state global variables
int selectedIndex = 0;

void displayPauseMenu(int selectedIndex) {
	const char* options[] = { "Resume", "Restart", "Save and exit", "Instructions", "High Score" };
	int numOptions = 5;
	int menuX = 570;  //X-pos for menu text
	int menuY = 280;  //Y-pos for menu option
	int menuSpacing = 60;  //Space btw

	myRect(500, 250, 900, 600, 255, 255, 255, 0, 0, 0);

	//pause menu options
	for (int i = 0; i < numOptions; i++) {
		if (i == selectedIndex) {
			drawText(20, menuX, menuY + (i * menuSpacing), 255, 255, 0, options[i], 0);  // Highlight selected option
		}
		else {
			drawText(20, menuX, menuY + (i * menuSpacing), 255, 255, 255, options[i], 0);  // Normal options
		}
	}
}

void handlePauseMenuInput(int& selectedIndex, bool& isPaused, int alienx[][10], int alieny[][10],
	int bullethit[][10], int rows, int cols, int& spaceshipX, int& spaceshipY,
	int& lives, int& score, int& level, bool& gameOver, double a_speed) {
	int key;
	if (isKeyPressed(key)) {
		if (key == 2) {  //Up arrow
			selectedIndex = (selectedIndex - 1 + 5) % 5;
			displayPauseMenu(selectedIndex);
		}
		else if (key == 4) {  //Down arrow
			selectedIndex = (selectedIndex + 1) % 5;
			displayPauseMenu(selectedIndex);
		}
		else if (key == 5) {  //Enter key
			system("cls");
			if (selectedIndex == 0) { //Resume
				isPaused = false;
				system("cls");
				drawText(20, 20, 10, 255, 255, 255, "Score: ", true, score);
				drawText(20, 850, 10, 255, 255, 255, "Lives: ", true, lives);
				drawText(20, 450, 10, 255, 255, 0, "Level: ", true, level);
				drawShip(spaceshipX, spaceshipY, 0, 255, 255);
			}
			else if (selectedIndex == 1) { //restart
				system("cls");
				initializeGame(alienx, alieny, bullethit, rows, cols, spaceshipX, spaceshipY, lives, score, level, gameOver, false);
				isPaused = false;
			}
			else if (selectedIndex == 2) {//save and exit
				system("cls");
				saveGameState(alienx, alieny, bullethit, rows, cols, spaceshipX, spaceshipY, score, lives, level);
				writeScore(score);
				drawText(40, 300, 350, 255, 0, 255, "Thank You for playing!");
				drawText(20, 450, 450, 255, 255, 0, "Your score: ", true, score);
				Sleep(1500);
				system("cls");
				exit(0);
			}
			else if (selectedIndex == 3) {  //Instructions
				system("cls");
				//display instructions
				drawText(20, 330, 300, 0, 255, 0, "Use arrow keys to navigate", 0);
				drawText(20, 330, 350, 0, 255, 0, "Space to fire.", 0);
				drawText(15, 20, 800, 0, 255, 0, "Press Escape to return to the menu.", 0);

				//Escape key handling
				while (true) {
					if (isKeyPressed(key)) {
						if (key == 7) {
							system("cls");
							break;
						}
					}
				}
				//dosent resume until resume or restart is pressed/displays the pause menu again
				drawText(20, 20, 10, 255, 255, 255, "Score: ", true, score);
				drawText(20, 850, 10, 255, 255, 255, "Lives: ", true, lives);
				drawText(20, 450, 10, 255, 255, 0, "Level: ", true, level);
				drawShip(spaceshipX, spaceshipY, 0, 255, 255);
				updateScoreNdbullet(alienx, alieny, bullethit, rows, cols, score);
				moveAliens(alienx, alieny, bullethit, rows, cols, a_speed);
				displayPauseMenu(selectedIndex);
			}
			else if (selectedIndex == 4) {  //High Score
				system("cls");

				ifstream ihighscore("highscore.txt");
				string line;
				bool isEmpty = true;

				if (ihighscore) {
					while (getline(ihighscore, line)) {
						isEmpty = false;
						break;
					}
				}

				if (isEmpty) {
					drawText(20, 330, 350, 255, 165, 0, "No high scores, play to show high score...", 0);
				}
				else {
					displayTopScores();
				}

				drawText(15, 20, 800, 255, 165, 0, "Press Escape to return to the menu...", 0);

				while (true) {
					if (isKeyPressed(key)) {
						if (key == 7) {
							system("cls");
							break;
						}
					}
				}
				//dosent resume until resume or restart is pressed/displays the pause menu again
				drawText(20, 20, 10, 255, 255, 255, "Score: ", true, score);
				drawText(20, 850, 10, 255, 255, 255, "Lives: ", true, lives);
				drawText(20, 450, 10, 255, 255, 0, "Level: ", true, level);
				drawShip(spaceshipX, spaceshipY, 0, 255, 255);
				updateScoreNdbullet(alienx, alieny, bullethit, rows, cols, score);
				moveAliens(alienx, alieny, bullethit, rows, cols, a_speed);
				displayPauseMenu(selectedIndex);
			}
		}
	}
}

void displayNxtLvl(int level) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		bulletActive[i] =  false ;
	
	}
	system("cls");
	drawText(40, 500, 400, 0, 255, 0, "Level: ", true, level);
	Sleep(1500);  // Pause for 1.5 seconds to show the message
}

bool is_gamesave = false;

void gameLoop() {
	//alien and game variables
	const int rows = 6, cols = 10; //number of alien rows and columns
	int bullethit[rows][cols];     //tracks if aliens are alive (1 = alive, 0 = destroyed)
	int spaceshipX = 100, spaceshipY = 450; //initial spaceship position
	const int spaceshipSpeed = 12; //speed of spaceship movement
	bool gameOver = false;         //game state
	int bulletX = 0, bulletY = 0, score = 0, lives = 3, level = 1;
	int alienx[rows][cols], alieny[rows][cols];
	// Assume loadGameState has been called and variables are updated
	loadGameState(alienx, alieny, bullethit, rows, cols, spaceshipX, spaceshipY, score, lives, level);

	if (!is_gamesave) {
		//initialize game
		initializeGame(alienx, alieny, bullethit, rows, cols, spaceshipX, spaceshipY, lives, score, level, gameOver, is_gamesave);
	}
	else if (is_gamesave) {
		// Display the game with loaded data
		initializeGame(alienx, alieny, bullethit, rows, cols, spaceshipX, spaceshipY, lives, score, level, gameOver, is_gamesave);
	}

	const int numStars = 20;
	int starX[numStars] = { 321, 90, 30, 130, 230, 50, 150, 300, 450, 600, 750, 900, 1050, 1200, 1350, 200, 800, 400, 1000, 500 };
	int starY[numStars] = { 0, 420, 470, 510, 380, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800 };
	const int screenWidth = 1200;

	//Game Loop
	while (!gameOver) {

		//for smooth firing
		updateScoreNdbullet(alienx, alieny, bullethit, rows, cols, score);

		for (int i = 0; i < numStars; i++) {
			clearStar(starX[i], starY[i], bgC);

			//update star position
			starX[i] += 1;
			if (starX[i] > screenWidth) {
				starX[i] = (i * 100) % screenWidth; //reset position
			}

			drawStar(starX[i], starY[i], 255, 255, 255);
		}

		if (levelOver(bullethit, rows, cols)) {
			level++;
			bullet_speed += 12;
			if (level > 3) {
				system("cls");
				drawText(40, 300, 350, 0, 255, 255, "CONGRATULATIONS! YOU WON!");
				drawText(20, 450, 450, 255, 255, 0, "Your final score: ", true, score);
				Sleep(1500);
				break;  // Exit the game loop
			}
			else {
				displayNxtLvl(level);
				initializeGame(alienx, alieny, bullethit, rows, cols, spaceshipX, spaceshipY, lives, score, level, gameOver, false);
			}
		}
		double a_speed = 1.0 + (level - 1) * 0.0005;  // Base speed increases with level

		//escape key/pause logic
		int key;
		if (isKeyPressed(key)) {
			if (key == 7) {
				isPaused = true;
				displayPauseMenu(selectedIndex);
				while (isPaused) {
					handlePauseMenuInput(selectedIndex, isPaused, alienx, alieny, bullethit, rows, cols,
						spaceshipX, spaceshipY, lives, score, level, gameOver, a_speed);
				}
			}
		}
		//if esc key is not pressed
		if (!isPaused) {
			//move aliens and check for game over if the aliens are at the left edge
			gameOver = moveAliens(alienx, alieny, bullethit, rows, cols, a_speed);

			//spaceship controls
			int whichKey;
			if (isKeyPressed(whichKey)) {
				//move spaceship left with bounds
				if (whichKey == 1 && spaceshipX > 20) {
					removeShip(spaceshipX, spaceshipY, bgC);
					spaceshipX -= spaceshipSpeed;
					drawShip(spaceshipX, spaceshipY, 0, 255, 255);
				}
				//move spaceship up with bounds
				else if (whichKey == 2 && spaceshipY > 50) {
					removeShip(spaceshipX, spaceshipY, bgC);
					spaceshipY -= spaceshipSpeed;
					drawShip(spaceshipX, spaceshipY, 0, 255, 255);
				}
				//move spaceship right with bounds
				else if (whichKey == 3 && spaceshipX < 1360) {
					removeShip(spaceshipX, spaceshipY, bgC);
					spaceshipX += spaceshipSpeed;
					drawShip(spaceshipX, spaceshipY, 0, 255, 255);
				}
				//move spaceship down with bounds
				else if (whichKey == 4 && spaceshipY < 850) {
					removeShip(spaceshipX, spaceshipY, bgC);
					spaceshipY += spaceshipSpeed;
					drawShip(spaceshipX, spaceshipY, 0, 255, 255);
				}
				//fire with spacebar
				if (whichKey == 8) {
					int bulletX, bulletY;
					bulletY = spaceshipY;
					fireBullet(spaceshipX, spaceshipY, alienx, alieny, bullethit, rows, cols, score);
				}
			}

			//handle collisions between spaceship and aliens
			spaceshiphit(spaceshipX, spaceshipY, alienx, alieny, lives, bullethit, rows, cols);

			//manage score,bullet and aliens when spacebar is hit everytime until game is finished
			updateScoreNdbullet(alienx, alieny, bullethit, rows, cols, score);

			//wont allow all the bullets to be fired at once until the required time
			if (bulletCooldown > 0) {
				bulletCooldown--;
			}

			//check lives are zero
			if (lives <= 0) {
				gameOver = true;
			}
		}
	}
	// Game over screen
	if (lives <= 0 || gameOver == true) {
		system("cls");
		drawText(40, 500, 350, 255, 0, 0, "GAME OVER!");
		writeScore(score);
		remove("saved_game.txt");
		drawText(20, 500, 450, 255, 255, 0, "Your score: ", true, score);
		drawSadAlien(450, 400, 255, 0, 0);
		drawSadAlien(930, 400, 255, 0, 0);
		Sleep(1500);
	}
}

int gameNdMenu() {
	bool check_game = checkSavedGame();
	bool gameOver = false;
	int numOptions = 4;
	if (check_game) {
		numOptions = 5;
	}
	int menuResult = gameMenu(numOptions);
	if (menuResult == 0) {
		is_gamesave = false;
		gameLoop();
	}
	else if (menuResult == 1) {
		int alienx[6][10], alieny[6][10], bullethit[6][10], rows = 6, cols = 10;
		int spaceshipX, spaceshipY, score, lives, level;
		if (loadGameState(alienx, alieny, bullethit, rows, cols, spaceshipX, spaceshipY, score, lives, level)) {
			is_gamesave = true;
			gameLoop();
		}
		else {
			drawText(20, 330, 350, 255, 0, 0, "No saved game found!", 0);
			Sleep(2000);
		}
	}
	else if (menuResult == 2) {
		return 0;
	}
	return 0;
}

int main() {
	enableFullScreen();
	gameNdMenu();
	return 0;
}
