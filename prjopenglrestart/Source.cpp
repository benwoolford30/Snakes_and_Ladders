#include "snakesandladderslibrary.h" // reference to main game header file

// declaration of functions title






Game SnakesandLadders; // only variable the game needs

int main()
{	
	SnakesandLadders.Maingameloop(); // calls the main game loop and once it ends the game closes
	return 0;
}

// functions are laid out at the bottom of the page in c++



void keycall(GLFWwindow* window, int key, int scancode, int action, int mode) 
/*
	
	For some reason or other it was impossible to set this function in the game class and GLFW would accept it 
	as the key call back function for input as a result Ive been forced to resort to having the function here
	and reference the global variable in the function to enable input in this game. 
*/ 
{

	if (action == GLFW_PRESS)
	{
		switch (key)
		{

		case 263: case 65: {//left arrow

			SnakesandLadders.setInput(true, 1, 2); // set the left arrow pressed value to true
		
		}break;
		case 262:case 68: {//right arrow
			SnakesandLadders.setInput(true, 2, 2);
		
		}break;
		case 265: case 87: {//up arrow
			SnakesandLadders.setInput(true, 3, 1);
		}break;
		case 264: case 83: {//down arrow
			SnakesandLadders.setInput(true, 4, 1);
		}break;
		case 257: {//Enter key 
		
			
		}break;
		}
	}
	if (action == GLFW_RELEASE)
	{
		switch (key)
		{

		case 263: case 65: {//left arrow
			SnakesandLadders.setInput(false, 1, 2);
			
		}break;
		case 262:case 68: {//right arrow
			SnakesandLadders.setInput(false, 2, 2);
		
		}break;
		case 265: case 87: {//up arrow
	
		}break;
		case 264: case 83: {//down arrow

		}break;
		case 257: {//Enter key 
			SnakesandLadders.setInput(true, 5,3);
		}break;
		}
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		SnakesandLadders.setInput(true, 6, 1);
	}
}
