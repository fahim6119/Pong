// pong version 11.06
//Added Menu, only Game Mode option doesn't work
#include "graphics.h"
#include<stdio.h>
#include<time.h>/* For Time count */
#include<windows.h> /* for audible sound */
#include<math.h> /* For Time printing */
void first_page();
void start_pong();
void menu();
void select_menu(int x , int y);
void create_menu();
void score_check(int n, int p);
void score_menu();
void about();
void settings_menu();
void score_card();
void hexagon(int x, int y);
void last_page();
void game_mode();
int time();
void draw_triangle(int x,int y,int z); // x,y is the point where the sharp end will be, z+10 is the size of the triangle
int  bat_speed=120;  /*speed of the BAT can be changed*/
#define bat_size 120   /*size of the BAT can be changed*/
#define bat_width 10
#define bat_pos_left screen_left+50
#define bat_pos_right screen_right-60
#define ball_size_x 10
#define ball_size_y 30 // for rectangular ball
#define ball_speed_x 20
#define ball_speed_y 40
#define screen_top 0  /*top line of the screen.it will always be zero, otherwise we will have to change all co-ordinates*/
#define screen_left 75  /*start of black screen*/
#define screen_right 675  /*end of black screen*/
#define screen_bottom 450 /*bottom of black screen*/
#define screen_end screen_right+screen_left  /* end line of screen...value of screen_end should be a multiple of 6 */
int high_score=3;//set the highest score
#define FONT SANS_SERIF_FONT
#define FONT_SIZE 4
#define D_E 35
#define D_H 20
#define SPEED 50 // serve speed
#define GREY COLOR(105,105,105)
#define MENU_C COLOR(240,255,240)
#define menu_x1 250
#define menu_x2 500
#define menu_x3 screen_end 
#define	menu_y1 225
#define	menu_y2 screen_bottom

int vs=0;//vs= 0 means Double player, vs =1 means single player
int mode=3; // Mode 1 = Survival, Mode 2 = Time Challenge 3 = Table Tennis, Mode 4 - Single Player, Mode 5 - Double Player
int SOUND=55; // Sets the sounds when the ball misses the bat
int ctr=0;// Decides if first part of the first_page() function works
int score_pos=2,score_back=GREY,score_col=WHITE;
int TIME= 30,x=0; // Time limit for time challenge
time_t start_t, end_t;
char timex[10];
int midx,midy,m,flag;//m=number of top scores available,flag sets the controls when we enter the game for the first time 
int p1[550],p2[550],dif[5][550];
int screen_mid=(screen_end)/2; // #define screen_mid screen_end/2 /*middle of the screen, where the net is */
int ball_y=300,ball_x=600,input_key,left_baty,right_baty,f,g,l,r,g_o=0,dev=SPEED,det,i,de,t;	// all variables are declared here
// value of f & g controls the limit of the motion of ball leftward-rightwards & ups-down respectively
// l & r for the score of left & right side respectively...g_o=1 means game over.
char left_score[3],right_score[3],choice,control_l,l_u,l_d,left_up[10],left_down[10];	//choice decides if the player will continue or not]
//left_up prints the up key for left player & l_u stores the up key for left player
int left_bat_up, left_bat_down,	time_flag=0; // Used for Time-Trial Mode
char top[50][10];
FILE *score_list=fopen("score log.txt","a");

void background()
{
	setfillstyle(SOLID_FILL,BLACK);
	bar(0,0,screen_end,screen_bottom);
    setfillstyle(SOLID_FILL,score_back);
    bar(0,screen_top,screen_left,screen_bottom);
    bar(screen_right,screen_top,screen_end,screen_bottom); 
}

void bat_create()
{
    if(kbhit())				//takes input for moving Bats
    {
       input_key=getch();
       if(input_key==left_bat_up && left_baty-bat_size>=0)
	        left_baty-=bat_speed;							//changing the postion of left bat
	   else if(input_key==left_bat_up && left_baty-bat_size<0)
	        left_baty=0;
	   else if(input_key==left_bat_down && left_baty+bat_size+bat_speed>screen_bottom)
			left_baty=screen_bottom-bat_size;
	   else if(input_key==left_bat_down && left_baty+bat_size<=screen_bottom) //screen limit =700, so last end of bat has to be inside 580 
			left_baty+=bat_speed;

    }
	if(ismouseclick(WM_MOUSEMOVE))
		right_baty=mousey();
	if(right_baty>=screen_bottom-bat_size)
		right_baty=screen_bottom-bat_size;
	setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
	bar(bat_pos_left,left_baty,bat_pos_left+bat_width,left_baty+bat_size); 
	bar(bat_pos_right,right_baty,bat_pos_right+bat_width,right_baty+bat_size);
}

void bat_clear() // removed only the bat, didn't remove the extra area [previous version removed area of 20, this one removes 10]
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    bar(bat_pos_left, screen_top, bat_pos_left+bat_width, left_baty);
    bar(bat_pos_left, left_baty+bat_size, bat_pos_left+bat_width, screen_bottom);
    bar(bat_pos_right, screen_top, bat_pos_right+bat_width, right_baty);
    bar(bat_pos_right, right_baty+bat_size,bat_pos_right+bat_width, screen_bottom);
}

void ball_create()
{
	 if(f==0)
    {
        setcolor(WHITE);
        setfillstyle(SOLID_FILL,WHITE);
        bar(ball_x, ball_y, ball_x+ball_size_x, ball_y+ball_size_y);
    }

    else
    {
        setcolor(WHITE);
        setfillstyle(SOLID_FILL,WHITE);
        bar(ball_x,ball_y,ball_x-ball_size_x,ball_y+ball_size_y);
    } 
}

void ball_movement()
{
    if(f==0)				// if f=0, BALL moves leftward and vice-versa
        ball_x-=ball_speed_x;			// the values of ball_x & ball_y controls the SPEED & DIRECTION of the BALL along x & y-axis respectively
    else if(f==1)
        ball_x+=ball_speed_x;
    if(g==0)				//if g=0, BALL moves upward and vice-versa
        ball_y-=ball_speed_y;
    else if(g==1)
        ball_y+=ball_speed_y;
	ball_create();
}


void ball_clear()
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
	if(f==0)
        bar(ball_x, ball_y, ball_x+ball_size_x+2, ball_y+ball_size_y);
    else
        bar(ball_x, ball_y, ball_x-ball_size_x-2, ball_y+ball_size_y);
}
void ball_limit_control()
{

    if( ball_x +ball_size_x >= bat_pos_left && ball_x <= bat_pos_left+bat_width  && ball_y <= left_baty + bat_size && ball_y + ball_size_y >= left_baty)	
        {
			if(ball_x-bat_width/2 >= bat_pos_left)
			f=1;       //ball touches the left bat & direction of the ball is changed to rightward.

			if(ball_y<=left_baty && g==1)
						g=0;
			else if(ball_y+ball_size_y>= left_baty + bat_size && g==0)
						g=1;

			if(ball_y<left_baty || (ball_y+ball_size_y)> (left_baty + bat_size))
				if(dev>det)
					dev-=20;
			else if(ball_y<=(bat_pos_left+(bat_size/2)-20) && ball_y>=(bat_pos_left+(bat_size/2)))
				if(de<SPEED)
					dev+=10;
		}
    else if(ball_x+ ball_size_x>= bat_pos_right && ball_x <= bat_pos_right+bat_width && ball_y+ball_size_y >= right_baty && ball_y <= right_baty +bat_size)
        {
			if(ball_x+ball_size_x<=bat_pos_right+bat_size/2)
			f=0;
			if(ball_y<=right_baty && g==1)
					g=0;
			else if(ball_y+ball_size_y>= right_baty + bat_size && g==0)
					g=1;
			if(ball_y<right_baty || (ball_y+ball_size_y)> (right_baty + bat_size))
				if(dev>det)
					dev-=20;
			else if(ball_y<=(bat_pos_right+(bat_size/2)-20) && ball_y>=(bat_pos_right+(bat_size/2)))
				if(dev<SPEED)
					dev+=5;
		}
    else if(ball_x <= bat_pos_left-20)	
    {									// BALL misses the left bat
        f=0;
		dev=SPEED;
        ball_x=screen_mid;						// BALL starts again from the mid position 
        r++;							// one score is added to the right side
		if(SOUND!=0)
			Beep(SOUND+25,500);
		else 
			delay(500);
    }
    else if(ball_x>=bat_pos_right+bat_width+20)
    {									//similarly BALL misses the right bat...
        f=1;
		dev=SPEED;
        ball_x=screen_mid;
        l++;
		if(SOUND!=0)
			Beep(SOUND,500);
		else 
			delay(500);
    }
	 
	if(ball_y<=screen_top)										
		{
				g=1; // if BALL touches the upper bound of window, direction is changed to downward
				if(dev>=det+5)
					dev-=5;
		}
    else if(ball_y+ball_size_y>=screen_bottom)
		{
				g=0;
				if(dev>=det+5)
					dev-=5;
		}
}


void score()
{
    sprintf(left_score, "%d", l);
    sprintf(right_score, "%d", r);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setbkcolor(score_back);
    setcolor(score_col);
    settextstyle(FONT,HORIZ_DIR,5);
	if(score_pos==1) /*score at top */
	{
		outtextxy(screen_left/2,100,left_score);
		outtextxy(screen_end-(screen_left/2),100,right_score);
	}
	else if(score_pos==2) /* score at middle */
	{
		outtextxy(screen_left/2,350,left_score);
		outtextxy(screen_end-(screen_left/2),350,right_score);
	}

	else if(score_pos==3) /* score at bottom */
	{
		outtextxy(screen_left/2,650,left_score);
		outtextxy(screen_end-(screen_left/2),650,right_score);
	}
}

void game_over()
{
    if(l>r)				//limit of score
    {
	settextjustify(RIGHT_TEXT,CENTER_TEXT);
	setbkcolor(BLACK);
        setcolor(COLOR(30,144,255));
        settextstyle(FONT,HORIZ_DIR,5);
        outtextxy(screen_mid -30,300,"WIN");
    }
    else if(r>l)
    {
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	setbkcolor(BLACK);
        setcolor(COLOR(30,144,255));
        settextstyle(FONT,HORIZ_DIR,5);
        outtextxy(screen_mid +30,300,"WIN");
    }
	else if(l==r)
	{
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		setbkcolor(BLACK);
        setcolor(COLOR(30,144,255));
        settextstyle(FONT,HORIZ_DIR,5);
        outtextxy(screen_mid,300,"TIE");
	}
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	fprintf(score_list," %d %d \n",l,r);
	g_o=1;
    delay(1000);						// delay after WIN
    l=r=0;							// score 0-0
	last_page();
}

void last_page()
{
	int x,y;
	start_pong();
	
	int color=COLOR(255,215,0) ;
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	hexagon(84,350); //hexagon length 195, height 120
	hexagon(363,350);
	hexagon(642,350);
	hexagon(921,350);
	setbkcolor(color);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(COLOR(122,19,215));
    settextstyle(FONT,HORIZ_DIR,3);
    outtextxy(184,357,"MAIN MENU");
	outtextxy(463,357,"PLAY AGAIN");
	outtextxy(742,357,"GAME MODE");
	outtextxy(1021,357,"EXIT");

	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>0 && x< 300 && y>300 && y< 500)
		choice=1;
	else if (x>300 && x< 600 && y>300 && y< 500)
		choice=2;
	else if(x>600 && x< 900 && y>300 && y< 500)
	{
		choice=3;
	}
	else if(x>900 && x< 1200 && y>300 && y< 500)
	{
		fclose(score_list);
		cleardevice();
		exit(0);
	}
	else
		choice=4;
}

void difficulty()
{
	int x,y;
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(menu_x1+5,205,menu_x2,450); 
	setcolor(font);
	setfillstyle(SOLID_FILL,GREY);
	bar(menu_x1,325,menu_x2,330);//The barrier
	setbkcolor(bk);
	setcolor(font);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x1+menu_x1/2,265,"EASY"); 
	outtextxy(menu_x1+menu_x1/2,395,"HARD"); 
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);
	if((x>menu_x1 && x<menu_x2) && (y>200 && y<325))//Easy
		det=D_E;
	else if((x>menu_x1 && x<menu_x2) && (y>325 && y<450)) //Hard
		det=D_H;
	menu();
}

void score_check(int n, int p)
{
	m=0;
	char l[1000];
	int i,j,k,max,maxi;
	fclose(score_list);
	score_list=fopen("score log.txt","r");
	fseek(score_list,0L,0);
	for(i=0;;i++)
	{
		fscanf(score_list,"%d %d",&p2[i],&p1[i]);//p2 = left, p1=right
		dif[1][i]=p1[i]-p2[i];
		dif[2][i]=p2[i]-p1[i];
		if(feof(score_list))
		{
			break;
		}
	}
	for(k=0;k<i;k++)
	{
		max=-100;
		for(j=0;j<i;j++)
		{
			if(dif[p][j]>max)
			{
				max=dif[p][j];
				maxi=j;
			}	
		}
		if(p==1)
			sprintf(top[m++],"%d - %d",p1[maxi],p2[maxi]);
		else if (p==2)
			sprintf(top[m++],"%d - %d",p2[maxi],p1[maxi]);
		dif[p][maxi]=-105;
    }
	if(i<n)
	{
		if(i==0)
			sprintf(top[m++],"Sorry, But you never played with us");
		else
			sprintf(top[m++],"Sorry you played only %d times",i);
	}
	fclose(score_list);

	score_list=fopen("score log.txt","a");
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(menu_x2+5,205,menu_x3,screen_end-5); 
	setbkcolor(bk);
	setcolor(font);
	settextstyle(FONT,HORIZ_DIR,3);
	sprintf(l,"Best %d Results for Player %d",n,p);
	outtextxy(menu_x2+menu_x1/2,185,l); 
	for(j=0;j<n && j<m;j++)
	{
		outtextxy(menu_x2+menu_x1/2,240+(440/n)*(j),top[j]); 
	}
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	menu();
} 

void score_menu()
{
	int x,y,n,p;
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_end,screen_bottom);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(font);
    settextstyle(BOLD_FONT,HORIZ_DIR,8);
    outtextxy(screen_mid,100,"HIGH SCORES");
	setfillstyle(SOLID_FILL,GREY);
	bar(0,150,screen_end,155);
	bar(0,200,screen_end,205);
	bar(0,450,screen_end,455);
	bar(0,screen_bottom-5,screen_end,screen_bottom);
	bar(menu_x1,150,menu_x1+5,screen_bottom);
	bar(menu_x2,150,menu_x2+5,screen_bottom);
	setcolor(font);
	setbkcolor(bk);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x1/2,185,"Select Player");
	outtextxy(menu_x1/2,325,"Player 1");
	outtextxy(menu_x1/2,575,"Player 2");

	player_select:
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>0 && x<menu_x1 && y>200  && y<450)
		p=1;
	else if (x>0 && x<menu_x1 && y>450 && y<screen_end)
		p=2;
	else 
		goto player_select;

	outtextxy(menu_x1+(menu_x1)/2,185,"Number of Records");
	outtextxy(menu_x1+(menu_x1)/2,325,"5");
	outtextxy(menu_x1+(menu_x1)/2,575,"10");
	
	record_select:
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>menu_x1 && y>200 && x<menu_x2 && y< 450)
		n=5;
	else if (x>menu_x1 && y>450 && x<menu_x2 && y<screen_end)
		n=10;
	else
		goto record_select;
	score_check(n,p);
}

int main( )
{
    initwindow(screen_end, screen_bottom, "Pong Edition 2014");
	begin:
	if(screen_right-screen_left>1150)
		det=D_H;
	else
		det=D_E;
	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	first_page();
	delay(1000);
	cleardevice();
	setbkcolor(BLACK);
    background();
	time(&start_t);

	while(1)
    {	
		setcolor(WHITE);
		setlinestyle(DASHED_LINE,3,1);
		line(screen_mid,screen_top,screen_mid,screen_bottom);

		t=dev/10;
		de=dev/t;

		ball_movement(); //movement of ball
		bat_create();
		bat_clear();
		delay(de);

		i=t;		
		while(i-1)   // movement of bat  
		{
			bat_create();
			if(i==t/2)
			ball_create();
			bat_clear();

			if(ball_x+ball_size_x > bat_pos_left && ball_x < bat_pos_left+bat_width ||ball_x+ball_size_x > bat_pos_right && ball_x < bat_pos_right+bat_width)
					break;
			delay(de);
			i--;
		}

		ball_create();

        ball_clear();

		ball_limit_control();

		score();

		if(l==high_score || r==high_score)
			game_over();
		else if(mode==2)
		{
			time();
			time_t timer=end_t-start_t;
			if(time()+1==0)
			{
				game_over();
			}
			else if(x==timer)
			{
				sprintf(timex,"%d",TIME-x);
				x++;
				if(score_pos==2) /* score at middle,so timer at bottom */
				{
					setcolor(score_back);
					setfillstyle(SOLID_FILL,score_back);
					bar(0,screen_bottom-100,screen_left,screen_bottom);
					bar(screen_right,screen_bottom-100,screen_end,screen_bottom); 
					setbkcolor(score_back);
					settextjustify(CENTER_TEXT, CENTER_TEXT);
					setcolor(COLOR(255,165,0));
					settextstyle(3,HORIZ_DIR,6);
					outtextxy(screen_left/2,650,timex);
					outtextxy(screen_end-(screen_left/2),650,timex);
				}
				else /* score not at middle  , so timer at Middle */
				{
					setcolor(score_back);
					setfillstyle(SOLID_FILL,score_back);
					bar(0,300,screen_left,400);
					bar(screen_right,300,screen_end,400); 
					setbkcolor(score_back);
					settextjustify(CENTER_TEXT, CENTER_TEXT);
					setcolor(COLOR(255,165,0));
					settextstyle(3,HORIZ_DIR,6);
					outtextxy(screen_left/2,350,timex);
					outtextxy(screen_end-(screen_left/2),350,timex);
				}
				settextjustify(CENTER_TEXT, CENTER_TEXT);
			}
		}
		if(g_o==1)
		{
			x=0;
			time(&start_t);
			if(choice==1)
			{
				g_o=0;
				menu();
				cleardevice();
				setbkcolor(BLACK);
				background();
			}
			else if(choice==2)
			{	
				cleardevice();
				g_o=0;
				setbkcolor(BLACK);
				background();
			}

			else if(choice==3)
			{	
				g_o=0;
				game_mode();
				cleardevice();
				setbkcolor(BLACK);
				background();
			}

			else if(choice==4)
			{	
				cleardevice();
				g_o=0;
				goto begin;
			}
		}
    }
    return 0;
}

void menu()
{
	int x=0, y=0;
	create_menu();
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);
	select_menu(x,y);
} 

void first_page()
{
	int x,y;
	if(ctr==1)
	{
		ctr=0;
		control_l=2;
	}
	else
	{
		start_pong();
		draw_triangle(screen_left/2,315,5);
		draw_triangle(screen_left/2,375,5);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(screen_left,300,"Use the mouse for Right Bat Control");
		outtextxy(screen_left,360,"Use 'UP' & 'DOWN' key for Left Bat Control");

		int color=COLOR(210,231,3);
		setcolor(color);
		setfillstyle(SOLID_FILL,color);
		hexagon(100,500); //hexagon length 195, height 120
		hexagon(500,500);
		hexagon(900,500);
		setbkcolor(color);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,3);
		outtextxy(200,507,"MENU");
		outtextxy(600,507,"PLAY");
		outtextxy(1000,507,"CONTROL");

		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if(x>200 && x< 500 && y>400 && y< 650)
			control_l=1;
		else if (x>800 && x< 1100 && y>400 && y< 650)
			control_l=2;
		else 
			control_l=3;
	}
	if(control_l==1)
	{
		menu();
	}
	else if(control_l==2)
	{
		cleardevice();
		start_pong();
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(100,300,"Choose a key to move left bat upwards");
		left_bat_up=getch();
		left_up[0]=left_bat_up;
		left_up[1]=0;
		if(left_bat_up==32)
			outtextxy(900,300,"Space Bar");
		else
			outtextxy(900,300,left_up);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(100,400,"Choose a key to move left bat downwards");
		left_bat_down=getch();
		left_down[0]=left_bat_down;
		left_down[1]=0;
		if(left_bat_down==32)
			outtextxy(900,400,"Space Bar");
		else
			outtextxy(900,400,left_down);
		delay(400);
	}
	setbkcolor(BLACK);
}

void settings_menu()
{
	int x,y;
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_end,screen_bottom);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(font);
    settextstyle(BOLD_FONT,HORIZ_DIR,10);
    outtextxy(midx,150,"SETTINGS");
	setfillstyle(SOLID_FILL,GREY);
	bar(0,200,screen_end,205);
	bar(0,450,screen_end,455);
	bar(0,screen_bottom-5,screen_end,screen_bottom);
	bar(menu_x1,200,menu_x1+5,screen_bottom);
	bar(menu_x2,200,menu_x2+5,screen_bottom);
	setcolor(font);
	setbkcolor(bk);
	settextstyle(FONT,HORIZ_DIR,3);

	outtextxy(menu_x1/2,325,"GAME POINT");
	outtextxy(menu_x1+menu_x1/2,325,"SOUNDS");
	outtextxy(menu_x2+menu_x1/2,325,"BAT SPEED");
	outtextxy(menu_x1/2,575,"CONTROLS");
	outtextxy(menu_x1+menu_x1/2,575,"SCORECARD VIEW");
	outtextxy(menu_x2+menu_x1/2,575,"BACK");
	
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	/* Game Point Menu */
	if((x>0 && x<menu_x1) && (y>200 && y<450))
	{
		printf("GAME POINT\n");
		setfillstyle(SOLID_FILL,bk);
		bar(0,205,menu_x1,450); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(0,325,menu_x1,330);//The barrier
		bar(menu_x1/2,200,menu_x1/2 + 5,450);
		setbkcolor(bk);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(menu_x1/4,265,"5"); 
		outtextxy(menu_x1-menu_x1/4,265,"10"); 
		outtextxy(menu_x1/4,395,"15"); 
		outtextxy(menu_x1-menu_x1/4,395,"20"); 
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if((x>0 && x<menu_x1/2) && (y>200 && y<325))/* Game Point 5 */
			high_score=5;
		else if((x>0 && x<menu_x1/2) && (y>325 && y<450))/* Game Point 15 */
			high_score=15;
		else if((x>menu_x1/2 && x<menu_x1) && (y>200 && y<325)) /* Game Point 10 */
			high_score=10;
		else if((x>menu_x1/2 && x<menu_x1) && (y>325 && y<450))/* Game Point 20 */
			high_score=20;
		settings_menu();
	}
	else if((x>menu_x1 && x<menu_x2) && (y>200 && y<450))
	{
		printf("SOUNDS\n");
		setfillstyle(SOLID_FILL,bk);
		bar(menu_x1+5,205,menu_x2,450); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(menu_x1,325,menu_x2,330);//The barrier
		bar(menu_x1+menu_x1/2,200,menu_x1+menu_x1/2+5,450);
		setbkcolor(bk);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,3);
		outtextxy(menu_x1+menu_x1/4,265,"MUTE"); 
		outtextxy(menu_x2-menu_x1/4,265,"SOUND 1"); 
		outtextxy(menu_x1+menu_x1/4,395,"SOUND 2"); 
		outtextxy(menu_x2-menu_x1/4,395,"SOUND 3"); 
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if((x>menu_x1 && x<menu_x1+menu_x1/2) && (y>200 && y<325))/*MUTE*/
			SOUND=0;
		else if((x>menu_x1 && x<menu_x1+menu_x1/2) && (y>325 && y<450))/*SOUND 1*/
			SOUND=55;
		else if((x>menu_x1+menu_x1/2 && x<menu_x2) && (y>200 && y<325)) /*SOUND 2*/
			SOUND=85;
		else if((x>menu_x1+menu_x1/2 && x<menu_x2) && (y>325 && y<450))/*SOUND 3*/
			SOUND=150; 
		settings_menu();
	}
	else if((x>menu_x2 && x<screen_end) && (y>200 && y<450))
	{
		printf("BAT SPEED\n");
		setfillstyle(SOLID_FILL,bk);
		bar(menu_x2+5,205,menu_x3,450); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(menu_x2,325,menu_x3,330);//The barrier
		bar(menu_x2+menu_x1/2,200,menu_x2+menu_x1/2+5,450);
		setbkcolor(bk);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,3);
		outtextxy(menu_x2+menu_x1/4,265,"1x"); 
		outtextxy(menu_x3-menu_x1/4,265,"1.2x"); 
		outtextxy(menu_x2+menu_x1/4,395,"1.4x"); 
		outtextxy(menu_x3-menu_x1/4,395,"1.75x"); 

		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if((x>menu_x2 && x<menu_x2+menu_x1/2) && (y>200 && y<325))/*batspeed 100 */
			bat_speed=100;
		else if((x>menu_x2 && x<menu_x2+menu_x1/2) && (y>325 && y<450))/*batspeed 140 seconds*/
			bat_speed=140;
		else if((x>menu_x2+menu_x1/2 && x<menu_x3) && (y>200 && y<325)) /* batspeed 120 seconds */
			bat_speed=120;
		else if((x>menu_x2+menu_x1/2 && x<menu_x3) && (y>325 && y<450))/*batspeed 175 seconds */
			bat_speed=175;
		settings_menu();
	}
	else if((x>0 && x<menu_x1) && (y>450 && y<screen_bottom))
	{
		printf("CONTROLS\n");
		ctr=1;
		first_page();
		settings_menu();
	}
	else if((x>menu_x1 && x<menu_x2) && (y>450 && y<screen_bottom))
	{
		printf("SCORECARD VIEW\n");
		score_card();
		settings_menu();
	}
	else if((x>menu_x2 && x<menu_x3) && (y>450 && y<screen_bottom))
	{
		printf("BACK\n");
		menu();
	}
}
void start_pong()
{
	int bk= COLOR(255,255,240);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_end,screen_bottom);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(COLOR(255,165,0));
    settextstyle(BOLD_FONT,HORIZ_DIR,10);
    outtextxy(midx,150,"PONG");

	settextjustify(RIGHT_TEXT, TOP_TEXT);
	setcolor(COLOR(154,205,50));
    settextstyle(FONT,HORIZ_DIR,4);
    outtextxy(midx+250,180,"Edition 2014");
	settextjustify(RIGHT_TEXT, TOP_TEXT);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(screen_right,screen_bottom-100,"Designed and Developed By :");
	outtextxy(screen_right,screen_bottom-50,"Md.Shorifuzzaman and Fahim Arefin");
	settextjustify(LEFT_TEXT, TOP_TEXT);
	if(flag==0)
	{
		left_bat_up=72;
		left_bat_down=80;
	}
	flag=1;
}

void create_menu()
{
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_end,screen_bottom);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(font);
    settextstyle(BOLD_FONT,HORIZ_DIR,10);
    outtextxy(midx,150,"MENU");
	setfillstyle(SOLID_FILL,GREY);
	bar(0,200,screen_end,205);
	bar(0,450,screen_end,455);
	bar(0,screen_bottom-5,screen_end,screen_bottom);
	bar(menu_x1,200,menu_x1+5,screen_bottom);
	bar(menu_x2,200,menu_x2+5,screen_bottom);
	setcolor(font);
	setbkcolor(bk);
	settextstyle(FONT,HORIZ_DIR,3);

	outtextxy(menu_x1/2,325,"GAME MODE");
	outtextxy(menu_x1+menu_x1/2,325,"DIFFICULTY");
	outtextxy(menu_x2+menu_x1/2,325,"SETTINGS");
	outtextxy(menu_x1/2,575,"ABOUT");
	outtextxy(menu_x1+menu_x1/2,575,"PLAY ");
	outtextxy(menu_x2+menu_x1/2,575,"HIGH SCORES");
}

void select_menu(int x , int y)
{
	if((x>0 && x<menu_x1) && (y>200 && y<450))
	{
		printf("Game Mode\n");
		game_mode();
	}
	else if((x>menu_x1 && x<menu_x2) && (y>200 && y<450))
	{
		printf("Difficulty\n");
		difficulty();
	}
	else if((x>menu_x2 && x<screen_end) && (y>200 && y<450))
	{
		printf("Settings\n");
		settings_menu();
	}
	else if((x>0 && x<menu_x1) && (y>450 && y<screen_bottom))
	{
		printf("About\n");
		about();
	}
	else if((x>menu_x1 && x<menu_x2) && (y>450 && y<screen_bottom))
	{
		printf("Play\n");
	}
	else if((x>menu_x2 && x<menu_x3) && (y>450 && y<screen_bottom))
	{
		printf("Score\n");
		score_menu();
	}
} 

void about()
{
	start_pong();
	setcolor(COLOR(255,165,50));
	setfillstyle(SOLID_FILL,COLOR(255,165,0));
	fillellipse(screen_left/2,315,10,10);
	fillellipse(screen_left/2,375,10,10);
	setcolor(COLOR(240,232,200));
	setfillstyle(SOLID_FILL,COLOR(240,232,170));
	draw_triangle(screen_left/2,432,3);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,4);
	outtextxy(screen_left,300,"Trivia: Pong is considered- the Mother of all Arcade Games");
	outtextxy(screen_left,360,"Instructions");
	outtextxy(screen_left,420,"Historically,The only instruction to play the game is:");
	settextjustify(CENTER_TEXT, TOP_TEXT);
	settextstyle(FONT,HORIZ_DIR,4);
	setcolor(COLOR(0,0,139));
	outtextxy(midx,480,"Avoid missing ball for high score.");
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	menu();
}

void draw_triangle(int x,int y,int z)
{
	int points[9]={320,150,420,300,250,300,320,150};
	points[0]=x+10+z;
	points[1]=y;
	points[6]=x+10+z;
	points[7]=y;
	points[2]=x-z;
	points[3]=y+10;
	points[4]=x-z;
	points[5]=y-10;
	setcolor(COLOR(255,165,0));
	setfillstyle(SOLID_FILL,COLOR(255,165,0));
	fillpoly(4,points);
}

int time()
{
	double diff_t;
	int time_flag=0;
    time(&end_t);
    diff_t = difftime(end_t, start_t);
    if(diff_t-TIME==1)
		time_flag=1;
	return time_flag;
 /*	char* c_time_string;
	c_time_string=ctime(&end_t);
	printf("Current time is %s", c_time_string); */
}

void score_card()
{
	int x,y;
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_end,screen_bottom);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(font);
    settextstyle(BOLD_FONT,HORIZ_DIR,10);
    outtextxy(midx,100,"SCORECARD VIEW");
	setfillstyle(SOLID_FILL,GREY);
	bar(0,150,screen_end,155);
	bar(0,200,screen_end,205);
	bar(0,365,menu_x1,370);
	bar(0,530,menu_x1,535);
	bar(0,screen_bottom-5,screen_end,screen_bottom);
	bar(menu_x1,150,menu_x1+5,screen_bottom);
	bar(menu_x2,150,menu_x2+5,screen_bottom);
	setcolor(font);
	setbkcolor(bk);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x1/2,185,"Score Position");
	outtextxy(menu_x1/2,285,"TOP");
	outtextxy(menu_x1/2,450,"MIDDLE");
	outtextxy(menu_x1/2,610,"BOTTOM");
	
	outtextxy(menu_x1+(menu_x1)/2,185,"SCORE COLOR");
	setfillstyle(SOLID_FILL,COLOR(240,255,240)); //HoneyDew
	bar(menu_x1+5,205,menu_x2,254);
	setfillstyle(SOLID_FILL,COLOR(255,255,240)); //Ivory
	bar(menu_x1+5,255,menu_x2,303);
	setfillstyle(SOLID_FILL,COLOR(251,249,249)); // Beige 5%
	bar(menu_x1+5,304,menu_x2,352);
	setfillstyle(SOLID_FILL,COLOR(255,250,205)); //Lemon Chiffon
	bar(menu_x1+5,353,menu_x2,401);
	setfillstyle(SOLID_FILL,COLOR(255,248,220)); //Corn Silk
	bar(menu_x1+5,402,menu_x2,450);
	setfillstyle(SOLID_FILL,COLOR(245,245,220)); //Beige
	bar(menu_x1+5,451,menu_x2,499);
	setfillstyle(SOLID_FILL,COLOR(239, 235, 214)); //Aths Special
	bar(menu_x1+5,500,menu_x2,548);
	setfillstyle(SOLID_FILL,COLOR(245,255,250) ); //Mint Cream
	bar(menu_x1+5,549,menu_x2,597);
	setfillstyle(SOLID_FILL,COLOR(223, 239, 240)); //Catskill White
	bar(menu_x1+5,598,menu_x2,646);
	setfillstyle(SOLID_FILL,COLOR(249, 246, 244)); //Peach
	bar(menu_x1+5,647,menu_x2,695);

	setfillstyle(SOLID_FILL,GREY);
	bar(menu_x2,150,menu_x2+5,screen_bottom);

	outtextxy(menu_x2+(menu_x1)/2,185,"SCOREBOARD COLOR");
	setfillstyle(SOLID_FILL,COLOR(157,149,115)); //Beige 100%
	bar(menu_x2+5,205,menu_x3,254);
	setfillstyle(SOLID_FILL,COLOR(221,207,153)); //Sandstone
	bar(menu_x2+5,255,menu_x3,303);
	setfillstyle(SOLID_FILL,COLOR( 138,136,125)); // Gray 60%
	bar(menu_x2+5,304,menu_x3,352);
	setfillstyle(SOLID_FILL,COLOR(88,87,84)); //Black 80%
	bar(menu_x2+5,353,menu_x3,401);
	setfillstyle(SOLID_FILL,COLOR( 140,21,21)); //Cardinal red
	bar(menu_x2+5,402,menu_x3,450);
	setfillstyle(SOLID_FILL,COLOR(21, 52, 80)); //Elephant Midnight Blue
	bar(menu_x2+5,451,menu_x3,499);
	setfillstyle(SOLID_FILL,COLOR(56, 46, 28)); //Bistre
	bar(menu_x2+5,500,menu_x3,548);
	setfillstyle(SOLID_FILL,COLOR(173, 116, 96) ); //Santa fe
	bar(menu_x2+5,549,menu_x3,597);
	setfillstyle(SOLID_FILL,COLOR(198, 199, 140)); //Pine glade
	bar(menu_x2+5,598,menu_x3,646);
	setfillstyle(SOLID_FILL,COLOR(231, 195, 156)); //Cashmere 
	bar(menu_x2+5,647,menu_x3,695);

	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>0 && x<menu_x1 && y>200  && y<370)
		score_pos=1;
	else if (x>0 && x<menu_x1 && y>370 && y<530)
		score_pos=2;
	else if (x>0 && x<menu_x1 && y>530 && y<screen_end)
		score_pos=3;
	else if(x>menu_x1 &&  x<menu_x2)
		score_col=getpixel(x,y);
	else if(x>menu_x2 &&  x<menu_x3)
		score_back=getpixel(x,y);
	
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>menu_x1 &&  x<menu_x2)
		score_col=getpixel(x,y);
	else if(x>menu_x2 &&  x<menu_x3)
		score_back=getpixel(x,y);
}

void hexagon(int x, int y)
{
	//int points[15]={x,y,x+45,y+40,x+90,y+40,x+135,y,x+90,y-40,x+45,y-40,x,y};
	int points[15]={x,y,x+65,y+60,x+130,y+60,x+195,y,x+130,y-60,x+65,y-60,x,y};	
	fillpoly(6,points);

}

void game_mode() /* No function of this menu works */
{
	int x,y;
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_end,screen_bottom);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(font);
    settextstyle(BOLD_FONT,HORIZ_DIR,10);
    outtextxy(midx,150,"GAME MODE");
	setfillstyle(SOLID_FILL,GREY);
	bar(0,200,screen_end,205);
	bar(0,450,screen_end,455);
	bar(0,screen_bottom-5,screen_end,screen_bottom);
	bar(menu_x1,200,menu_x1+5,screen_bottom);
	bar(menu_x2,200,menu_x2+5,screen_bottom);
	setcolor(font);
	setbkcolor(bk);
	settextstyle(FONT,HORIZ_DIR,3);

	outtextxy(menu_x1/2,325,"SURVIVAL MODE"); // 3 lives
	outtextxy(menu_x1+menu_x1/2,325,"TIME CHALLENGE");
	outtextxy(menu_x2+menu_x1/2,325,"TABLE TENNIS");
	outtextxy(menu_x1/2,575,"vs ROBO");
	outtextxy(menu_x1+menu_x1/2,575,"vs PLAYER");
	outtextxy(menu_x2+menu_x1/2,575,"BACK");
	
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	/* SURVIVAL MODE */
	if((x>0 && x<menu_x1) && (y>200 && y<450))
	{
		mode=1;
		printf("SURVIVAL MODE\n");
		settings_menu();
	}
	/* TIME CHALLENGE */
	else if((x>menu_x1 && x<menu_x2) && (y>200 && y<450))
	{
		mode=2;
		high_score=99;
		printf("TIME CHALLENGE\n");
		setfillstyle(SOLID_FILL,bk);
		bar(menu_x1+5,205,menu_x2,450); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(menu_x1,325,menu_x2,330);//The barrier
		bar(menu_x1+menu_x1/2,200,menu_x1+menu_x1/2+5,450);
		setbkcolor(bk);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,3);
		outtextxy(menu_x1+menu_x1/4,265,"60 seconds"); 
		outtextxy(menu_x2-menu_x1/4,265,"150 seconds"); 
		outtextxy(menu_x1+menu_x1/4,395,"300 seconds"); 
		outtextxy(menu_x2-menu_x1/4,395,"450 seconds"); 
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if((x>menu_x1 && x<menu_x1+menu_x1/2) && (y>200 && y<325))/*Option 1*/
			TIME=60;
		else if((x>menu_x1+menu_x1/2 && x<menu_x2) && (y>200 && y<325)) /* Option 2 */
			TIME=150;
		else if((x>menu_x1 && x<menu_x1+menu_x1/2) && (y>325 && y<450))/*Option 3*/
			TIME=300;
		else if((x>menu_x1+menu_x1/2 && x<menu_x2) && (y>325 && y<450))/* Option 4 */
			TIME=450; 
		else 
			TIME=5;
		x=0;
		time(&start_t);
	}
	/*TABLE TENNIS */
	else if((x>menu_x2 && x<screen_end) && (y>200 && y<450))
	{
		mode=3;
		printf("TABLE TENNIS\n");
		game_mode();
	}
	/*SINGLE PLAYER */
	else if((x>0 && x<menu_x1) && (y>450 && y<screen_bottom))
	{
		mode=4;
		printf("vs ROBO\n");
		vs=1;
		menu();
	}
	/*DOUBLE PLAYER */
	else if((x>menu_x1 && x<menu_x2) && (y>450 && y<screen_bottom))
	{
		mode=5;
		vs=0;
		printf("vs PLAYER\n");
		menu();
	}
	else if((x>menu_x2 && x<menu_x3) && (y>450 && y<screen_bottom))
	{
		printf("BACK\n");
		menu();
	}


}