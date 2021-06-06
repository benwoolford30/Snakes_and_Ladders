
#define SHADER_H
#include <fstream> // reference for file functions
#define GLEW_STATIC
#include <GL/glew.h>
// reference glew library
#include <GLFW/glfw3.h>
// reference glfw library
#include "libraries/glm/glm/glm.hpp"
#include "libraries/glm/glm/gtc/matrix_transform.hpp""
#include "libraries/glm/glm/gtc/type_ptr.hpp"
// reference to the glm library
#include <map>

#include <iostream>
#include "Shader.h"
// reference shader headerfile
#include <SOIL.h>
// reference soil library
#include <Windows.h> // header for windows
#include <time.h> // header for time
#include <string> // header for strings

#include  <ft2build.h>
#include FT_FREETYPE_H 
//reference  freetype library
#include <stack> // header for stacks
using namespace std;
#pragma region Classes // block of code for all of the classes





#pragma region Board // block of code for board class
class Board // this class stores the coordinates for the board of the game 
{
public:
	Board();
	~Board();
	struct Space
	{
		float cordx;
		float cordy;
		int Spacenum;
		int type;
		Space()
		{
			cordx = 0.0f;
			cordy = 0.0f;
			Spacenum = 0;
			type = 0;
		}
	
	};
	Space* spaces = new Space[101];// create spaces of the board
private:
	
};

Board::Board() // constructor call for the board
{
	float xcord = -12.25 - 2.04; 
	float ycord = -11.9;
	int timesmoved = 0;
	float xchange = 2.04;
	int i = 0;
	for (i = 1;i <= 100;i++) // go through each space and assigning correct information to each one
	{
		if (timesmoved == 10)
		{
			ycord += 2.525;
			xcord += xchange;
			xchange *= -1;
			timesmoved = 0;
		}
		timesmoved += 1;
		xcord += xchange;
		spaces[i].cordx = xcord;
		spaces[i].cordy = ycord;
		spaces[i].Spacenum = i;

	}
}

Board::~Board() // deconstructor call for the board 
{
	delete spaces; //delete the pointer
	spaces = NULL; // make the pointer null afterwards
}

#pragma endregion //end of board class

#pragma region Player // block of code for the player class

class Player
{
public:
	
	Player();
	Player(int playerplace); // overloaded function for the constructor purpose is to allow for initialisation of players in different positions
	~Player();
	void Finishturn();	//end the players turn	
	void doturn(int* Playerorder, stack<int>* finishorder); //
	int spaceposition;
	int turnsroll;
	GLfloat xcord;
	GLfloat ycord;
	GLfloat Xoffset;
	GLfloat Yoffset;
	bool finished;	
	bool nextturn; 
	bool rolleddice;		// these three boolean variables are used for determining which part of the turn the current player is on- beginning to roll, landed on a snake or ladder and finishing their turn 
	
private:
	void rolldice(stack<int>* finishorder);
	bool Getfinished();
	int playerno;
	int generatenum(int num);
	void Taketurn(int spacemove,Board* gameboard, stack<int>* finishorder);
	
};
int Player::generatenum(int num)
{
	return rand() % num + 1; // returns a number between 1 and num based on the parametre sent and returns an int of it
};
void Player::Finishturn()
{
	
	Board* gameboard = new Board; //create a pointer to the board class
	
	#pragma region checksnakeandladder	
	switch (spaceposition)
	{
	case 3: { // Only way to do it was to do each snake and ladder one by one 
		xcord = gameboard->spaces[39].cordx + Xoffset;	// Ladder move player from space 3 to space 39
		ycord = gameboard->spaces[39].cordy + Yoffset;	// By using the boards coordinates the player translates to the appropriate space
		spaceposition = gameboard->spaces[39].Spacenum; 
	}break;
	case 10: {
		xcord = gameboard->spaces[12].cordx + Xoffset;
		ycord = gameboard->spaces[12].cordy + Yoffset;
		spaceposition = gameboard->spaces[12].Spacenum;
	}break;
	case 16: {// landed on snake
		xcord = gameboard->spaces[13].cordx + Xoffset; //Player goes to space 13
		ycord = gameboard->spaces[13].cordy + Yoffset;
		spaceposition = gameboard->spaces[13].Spacenum;
	}break;
	case 27: {
		xcord = gameboard->spaces[53].cordx + Xoffset;
		ycord = gameboard->spaces[53].cordy + Yoffset;
		spaceposition = gameboard->spaces[53].Spacenum;
	}break;
	case 31: {
		xcord = gameboard->spaces[4].cordx + Xoffset;
		ycord = gameboard->spaces[4].cordy + Yoffset;
		spaceposition = gameboard->spaces[4].Spacenum;
	}break;
	case 47: {
		xcord = gameboard->spaces[25].cordx + Xoffset;
		ycord = gameboard->spaces[25].cordy + Yoffset;
		spaceposition = gameboard->spaces[25].Spacenum;
	}break;
	case 56: {
		xcord = gameboard->spaces[84].cordx + Xoffset;
		ycord = gameboard->spaces[84].cordy + Yoffset;
		spaceposition = gameboard->spaces[84].Spacenum;
	}break;
	case 61: {
		xcord = gameboard->spaces[99].cordx + Xoffset;
		ycord = gameboard->spaces[99].cordy + Yoffset;
		spaceposition = gameboard->spaces[99].Spacenum;
	}break;
	case 63: {
		xcord = gameboard->spaces[60].cordx + Xoffset;
		ycord = gameboard->spaces[60].cordy + Yoffset;
		spaceposition = gameboard->spaces[60].Spacenum;
	}break;
	case 66: {
		xcord = gameboard->spaces[52].cordx + Xoffset;
		ycord = gameboard->spaces[52].cordy + Yoffset;
		spaceposition = gameboard->spaces[52].Spacenum;
	}break;
	case 72: {
		xcord = gameboard->spaces[90].cordx + Xoffset;
		ycord = gameboard->spaces[90].cordy + Yoffset;
		spaceposition = gameboard->spaces[90].Spacenum;
	}break;
	case 97: {
		xcord = gameboard->spaces[75].cordx + Xoffset;
		ycord = gameboard->spaces[75].cordy + Yoffset;
		spaceposition = gameboard->spaces[75].Spacenum;
	}break;
	}
#pragma endregion; // this chunk of code  is used to determine whther the player should move depending on if they landed on a snkae or ladder
	delete gameboard; //delete the board
	gameboard = NULL;
};
void Player::Taketurn(int spacemove,Board* gameboard, stack<int>* finishorder) //Action after player rolls dice
{
	spaceposition += spacemove; //add dice roll to movement
	if (spaceposition >= 100) // To prevent error plus check if end for player
	{
		spaceposition = 100;
		finished = true;
		finishorder->push(playerno); // push the current finished player to stack
	}
	xcord=gameboard->spaces[spaceposition].cordx+Xoffset; // put player x cord to x cord of space landed on
	ycord = gameboard->spaces[spaceposition].cordy+Yoffset;// put player y cord to y cord of space landed on
	rolleddice = true; // set to true to establish that the player has rolled the dice
	
	
	

	
};
void Player::rolldice(stack<int>* finishorder) // function to roll the dice
{
	 turnsroll=generatenum(6); // calls the generate num function
	Board* boardcoords = new Board; // create pointer of board
	Taketurn(turnsroll, boardcoords,finishorder); // call the take turns function
	delete boardcoords; // delete boardcoords
	boardcoords = NULL;
	
	
	
}
bool Player::Getfinished() // funciton to return the finished value
{
	return finished;
	
}
void Player::doturn(int* Playerorder , stack<int>* finishorder) // function called when enter is pressed on the keyboard

{
	if (Getfinished() == false) //check if player has finished
	{	
		if (rolleddice == false)
		{
			rolldice(finishorder); // Current player rolls dice

		}
		else
		{
			if (nextturn == true) // check if must now go to the next players turn
			{

				rolleddice = false;
				nextturn = false;	// set booleans to false for when the player class next has its turn

			}
			if (spaceposition == 3 || spaceposition == 10 || spaceposition == 16 || spaceposition == 27 || spaceposition == 31 || spaceposition == 47 || spaceposition == 56 || spaceposition == 61 || spaceposition == 63 || spaceposition == 66 || spaceposition == 72 || spaceposition == 97)
			// check if the player has landed on a snake or ladder
			{
				nextturn = true; 
				Finishturn(); // call finishturn function
			}
			if (nextturn == false) // goes here for if the player didnt land on a snake/ladder or it has been resolved
			{
				rolleddice = false; // set dice roll to false
				*Playerorder += 1; // Goes to next players turn 
			}
		}
	}
	else
	{
		*Playerorder += 1;// Goes to next players turn 

	}
		if (*Playerorder > 4) // Checks if gone over the 4th player which will set it back to 1
			*Playerorder = 1;
	};
Player::Player() // constructor call for player class
{
	// initialising variables
	Xoffset = 0.0f;
	Yoffset = 0.0f;
	playerno = 0;
	xcord = -12.25+Xoffset;
	ycord = -11.9+Yoffset;
	spaceposition = 1;
	nextturn = false;
	rolleddice = false;
}
Player::Player(int playerplace) // overloaded function constructor used for setting values for each different player
{
	switch (playerplace) // switch statment to check which player is being initialised
	{
		case 1: {
			Xoffset = 0.0f;
			Yoffset = 0.0f;
			playerno = 1;
		}break;
		case 2: {
			Xoffset = 1.0f;
			Yoffset = 0.0f;
			playerno = 2;
		}break;
		case 3: {
			Xoffset = 0.0f;
			Yoffset = 1.0f;
			playerno = 3;
		}break;
		case 4: {
			Xoffset = 1.0f;
			Yoffset = 1.0f;
			playerno = 4;
		}break;
	}
	xcord = -12.25+Xoffset; // this cord places the player in space 1 and aligned appropriately  depending on which player they're
	ycord = -11.9+Yoffset;
	spaceposition = 1;
	nextturn = false;
	rolleddice = false;
}
Player::~Player() // deconstructor for player class
{
}

#pragma endregion  // end of player class

#pragma region Controls // block of code for the control class

class Controls // Base Class to handle input
{
public: // public members of class
	Controls();
	~Controls();
	void setInput(bool set, int keytype, int actiontype); // function that takes the input, determines what key it is, whether its being pressed, held or released 
	protected: // protected members of class
	virtual void UseInput(); // allow for overide for a child class
	
	/*
	key rundown 
	inputkeys[keytype,actiontype]
	keytype= what key was pressed
	keytype=1 means left key
	keytype=2 means right key
	keytype=3 means up key
	keytype=4 means down key
	keytype=5 means enter key
	keytype=6 means escape key
	actiontype= whether key was pressed, held or released
	actiontype =1 means pressed 
	actiontype =2 means held
	actiontype =3 means released

	ie 
	input keys[1,1] means left key was pressed
	*/
	bool inputkeys[7][3]; // initialise size of array
};

Controls::Controls()
{
	  
}

Controls::~Controls()
{
}
void Controls::setInput(bool set, int keytype ,int actiontype)// function for setting whether a key was pressed, released or held and which key
{
	inputkeys[keytype][actiontype] = set; //set the key that was pressed/held/released to true or false
};
void Controls::UseInput() //function that executes events based on what has been inputted
{

	#pragma region leftkey //left key event input
		if (inputkeys[1][1] == true) //if the leftkey was pressed
		{
			cout << "Left key is pressed" << endl;
			inputkeys[1][1] = false;
		}
		if (inputkeys[1][2] == true) // if the left key is being held
		{
			cout << "Left key is held" << endl;
		}
		if (inputkeys[1][3] == true) // if the left key was released
		{
			cout << "Left key is released" << endl;
			inputkeys[1][3] = false;
		}
	#pragma endregion  //trigger events to do with leftkey
	#pragma region rightkey
	if (inputkeys[2][ 1] == true)
	{
		cout << "Right key is pressed" << endl;
		inputkeys[2][ 1] = false;
	}
	if (inputkeys[2][ 2] == true)
	{
		cout << "Right key is held" << endl;
	}
	if (inputkeys[2][ 3] == true)
	{
		cout << "Right key is released" << endl;
		inputkeys[2][ 3] = false;
	}
	#pragma endregion 
	#pragma region upkey
	if (inputkeys[3][1] == true)
	{
		cout << "Up key is pressed" << endl;
		inputkeys[3][1] = false;
	}
	if (inputkeys[3][2] == true)
	{
		cout << "Up key is held" << endl;
	}
	if (inputkeys[3][3] == true)
	{
		cout << "Up key is released" << endl;
		inputkeys[3][3] = false;
	}
#pragma endregion 
	#pragma region downkey
	if (inputkeys[4][1] == true)
	{
		cout << "Down key is pressed" << endl;
		inputkeys[4][1] = false;
	}
	if (inputkeys[4][2] == true)
	{
		cout << "Down key is held" << endl;
	}
	if (inputkeys[4][3] == true)
	{
		cout << "Down key is released" << endl;
		inputkeys[4][3] = false;
	}
	#pragma endregion 
	#pragma region enterkey
	if (inputkeys[5][1] == true)
	{
		cout << "Enter key is pressed" << endl;
		inputkeys[5][1] = false;
	}
	if (inputkeys[5][2] == true)
	{
		cout << "Enter key is held" << endl;
	}
	if (inputkeys[5][3] == true)
	{
		cout << "Enter key is released" << endl;
		inputkeys[5][3] = false;
	}
#pragma endregion	
	#pragma region escapekey
	if (inputkeys[6][1] == true)
	{
		cout << "Escape key is pressed" << endl;
		inputkeys[6][1] = false;
	}
	if (inputkeys[6][2] == true)
	{
		cout << "Escape key is held" << endl;
	}
	if (inputkeys[6][3] == true)
	{
		cout << "Escape key is released" << endl;
		inputkeys[6][3] = false;
	}
#pragma endregion 
	// this function is used as a basis where it informs the user on the console window what key they've pressed however in the final build the console window is freed
};
#pragma endregion // end of controls class

void keycall(GLFWwindow* window, int key, int scancode, int action, int mode); // function declaration for registering key input
/*
	unfortunately was unable to figure out how to use thiws function inside my game class so it had to declared externally and above the game class 
	and then defined in the source file to allow for input to function correctly- more into this in the source file 
*/ 
#pragma region Game // block of code for the game class 


class Game: public Controls // Class of game inheriting from the Controls class
{
	/*
	IMPORTANT NOTE-
	a lot of the glew and glfw code in this class uses templates provided from learnopengl.com since this
	is what enabled me to create this game as a result there will be bits that were taken from the site.
	I will specify where exactly at each point 
	*/
public:
	Game();
	~Game();
	void Maingameloop(); // function for main game loop 
	
	
	
private:// private members of class
	
	struct Character  // structure taken from learnopengl.com to allow for use of text
	{
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
	};
	struct menu // structure for a game menu 
	{
		GLfloat cursorxcord; 
		GLfloat cursorycord;
		int choice;	// the option currently selceted  in the menu
		GLfloat spacebetweentext; // used to help space out text equally 
		menu()
		{
			choice = 1;
			cursorxcord = -10;
			cursorycord = 5;
			spacebetweentext = 100;
		};
	};
	void dostate(); // function that tells the game which state where in- start menu or game 
	void UseInput() override; // override of Useinput function to make the function make sense for the game
	void setupgamewindow(); // Set up openGL window
	void setupbackgroundimage(); //Set up VAO to store info for the snakesandladders board image
	void setupplayerpiece(); // set up VAO2 to store info to do with playerpiece
	void setimagetexture(const char* loadimage); // Function to assign an image to a texture
	void drawgameassets(); // function to draw to the window
	void RenderText(Shaders* shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color); // function taken and amended from learnopengl.com to enable text on a GLFW window 
	void setuptext(); // function to enable text to be written on the screen was taken and amended to fit for my game from learnopengl.com
	void resetgame(int count); //recursive procedure
	void savegame(); // creates a textfile that stores variables to allow for the game to be continued 
	void loadgame(); // loads the game is a savefile exists
	GLFWwindow* window; // game window	
	GLuint VAO; // Vertex attribute object used to store data to do with the board
	GLuint VBO; 
	GLuint EBO;
	GLuint texture;	
	GLuint VAO2; // Used to store data about the player piece
	GLuint VBO2;
	GLuint EBO2;
	GLuint VAO3; // Used to store data about text
	GLuint VBO3;
	GLuint EBO3;
    map<GLchar, Character> Characters; // variable required to enable text on the screen from Learnopengl.com
	Player Players[4]{ 1,2,3,4 }; //Create 4 player objects and initialise them
	int  Finishorder[4]{0,0,0,0}; // array to store the finish order of the player
	Shaders* ptrSnakesandladdersbackgroundshader; // shader pointer to run the code to create the snakes and ladders board image
	Shaders* ptrtriangleshader; // shader pointer to create the player icon on the screen which is a simple triangle 
	Shaders* ptrtextShader; // shader pointer used to draw text on the screen 
	int Playerorder; // value to store which players turn it currently is
	int windowWidth; // width of the window screen
	int WindowHeight; // height of the window screen
	stack <int> Finishedorder; //Stack to keep track of the order the players finished in 
	int states; // game state
	menu startmenu; // start menu varible
	
};
void Game::savegame() // function to create a textfile to store variables that will enable the game to be picked up at a different time
{
	ofstream savefile;
	savefile.open("Savefile.txt"); // create textfile if it doesnt exist or access it 
	savefile << Playerorder <<endl;
	for (int i = 0; i <= 3; i++) // go through all 4 players
	{
		savefile << Players[i].spaceposition  << endl;
		savefile << Players[i].xcord << endl;
		savefile << Players[i].ycord << endl;
		savefile << Players[i].finished << endl;
		savefile << Players[i].rolleddice << endl;
		savefile << Players[i].nextturn << endl;
	} // pass all required variables to savefile
	savefile.close(); // closefile
};
void Game::loadgame() // function to load a game if the savefile exists
{
	ifstream savefile("Savefile.txt"); // set up file for reading- if it exists
	string line;// local variable used to store variables from the file
	if (savefile.is_open()) // check for if file exists if not then nothing happens
	{
		states = 2;
		while (getline(savefile, line))
		{
			Playerorder = stoi(line, NULL);
			for (int i = 0; i <= 3; i++)
			{
				getline(savefile, line);
				Players[i].spaceposition =stoi(line, NULL);
				getline(savefile, line);
				Players[i].xcord =stof(line, NULL);
				getline(savefile, line);
				Players[i].ycord = stof(line, NULL);
				getline(savefile, line);
				Players[i].finished= stoi(line, NULL);
				getline(savefile, line);
				Players[i].rolleddice= stoi(line, NULL);
				getline(savefile, line);
				Players[i].nextturn= stoi(line, NULL)
					;
			}// read contents of the file and assign to the game variables as we stored them in order we know which variable is which so its a matter of reassigning them back 
		}
	}
};
void Game::resetgame(int count) // function called when the game either ends or the player presses escapes
{
	Players[count].spaceposition = 1;
	Players[count].xcord = -12.25 + Players[count].Xoffset;
	Players[count].ycord = -11.9 + Players[count].Yoffset;
	Players[count].finished = false;
	Players[count].rolleddice = false;
	Players[count].nextturn = false;
	Finishorder[count] = 0;
	count += 1;
	if (count <= 3) // if the function hasnt gone through all players then call the function again
		resetgame(count); // recursion 
};
void Game::dostate() // function that checks which state the game is in and output appropriately
{
	switch (states) // check which state in 
	{
		case 1: { // start menu state
			GLfloat width= (windowWidth / 2);
			GLfloat	height= (WindowHeight / 2)+200;
			RenderText(ptrtextShader, "Snakes and Ladders Game"  , width-200, height, 1.0f, glm::vec3(0.5, 0.8f, 0.2f)); // outputs text snakes and ladders game 
			RenderText(ptrtextShader, "Start Game", width-100, height-100, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			RenderText(ptrtextShader, "Continue previous game", width-100, height-200, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			RenderText(ptrtextShader, "Quit", width-100, height-300, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			ptrtriangleshader->Use(); // use the shader for drawing a triangle 
			glBindVertexArray(VAO2); // assiginng triangle VAO to the vertex array 
			glm::mat4 transform; // apply transformations to the triangle 
			transform = glm::scale(transform, glm::vec3(0.075, 0.075, 0.75)); // adjust the size
			transform = glm::translate(transform, glm::vec3( startmenu.cursorxcord,  startmenu.cursorycord, 0.0f)); // adjust the coordinates
			GLint transformLoc = glGetUniformLocation(ptrtriangleshader->Program, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			// the code to output the triangle was inspired by used examples from learnopengl.com
		}break;
		case 2: { // game state
			if (Players[Playerorder - 1].rolleddice == false && Players[Playerorder-1].finished==false) // check if the player has not rolled the dice and also havent finished 
			{
				RenderText(ptrtextShader, "Player " + to_string(Playerorder) + "'s turn", 650.0f, 25.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, "Press Esc to go", 650.0f, 500.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, "back", 650.0f, 470.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, "Press Enter to", 650.0f, 440.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, "roll", 650.0f, 410.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, "This game", 650.0f, 380.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, "autosaves every", 650.0f, 350.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, "turn", 650.0f, 320.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				/*
				outputs text
				-------------------------------
										Press Esc to go 
										back
										Press Enter to roll
										This game
										autosaves every 
										turn



										Player 1's turn
				------------------------------------
				*/
			}
			if (Players[Playerorder - 1].finished == true && Finishedorder.size() < 4 && Finishorder[1] == 0) // checks if the player has finished however not all players have finished 
			{
				RenderText(ptrtextShader, "Player " + to_string(Playerorder), 650.0f, 250.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, " has finished!", 650.0f, 220.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
			}
			if (Players[Playerorder - 1].rolleddice == true && Players[Playerorder - 1].finished == false) //checks if the player has rolled their dice however havent landed on space 100 yet
				RenderText(ptrtextShader, "Player " + to_string(Playerorder) + " rolled a " + to_string(Players[Playerorder - 1].turnsroll) + "!", 650.0f, 250.0f, 0.35f, glm::vec3(0.5, 0.8f, 0.2f));
			if (Players[Playerorder - 1].nextturn == true) // checks if the player has landed on a snake or ladder
			{ 
				RenderText(ptrtextShader, "Player " + to_string(Playerorder) + " landed on ", 650.0f, 450.0f, 0.35f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, "a snake/ladder!", 650.0f, 420.0f, 0.35f, glm::vec3(0.5, 0.8f, 0.2f));

			}
			if (Finishedorder.size() == 4) // checks if the stack has 4 items in it which signifys the end of the game
			{


				Finishorder[0] = Finishedorder.top(); // assign the top of the stack to the array
				Finishedorder.pop();// pop the stack to allow for ther next item to be read
				Finishorder[1] = Finishedorder.top();
				Finishedorder.pop();
				Finishorder[2] = Finishedorder.top();
				Finishedorder.pop();
				Finishorder[3] = Finishedorder.top();
				Finishedorder.pop();
			}
			if (Finishorder[1] != 0) // check if the finish order array is empty which if isnt means the game is over
			{
				RenderText(ptrtextShader, "Game Finished! " , 650.0f, 250.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
				RenderText(ptrtextShader, "Player " + to_string(Finishorder[0]) + " was 4th", 650.0f, 420.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));				
				RenderText(ptrtextShader, "Player " + to_string(Finishorder[1]) + " was 3rd", 650.0f, 390.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));			
				RenderText(ptrtextShader, "Player " + to_string(Finishorder[2]) + " was 2nd", 650.0f, 360.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));				
				RenderText(ptrtextShader, "Player " + to_string(Finishorder[3]) + " was 1st!", 650.0f, 330.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));				
				/*
				outputs text
				------------------------------





										Game Finished!
										Player 2 was 4th
										Player 3 was 3rd
										Playr 1 was 2nd
										Player 4 was 1st!




				-------------------------------------
				*/
			}
			drawgameassets(); //Draw the game
		}break;

	}
	
};
void Game::setimagetexture(const char* loadimage)// sets up the image of the snakes and ladders board inspired by learnopengl.com
{
	//texturing	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	unsigned char* image = SOIL_load_image(loadimage, &windowWidth, &WindowHeight, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, WindowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image); // free image since no longer need it 
	glBindTexture(GL_TEXTURE_2D, 0);
};
void Game::setupgamewindow() // sets up the game window code inspired by learnopengl.com
{
	glfwInit(); // initialise glfw library
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	FreeConsole(); // no need for console window 
	 window = glfwCreateWindow(800, 600, "Snakes and Ladders", nullptr, nullptr); // creates the game window 
	

	glfwMakeContextCurrent(window);
	// Set the  callback functions for input
	glfwSetKeyCallback(window, keycall);

	glewExperimental = GL_TRUE; //setting experimental to true allows modern opengl functions to be used
	glewInit();	 // initialises glew library
	glfwGetFramebufferSize(window, &windowWidth, &WindowHeight);
	glViewport(0, 0, windowWidth, WindowHeight);
};
void Game::setupbackgroundimage() // sets up the snakes and ladders game board image code inspired by learnopengl.com

{
	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.3f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // Top Right
		0.3f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // Bottom Left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); // Unbind VAO to allow for new VAO to be assigned

	setimagetexture("images/snakesandladders.jpg"); // Load jpg image snakesandladders and assign it to the texture
};
void Game::setupplayerpiece() // function that intialises the VAO for the triangle that will represent the player piece code inspired by learnopengl.com
{

	GLfloat vertices2[] = {
		-0.5f, -0.5f, 0.0f, // Left  
		0.5f, -0.5f, 0.0f, // Right 
		0.0f, 0.5f, 0.0f  // Top   
	};
	GLuint indices2[] = {  // Note that we start from 0!
		0, 1, 2,   // First Triangle
	};
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO2 as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO2 (it's always a good thing to unbind any buffer/array to prevent strange bugs)
};
void Game::UseInput() // override  of the Useinput function of the control class to suit the game class
{
	switch (states) // check which state the game is in 
	{ 
		case 1: { // state for when game is in the start menu
			#pragma region leftkey
						if (inputkeys[1][1] == true)
						{
							cout << "Left key is pressed" << endl;
							inputkeys[1][1] = false;
						}
						if (inputkeys[1][2] == true)
						{
							cout << "Left key is held" << endl;						
						}
						if (inputkeys[1][3] == true)
						{
							cout << "Left key is released" << endl;
							inputkeys[1][3] = false;
						}
			#pragma endregion  //trigger events to do with leftkey
			#pragma region rightkey
						if (inputkeys[2][1] == true)
						{
							cout << "Right key is pressed" << endl;
							inputkeys[2][1] = false;
						}
						if (inputkeys[2][2] == true)
						{
							cout << "Right key is held" << endl;
						}
						if (inputkeys[2][3] == true)
						{
							cout << "Right key is released" << endl;
							inputkeys[2][3] = false;
						}
			#pragma endregion 
			#pragma region upkey
						if (inputkeys[3][1] == true) // when the up key is pressed decrement the choice value and move the cursor up
						{
							startmenu.choice -= 1;
							if (startmenu.choice < 1) // check that the choice variable is not less than the last option
							{
								startmenu.choice = 1;
							}
							switch (startmenu.choice) // depending on which choice is hovering over move the cursor to that option
							{
							case 1: {
								startmenu.cursorycord = 5;
							}break;
							case 2: {
								startmenu.cursorycord = 0;
							}break;
							case 3: {
								startmenu.cursorycord = -5;
							}break;
							};
							cout << "Up key is pressed" << endl;
							inputkeys[3][1] = false;
						}
						if (inputkeys[3][2] == true)
						{
							cout << "Up key is held" << endl;
						}
						if (inputkeys[3][3] == true)
						{
							
							cout << "Up key is released" << endl;
							inputkeys[3][3] = false;
						}
			#pragma endregion 
			#pragma region downkey
						if (inputkeys[4][1] == true)// when the down key is pressed increment the choice value and move the cursor down
						{
							startmenu.choice += 1;
							if (startmenu.choice >3)// check that the choice variable is not more than the last option
							{
								startmenu.choice = 3;
							}
							switch (startmenu.choice) // depending on which choice is hovering over move the cursor to that option
							{
							case 1: {
								startmenu.cursorycord = 5;
							}break;
							case 2: {
								startmenu.cursorycord = 0;
							}break;
							case 3: {
								startmenu.cursorycord = -5;
							}break;
							};
							cout << "Down key is pressed" << endl;
							inputkeys[4][1] = false;
						}
						if (inputkeys[4][2] == true)
						{
							cout << "Down key is held" << endl;
						}
						if (inputkeys[4][3] == true)
						{
							
							cout << "Down key is released" << endl;
							inputkeys[4][3] = false;
						}
			#pragma endregion 
			#pragma region enterkey
						if (inputkeys[5][1] == true)
						{
							cout << "Enter key is pressed" << endl;
							inputkeys[5][1] = false;
						}
						if (inputkeys[5][2] == true)
						{
							cout << "Enter key is held" << endl;
						}
						if (inputkeys[5][3] == true)
						{
							switch (startmenu.choice) // depending on which option is selceted execute  that bit of code
							{
								case 1: {
									states = 2; // change to the game state
								}break;
								case 2: {
									loadgame(); // checks if the savefile exists and if it does loads the game from there
								}break;
								case 3: {
									glfwSetWindowShouldClose(window, GL_TRUE); // destroys the window which leads to the programme closing
								}break;
							}							
							inputkeys[5][3] = false;
						}
			#pragma endregion
			#pragma region escapekey
						if (inputkeys[6][1] == true)
						{
							cout << "Escape key is pressed" << endl;
							inputkeys[6][1] = false;
						}
						if (inputkeys[6][2] == true)
						{
							cout << "Escape key is held" << endl;
						}
						if (inputkeys[6][3] == true)
						{
							cout << "Escape key is released" << endl;
							inputkeys[6][3] = false;
						}
			#pragma endregion 
		}break;
		case 2: { // state for when the game is playing
			#pragma region leftkey
						if (inputkeys[1][1] == true)
						{
							cout << "Left key is pressed" << endl;
							inputkeys[1][1] = false;
						}
						if (inputkeys[1][2] == true)
						{
							cout << "Left key is held" << endl;
						}
						if (inputkeys[1][3] == true)
						{
							cout << "Left key is released" << endl;
							inputkeys[1][3] = false;
						}
			#pragma endregion  //trigger events to do with leftkey
			#pragma region rightkey

						if (inputkeys[2][1] == true)
						{
							cout << "Right key is pressed" << endl;
							inputkeys[2][1] = false;
						}
						if (inputkeys[2][2] == true)
						{
							cout << "Right key is held" << endl;
						}
						if (inputkeys[2][3] == true)
						{
							cout << "Right key is released" << endl;
							inputkeys[2][3] = false;
						}
			#pragma endregion 
			#pragma region upkey
						if (inputkeys[3][1] == true)
						{
							cout << "Up key is pressed" << endl;
							inputkeys[3][1] = false;
						}
						if (inputkeys[3][2] == true)
						{
							cout << "Up key is held" << endl;
						}
						if (inputkeys[3][3] == true)
						{
							cout << "Up key is released" << endl;
							inputkeys[3][3] = false;
						}
			#pragma endregion 
			#pragma region downkey
						if (inputkeys[4][1] == true)
						{
							cout << "Down key is pressed" << endl;
							inputkeys[4][1] = false;
						}
						if (inputkeys[4][2] == true)
						{
							cout << "Down key is held" << endl;
						}
						if (inputkeys[4][3] == true)
						{
							cout << "Down key is released" << endl;
							inputkeys[4][3] = false;
						}
			#pragma endregion 
			#pragma region enterkey
						if (inputkeys[5][1] == true)
						{
							cout << "Enter key is pressed" << endl;
							inputkeys[5][1] = false;
						}
						if (inputkeys[5][2] == true)
						{
							cout << "Enter key is held" << endl;;
						}
						if (inputkeys[5][3] == true)
						{
							savegame(); // when the user presses enter save the game 
							if (Finishorder[1] == 0) // check if the game is not finished yet
								Players[Playerorder - 1].doturn(&Playerorder, &Finishedorder); // call the player do turn function
							else
							{
								states = 1;
								Playerorder = 1;
								resetgame(0);
								remove("Savefile.txt"); // reset the programme to the point where it was as if the programme was opened for the first time
							}
							inputkeys[5][3] = false;
						}
			#pragma endregion
			#pragma region escapekey
						if (inputkeys[6][1] == true)
						{
							if (Players[Playerorder-1].rolleddice==false) // check if the player is not in the middle of its turn
							{
							states = 1;
							Playerorder = 1;
							resetgame(0);		// reset the game and go back to the start menu
							}
							cout << "Escape key is pressed" << endl;
							inputkeys[6][1] = false;
						}
						if (inputkeys[6][2] == true)
						{
							cout << "Escape key is held" << endl;
						}
						if (inputkeys[6][3] == true)
						{
							cout << "Escape key is released" << endl;
							inputkeys[6][3] = false;
						}
			#pragma endregion 
		}break;		
	}
	
	
};
void Game::drawgameassets() // function that draws  the board and players onto the screen code inspired by example in learnopengl.com
{
		

		ptrSnakesandladdersbackgroundshader->Use(); // use shader
		glBindTexture(GL_TEXTURE_2D, texture); // set texture of board image
		glBindVertexArray(VAO); // bind the VAO for the board image
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw the image (two triangles filled with texture data)
		glBindVertexArray(0); // reset the VAO for the next one
		ptrtriangleshader->Use();
		glBindVertexArray(VAO2);
		int i = 0;
		for (i = 0;i <= 3;i++)
		{

			glm::mat4 transform;
			transform = glm::scale(transform, glm::vec3(0.075, 0.075, 0.75));
			transform = glm::translate(transform, glm::vec3(0.0f + Players[i].xcord, 0.0f + Players[i].ycord, 0.0f));
			GLint transformLoc = glGetUniformLocation(ptrtriangleshader->Program, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);
		
};
void Game::RenderText(Shaders* shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) // Function taken from learnopengl.com and amended to work for my game in particular
{
	// Activate corresponding render state	
	shader->Use();
	glUniform3f(glGetUniformLocation(shader->Program, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO3);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat textvertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO3);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textvertices), textvertices); // Be sure to use glBufferSubData and not glBufferData


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
};
void Game::setuptext() // Function that enables text to be written on the screen taken from learnopengl.com and amended  to work with this game
{
	ptrtextShader = new Shaders("Shaders/textvertex.txt", "Shaders/textfragment.txt");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowWidth), 0.0f, static_cast<GLfloat>(WindowHeight));
	ptrtextShader->Use();
	glUniformMatrix4fv(glGetUniformLocation(ptrtextShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// FreeType
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	
	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texturetext;
		glGenTextures(1, &texturetext);
		glBindTexture(GL_TEXTURE_2D, texturetext);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texturetext,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glBindVertexArray(VAO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
};
void Game::Maingameloop() // function where every frame of the game takes place
{
	ptrtriangleshader=new Shaders("Shaders/vertextriangle.txt", "Shaders/fragmenttriangle.txt"); // initialises the pointers of shaders
	ptrSnakesandladdersbackgroundshader=new Shaders("Shaders/shadervertex.txt", "Shaders/shaderfragment.txt");	
	// set up and link shaders from textfiles 
	

	while (!glfwWindowShouldClose(window))// while the window is not destroyed keep doing this code
	{
		//clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();// check whether keyboard has inputted
		UseInput(); // execute code based on what was inputted
		dostate(); // depending on game state run code to output either the start menu or game 
		
		//	swap buffers always last
		glfwSwapBuffers(window);
	}
};
Game::Game() // constructor call for the game
{		
	states = 1;
	Playerorder = 1;
	srand(time(NULL));
	setupgamewindow();
	setuptext();
	setupbackgroundimage();
	setupplayerpiece();
	// set up the seed for randomness and initialise variables to set up the game
}

Game::~Game() //deconstructor for the game 
{
	delete ptrtriangleshader;
	ptrtriangleshader = NULL;
	delete ptrSnakesandladdersbackgroundshader;
	ptrSnakesandladdersbackgroundshader = NULL;
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate(); // terminate glfw library 
	// free all pointers or variables
}

	#pragma endregion 
 
#pragma endregion  



