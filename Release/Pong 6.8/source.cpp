// pong version 12.01
//Changed menu
#include "graphics.h"
#include<stdio.h>
#include<time.h>/* For Time count */
#include<windows.h> /* for audible sound */

void about();
void background();
void ball_clear();
void ball_create();
void ball_limit_control();
void ball_movement();
void bat_clear();
void bat_create();
void create_menu();
void draw_triangle(int x,int y,int z);  // x,y is the point where the sharp end will be, z+10 is the size of the triangle
void first_page();
void game_over();
void menu();
void pause();
void play();
void score();
void score_card();
void score_check(int n, int p);
void score_menu();
void select_menu(int x , int y);
void settings_menu();
void start_pong();
int timel();
void user_input(int us);
void leaderboard(int n, int p);

/* Screen Controls */

#define screen_top 0  /*top line of the screen.it will always be zero, otherwise we will have to change all co-ordinates*/
int screen_left=75;  /*start of black screen*/
int screen_right=675;  /*end of black screen*/
int screen_bottom=480; /*bottom of black screen*/
int screen_end=screen_right+screen_left;  /* end line of screen...value of screen_end should be a multiple of 6 */
int screen_mid=(screen_end)/2; /*middle of the screen, where the net is */


/* GamePlay Settings */

int high_score=10;//set the highest score
#define D_E 15
#define D_H 10
int SPEED=15; // serve speed
int mode=1; // Mode 1 = Tennis, Mode 2 = Time Challenge
int TIME= 30,x=0,timez=0,timey=1; // Time limit for time challenge, timey - timez =1 means one second has elapsed
time_t start_t, end_t;
char timex[10];

/* Game Basics */

int  bat_speed=90;  /*speed of the BAT can be changed*/
#define bat_size 120   /*size of the BAT can be changed*/
#define bat_width 10
#define bat_pos_left screen_left+50
#define bat_pos_right screen_right-60
int ball_y=screen_bottom/2,ball_x=screen_mid,input_key,left_baty,right_baty,f=1,g,l,r,g_o=0;// all variables are declared here
int ball_radius=8;
int prex=ball_y+20,prey=ball_y+20;
int dev=SPEED,det,de,i,ball_speed_x=7,ball_speed_y=7;	//Ball speed variables.dev=ball Speed(delay),det=lower limit of delay, SPEED = higher limit of delay, ball_speed_x=x axis wise speed,ball_speed_y=y axis wise speed
int bat_pause_y= 0,pausey=0,quit=0,used=0,j[3],elim=0,m=0;//for leaderboard and pause ..here m=number of top scores available,flag sets the controls when we enter the game for the first time 

/*Menu */
#define FONT SANS_SERIF_FONT
#define FONT_SIZE 4
#define GREY COLOR(105,105,105)
#define MENU_C COLOR(240,255,240)
#define score_col WHITE
#define ball_col WHITE
int bat_col=WHITE;
int bat_fill=1;
int menu_x1, menu_x2,menu_x3,menu_y1,menu_y2,menu_ymid,menu_ytop;
int SOUND=55; // Sets the sounds when the ball misses the bat
int score_pos=2,score_back=GREY;
int midx,midy,flag,screen_x=getmaxwidth(),screen_y;
int p1[550],p2[550],dif[5][550]; /* Leaderboard array */
char left_score[3],right_score[3],choice,control_l,l_u,l_d;	//choice decides if the player will continue or not]
//left_up prints the up key for left player & l_u stores the up key for left player
int left_bat_up, left_bat_down,	time_flag=0; // Used for Time-Trial Mode
char top[4][50][100]; /* Generates the Leaderboard */
// value of f & g controls the limit of the motion of ball leftward-rightwards & ups-down respectively
// l & r for the score of left & right side respectively...g_o=1 means game over.
char username[100];
FILE *score_list=fopen("score log.fs","a");

#include"menufunc.h"
#include"scorefunc.h"
#include"gameplay.h"

int main( )
{
	l=0,r=0;
    initwindow(getmaxwidth(), getmaxheight(), "Pong Edition 6.8");
	screen_x=getmaxx();
	screen_y=getmaxy();
	midx = screen_x/ 2;
	midy = screen_y / 2;
	menu_x1=(int)(screen_x/3);
	menu_x2=(int)((2*screen_x)/3);
	menu_x3=screen_x;
	menu_y1=(int)(200+(screen_y-200)/2);
	menu_y2=screen_y;
	menu_ymid=(int) ((screen_y-200)/4);
	menu_ytop=200+ (screen_y-200)/8;
	while(1)
	{
		play();
	}
	system("pause");
    return 0;
}

