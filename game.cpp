//============================================================================
// Name        : game.cpp
// Author      : Asim Ali
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath>
#include <fstream> 
using namespace std;
	float xaxis = 0;//initializing xaxis
	float yaxis = 0;//intaializing yaxis
	int carrow = 2;//start row of my car
	int carcol = 25;//start colmn of my car
	int opprow = 5+rand()%10;//start row of computer car
	int oppcol = 37;//start colmn of computer car
	int score =0;// start score per eating one piece of food
	void getPixel(int row,int col);//function to get pixels of cells
	char array[40][40];//declaration of character array on which my game is based 
	int mymenu=0;//start of my menu
	int lives=3;//lives of car
	int gamepause=0;//variable for pause the game
	int carroad;//roads of car
	int opproad;//roads of opponent car
	void getArenaFood(int row, int col);//function to get food on collision
	int a=1;//increment in speed
	int gamespeed=0;//to double the speed we use it
	int level=1;//variable for levels
	float b=1;//incremenet of spped in opponents
	int opprow2=5+rand()%15;//2nd opponent car rows
	int oppcol2=2;//2nd opponent car colmns
	int opproad2;//roads of 2nd opponent car
	int replay; //replaying game
	int highscore;//storing food

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// calling some functions from util.cpp file to help students

	//Square at 400,20 position
	//DrawSquare(0 , 0 ,840,colors[RED]);
	//DrawString(450, 450,"1. Press (1) to play the game", colore[WHITE]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(400,400,50,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
//------start of menu----------------------------------------------------------------------------------------------------------------------------------
if(mymenu==0)
{
DrawSquare(0 , 0 ,850,colors[BLUE]);
DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
DrawString( 170, 550,"WELCOME TO THE DODGE_EM ATTARI 2600", colors[MISTY_ROSE]);
DrawString( 300, 500,"1.start the game(PRESS 1)", colors[MISTY_ROSE]);
DrawString( 350, 450, "2. Help", colors[MISTY_ROSE]);
DrawString( 300, 400, "3. High Scores", colors[MISTY_ROSE]);
DrawString( 350, 350, "4. Exit (Press (E) to exit)", colors[MISTY_ROSE]);
}
if(mymenu==5)
{
DrawSquare(0 , 0 ,850,colors[BLUE]);
DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
DrawString( 170, 550,"WELCOME TO THE DODGE_EM ATTARI 2600", colors[MISTY_ROSE]);
DrawString( 300, 500,"1.start the game(PRESS 1)", colors[MISTY_ROSE]);
DrawString( 350, 450, "2. Help", colors[MISTY_ROSE]);
DrawString( 300, 400, "3. High Scores", colors[MISTY_ROSE]);
DrawString( 350, 350, "4. Exit (Press (E) to exit)", colors[MISTY_ROSE]);
}
//------taking help -------------------------------------------------------------------------------------------------------------
if(mymenu==2)
{
	DrawSquare(0 , 0 ,840,colors[RED]);
	DrawString( 175, 600,"HELP FOR YOU", colors[YELLOW]);
	DrawString( 175, 550,"1. white car is your car", colors[YELLOW]);
	DrawString( 175, 520,"2. red car is opponent car", colors[YELLOW]);
	DrawString( 175, 490,"3. left arrow key is to move left", colors[YELLOW]);
	DrawString( 175, 460,"4. reight arrow key is to move right", colors[YELLOW]);
	DrawString( 175, 430,"5. up arrow key is to move above", colors[YELLOW]);
	DrawString( 175, 400,"6. Down arrow key is to move down", colors[YELLOW]);
	DrawString( 175, 370,"7. you have to eat every food piece without collsion with red car.", colors[YELLOW]);
	DrawString( 175, 300," PRESS (5) TO GO BACK", colors[YELLOW]);
}
if(mymenu==3)
{
DrawSquare(0 , 0 ,850,colors[BLUE]);
DrawString( 170, 550,"High scores=", colors[MISTY_ROSE]);
DrawString(350, 550,to_string(highscore), colors[MISTY_ROSE]);
}

//-------if user select 1 then game will be start----------------------------------------------------------------------------------------------------
if(mymenu==1||replay==1)
{
	if(level>0&&level<5)
	{
		DrawString( 20, 810,"SCORES==", colors[MISTY_ROSE]);
		DrawString( 150, 810, to_string(score), colors[MISTY_ROSE]);
		DrawString( 190, 810,"Highscore", colors[MISTY_ROSE]);
		DrawString( 320, 810, to_string(highscore), colors[MISTY_ROSE]);
		DrawString( 650, 810,"LIVES===", colors[MISTY_ROSE]);
		DrawString( 770, 810, to_string(lives), colors[MISTY_ROSE]);
		DrawString( 400, 810,"LEVEL==", colors[MISTY_ROSE]);
		DrawString( 520, 810, to_string(level), colors[MISTY_ROSE]);
		int row=0;
		int col=0;
		while(row<40)
		{
			while(col<40)
			{
						if(array[row][col]=='b')
						{
							getPixel(col,row);
							DrawRectangle(xaxis, yaxis,20, 20, colors[GREEN]);
						}
						if(array[row][col]=='w')
						{
							getPixel(col,row);
							DrawRectangle(xaxis, yaxis,22, 22, colors[BROWN]);
						}
					
				col++;
			}
			col=0;
			row++;	
		}
//---------transfer of level ----------------------------------------------------------------------------------------------------		 
if(score==64)
	{
	level=2;
	getArenaFood(row,col);}
if(score==128)
	{
	level=3;
	getArenaFood(row,col);}	
if(score==192)
	{
	level=4;
	getArenaFood(row,col);}		
if(level==3)
{b=1;}	
if(score==256)
{
	DrawSquare(0 , 0 ,850,colors[BLUE]);
	DrawString( 0, 550,"--------------------------------YOU WON-----------------------------", colors[MISTY_ROSE]);
	level=5;
}
	if(lives>0)
	{
	//-------creating my car ..i am doing by square cells by using array that's why i draw a sqaure which will be my car-----------------------------------
		if(score<256)
		{getPixel(carcol,carrow);
		DrawRectangle(xaxis, yaxis,20, 20, colors[WHITE]);}	
	//-------creating opponent/computer car..same like my car but its colour is DIFFERENT------------------------------------------------------------------
		if(score<256)
		{getPixel(oppcol,opprow);
		DrawRectangle(xaxis, yaxis,20, 20, colors[RED]);}
//-------creating 2nd opponent/computer car..same like my car but its colour is DIFFERENT and its collision with own car ------------------------------------------------------------------
		if(score>=192&&score<256)
		{	getPixel(oppcol2,opprow2);
			DrawRectangle(xaxis, yaxis,20, 20, colors[RED]);
			if((carrow==opprow2&&carcol==oppcol2)||(carrow+1==opprow2&&carcol==oppcol2)||(carrow-1==opprow2&&carcol==oppcol2)||(carrow==opprow2&&carcol-1==oppcol2)||(carrow==opprow2&&carcol+1==oppcol2))
			{
				carrow = 2;
				carcol = 25;
				opprow2=5+rand()%15;
				oppcol2=2;
				opprow = 5+rand()%10;
				oppcol = 37;
				lives--;
				if(lives>0)
				{score=192;}
			}
		}
				
		
	//------condition of collision of both cars------------------------------------------------------------------------------------------------------------
		if((carrow==opprow&&carcol==oppcol)||(carrow+1==opprow&&carcol==oppcol)||(carrow-1==opprow&&carcol==oppcol)||(carrow==opprow&&carcol-1==oppcol)||(carrow==opprow&&carcol+1==oppcol))	
					{
						carrow = 2;
						carcol = 20;
						opprow = 2;
						oppcol = 22;
						lives--;
						if(lives>0)
						{
							if(level==1)
							{
							score=0;
							}
							if(level==2)
							{
							score=64;
							}
							if(level==3)
							{
							score=128;
							}
							if(level==4)
							{
							score=192;
							}
						}
						getArenaFood(row,col);
					} 
	//------condition for eating food and increasing score-------------------------------------------------------------------------------------------------
		if(array[carrow][carcol]=='b')
		{
			array[carrow][carcol] = 'e';
			score+=1;
		}
	
		
	}
	//------if player car tryouter wall---------------------------------------------------------------------------------------------------------------
			if(carcol>37)
			{
				carcol=37;
			}
			if(carcol<2)
			{
				carcol=2;
			}
			if(carrow<2)	
			{	
				carrow=2;
			}
			if(carrow>37)
			{
				carrow=37;
			}
//----------------if opponent car try  outer walls-------------------------------------------------------------------------			
			if(oppcol>37)
			{
				oppcol=37;
			}
			if(oppcol<2)
			{
				oppcol=2;
			}
			if(opprow<2)	
			{	
				opprow=2;
			}
			if(opprow>37)
			{
				opprow=37;
			}	
	}
}
//closing condition of playing game-----------------------------------------------------------------------------------------------------------	
if(lives<=0)
	{
		DrawSquare(0 , 0 ,850,colors[BLUE]);
		DrawCircle(400,400,330,colors[RED]);
		DrawString( 170, 600,"GAME OVER!!!!!!!!!!!!!", colors[MISTY_ROSE]);
		DrawString( 350, 500, " press 'R' to replay", colors[MISTY_ROSE]);
		DrawString( 350,550, " press 'v' to check high score", colors[MISTY_ROSE]);
		DrawString( 300, 400, " Scores==", colors[MISTY_ROSE]);
		DrawString( 400, 400, to_string(score), colors[MISTY_ROSE]);
		DrawString( 350, 350, "Exit (Press 'E' to exit)", colors[MISTY_ROSE]);
	}
	
//---------- pausing the game-----------------------------------------------------------------------------------------------------------------------
if((gamepause)%2==1)
	{	
	DrawSquare(0 , 0 ,840,colors[BLUE]);
	DrawCircle(400,400,330,colors[RED]);
	DrawString( 170, 550,"________________paused_____________", colors[MISTY_ROSE]);
	DrawString( 300, 500,"press (p) to resume", colors[MISTY_ROSE]);
	DrawString( 350, 350, " Exit (Press 'E' to exit)", colors[MISTY_ROSE]);
	}
//file handling of highscore----------------------------------------------------------------------------------------------------------	
ifstream i;
		i.open("highscore.txt");
		i>> highscore;
		i.close();
		if(highscore<score)
		{
			highscore=score;}
			ofstream ik;
			ik.open("highscore.txt");
			ik<<highscore;
			ik.close();
			
		
	glutPostRedisplay();

	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
			{
				if(carrow>=19&&carrow<=21)
				{
					carcol-=4;
				}	
			}
	else if (key== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
			{
				if(carrow>=19&&carrow<=21)
				{
				carcol+=4;
				}
			}
	else if (key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
			{
				if(carcol>=19&&carcol<=21)
				{
				carrow+=4;
				}
			}
	else if (key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) 
			{
				if(carcol>=19&&carcol<=21)
				{
				carrow-=4;
				}
			}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == '1')
	{
		mymenu=1;
	}
	if(key=='r'||key=='R')
	{
	replay=1;
	lives=3;
	if(level==1)
	{score=0;}
	if(level==2)
	{score=64;}
	if(level==3)
	{score=128;}
	if(level==4)
	{score=192;}
	mymenu=1;
	}
	if (key == 'e'|| key == 'E') 
	{
		exit(0); // exit the program when 'E' key is pressed.
	}
	if (key == '2')
	{
		mymenu=2;//for help
	}
	if (key == '3')
	{
		mymenu=3;//for high scores
	}
	if (key == '5')
	{
		mymenu=0;// from help back 
	}
	if (key == 'p'|| key == 'P')
	{
		gamepause++;
	}
	if(key==32)
	{
		gamespeed++;
		if(gamespeed%2==1)
		{
		a=a*2;
		}
		else if(gamespeed%2!=1)
		{a=1;}
		
	}
	if(key=='v'||key=='P')
	{
	mymenu=0;
	
	}
	
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
 
void Timer(int m) {

	// implement your functionality here
if(level<5)
{
if(mymenu==1||lives>0)
{
	if((gamepause)%2!=1)
	{	
//-------------------automotion of own car----------------------------------------------------------------------------------------------------	
		if(carcol==2&&carrow>=2&&carrow<37)
		{carrow+=a;
		carroad=1;}
		else if(carcol==37&&carrow>2&&carrow<=37)
		{carrow-=a;
		carroad=1;}
		else if(carcol>=2&&carcol<=37&&carrow==2)
		{carcol-=a;
		carroad=1;}
		else if(carcol>1&&carcol<=37&&carrow==37)
		{carcol+=a;
		carroad=1;}
		
		if(carcol==6&&carrow>5&&carrow<33)
		{carrow+=a;
		carroad=2;}
		else if(carcol==33&&carrow<34&&carrow>6)
		{carrow-=a;
		carroad=2;}
		else if(carcol>5&&carcol<34&&carrow==6)
		{carcol-=a;
		carroad=2;}
		else if(carcol>5&&carcol<34&&carrow==33)
		{carcol+=a;
		carroad=2;}
		
		if(carcol==10&&carrow>9&&carrow<29)
		{carrow+=a;
		carroad=3;}
		else if(carcol==29&&carrow<30&&carrow>10)
		{carrow-=a;
		carroad=3;}
		else if(carcol>9&&carcol<30&&carrow==10)
		{carcol-=a;
		carroad=3;}
		else if(carcol>9&&carcol<30&&carrow==29)
		{carcol+=a;
		carroad=3;}
				
		if(carcol==14&&carrow>13&&carrow<25)
		{carrow+=a;
		carroad=4;}
		else if(carcol==25&&carrow<27&&carrow>14)
		{carrow-=a;
		carroad=4;}
		else if(carcol>13&&carcol<26&&carrow==14)
		{carcol-=a;
		carroad=4;}
		else if(carcol>13&&carcol<26&&carrow==25)
		{carcol+=a;
		carroad=4;} 
//--------auto motion of computer car -----------------------------------------------------------------------------------------------------------------

		if(oppcol==2&&opprow>2&&opprow<=37)
		{opprow-=b;
		opproad=1;}
		else if(oppcol==37&&opprow>=2&&opprow<37)
		{opprow+=b;
		opproad=1;}
		else if(oppcol>1&&oppcol<37&&opprow==2)
		{oppcol+=b;
		opproad=1;}
		else if(oppcol>1&&oppcol<38&&opprow==37)
		{oppcol-=b;
		opproad=1;}
		
		if(oppcol==6&&opprow>6&&opprow<34)
		{opprow-=b;
		opproad=2;}
		else if(oppcol==33&&opprow>=5&&opprow<33)
		{opprow+=b;
		opproad=2;}
		else if(oppcol>=6&&oppcol<33&&opprow==6)
		{oppcol+=b;
		opproad=2;}
		else if(oppcol>5&&oppcol<34&&opprow==33)
		{oppcol-=b;
		opproad=2;}
		
		
		if(oppcol==10&&opprow>10&&opprow<30)
		{opprow-=b;
		opproad=3;}
		else if(oppcol==29&&opprow>=9&&opprow<29)
		{opprow+=b;
		opproad=3;}
		else if(oppcol>=10&&oppcol<29&&opprow==10)
		{oppcol+=b;
		opproad=3;}
		else if(oppcol>10&&oppcol<30&&opprow==29)
		{oppcol-=b;
		opproad=3;}
		
		if(oppcol==14&&opprow>14&&opprow<26)
		{opprow-=b;
		opproad=4;}
		else if(oppcol==25&&opprow>=13&&opprow<25)
		{opprow+=b;
		opproad=4;}
		else if(oppcol>=14&&oppcol<25&&opprow==14)
		{oppcol+=b;
		opproad=4;}
		else if(oppcol>14&&oppcol<26&&opprow==25)
		{oppcol-=b;
		opproad=4;}
//----------------automotion of 2nd opponent car -------------------------------------------------------------------------------------
				
	if(level==4)
	{
		if(oppcol2==2&&opprow2>2&&opprow2<=37)
		{opprow2-=b;
		opproad2=1;}
		else if(oppcol2==37&&opprow2>=2&&opprow2<37)
		{opprow2+=b;
		opproad2=1;}
		else if(oppcol2>1&&oppcol2<37&&opprow2==2)
		{oppcol2+=b;
		opproad2=1;}
		else if(oppcol2>1&&oppcol2<38&&opprow2==37)
		{oppcol2-=b;
		opproad2=1;}
		
		if(oppcol2==6&&opprow2>6&&opprow2<34)
		{opprow2-=b;
		opproad2=2;}
		else if(oppcol2==33&&opprow2>=5&&opprow2<33)
		{opprow2+=b;
		opproad2=2;}
		else if(oppcol2>=6&&oppcol2<33&&opprow2==6)
		{oppcol2+=b;
		opproad2=2;}
		else if(oppcol2>5&&oppcol2<34&&opprow2==33)
		{oppcol2-=b;
		opproad2=2;}
		
		
		if(oppcol2==10&&opprow2>10&&opprow2<30)
		{opprow2-=b;
		opproad2=3;}
		else if(oppcol2==29&&opprow2>=9&&opprow2<29)
		{opprow2+=b;
		opproad2=3;}
		else if(oppcol2>=10&&oppcol2<29&&opprow2==10)
		{oppcol2+=b;
		opproad2=3;}
		else if(oppcol2>10&&oppcol2<30&&opprow2==29)
		{oppcol2-=b;
		opproad2=3;}
		
		if(oppcol2==14&&opprow2>14&&opprow2<26)
		{opprow2-=b;
		opproad2=4;}
		else if(oppcol2==25&&opprow2>=13&&opprow2<25)
		{opprow2+=b;
		opproad2=4;}
		else if(oppcol2>=14&&oppcol2<25&&opprow2==14)
		{oppcol2+=b;
		opproad2=4;}
		else if(oppcol2>14&&oppcol2<26&&opprow2==25)
		{oppcol2-=b;
		opproad2=4;}		
	}			
//------------------AI OF OPPONENT CAR----------------------------------------------------------------------------------------------		
		if(level==1)
		{
			if((carroad==2||carroad==3||carroad==4)&&opproad==1)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>35&&opprow<39)
				{opprow-=4;}
				else if(oppcol>=19&&oppcol<=21&&opprow>1&&opprow<4)
				{opprow+=4;}
			}
			if((carroad==3||carroad==4)&&opproad==2)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>5&&opprow<8)
				{opprow+=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>30&&opprow<35)
				{opprow-=4;}
			}
			if(carroad==4&&opproad==3)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>8&&opprow<12)
				{opprow+=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>27&&opprow<31)
				{opprow-=4;}
			}
			if((carroad==3||carroad==2)&&opproad==4)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>12&&opprow<16)
				{opprow-=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>23&&opprow<27)
				{opprow+=4;}
			}
			if((carroad==2||carroad==1)&&opproad==3)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>8&&opprow<12)
				{opprow-=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>27&&opprow<31)
				{opprow+=4;}
			}
			if(carroad==1&&opproad==2)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>4&&opprow<8)
				{opprow-=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>31&&opprow<35)
				{opprow+=4;}
			}
		}	
		if(level==2||level==3||level==4)
		{
			if((carroad==2||carroad==3||carroad==4)&&opproad==1)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>35&&opprow<39)
				{opprow-=4;}
				else if(oppcol>=19&&oppcol<=21&&opprow>1&&opprow<4)
				{opprow+=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>35&&oppcol<39)
				{oppcol-=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>1&&oppcol<4)
				{oppcol+=4;}
			}
			if((carroad==3||carroad==4)&&opproad==2)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>5&&opprow<8)
				{opprow+=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>30&&opprow<35)
				{opprow-=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>30&&oppcol<35)
				{oppcol-=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>5&&oppcol<8)
				{oppcol+=4;}
			}
			if(carroad==4&&opproad==3)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>8&&opprow<12)
				{opprow+=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>27&&opprow<31)
				{opprow-=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>27&&oppcol<31)
				{oppcol-=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>8&&oppcol<12)
				{oppcol+=4;}
			}
			if((carroad==3||carroad==2)&&opproad==4)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>12&&opprow<16)
				{opprow-=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>23&&opprow<27)
				{opprow+=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>23&&oppcol<27)
				{oppcol+=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>12&&oppcol<16)
				{oppcol-=4;}
			}
			if((carroad==2||carroad==1)&&opproad==3)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>8&&opprow<12)
				{opprow-=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>27&&opprow<31)
				{opprow+=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>27&&oppcol<31)
				{oppcol+=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>8&&oppcol<12)
				{oppcol-=4;}
			}
			if(carroad==1&&opproad==2)
			{
				if(oppcol>=19&&oppcol<=21&&opprow>4&&opprow<8)
				{opprow-=4;}
				if(oppcol>=19&&oppcol<=21&&opprow>31&&opprow<35)
				{opprow+=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>31&&oppcol<35)
				{oppcol+=4;}
				else if(opprow>=19&&opprow<=21&&oppcol>4&&oppcol<8)
				{oppcol-=4;}
			}
		}
//----------------------------------------------------------------------------------
		if(level==4)
		{
			if((carroad==2||carroad==3||carroad==4)&&opproad2==1)
			{
				if(oppcol2>=19&&oppcol2<=21&&opprow2>35&&opprow2<39)
				{opprow2-=4;}
				else if(oppcol2>=19&&oppcol2<=21&&opprow2>1&&opprow2<4)
				{opprow2+=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>35&&oppcol2<39)
				{oppcol2-=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>1&&oppcol2<4)
				{oppcol2+=4;}
			}
			if((carroad==3||carroad==4)&&opproad2==2)
			{
				if(oppcol2>=19&&oppcol2<=21&&opprow2>5&&opprow2<8)
				{opprow2+=4;}
				if(oppcol2>=19&&oppcol2<=21&&opprow2>30&&opprow2<35)
				{opprow2-=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>30&&oppcol2<35)
				{oppcol2-=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>5&&oppcol2<8)
				{oppcol2+=4;}
			}
			if(carroad==4&&opproad2==3)
			{
				if(oppcol2>=19&&oppcol2<=21&&opprow2>8&&opprow2<12)
				{opprow2+=4;}
				if(oppcol2>=19&&oppcol2<=21&&opprow2>27&&opprow2<31)
				{opprow2-=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>27&&oppcol2<31)
				{oppcol2-=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>8&&oppcol2<12)
				{oppcol2+=4;}
			}
			if((carroad==3||carroad==2)&&opproad2==4)
			{
				if(oppcol2>=19&&oppcol2<=21&&opprow2>12&&opprow2<16)
				{opprow2-=4;}
				if(oppcol2>=19&&oppcol2<=21&&opprow2>23&&opprow2<27)
				{opprow2+=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>23&&oppcol2<27)
				{oppcol2+=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>12&&oppcol2<16)
				{oppcol2-=4;}
			}
			if((carroad==2||carroad==1)&&opproad2==3)
			{
				if(oppcol2>=19&&oppcol2<=21&&opprow2>8&&opprow2<12)
				{opprow2-=4;}
				if(oppcol2>=19&&oppcol2<=21&&opprow2>27&&opprow2<31)
				{opprow2+=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>27&&oppcol2<31)
				{oppcol2+=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>8&&oppcol2<12)
				{oppcol2-=4;}
			}
			if(carroad==1&&opproad2==2)
			{
				if(oppcol2>=19&&oppcol2<=21&&opprow2>4&&opprow2<8)
				{opprow2-=4;}
				if(oppcol2>=19&&oppcol2<=21&&opprow2>31&&opprow2<35)
				{opprow2+=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>31&&oppcol2<35)
				{oppcol2+=4;}
				else if(opprow2>=19&&opprow2<=21&&oppcol2>4&&oppcol2<8)
				{oppcol2-=4;}
			}
		}			
			
	}
}

}	
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0/FPS+50, Timer, 0);

}
/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
void getPixel(int row,int col)//function that will take rows and colmns from loop and basically impliments the oixels
{
	xaxis = 0;
	yaxis = 0;
	xaxis=row*20;
	yaxis=col*20;
}
void getArenaFood(int row, int col)
{
	row = 0;
	col = 0;
	while (row<40)
	{
		while(col<40)
		{
			if(row==0||col==0||row==39||col==39)
			{
				array[row][col] = 'w';
			}
			if((row>=4&&row<19)||(row>21&&row<=35)){
				if(col==4 || col==35)
				{
					array[row][col] = 'w';
				}
			}
			if(row==4||row==35)
			{
				if((col>=4&&col<19)||(col>21&&col<=35))   
				{
					array[row][col] = 'w';
				}
			}
			if((row>=8&&row<19)||(row>21&&row<=31)){
				if(col==8 || col==31)
				{
					array[row][col] = 'w';
				}
			}
			if(row==8||row==31)
			{
				if((col>=8&&col<19)||(col>21&&col<=31))   
				{
					array[row][col] = 'w';
				}
			}
			
			if((row>=12&&row<19)||(row>21&&row<=27)){
				if(col==12|| col==27)
				{
					array[row][col] = 'w';
				}
			}
			if(row==12||row==27)
			{
				if((col>=12&&col<19)||(col>21&&col<=27))   
				{
					array[row][col] = 'w';
				}
			}
			
			if(row>=16&&row<=23){
				if(col==16|| col==23)
				{
					array[row][col] = 'w';
				}
			}
			if(row==16||row==23)
			{
				if(col>15&&col<24)   
				{
					array[row][col] = 'w';
				}
			}
		
		if(row==2)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==6)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==10)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==14)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==25)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==29)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==33)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==37)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			} 
			col++;		
		}
		col = 0;
		row++;
	}
	
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	int row = 0;
	int col = 0;
	while (row<40)
	{
		while(col<40)
		{
			array[row][col] = 'e';//for empty space
			col++;
		}
		col = 0;
		row++;	
	}
	row = 0;
	col = 0;
	while (row<40)
	{
		while(col<40)
		{
//----------------conditions for making walls of arena-------------------------------------------------------------------------------------------------
			if(row==0||col==0||row==39||col==39)
			{
				array[row][col] = 'w';
			}
			if((row>=4&&row<19)||(row>21&&row<=35)){
				if(col==4 || col==35)
				{
					array[row][col] = 'w';
				}
			}
			if(row==4||row==35)
			{
				if((col>=4&&col<19)||(col>21&&col<=35))   
				{
					array[row][col] = 'w';
				}
			}
			if((row>=8&&row<19)||(row>21&&row<=31)){
				if(col==8 || col==31)
				{
					array[row][col] = 'w';
				}
			}
			if(row==8||row==31)
			{
				if((col>=8&&col<19)||(col>21&&col<=31))   
				{
					array[row][col] = 'w';
				}
			}
			
			if((row>=12&&row<19)||(row>21&&row<=27)){
				if(col==12|| col==27)
				{
					array[row][col] = 'w';
				}
			}
			if(row==12||row==27)
			{
				if((col>=12&&col<19)||(col>21&&col<=27))   
				{
					array[row][col] = 'w';
				}
			}
			
			if(row>=16&&row<=23){
				if(col==16|| col==23)
				{
					array[row][col] = 'w';
				}
			}
			if(row==16||row==23)
			{
				if(col>15&&col<24)   
				{
					array[row][col] = 'w';
				}
			}
//----------------------conditions for making food-----------------------------------------------------------------------------------------------------
			if(row==2)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==6)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==10)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==14)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==25)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==29)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==33)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			}
			if(row==37)
			{
				if(col==2||col==6||col==10||col==14||col==25||col==29||col==33||col==37)
				{
					array[row][col] = 'b';
				}
			} 
			col++;		
		}
		col = 0;
		row++;
	}
	//b = new Board(60, 60); // create a new board object to use in the ;Display Function ...

	int width = 840, height = 840; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Dodge_Em"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse


	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
