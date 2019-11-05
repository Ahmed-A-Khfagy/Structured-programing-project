#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>
using namespace std;
using namespace sf;
#define Size 9
#define Window_size 693
#pragma warning(disable : 4996)

struct boared {
	int candy;
	bool jelly;
	Sprite  spriteshapes;
	Texture textureshapes;
	Sprite  jellysprite;
	Texture jellytexture;
};

struct player {
	string name; int score, lives;
}
players[3];

void getTm(int& year, int& month, int& day, int& hour, int& mins, int& secs, int& weekDay) {
	time_t tt;
	time(&tt);
	tm TM = *localtime(&tt);

	year = TM.tm_year + 1900;
	month = TM.tm_mon;
	day = TM.tm_mday;
	hour = TM.tm_hour;
	mins = TM.tm_min;
	secs = TM.tm_sec;
	weekDay = TM.tm_wday;
}

void check(boared Board[Size][Size], int& score, int& moves, bool& checker) {
	for (int x = 0; x < Size; x++) {
		bool cont = false;
		for (int y = 0; y < Size; y++) {
			if (y + 2 < Size) {
				if (Board[x][y].candy == Board[x][y + 1].candy && Board[x][y + 1].candy == Board[x][y + 2].candy) {
					checker = true;
					for (int z = x; z < Size; z++) {
						if (y + 3 < Size) {
							for (int d = y + 3; d < Size; d++) {
								if (d < Size) {
									if (Board[z][d].candy == Board[x][y].candy) {
										Board[z][d].candy = 11;
										Board[z][d].jelly = 0;
										score += 15;
									}
									else {
										cont = true;
										break;
									}
								}
								else break;
							}
						}
						if (cont) break;
					}
					// lw 3 horizontal
					Board[x][y].jelly = 0; Board[x][y + 1].jelly = 0; Board[x][y + 2].jelly = 0;
					Board[x][y].candy = 11; Board[x][y + 1].candy = 11; Board[x][y + 2].candy = 11;
					score += 30;
				}
			}
			if (cont) break;
		}
		if (cont) break;
	}

	for (int x = 0; x < Size - 2; x++) {
		bool khaf5aj = 0;
		for (int y = 0; y < Size; y++) {
			if (Board[x][y].candy == Board[x + 1][y].candy && Board[x + 1][y].candy == Board[x + 2][y].candy) {
				checker = true;
				if (x + 3 < Size) {
					for (int d = x + 3; d <= Size; d++) {
						if (d < Size) {
							if (Board[d][y].candy == Board[x][y].candy) {
								Board[d][y].candy = 12;
								Board[d][y].jelly = 0;
								score += 15;
							}
							else {
								khaf5aj = 1;
								break;
							}
						}
					}

				}

				// lw 3 vertical
				Board[x][y].jelly = 0; Board[x + 1][y].jelly = 0; Board[x + 2][y].jelly = 0;
				Board[x][y].candy = 12; Board[x + 1][y].candy = 12; Board[x + 2][y].candy = 12;
				score += 30;
				if (khaf5aj == 1)
					break;
			}
		}
	}
}

void shifting(boared Board[Size][Size]) {
	srand(time(NULL));
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {

			for (int x = 0; x < Size; x++) {
				for (int y = 0; y < Size; y++) {
					if (Board[x][y].candy == 55) {
						for (int i = x; i >= 0; i--) {
							if (i == 0) {
								Board[i][y].candy = 1 + rand() % 5;
							}
							else Board[i][y].candy = Board[i - 1][y].candy;
						}
					}
				}
			}
		}
	}
	for (int x = 0; x < Size; x++) {
		for (int y = 0; y < Size; y++) {
			if (Board[x][y].candy == 11) {
				for (int i = x; i >= 0; i--) {
					if (i == 0) {
						Board[i][y].candy = 1 + rand() % 5;
					}
					else Board[i][y].candy = Board[i - 1][y].candy;
				}
			}
		}
	}
	for (int x = 0; x < Size; x++) {
		for (int y = 0; y < Size; y++) {
			if (Board[x][y].candy == 12 && x != 0) {
				if (Board[x][y].candy == 12) {
					for (int h = x; h >= 0; h--) {
						if (h != 0) {
							Board[h][y].candy = Board[h - 1][y].candy;
						}
						else Board[h][y].candy = 1 + rand() % 5;
					}
					//x += 1;
				}
			}
			else
				while (Board[x][y].candy == 12) {
					Board[x][y].candy = 1 + rand() % 5;
				}
		}
	}
}

void special(boared Board[Size][Size], int& score, bool& checker) {
	//Special T
					//T up

	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (j >= 1 && j <= Size - 2 && i <= Size - 3) {
				if (Board[i][j].candy == Board[i][j - 1].candy && Board[i][j].candy == Board[i][j + 1].candy && Board[i][j].candy == Board[i + 1][j].candy && Board[i][j].candy == Board[i + 2][j].candy) {
					Board[i][j].candy = Board[i][j - 1].candy = Board[i][j + 1].candy = Board[i + 1][j].candy = Board[i + 2][j].candy = 55;
					Board[i][j].jelly = Board[i][j - 1].jelly = Board[i][j + 1].jelly = Board[i + 1][j].jelly = Board[i + 2][j].jelly = 0;
					checker = true;
					score += 50;
				}
			}
		}
	}
	// T Down
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (j >= 1 && j <= Size - 2 && i >= 2) {
				if (Board[i][j].candy == Board[i][j - 1].candy && Board[i][j].candy == Board[i][j + 1].candy && Board[i][j].candy == Board[i - 1][j].candy && Board[i][j].candy == Board[i - 2][j].candy) {
					Board[i][j].candy = Board[i][j - 1].candy = Board[i][j + 1].candy = Board[i - 1][j].candy = Board[i - 2][j].candy = 55;
					Board[i][j].jelly = Board[i][j - 1].jelly = Board[i][j + 1].jelly = Board[i - 1][j].jelly = Board[i - 2][j].jelly = 0;
					checker = true;
					score += 50;
				}
			}
		}
	}

	// T Right
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (i >= 1 && i <= Size - 2 && j >= 2) {
				if (Board[i][j].candy == Board[i - 1][j].candy && Board[i][j].candy == Board[i + 1][j].candy && Board[i][j].candy == Board[i][j + 1].candy && Board[i][j].candy
					== Board[i][j + 2].candy) {
					Board[i][j].candy = Board[i + 1][j].candy = Board[i - 1][j].candy = Board[i][j + 1].candy = Board[i][j + 2].candy = 55;
					Board[i][j].jelly = Board[i + 1][j].jelly = Board[i - 1][j].jelly = Board[i][j + 1].jelly = Board[i][j + 2].jelly = 0;
					checker = true;
					score += 55;
				}
			}
		}
	}

	// T LEft
/*for (int i = 0;i < size;i++) {
	for (int j = 0;j < size;j++) {
	if (i >= 1 && i <= size - 2 && j <= size-3)
		if (arr[i][j].candy == arr[i - 1][j].candy && arr[i][j].candy == arr[i + 1][j].candy && arr[i][j].candy == arr[i][j - 1].candy && arr[i][j].candy == arr[i][j - 2].candy) {
			arr[i][j].candy = arr[i - 1][j].candy = arr[i + 1][j].candy = arr[i][j - 1].candy = arr[i][j - 2].candy = 55;
			arr[i][j].jelly = arr[i - 1][j].jelly = arr[i + 1][j].jelly = arr[i][j - 1].jelly = arr[i][j - 2].jelly = 0;
			checker = true;
			score += 55;
		}
	}
}*/
// Special L
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (Board[i][j].candy == Board[i][j + 1].candy && Board[i][j].candy == Board[i][j + 2].candy && Board[i][j].candy
				== Board[i + 1][j].candy && Board[i][j].candy == Board[i + 2][j].candy) {
				Board[i][j].candy = Board[i][j + 1].candy = Board[i][j + 2].candy = Board[i + 1][j].candy = Board[i + 2][j].candy = 55;
				Board[i][j].jelly = Board[i][j + 1].jelly = Board[i][j + 2].jelly = Board[i + 1][j].jelly = Board[i + 2][j].jelly = 0;
				checker = true;
				score += 50;
			}
		}
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (i <= Size - 3 && j < Size - 3) {
				if (Board[i][j].candy == Board[i][j - 1].candy && Board[i][j].candy == Board[i][j - 2].candy && Board[i][j].candy == Board[i + 1][j].candy && Board[i][j].candy == Board[i + 2][j].candy) {
					Board[i][j].candy = 55; Board[i][j - 1].candy = 55; Board[i][j - 2].candy = 55; Board[i + 1][j].candy = 55; Board[i + 2][j].candy = 55;
					Board[i][j].jelly = 0; Board[i][j - 1].jelly = 0; Board[i][j - 2].jelly = 0; Board[i + 1][j].jelly = 0; Board[i + 2][j].jelly = 0;
					checker = true;
					score += 50;
				}
			}
		}
	}

	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (Board[i][j].candy == Board[i][j + 1].candy && Board[i][j].candy == Board[i][j + 2].candy && Board[i][j].candy == Board[i - 1][j].candy && Board[i][j].candy == Board[i - 2][j].candy) {
				Board[i][j].candy = Board[i][j + 1].candy = Board[i][j + 2].candy = Board[i - 1][j].candy = Board[i - 2][j].candy = 55;
				Board[i][j].jelly = Board[i][j + 1].jelly = Board[i][j + 2].jelly = Board[i - 1][j].jelly = Board[i - 2][j].jelly = 0;
				checker = true;
				score += 50;
			}
		}
	}

	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (Board[i][j].candy == Board[i][j - 1].candy && Board[i][j].candy == Board[i][j - 2].candy && Board[i][j].candy == Board[i - 1][j].candy && Board[i][j].candy == Board[i - 2][j].candy) {
				Board[i][j].candy = 55; Board[i][j - 1].candy = 55; Board[i][j - 2].candy = 55; Board[i - 1][j].candy = 55; Board[i - 2][j].candy = 55;
				Board[i][j].jelly = Board[i][j - 1].jelly = Board[i][j - 2].jelly = Board[i - 1][j].jelly = Board[i - 2][j].jelly = 0;
				checker = true;
				score += 50;
			}
		}
	}
}

void swap(boared Bored[Size][Size], int& i1, int& j1, int& i2, int& j2) {
	boared  temp;
	if ((i1 == i2 && j1 == j2 + 1) || (i1 == i2 && j1 == j2 - 1) || (j1 == j2 && i1 == i2 - 1) || (j1 == j2 && i1 == i2 + 1)) {
		temp = Bored[i1 - 1][j1 - 1];
		Bored[i1 - 1][j1 - 1] = Bored[i2 - 1][j2 - 1];
		Bored[i2 - 1][j2 - 1] = temp;
	}
	else std::cout << "wrong coordinates" << endl << endl;
}

void Positioning(boared Board[Size][Size]) {
	// Tanzeem positions al candies initially
	int x1 = 29, y1 = 25;
	for (int i = 0; i < Size; i++) {
		x1 = 30;
		for (int j = 0; j < Size; j++) {
			Board[i][j].spriteshapes.setPosition(x1, y1);
			x1 = x1 + 72;
		}
		y1 = y1 + 66;;
	}
}

void PositioningJelly(boared Board[Size][Size]) {
	// Tanzeem positions al candies initially
	int x1 = 29, y1 = 25;
	for (int i = 0; i < Size; i++) {
		x1 = 30;
		for (int j = 0; j < Size; j++) {
			if (Board[i][j].jelly)
				Board[i][j].jellysprite.setPosition(x1, y1);
			x1 = x1 + 72;
		}
		y1 = y1 + 66;;
	}
}

void Shapping(boared Board[Size][Size], Texture & s1, Texture & s2, Texture & s3, Texture & s4, Texture & s5) {
	// Tanzeem al a4kal
	for (int i = 0; i < Size; i++) {

		for (int j = 0; j < Size; j++) {
			if (Board[i][j].candy == 1) {
				Board[i][j].spriteshapes.setTexture(s1);

			}
			else if (Board[i][j].candy == 2) {
				Board[i][j].spriteshapes.setTexture(s2);

			}
			else if (Board[i][j].candy == 3) {
				Board[i][j].spriteshapes.setTexture(s3);

			}
			else if (Board[i][j].candy == 4) {
				Board[i][j].spriteshapes.setTexture(s4);

			}
			else if (Board[i][j].candy == 5) {
				Board[i][j].spriteshapes.setTexture(s5);

			}
		}
	}
}

void ShappingJelly(boared Bored[Size][Size], Texture & s1, Texture & s2, Texture & s3, Texture & s4, Texture & s5, Texture & jelly) {
	// Tanzeem al a4kal
	for (int i = 0; i < Size; i++) {

		for (int j = 0; j < Size; j++) {
			if (Bored[i][j].candy == 1) {
				Bored[i][j].spriteshapes.setTexture(s1);
				if (Bored[i][j].jelly == 1)
					Bored[i][j].jellysprite.setTexture(jelly);
			}
			else if (Bored[i][j].candy == 2) {
				Bored[i][j].spriteshapes.setTexture(s2);
				if (Bored[i][j].jelly == 1)
					Bored[i][j].jellysprite.setTexture(jelly);
			}
			else if (Bored[i][j].candy == 3) {
				Bored[i][j].spriteshapes.setTexture(s3);
				if (Bored[i][j].jelly == 1)
					Bored[i][j].jellysprite.setTexture(jelly);
			}
			else if (Bored[i][j].candy == 4) {
				Bored[i][j].spriteshapes.setTexture(s4);
				if (Bored[i][j].jelly == 1)
					Bored[i][j].jellysprite.setTexture(jelly);
			}
			else if (Bored[i][j].candy == 5) {
				Bored[i][j].spriteshapes.setTexture(s5);
				if (Bored[i][j].jelly == 1)
					Bored[i][j].jellysprite.setTexture(jelly);
			}
		}
	}
}

void boardgeneratorGUI(boared Board[Size][Size]) {
	srand(time(NULL));
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			Board[i][j].candy = 1 + rand() % 5;
		}
	}
}

void boaredgeneratorJellyGUI(boared Bored[Size][Size]) {
	srand(time(NULL));
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			Bored[i][j].candy = 1 + rand() % 5;
		}
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			Bored[i][j].jelly = 1;
		}
	}
}

void getHint(boared Board[Size][Size], vector <int> v[Size]) {
	boared Backup[Size][Size];
	for (int i = 0; i < Size; ++i) {
		for (int j = 0; j < Size; ++j) {
			Backup[i][j].candy = Board[i][j].candy;
		}
	}
	for (int i = 0; i < Size; ++i) {
		for (int j = 0; j < Size - 1; ++j) {
			bool cheker = false;
			int score = 0, moves = 0;
			swap(Board[i][j].candy, Board[i][j + 1].candy);
			check(Board, score, moves, cheker);
			if (cheker)
				v[i].push_back(j);
			for (int ii = 0; ii < Size; ++ii) {
				for (int jj = 0; jj < Size; ++jj) {
					Board[ii][jj].candy = Backup[ii][jj].candy;
				}
			}
		}
	}
	for (int j = 0; j < Size; ++j) {
		for (int i = 0; i < Size - 1; ++i) {
			bool cheker = false;
			int score = 0, moves = 0;
			swap(Board[i][j].candy, Board[i][j + 1].candy);
			check(Board, score, moves, cheker);
			if (cheker)
				v[i].push_back(j);
			for (int ii = 0; ii < Size; ++ii) {
				for (int jj = 0; jj < Size; ++jj) {
					Board[ii][jj].candy = Backup[ii][jj].candy;
				}
			}
		}
	}
}

void letsPlay() {
	bool checker = false;
	int score = 0, moves = 15;
	player curPlayer;
	player defaultPlayer = { "NewPlayer" ,0 ,5 };
	//initially start
	Music _star1;
	_star1.openFromFile("SFX - 1 Star.ogg");
	Music _star2;
	_star2.openFromFile("SFX - 2 Star.ogg");
	Music _star3;
	_star3.openFromFile("SFX - 3 Star.ogg");
	Music _delecious;
	_delecious.openFromFile("SFX - Delicious.ogg");
	Music _devine;
	_devine.openFromFile("SFX - Divine.ogg");
	Music _sweet;
	_sweet.openFromFile("SFX - Sweet.ogg");
	Music _tasty;
	_tasty.openFromFile("SFX - Tasty.ogg");
	Music music;
	music.openFromFile("AFD.ogg");
	Texture ph;
	Sprite phs;
	ph.loadFromFile("menu.png");
	phs.setTexture(ph);
	Texture cr;
	Sprite crs;
	cr.loadFromFile("credits.png");
	crs.setTexture(cr);
	Texture sh1;
	Texture sh2;
	Texture sh3;
	Texture sh4;
	Texture sh5;
	sh1.loadFromFile("1.png");
	sh2.loadFromFile("2.png");
	sh3.loadFromFile("3.png");
	sh4.loadFromFile("4.png");
	sh5.loadFromFile("5.png");
	Texture jelly;
	jelly.loadFromFile("jelly.png");
	boared Board[Size][Size];
	vector <int> hints[Size];
	boardgeneratorGUI(Board);
	boaredgeneratorJellyGUI(Board);
	do {
		checker = false;
		special(Board, score, checker);
		check(Board, score, moves, checker);
		shifting(Board);
		Shapping(Board, sh1, sh2, sh3, sh4, sh5);
		ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
	} while (checker);

	Shapping(Board, sh1, sh2, sh3, sh4, sh5);
	Positioning(Board);
	getHint(Board, hints);
	for (int i = 0; i < Size; ++i) {
		for (int j = 0; j < Size; ++j)
			std::cout << Board[i][j].candy << ' ';
		std::cout << "\n";
	}

	//Fonts & Texts
	Font font;
	if (!font.loadFromFile("Brushcrazy DEMO.otf")) {
		std::cout << "ERROR LOADING FONT" << endl;
	}

	Font numbers;
	numbers.loadFromFile("ariali.ttf");

	Text totalPoints;
	totalPoints.setFont(font);
	totalPoints.setString("Total Points");
	totalPoints.setCharacterSize(35);
	totalPoints.setPosition(700, 18);
	totalPoints.setFillColor(Color::Red);
	totalPoints.setOutlineColor(Color::Black);
	totalPoints.setOutlineThickness(5);

	Text movesLeft;
	movesLeft.setFont(font);
	movesLeft.setString("Moves Left!!");
	movesLeft.setCharacterSize(35);
	movesLeft.setPosition(700, 202);
	movesLeft.setFillColor(Color::Red);
	movesLeft.setOutlineColor(Color::Black);
	movesLeft.setOutlineThickness(5);

	RenderWindow window;
	window.create(VideoMode(Window_size + 250, Window_size - 65), "Candy Crush Demo");
	RectangleShape rectangle(Vector2f(650, 593));
	rectangle.move(Vector2f(18, 18));
	Texture texture;
	if (!texture.loadFromFile("7F9WvB.jpg")) {
		std::cout << "Load Failed" << endl;
	}
	Sprite sprite;
	sprite.setTexture(texture);
	rectangle.setFillColor(Color(255, 255, 255, 200));

	Texture playerMenuPicLoad;
	playerMenuPicLoad.loadFromFile("playersLoad.png");

	Sprite playerMenuLoad;
	playerMenuLoad.setTexture(playerMenuPicLoad);

	Texture playerMenuPicNew;
	playerMenuPicNew.loadFromFile("playersNew.png");

	Sprite playerMenuNew;
	playerMenuNew.setTexture(playerMenuPicNew);

	Texture hintsPic;
	hintsPic.loadFromFile("hints.png");

	Sprite hintsSprite;
	hintsSprite.setTexture(hintsPic);

	Texture loadOrNewPic;
	loadOrNewPic.loadFromFile("loadOrNew.png");

	Sprite loadOrNewS;
	loadOrNewS.setTexture(loadOrNewPic);

	Texture DeleteMenuPic;
	DeleteMenuPic.loadFromFile("deleteMenu.png");

	Sprite DeleteMenu;
	DeleteMenu.setTexture(DeleteMenuPic);

	Texture confirmMakeNewPic;
	confirmMakeNewPic.loadFromFile("newButHere.png");

	Sprite confirmMakeNews;
	confirmMakeNews.setTexture(confirmMakeNewPic);

	Texture makeNewPic;
	makeNewPic.loadFromFile("makeNew.png");

	Sprite makeNews;
	makeNews.setTexture(makeNewPic);

	Texture BasicGameOrJellyPic;
	BasicGameOrJellyPic.loadFromFile("basicOrJelly.png");

	Sprite BasicGameOrJelly;
	BasicGameOrJelly.setTexture(BasicGameOrJellyPic);

	Texture Star1Pic;
	Star1Pic.loadFromFile("1star.png");

	Sprite Star1Pics;
	Star1Pics.setTexture(Star1Pic);


	Texture Star2Pic;
	Star2Pic.loadFromFile("2star.png");

	Sprite Star2Pics;
	Star2Pics.setTexture(Star2Pic);


	Texture Star3Pic;
	Star3Pic.loadFromFile("3star.png");

	Sprite Star3Pics;
	Star3Pics.setTexture(Star3Pic);


	Texture loosePic;
	loosePic.loadFromFile("loose.png");

	Sprite loosePics;
	loosePics.setTexture(loosePic);

	int x4, y4, click = 0; int i1, j1, i2, j2; bool lolo = false;
	Vector2i vec;
	bool onetime = true;
	bool isInMenu = false, isInBasicGame = false, isIncredits = false, toQuit = false, isInHints = false, leaderBoard = false;
	bool loadOrNew = true, inChoosePlayerMenuLoad = false, inChoosePlayerMenuNew = false, toDelete = false;
	bool makeNew = false, confirmMakingNew = false, basicOrJelly = false, isInJellyGame = false;
	bool isBasic = false, isJelly = false, heGot1 = false, heGot2 = false, heGot3 = false, heDidntGetAnything = false;
	bool oneIsRegenerating = false, twoIsRegenerating = false, threeIsRegenerating = false, isInit = false;
	bool start1isSet = false, start2isSet = false, start3isSet = false, itwasDec = false, IHaveNoLives = false;
	bool toPause = false, musicOn = true, soundOn = false, makeTheJellyBeGeneratedInTheGameOnce = false;
	bool star1WasPlayed = false, star2WasPlayed = false, star3WasPlayed = false, heHasSoundOn = true;
	int theNewOne, curPlayerIdx;

	Texture haveNoLivesPic;
	haveNoLivesPic.loadFromFile("IHaveNoLives.png");

	Sprite haveNoLives;
	haveNoLives.setTexture(haveNoLivesPic);

	music.play();
	music.setLoop(true);

	Font NamesFont;
	NamesFont.loadFromFile("jsd__3__.ttf");

	String playerInput = "";
	Text playerText;

	Texture pauseMenuPic;
	pauseMenuPic.loadFromFile("pause.png");

	Sprite pauseMenu;
	pauseMenu.setTexture(pauseMenuPic);

	playerText.setFont(NamesFont);
	playerText.setCharacterSize(40);
	playerText.setPosition(372, 272);
	playerText.setFillColor(Color::Black);

	ifstream dataOfPlayer1("player1.txt");
	ifstream dataOfPlayer2("player2.txt");
	ifstream dataOfPlayer3("player3.txt");

	dataOfPlayer1 >> players[0].name >> players[0].score >> players[0].lives;

	dataOfPlayer2 >> players[1].name >> players[1].score >> players[1].lives;

	dataOfPlayer3 >> players[2].name >> players[2].score >> players[2].lives;

	dataOfPlayer1.close();
	dataOfPlayer2.close();
	dataOfPlayer3.close();

	while (window.isOpen()) {

		Event event;

		if (players[0].lives < 5) {
			int year, month, day, hour, mins, secs, weekDay;
			getTm(year, month, day, hour, mins, secs, weekDay);
			ifstream iFile("player1LooseTime.txt");
			int lyear, lmonth, lday, lhour, lmins, lsecs, lweekDay;
			iFile >> lyear >> lmonth >> lday >> lhour >> lmins >> lsecs >> lweekDay;
			if (lyear != year) {
				ofstream oFile("player1.txt");
				oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
				oFile.close();
			}
			if (lmonth != month) {
				ofstream oFile("player1.txt");
				oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
				oFile.close();
			}
			if (lday != day) {
				ofstream oFile("player1.txt");
				oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
				oFile.close();
			}
			if (lhour != hour) {
				ofstream oFile("player1.txt");
				oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
				oFile.close();
			}
			if (lweekDay != weekDay) {
				ofstream oFile("player1.txt");
				oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
				oFile.close();
			}
			if (lmins != mins) {
				ofstream oFile("player1.txt");
				if (abs(mins - lmins) >= 5) {
					oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
				}
				else if (abs(mins - lmins) == 4) {
					players[0].lives += 4;
					if (players[0].lives >= 5)
						oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
					else {
						oFile << players[0].name << ' ' << players[0].score << ' ' << players[0].lives;
					}
				}
				else if (abs(mins - lmins) == 3) {
					players[0].lives += 3;
					if (players[0].lives >= 5)
						oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
					else {
						oFile << players[0].name << ' ' << players[0].score << ' ' << players[0].lives;
					}
				}
				else if (abs(mins - lmins) == 2) {
					players[0].lives += 2;
					if (players[0].lives >= 5)
						oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
					else {
						oFile << players[0].name << ' ' << players[0].score << ' ' << players[0].lives;
					}
				}
				else if (abs(mins - lmins) == 1) {
					players[0].lives += 1;
					if (players[0].lives >= 5)
						oFile << players[0].name << ' ' << players[0].score << ' ' << 5;
					else {
						oFile << players[0].name << ' ' << players[0].score << ' ' << players[0].lives;
					}
				}
				else {
					oFile << players[0].name << ' ' << players[0].score << ' ' << players[0].lives;
				}
				ofstream OFile("player1LooseTime.txt");
				OFile << year << ' ' << month << ' ' << day << ' ' << hour << ' ' << mins << ' ' << secs << ' ' << weekDay;
				OFile.close();
				oFile.close();
			}
		}

		if (players[1].lives < 5) {
			int year, month, day, hour, mins, secs, weekDay;
			getTm(year, month, day, hour, mins, secs, weekDay);
			ifstream iFile("player2LooseTime.txt");
			int lyear, lmonth, lday, lhour, lmins, lsecs, lweekDay;
			iFile >> lyear >> lmonth >> lday >> lhour >> lmins >> lsecs >> lweekDay;
			if (lyear != year) {
				ofstream oFile("player2.txt");
				oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
				oFile.close();
			}
			if (lmonth != month) {
				ofstream oFile("player2.txt");
				oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
				oFile.close();
			}
			if (lday != day) {
				ofstream oFile("player2.txt");
				oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
				oFile.close();
			}
			if (lhour != hour) {
				ofstream oFile("player2.txt");
				oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
				oFile.close();
			}
			if (lweekDay != weekDay) {
				ofstream oFile("player2.txt");
				oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
				oFile.close();
			}
			if (lmins != mins) {
				ofstream oFile("player2.txt");
				if (abs(mins - lmins) >= 5) {
					oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
				}
				else if (abs(mins - lmins) == 4) {
					players[1].lives += 4;
					if (players[1].lives >= 5)
						oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
					else {
						oFile << players[1].name << ' ' << players[1].score << ' ' << players[1].lives;
					}
				}
				else if (abs(mins - lmins) == 3) {
					players[1].lives += 3;
					if (players[1].lives >= 5)
						oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
					else {
						oFile << players[1].name << ' ' << players[1].score << ' ' << players[1].lives;
					}
				}
				else if (abs(mins - lmins) == 2) {
					players[1].lives += 2;
					if (players[1].lives >= 5)
						oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
					else {
						oFile << players[1].name << ' ' << players[1].score << ' ' << players[1].lives;
					}
				}
				else if (abs(mins - lmins) == 1) {
					players[1].lives += 1;
					if (players[1].lives >= 5)
						oFile << players[1].name << ' ' << players[1].score << ' ' << 5;
					else {
						oFile << players[1].name << ' ' << players[1].score << ' ' << players[1].lives;
					}
				}
				else {
					oFile << players[1].name << ' ' << players[1].score << ' ' << players[1].lives;
				}
				ofstream OFile("player2LooseTime.txt");
				OFile << year << ' ' << month << ' ' << day << ' ' << hour << ' ' << mins << ' ' << secs << ' ' << weekDay;
				OFile.close();
				oFile.close();
			}
		}

		if (players[2].lives < 5) {
			int year, month, day, hour, mins, secs, weekDay;
			getTm(year, month, day, hour, mins, secs, weekDay);
			ifstream iFile("player3LooseTime.txt");
			int lyear, lmonth, lday, lhour, lmins, lsecs, lweekDay;
			iFile >> lyear >> lmonth >> lday >> lhour >> lmins >> lsecs >> lweekDay;
			if (lyear != year) {
				ofstream oFile("player3.txt");
				oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
				oFile.close();
			}
			if (lmonth != month) {
				ofstream oFile("player3.txt");
				oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
				oFile.close();
			}
			if (lday != day) {
				ofstream oFile("player3.txt");
				oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
				oFile.close();
			}
			if (lhour != hour) {
				ofstream oFile("player3.txt");
				oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
				oFile.close();
			}
			if (lweekDay != weekDay) {
				ofstream oFile("player3.txt");
				oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
				oFile.close();
			}
			if (lmins != mins) {
				ofstream oFile("player3.txt");
				if (abs(mins - lmins) >= 5 && lsecs <= secs) {
					oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
				}
				else if (abs(mins - lmins) == 4) {
					players[1].lives += 4;
					if (players[1].lives >= 5)
						oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
					else {
						oFile << players[2].name << ' ' << players[2].score << ' ' << players[2].lives;
					}
				}
				else if (abs(mins - lmins) == 3) {
					players[1].lives += 3;
					if (players[1].lives >= 5)
						oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
					else {
						oFile << players[2].name << ' ' << players[2].score << ' ' << players[2].lives;
					}
				}
				else if (abs(mins - lmins) == 2) {
					players[1].lives += 2;
					if (players[1].lives >= 5)
						oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
					else {
						oFile << players[2].name << ' ' << players[2].score << ' ' << players[2].lives;
					}
				}
				else if (abs(mins - lmins) == 1) {
					players[1].lives += 1;
					if (players[1].lives >= 5)
						oFile << players[2].name << ' ' << players[2].score << ' ' << 5;
					else {
						oFile << players[2].name << ' ' << players[2].score << ' ' << players[2].lives;
					}
				}
				else {
					oFile << players[2].name << ' ' << players[2].score << ' ' << players[2].lives;
				}
				ofstream OFile("player3LooseTime.txt");
				OFile << year << ' ' << month << ' ' << day << ' ' << hour << ' ' << mins << ' ' << secs << ' ' << weekDay;
				OFile.close();
				oFile.close();
			}
		}

		if (loadOrNew) {
			window.clear();
			window.draw(loadOrNewS);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 285 && x4 < 657) {
							if (y4 > 99 && y4 < 260) {
								loadOrNew = false, inChoosePlayerMenuLoad = true;
							}
							else if (y4 > 344 && y4 < 506) {
								loadOrNew = false, inChoosePlayerMenuNew = true;
							}
						}
						else if (x4 > 36 && x4 < 147 && y4 > 34 && y4 < 165) {
							loadOrNew = false, toQuit = true;
						}
					}
				}
			}
			window.display();
		}
		else if (toDelete) {
			window.clear();
			window.draw(DeleteMenu);
			Font NamesFont;
			NamesFont.loadFromFile("jsd__3__.ttf");
			Text name1;
			name1.setFont(NamesFont);
			name1.setString(players[0].name);
			name1.setCharacterSize(40);
			name1.setPosition(427, 81);
			name1.setFillColor(Color::Black);
			window.draw(name1);
			Text name2;
			name2.setFont(NamesFont);
			name2.setString(players[1].name);
			name2.setCharacterSize(40);
			name2.setPosition(427, 289);
			name2.setFillColor(Color::Black);
			window.draw(name2);
			Text name3;
			name3.setFont(NamesFont);
			name3.setString(players[2].name);
			name3.setCharacterSize(40);
			name3.setPosition(427, 481);
			name3.setFillColor(Color::Black);
			window.draw(name3);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 232 && x4 < 743) {
							if (y4 > 25 && y4 < 191) {
								players[0] = defaultPlayer;
								ofstream toScreen1("player1.txt");
								toScreen1 << players[0].name << ' ' << players[0].score << ' ' << players[0].lives;
								toDelete = false;
							}
							else if (y4 > 229 && y4 < 395) {
								players[1] = defaultPlayer;
								ofstream toScreen1("player2.txt");
								toScreen1 << players[1].name << ' ' << players[1].score << ' ' << players[1].lives;
								toDelete = false;
							}
							else if (y4 > 429 && y4 < 595) {
								players[2] = defaultPlayer;
								ofstream toScreen1("player3.txt");
								toScreen1 << players[2].name << ' ' << players[2].score << ' ' << players[2].lives;
								toDelete = false;
							}
						}
						else if (x4 > 788 && x4 < 919 && y4 > 70 && y4 < 208) {
							toDelete = false;
						}
					}
				}
			}
			window.display();
		}
		else if (inChoosePlayerMenuNew) {
			window.clear();
			window.draw(playerMenuNew);
			playerInput = "";
			ifstream toScreen1("player1.txt");
			ifstream toScreen2("player2.txt");
			ifstream toScreen3("player3.txt");
			Text name1;
			name1.setFont(NamesFont);
			Text name2;
			name2.setFont(NamesFont);
			Text name3;
			name3.setFont(NamesFont);
			if (toScreen1.is_open()) {
				toScreen1 >> players[0].name >> players[0].score >> players[0].lives;
				name1.setString(players[0].name);
				name1.setCharacterSize(40);
				name1.setPosition(427, 81);
				name1.setFillColor(Color::Black);
				window.draw(name1);
			}
			if (toScreen2.is_open()) {
				toScreen2 >> players[1].name >> players[1].score >> players[1].lives;
				name2.setString(players[1].name);
				name2.setCharacterSize(40);
				name2.setPosition(427, 289);
				name2.setFillColor(Color::Black);
				window.draw(name2);
			}
			if (toScreen3.is_open()) {
				toScreen3 >> players[2].name >> players[2].score >> players[2].lives;
				name3.setString(players[2].name);
				name3.setCharacterSize(40);
				name3.setPosition(427, 481);
				name3.setFillColor(Color::Black);
				window.draw(name3);
			}
			toScreen1.close();
			toScreen2.close();
			toScreen3.close();
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.key.code == Keyboard::B)
					loadOrNew = true, inChoosePlayerMenuLoad = false;
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 232 && x4 < 743) {
							if (y4 > 25 && y4 < 191) {
								if (players[0].name == defaultPlayer.name) {
									theNewOne = 0;
									makeNew = true, inChoosePlayerMenuNew = false;
								}
								else {
									theNewOne = 0;
									confirmMakingNew = true, inChoosePlayerMenuNew = false;
								}
							}
							else if (y4 > 229 && y4 < 395) {
								if (players[1].name == defaultPlayer.name) {
									theNewOne = 1;
									makeNew = true, inChoosePlayerMenuNew = false;
								}
								else {
									theNewOne = 1;
									confirmMakingNew = true, inChoosePlayerMenuNew = false;
								}
							}
							else if (y4 > 429 && y4 < 595) {
								if (players[2].name == defaultPlayer.name) {
									theNewOne = 2;
									makeNew = true, inChoosePlayerMenuNew = false;
								}
								else {
									theNewOne = 2;
									confirmMakingNew = true, inChoosePlayerMenuNew = false;
								}
							}
						}
						else if (x4 > 791 && x4 < 919 && y4 > 110 && y4 < 518) {
							toDelete = true;
						}
					}
				}
			}
			window.display();
		}
		else if (confirmMakingNew) {
			window.clear();
			window.draw(confirmMakeNews);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (y4 > 371 && y4 < 482) {
							if (x4 > 221 && x4 < 455) {
								confirmMakingNew = false, makeNew = true;
							}
							else if (x4 > 520 && x4 < 754) {
								confirmMakingNew = false, loadOrNew = true;
							}
						}
					}
				}
			}
			window.display();
		}
		else if (makeNew) {
			window.clear();
			window.draw(makeNews);
			window.draw(playerText);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == sf::Event::TextEntered) {
					cout << "hi\n";
					playerInput += event.text.unicode;
					playerText.setString(playerInput);
				}
				string s = playerInput;
				cout << s << endl;
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (y4 > 385 && y4 < 496) {
							if (x4 > 220 && x4 < 453) {
								if (s.size()) {
									players[theNewOne].name = s;
									players[theNewOne].lives = 5;
									players[theNewOne].score = 0;
									if (theNewOne == 0) {
										ofstream toScreen1("player1.txt");
										toScreen1 << players[theNewOne].name << ' ' << players[theNewOne].score << ' ' << players[theNewOne].lives;
										toScreen1.close();
									}
									else if (theNewOne == 1) {
										ofstream toScreen2("player2.txt");
										toScreen2 << players[theNewOne].name << ' ' << players[theNewOne].score << ' ' << players[theNewOne].lives;
										toScreen2.close();
									}
									else {
										ofstream toScreen3("player3.txt");
										toScreen3 << players[theNewOne].name << ' ' << players[theNewOne].score << ' ' << players[theNewOne].lives;
										toScreen3.close();
									}
									playerInput = "";
									playerText.setString(playerInput);
									makeNew = false, loadOrNew = true;
								}
							}
							else if (x4 > 510 && x4 < 743) {
								playerInput = "";
								playerText.setString(playerInput);
								makeNew = false, loadOrNew = true;
							}
						}
					}
				}
			}
			window.display();
		}
		else if (inChoosePlayerMenuLoad) {
			window.clear();
			window.draw(playerMenuLoad);
			ifstream toScreen1("player1.txt");
			ifstream toScreen2("player2.txt");
			ifstream toScreen3("player3.txt");
			Font NamesFont;
			NamesFont.loadFromFile("jsd__3__.ttf");
			Text name1;
			name1.setFont(NamesFont);
			Text name2;
			name2.setFont(NamesFont);
			Text name3;
			name3.setFont(NamesFont);
			if (toScreen1.is_open()) {
				toScreen1 >> players[0].name >> players[0].score >> players[0].lives;
				name1.setString(players[0].name);
				name1.setCharacterSize(40);
				name1.setPosition(427, 81);
				name1.setFillColor(Color::Black);
				window.draw(name1);
			}
			if (toScreen2.is_open()) {
				toScreen2 >> players[1].name >> players[1].score >> players[1].lives;
				name2.setString(players[1].name);
				name2.setCharacterSize(40);
				name2.setPosition(427, 289);
				name2.setFillColor(Color::Black);
				window.draw(name2);
			}
			if (toScreen3.is_open()) {
				toScreen3 >> players[2].name >> players[2].score >> players[2].lives;
				name3.setString(players[2].name);
				name3.setCharacterSize(40);
				name3.setPosition(427, 481);
				name3.setFillColor(Color::Black);
				window.draw(name3);
			}
			toScreen1.close();
			toScreen2.close();
			toScreen3.close();
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.key.code == Keyboard::F)
					loadOrNew = true, inChoosePlayerMenuLoad = false;
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 232 && x4 < 743) {
							if (y4 > 25 && y4 < 191) {
								curPlayer = players[0];
								score = 0, moves = 15;
								curPlayerIdx = 0;
								isJelly = false, isBasic = false;
								Shapping(Board, sh1, sh2, sh3, sh4, sh5);
								Positioning(Board);
								do {
									checker = false;
									special(Board, score, checker);
									check(Board, score, moves, checker);
									shifting(Board);
									Shapping(Board, sh1, sh2, sh3, sh4, sh5);
									ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
								} while (checker);
								Shapping(Board, sh1, sh2, sh3, sh4, sh5);
								Positioning(Board);
								for (int ii = 0; ii < Size; ++ii)
									if (hints[ii].size())
										hints[ii].clear();
								getHint(Board, hints);
								score = 0, moves = 15;
								inChoosePlayerMenuLoad = false, isInMenu = true;
							}
							else if (y4 > 229 && y4 < 395) {
								curPlayer = players[1];
								score = 0, moves = 15;
								curPlayerIdx = 1;
								isJelly = false, isBasic = false;
								Shapping(Board, sh1, sh2, sh3, sh4, sh5);
								Positioning(Board);
								do {
									checker = false;
									special(Board, score, checker);
									check(Board, score, moves, checker);
									shifting(Board);
									Shapping(Board, sh1, sh2, sh3, sh4, sh5);
									ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
								} while (checker);
								Shapping(Board, sh1, sh2, sh3, sh4, sh5);
								Positioning(Board);
								for (int ii = 0; ii < Size; ++ii)
									if (hints[ii].size())
										hints[ii].clear();
								getHint(Board, hints);
								score = 0, moves = 15;
								inChoosePlayerMenuLoad = false, isInMenu = true;
							}
							else if (y4 > 429 && y4 < 595) {
								curPlayer = players[2];
								score = 0, moves = 15;
								curPlayerIdx = 2;
								isJelly = false, isBasic = false;
								Shapping(Board, sh1, sh2, sh3, sh4, sh5);
								Positioning(Board);
								do {
									checker = false;
									special(Board, score, checker);
									check(Board, score, moves, checker);
									shifting(Board);
									Shapping(Board, sh1, sh2, sh3, sh4, sh5);
									ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
								} while (checker);
								Shapping(Board, sh1, sh2, sh3, sh4, sh5);
								Positioning(Board);
								for (int ii = 0; ii < Size; ++ii)
									if (hints[ii].size())
										hints[ii].clear();
								getHint(Board, hints);
								score = 0, moves = 15;
								inChoosePlayerMenuLoad = false, isInMenu = true;
							}
						}
						else if (x4 > 791 && x4 < 919 && y4 > 110 && y4 < 518) {
							toDelete = true;
						}
					}
				}
			}
			window.display();
		}
		else if (isInMenu) {
			window.clear();
			window.draw(phs);

			Font NamesFont;
			NamesFont.loadFromFile("jsd__3__.ttf");
			Text name;
			name.setFont(NamesFont);
			name.setString(curPlayer.name);
			name.setCharacterSize(40);
			name.setPosition(401, 48);
			name.setFillColor(Color::Black);
			window.draw(name);
			Text lives;
			lives.setFont(NamesFont);
			lives.setString(to_string(curPlayer.lives));
			lives.setCharacterSize(40);
			lives.setPosition(800, 155);
			lives.setFillColor(Color::Black);
			window.draw(lives);
			Text l1, l2, l3;
			l1.setFont(NamesFont);
			l2.setFont(NamesFont);
			l3.setFont(NamesFont);
			ifstream p1("player1.txt");
			ifstream p2("player2.txt");
			ifstream p3("player3.txt");
			p1 >> players[0].name >> players[0].score >> players[0].lives;
			p2 >> players[1].name >> players[1].score >> players[1].lives;
			p3 >> players[2].name >> players[2].score >> players[2].lives;
			if (players[0].score >= players[1].score && players[0].score >= players[2].score) {
				l1.setString("1." + players[0].name);
				if (players[1].score >= players[2].score)
					l2.setString("2." + players[1].name), l3.setString("3." + players[2].name);
				else
					l2.setString("2." + players[2].name), l3.setString("3." + players[1].name);
			}
			else if (players[1].score >= players[0].score && players[1].score >= players[2].score) {
				l1.setString("1." + players[1].name);
				if (players[0].score >= players[2].score)
					l2.setString("2." + players[0].name), l3.setString("3." + players[2].name);
				else
					l2.setString("2." + players[2].name), l3.setString("3." + players[0].name);
			}
			else if (players[2].score >= players[1].score && players[2].score >= players[0].score) {
				l1.setString("1." + players[2].name);
				if (players[1].score >= players[0].score)
					l2.setString("2." + players[1].name), l3.setString("3." + players[0].name);
				else
					l2.setString("2." + players[0].name), l3.setString("3." + players[1].name);
			}
			l1.setCharacterSize(40);
			l1.setPosition(90, 186);
			l1.setFillColor(Color::Black);
			window.draw(l1);
			l2.setCharacterSize(40);
			l2.setPosition(90, 278);
			l2.setFillColor(Color::Black);
			window.draw(l2);
			l3.setCharacterSize(40);
			l3.setPosition(90, 370);
			l3.setFillColor(Color::Black);
			window.draw(l3);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 358 && x4 < 586) {
							if (y4 > 153 && y4 < 252) {
								if(curPlayer.lives > 0)
									isInMenu = false, basicOrJelly = true;
								else 
									isInMenu = false, IHaveNoLives = true;
							}
							else if (y4 > 303 && y4 < 401) {
								isInMenu = false, isIncredits = true;
							}
							else if (y4 > 453 && y4 < 547) {
								isInMenu = false, toQuit = true;
							}
						}
						else if (x4 > 702 && x4 < 917 && y4 > 407 && y4 < 580) {
							isInMenu = false, loadOrNew = true;
						}
					}
				}
			}
			window.display();

		}
		else if (IHaveNoLives) {
			window.clear();
			window.draw(haveNoLives);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 467 && x4 < 692 && y4 > 394 && y4 < 521) {
							isInMenu = true, IHaveNoLives = false;
						}
					}
				}
			}
			window.display();
		}
		else if (basicOrJelly) {
			window.clear();
			window.draw(BasicGameOrJelly);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 306 && x4 < 635) {
							if (y4 > 126 && y4 < 280) {
								if (!isBasic) {
									score = 0, moves = 15;
									isJelly = false;
									Shapping(Board, sh1, sh2, sh3, sh4, sh5);
									Positioning(Board);
									do {
										checker = false;
										special(Board, score, checker);
										check(Board, score, moves, checker);
										shifting(Board);
										Shapping(Board, sh1, sh2, sh3, sh4, sh5);
										ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
									} while (checker);
									Shapping(Board, sh1, sh2, sh3, sh4, sh5);
									Positioning(Board);
									for (int ii = 0; ii < Size; ++ii)
										if (hints[ii].size())
											hints[ii].clear();
									getHint(Board, hints);
									score = 0, moves = 15;
								}
								isBasic = true;
								basicOrJelly = false, isInBasicGame = true;

							}
							else if (y4 > 361 && y4 < 512) {
								if (!isJelly) {
									score = 0, moves = 15;
									isBasic = false;
									Shapping(Board, sh1, sh2, sh3, sh4, sh5);
									Positioning(Board);
									do {
										checker = false;
										special(Board, score, checker);
										check(Board, score, moves, checker);
										shifting(Board);
										Shapping(Board, sh1, sh2, sh3, sh4, sh5);
										ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
									} while (checker);
									Shapping(Board, sh1, sh2, sh3, sh4, sh5);
									Positioning(Board);
									for (int ii = 0; ii < Size; ++ii)
										if (hints[ii].size())
											hints[ii].clear();
									getHint(Board, hints);
									for (short idx1 = 0; idx1 < Size; ++idx1)
										for (short idx2 = 0; idx2 < Size; ++idx2)
											Board[idx1][idx2].jelly = true;
									Shapping(Board, sh1, sh2, sh3, sh4, sh5);
									Positioning(Board);
									score = 0, moves = 15;
									isInit = false;
								}
								isJelly = true;
								basicOrJelly = false, isInJellyGame = true;
								makeTheJellyBeGeneratedInTheGameOnce = true;
								
							}
						}
					}
				}
			}
			window.display();
		}
		else if (toPause) {
			window.clear();
			window.draw(pauseMenu);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						//Sound
						if ((x4 > 550 && x4 < 640) && (y4 > 110 && y4 < 210)) {
							heHasSoundOn = !heHasSoundOn;
						}
						//Close
						if ((x4 > 400 && x4 < 550) && (y4 > 300 && y4 < 475)) {
							toPause = false;
						}
						//Music
						if ((x4 > 310 && x4 < 400) && (y4 > 110 && y4 < 210)) {
							if (musicOn) {
								music.pause();
								musicOn = false;
							}
							else {
								music.play();
								music.setLoop(true);
								musicOn = true;
							}
						}
					}
				}
			}
			window.display();
		}
		else if (isInHints) {
		window.clear();
		window.draw(hintsSprite);
		Text TXT;
		TXT.setFont(font);
		TXT.setString("( 0-Based )");
		TXT.setCharacterSize(35);
		TXT.setPosition(436, 115);
		TXT.setFillColor(Color::Red);
		TXT.setOutlineColor(Color::Black);
		TXT.setOutlineThickness(5);
		window.draw(TXT);
		int xcor1 = 250, xcor2 = 485, ycor1 = 177, ycor2 = 250;
		int hintsCount = 0;
		/*for (int i = 0; i < Size; ++i) {
			vector <int> v;
			for (int j = 0; j < hints[i].size(); ++j) {
				v.push_back(hints[i][j]);
			}
			if(hints[i].size())
				sort(v.begin(), v.end());
			
			vector <int>::iterator j = v.begin(); 
			if(v.size() > 1)
				++j;
			for (vector <int>::iterator it = v.begin(); j != v.end() || it != v.end(); ++it) {
				if (*j == *it) {
					v.erase(j);
				}
			}
		}*/
		int hh = 4;
		while (hh--) {
			for (int i = 0; i < Size; i++) {
				if (hintsCount > 0)
					xcor1 += 485 - 250;
				ycor1 = 177;
				for (int j = 0; j < hints[i].size(); ++j) {
					xcor1 += 40;
					Text hintTXT;
					hintTXT.setFont(numbers);
					hintTXT.setCharacterSize(35);
					hintTXT.setFillColor(Color::Black);
					String sss = to_string(i);
					hintTXT.setString(sss);
					hintTXT.setPosition(xcor1, ycor1);
					window.draw(hintTXT);

					sss = to_string(hints[i][j]);
					hintTXT.setString(sss);
					xcor1 += 40;
					hintTXT.setPosition(xcor1, ycor1);
					window.draw(hintTXT);
					ycor1 += 250 - 177;
					hintsCount++;
					if (hintsCount == 4)
						break;
				}
				if (hintsCount == 4)
					break;
			}
		}
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left) {
					vec = Mouse::getPosition(window);
					x4 = vec.x; y4 = vec.y;
					cout << x4 << ' ' << y4 << endl;
					if (x4 > 800 && x4 < 910 && y4 > 495 && y4 < 570) {
						isInHints = false;
					}


				}
			}
		}
		window.display();
		}
		else if (isInBasicGame) {
			window.clear();
			window.draw(sprite);
			window.draw(rectangle);
			isBasic = true;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (moves <= 0) {
					if (score >= 2000) {
						cout << "inMoves\n";
						heGot3 = true, isInBasicGame = false;
					}
					else if (score >= 1500 && score <= 1999) {
						cout << "inMoves\n";
						heGot2 = true, isInBasicGame = false;
					}
					else if (score >= 1000 && score <= 1499) {
						cout << "inMoves\n";
						heGot1 = true, isInBasicGame = false;
					}
					else {
						heDidntGetAnything = true, isInBasicGame = false;
					}
				}
				else {
					if (event.type == Event::MouseButtonPressed) {
						if (event.key.code == Mouse::Left) {
							vec = Mouse::getPosition(window);
							//cout << "MOUSE BUTTEN PRESSED" << endl;
							x4 = vec.x; y4 = vec.y;
							cout << x4 << " " << y4 << endl;
							if (x4 > 742 && x4 < 929) {
								if (y4 > 502 && y4 < 608) {
									isInHints = true;
								}
								else if (y4 > 383 && y4 < 486) {
									toPause = true;
								}
							}
							int x1 = 29, y1 = 25;
							for (int i = 1; i <= Size; i++) {
								x1 = 29;
								for (int j = 1; j <= Size; j++) {
									if ((x4 > x1 && x4 < x1 + 72) && (y4 > y1 && y4 < y1 + 66)) {
										std::cout << i << " " << j << endl;
										std::cout << "click" << click << endl;
										// 23mel SWAP
										click++;
										if (click == 1) {
											i1 = i; j1 = j;
										}
										if (click == 2) {
											i2 = i; j2 = j;
											// e2mel swap lw abs difference
											if (abs(i1 - i2) > 1 || abs(j1 - j2) > 1) {
												// mt3ml4 swap
												std::cout << "NOT VALID TO SWAP" << endl;
											}
											else {
												int scoreBef = score;
												// e3mel swap
												swap(Board, i1, j1, i2, j2);
												Shapping(Board, sh1, sh2, sh3, sh4, sh5);
												do {
													checker = false;
													special(Board, score, checker);
													check(Board, score, moves, checker);
													shifting(Board);
													Shapping(Board, sh1, sh2, sh3, sh4, sh5);
												} while (checker);

												if (scoreBef == score)
													swap(Board, i1, j1, i2, j2);
												else {
													if (heHasSoundOn) {
														_delecious.stop();
														_devine.stop();
														_tasty.stop();
														_sweet.stop();
														srand(time(NULL));
														int soundHere = rand() & 4;
														cout << "sound Here : " << soundHere << endl;
														switch (soundHere) {
														case 0:
															_delecious.play();
															break;
														case 1:
															_devine.play();
															break;
														case 2:
															_sweet.play();
															break;
														case 3:
															_tasty.play();
															break;
														default:
															_tasty.play();
															break;
														}
													}
													--moves;
												}

												for (int ii = 0; ii < Size; ++ii)
													if (hints[ii].size())
														hints[ii].clear();
												getHint(Board, hints);

												std::cout << "\n\n";
												for (int ii = 0; ii < Size; ++ii) {
													for (int jj = 0; jj < Size; ++jj)
														std::cout << Board[ii][jj].candy << ' ';
													std::cout << std::endl;
												}

												lolo = true;
											}
											click = 0;
										}
									}
									x1 = x1 + 72;
								}
								y1 = y1 + 66;;
							}
						}
					}
				}
			}
			Positioning(Board);
			Shapping(Board, sh1, sh2, sh3, sh4, sh5);
			for (int i = 0; i < Size; i++) {
				for (int j = 0; j < Size; j++) {
					window.draw(Board[i][j].spriteshapes);
				}
			}

			Text ScoreNow, movesLefts;
			ScoreNow.setFont(numbers);
			ScoreNow.setString(to_string(score));
			ScoreNow.setCharacterSize(35);
			ScoreNow.setPosition(753, 91);
			ScoreNow.setFillColor(Color::Red);
			ScoreNow.setOutlineColor(Color::Black);
			ScoreNow.setOutlineThickness(5);
			movesLefts.setFont(numbers);
			movesLefts.setString(to_string(moves));
			movesLefts.setCharacterSize(35);
			movesLefts.setPosition(753, 271);
			movesLefts.setFillColor(Color::Red);
			movesLefts.setOutlineColor(Color::Black);
			movesLefts.setOutlineThickness(5);

			window.draw(ScoreNow);
			window.draw(movesLefts);
			window.draw(movesLeft);
			window.draw(totalPoints);
			window.display();
		}
		else if (isInJellyGame) {
			window.clear();
			window.draw(sprite);
			window.draw(rectangle);
			isJelly = true;
			bool heWon = true;
			for (int i = 0; i < Size; ++i) {
				for (int j = 0; j < Size; ++j) {
					if (Board[i][j].jelly) {
						heWon = false;
						break;
					}
				}
				if (!heWon)
					break;
			}
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (moves <= 0) {
					if (event.type == Event::Closed)
						window.close();
					if (heWon) {
						if (score >= 2000) {
							heGot3 = true, isInJellyGame = false;
						}
						else if (score >= 1500 && score <= 1999) {
							heGot2 = true, isInJellyGame = false;
						}
						else if (score >= 1000 && score <= 1499) {
							heGot1 = true, isInJellyGame = false;
						}
						else {
							heDidntGetAnything = true, isInJellyGame = false;
						}
					}
					else {
						heDidntGetAnything = true, isInJellyGame = false;
					}
				}
				else {
					if (event.type == Event::MouseButtonPressed) {
						if (event.key.code == Mouse::Left) {
							vec = Mouse::getPosition(window);
							x4 = vec.x; y4 = vec.y;
							cout << x4 << " " << y4 << endl;
							if (x4 > 742 && x4 < 929) {
								if (y4 > 502 && y4 < 608) {
									isInHints = true;
								}
								else if (y4 > 383 && y4 < 486) {
									toPause = true;
								}
							}
							int x1 = 29, y1 = 25;
							for (int i = 1; i <= Size; i++) {
								x1 = 29;
								for (int j = 1; j <= Size; j++) {
									if ((x4 > x1 && x4 < x1 + 72) && (y4 > y1 && y4 < y1 + 66)) {
										std::cout << i << " " << j << endl;
										std::cout << "click" << click << endl;
										// 23mel SWAP
										click++;
										if (click == 1) {
											i1 = i; j1 = j;
										}
										if (click == 2) {
											i2 = i; j2 = j;
											// e2mel swap lw abs difference
											if (abs(i1 - i2) > 1 || abs(j1 - j2) > 1) {
												// mt3ml4 swap
												std::cout << "NOT VALID TO SWAP" << endl;
											}
											else {
												int scoreBef = score;
												
												// e3mel swap
												swap(Board, i1, j1, i2, j2);
												Shapping(Board, sh1, sh2, sh3, sh4, sh5);
												ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
												do {
													checker = false;
													special(Board, score, checker);
													check(Board, score, moves, checker);
													shifting(Board);
													Shapping(Board, sh1, sh2, sh3, sh4, sh5);
													ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
												} while (checker);

												if (scoreBef == score)
													swap(Board, i1, j1, i2, j2);
												else {
													if (heHasSoundOn) {
														_delecious.stop();
														_devine.stop();
														_sweet.stop();
														_tasty.stop();
														srand(time(NULL));
														int soundHere = rand() & 4;
														cout << "sound Here : " << soundHere << endl;
														switch (soundHere) {
														case 0:
															_delecious.play();
															break;
														case 1:
															_devine.play();
															break;
														case 2:
															_sweet.play();
															break;
														case 3:
															_tasty.play();
															break;
														default:
															_tasty.play();
															break;
														}
													}
													--moves;
												}
												for (int ii = 0; ii < Size; ++ii)
													if (hints[ii].size())
														hints[ii].clear();
												getHint(Board, hints);

												std::cout << "\n\n";
												for (int ii = 0; ii < Size; ++ii) {
													for (int jj = 0; jj < Size; ++jj)
														std::cout << Board[ii][jj].candy << ' ';
													std::cout << std::endl;
												}

												lolo = true;
											}
											click = 0;
										}
									}
									x1 = x1 + 72;
								}
								y1 = y1 + 66;;
							}
						}
					}
				}
			}
			Positioning(Board);
			PositioningJelly(Board);
			Shapping(Board, sh1, sh2, sh3, sh4, sh5);
			ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
			do {
				checker = false;
				special(Board, score, checker);
				check(Board, score, moves, checker);
				shifting(Board);
				Shapping(Board, sh1, sh2, sh3, sh4, sh5);
				ShappingJelly(Board, sh1, sh2, sh3, sh4, sh5, jelly);
			} while (checker);
			
			if (onetime) {
				for (int i = 0; i < Size; i++) {
					for (int j = 0; j < Size; j++) {
						Board[i][j].jelly = true;
					}
				}
				onetime = false;
			}
			for (int i = 0; i < Size; i++) {
				for (int j = 0; j < Size; j++) {
					if (Board[i][j].jelly == 1) {
						window.draw(Board[i][j].jellysprite);
					}
				}
			}

			for (int i = 0; i < Size; i++) {
				for (int j = 0; j < Size; j++) {
					window.draw(Board[i][j].spriteshapes);
				}
			}
			if (!isInit) {
				score = 0, moves = 15;
				isInit = true;
			}
			Text ScoreNow, movesLefts;
			ScoreNow.setFont(numbers);
			ScoreNow.setString(to_string(score));
			ScoreNow.setCharacterSize(35);
			ScoreNow.setPosition(753, 91);
			ScoreNow.setFillColor(Color::Red);
			ScoreNow.setOutlineColor(Color::Black);
			ScoreNow.setOutlineThickness(5);
			movesLefts.setFont(numbers);
			movesLefts.setString(to_string(moves));
			movesLefts.setCharacterSize(35);
			movesLefts.setPosition(753, 271);
			movesLefts.setFillColor(Color::Red);
			movesLefts.setOutlineColor(Color::Black);
			movesLefts.setOutlineThickness(5);

			window.draw(ScoreNow);
			window.draw(movesLefts);
			window.draw(movesLeft);
			window.draw(totalPoints);
			window.display();
		}
		else if (heGot1) {
			window.clear();
			window.draw(Star1Pics);
			if (!star1WasPlayed) {
				_star1.stop();
				_star1.play();
				star1WasPlayed = true;
			}
			Text ScoreTXTforScreen;
			Text word;
			if (score > curPlayer.score) {
				curPlayer.score = score;
				if (curPlayerIdx == 0) {
					ofstream oFile("player1.txt");
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					oFile.close();
				}
				else if (curPlayerIdx == 1) {
					ofstream oFile("player2.txt");
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					oFile.close();
				}
				else if (curPlayerIdx == 2) {
					ofstream oFile("player3.txt");
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					oFile.close();
				}
				word.setFont(font);
				word.setString("New High Score!!");
				word.setCharacterSize(35);
				word.setPosition(370, 232);
				word.setFillColor(Color::Red);
				word.setOutlineColor(Color::Black);
				word.setOutlineThickness(5);
				ScoreTXTforScreen.setFont(numbers);
				ScoreTXTforScreen.setString(to_string(score));
				ScoreTXTforScreen.setCharacterSize(35);
				ScoreTXTforScreen.setPosition(423, 299);
				ScoreTXTforScreen.setFillColor(Color::Red);
				ScoreTXTforScreen.setOutlineColor(Color::Black);
				ScoreTXTforScreen.setOutlineThickness(5);
			}
			else {
				word.setFont(font);
				word.setString("Your Score!!");
				word.setCharacterSize(35);
				word.setPosition(370, 232);
				word.setFillColor(Color::Red);
				word.setOutlineColor(Color::Black);
				word.setOutlineThickness(5);
				ScoreTXTforScreen.setFont(numbers);
				ScoreTXTforScreen.setString(to_string(score));
				ScoreTXTforScreen.setCharacterSize(35);
				ScoreTXTforScreen.setPosition(423, 299);
				ScoreTXTforScreen.setFillColor(Color::Red);
				ScoreTXTforScreen.setOutlineColor(Color::Black);
				ScoreTXTforScreen.setOutlineThickness(5);
			}
			window.draw(word);
			window.draw(ScoreTXTforScreen);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 661 && x4 < 905 && y4 > 487 && y4 < 598) {
							isBasic = false, isJelly = false;
							star1WasPlayed = false;
							heGot1 = false, isInMenu = true;
							_star1.stop();
						}
					}
				}
			}
			window.display();
		}
		else if (heGot2) {
			window.clear();
			window.draw(Star2Pics);
			if (!star2WasPlayed) {
				_star2.stop();
				_star2.play();
				star2WasPlayed = true;
			}
			Text ScoreTXTforScreen;
			Text word;
			if (score > curPlayer.score) {
				curPlayer.score = score;
				if (curPlayerIdx == 0) {
					ofstream oFile("player1.txt");
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					oFile.close();
				}
				else if (curPlayerIdx == 1) {
					ofstream oFile("player2.txt");
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					oFile.close();
				}
				else if (curPlayerIdx == 2) {
					ofstream oFile("player3.txt");
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					oFile.close();
				}
				word.setFont(font);
				word.setString("New High Score!!");
				word.setCharacterSize(35);
				word.setPosition(370, 232);
				word.setFillColor(Color::Red);
				word.setOutlineColor(Color::Black);
				word.setOutlineThickness(5);
				ScoreTXTforScreen.setFont(numbers);
				ScoreTXTforScreen.setString(to_string(score));
				ScoreTXTforScreen.setCharacterSize(35);
				ScoreTXTforScreen.setPosition(423, 299);
				ScoreTXTforScreen.setFillColor(Color::Red);
				ScoreTXTforScreen.setOutlineColor(Color::Black);
				ScoreTXTforScreen.setOutlineThickness(5);
			}
			else {
				word.setFont(font);
				word.setString("Your Score!!");
				word.setCharacterSize(35);
				word.setPosition(370, 232);
				word.setFillColor(Color::Red);
				word.setOutlineColor(Color::Black);
				word.setOutlineThickness(5);
				ScoreTXTforScreen.setFont(numbers);
				ScoreTXTforScreen.setString(to_string(score));
				ScoreTXTforScreen.setCharacterSize(35);
				ScoreTXTforScreen.setPosition(423, 299);
				ScoreTXTforScreen.setFillColor(Color::Red);
				ScoreTXTforScreen.setOutlineColor(Color::Black);
				ScoreTXTforScreen.setOutlineThickness(5);
			}
			window.draw(word);
			window.draw(ScoreTXTforScreen);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 661 && x4 < 905 && y4 > 487 && y4 < 598) {
							isBasic = false, isJelly = false;
							heGot2 = false, isInMenu = true;
							star2WasPlayed = false;
							_star2.stop();
						}
					}
				}
			}
			window.display();
		}
		else if (heGot3) {
			window.clear();
			window.draw(Star3Pics);
			if (!star3WasPlayed) {
				_star3.play();
				star3WasPlayed = true;
			}
			Text ScoreTXTforScreen;
			Text word;
			if (score > curPlayer.score) {
				curPlayer.score = score;
				if (curPlayerIdx == 0) {
					ofstream oFile("player1.txt");
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					oFile.close();
				}
				else if (curPlayerIdx == 1) {
					ofstream oFile("player2.txt");
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					oFile.close();
				}
				else if (curPlayerIdx == 2) {
					ofstream oFile("player3.txt");
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					oFile.close();
				}
				word.setFont(font);
				word.setString("New High Score!!");
				word.setCharacterSize(35);
				word.setPosition(370, 232);
				word.setFillColor(Color::Red);
				word.setOutlineColor(Color::Black);
				word.setOutlineThickness(5);
				ScoreTXTforScreen.setFont(numbers);
				ScoreTXTforScreen.setString(to_string(score));
				ScoreTXTforScreen.setCharacterSize(35);
				ScoreTXTforScreen.setPosition(423, 299);
				ScoreTXTforScreen.setFillColor(Color::Red);
				ScoreTXTforScreen.setOutlineColor(Color::Black);
				ScoreTXTforScreen.setOutlineThickness(5);
			}
			else {
				word.setFont(font);
				word.setString("Your Score!!");
				word.setCharacterSize(35);
				word.setPosition(370, 232);
				word.setFillColor(Color::Red);
				word.setOutlineColor(Color::Black);
				word.setOutlineThickness(5);
				ScoreTXTforScreen.setFont(numbers);
				ScoreTXTforScreen.setString(to_string(score));
				ScoreTXTforScreen.setCharacterSize(35);
				ScoreTXTforScreen.setPosition(423, 299);
				ScoreTXTforScreen.setFillColor(Color::Red);
				ScoreTXTforScreen.setOutlineColor(Color::Black);
				ScoreTXTforScreen.setOutlineThickness(5);
			}
			window.draw(word);
			window.draw(ScoreTXTforScreen);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 661 && x4 < 905 && y4 > 487 && y4 < 598) {
							isBasic = false, isJelly = false;
							heGot3 = false, isInMenu = true;
							star3WasPlayed = false;
							_star3.stop();
						}
					}
				}
			}
			window.display();
		}
		else if (heDidntGetAnything) {
			window.clear();
			window.draw(loosePics);
			Text ScoreTXTforScreen;
			Text word;
			if (!itwasDec) {
				curPlayer.lives--; itwasDec = true;
			}
			cout << curPlayer.lives << endl;
			if (score > curPlayer.score) {
				curPlayer.score = score;
				if (curPlayerIdx == 0) {
					ofstream oFile("player1.txt");
					ofstream looseTime("player1LooseTime.txt");
					int year, month, day, hour, mins, secs, weekDay;
					getTm(year, month, day, hour, mins, secs, weekDay);
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					looseTime << year << ' ' << month << ' ' << day << ' ' << hour << ' ' << mins << ' ' << secs << ' ' << weekDay;
					oFile.close();
					looseTime.close();
				}
				else if (curPlayerIdx == 1) {
					ofstream oFile("player2.txt");
					ofstream looseTime("player2LooseTime.txt");
					int year, month, day, hour, mins, secs, weekDay;
					getTm(year, month, day, hour, mins, secs, weekDay);
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					looseTime << year << ' ' << month << ' ' << day << ' ' << hour << ' ' << mins << ' ' << secs << ' ' << weekDay;
					oFile.close();
					looseTime.close();
				}
				else if (curPlayerIdx == 2) {
					ofstream oFile("player3.txt");
					ofstream looseTime("player3LooseTime.txt");
					int year, month, day, hour, mins, secs, weekDay;
					getTm(year, month, day, hour, mins, secs, weekDay);
					oFile << curPlayer.name << ' ' << curPlayer.score << ' ' << curPlayer.lives;
					looseTime << year << ' ' << month << ' ' << day << ' ' << hour << ' ' << mins << ' ' << secs << ' ' << weekDay;
					oFile.close();
					looseTime.close();
				}
				word.setFont(font);
				word.setString("New High Score!!");
				word.setCharacterSize(35);
				word.setPosition(370, 232);
				word.setFillColor(Color::Red);
				word.setOutlineColor(Color::Black);
				word.setOutlineThickness(5);
				ScoreTXTforScreen.setFont(numbers);
				ScoreTXTforScreen.setString(to_string(score));
				ScoreTXTforScreen.setCharacterSize(35);
				ScoreTXTforScreen.setPosition(423, 299);
				ScoreTXTforScreen.setFillColor(Color::Red);
				ScoreTXTforScreen.setOutlineColor(Color::Black);
				ScoreTXTforScreen.setOutlineThickness(5);
			}
			else {
				word.setFont(font);
				word.setString("Your Score!!");
				word.setCharacterSize(35);
				word.setPosition(370, 232);
				word.setFillColor(Color::Red);
				word.setOutlineColor(Color::Black);
				word.setOutlineThickness(5);
				ScoreTXTforScreen.setFont(numbers);
				ScoreTXTforScreen.setString(to_string(score));
				ScoreTXTforScreen.setCharacterSize(35);
				ScoreTXTforScreen.setPosition(423, 299);
				ScoreTXTforScreen.setFillColor(Color::Red);
				ScoreTXTforScreen.setOutlineColor(Color::Black);
				ScoreTXTforScreen.setOutlineThickness(5);
			}
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						vec = Mouse::getPosition(window);
						x4 = vec.x; y4 = vec.y;
						cout << x4 << ' ' << y4 << endl;
						if (x4 > 661 && x4 < 905 && y4 > 487 && y4 < 598) {
							isBasic = false, isJelly = false;
							itwasDec = false;
							heDidntGetAnything = false, isInMenu = true;
						}
					}
				}
			}
			window.display();
		}
		else if (isIncredits) {
			window.clear();
			window.draw(crs);
			window.display();
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				if (event.key.code == Keyboard::F)
					isInMenu = true, isIncredits = false;
			}
		}
		else if (toQuit) {
			window.close();
		}

	}

}

int main() {
	letsPlay();
	return 0;
}
