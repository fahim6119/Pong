// pong version 11.01
//brand_new interface
#include "graphics.h"
#include<stdio.h>
void first_page();
void start_pong();
#define bat_speed 120  /*speed of the BAT can be changed*/
#define bat_size 120   /*size of the BAT can be changed*/
#define bat_width 10
#define bat_pos_left screen_left+50
#define bat_pos_right screen_right-60
#define ball_size_x 10
#define ball_size_y 30 // for rectangular ball
#define ball_speed_x 20
#define ball_speed_y 40
#define screen_top 0  /*top line of the screen.it will always be zero, otherwise we will have to change all co-ordinates*/
#define screen_left 100  /*start of black screen*/
#define screen_right 1200  /*end of black screen*/
#define screen_bottom 700 /*bottom of black screen*/
#define screen_end screen_right+screen_left  /* screen_right+screen_left =end line of screen, so that width of brown portion on the left = width of brown portion on the right */
#define high_score 1//set the highest score
#define FONT SANS_SERIF_FONT
#define FONT_SIZE 4
#define DELAY1 25
#define DELAY2 30
#define SPEED 50 // serve speed
#define GREY COLOR(105,105,105)
int midx,midy;
int screen_mid=(screen_end)/2; // #define screen_mid screen_end/2 /*middle of the screen, where the net is */
int ball_y=300,ball_x=600,input_key,left_baty,right_baty,f,g,l,r,g_o=0,de=SPEED,det;	// all variables are declared here
// value of f & g controls the limit of the motion of ball leftward-rightwards & ups-down respectively
// l & r for the score of left & right side respectively...g_o=1 means game over.
char left_score[3],right_score[3],choice,control_l,l_u,l_d,left_up[10],left_down[10];	//choice decides if the player will continue or not]
//left_up prints the up key for left player & l_u stores the up key for left player
int left_bat_up, left_bat_down;

FILE *score_list=fopen("score log.txt","a");

void background()
{
    setfillstyle(SOLID_FILL,GREY);
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

		else if(input_key==left_bat_down && left_baty<=screen_bottom-bat_size) //screen limit =600, so last end of bat has to be inside 480 
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
    if(f==0)				// if f=0, BALL moves leftward and vice-versa
        ball_x-=ball_speed_x;			// the values of ball_x & ball_y controls the SPEED & DIRECTION of the BALL along x & y-axis respectively
    else if(f==1)
        ball_x+=ball_speed_x;
    if(g==0)				//if g=0, BALL moves upward and vice-versa
        ball_y-=ball_speed_y;
    else if(g==1)
        ball_y+=ball_speed_y;
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
    if( ball_x >= bat_pos_left && ball_x <= bat_pos_left+bat_width  && ball_y <= left_baty + bat_size && ball_y + ball_size_y >= left_baty )	
        f=1;										//ball touches the left bat & direction of ball is changed to rightward.
    else if(ball_x >= bat_pos_right && ball_x <= bat_pos_right+bat_width && ball_y+ball_size_y >= right_baty && ball_y <= right_baty +bat_size)
        f=0;
    else if(ball_x <= bat_pos_left-20)	
    {									// BALL misses the left bat
        f=0;
		de=SPEED;
        ball_x=screen_mid;						// BALL starts again from the mid position 
        r++;							// one score is added to the right side
        delay(500);			
    }
    else if(ball_x>=bat_pos_right+bat_width+20)
    {									//similarly BALL misses the right bat...
        f=1;
		de=SPEED;
        ball_x=screen_mid;
        l++;
        delay(500);
    }
    if(ball_y<=screen_top)										
        g=1;							// if BALL touches the upper bound of window, direction is changed to downward 
    else if(ball_y+ball_size_y>=screen_bottom)
        g=0;
}

void score()
{
    sprintf(left_score, "%d", l);
    sprintf(right_score, "%d", r);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setbkcolor(GREY);
    setcolor(WHITE);
    settextstyle(FONT,HORIZ_DIR,9);
    outtextxy(screen_left/2,100,left_score);
    outtextxy(screen_end-(screen_left/2),100,right_score);
}

void game_over()
{
    if(l==high_score)				//limit of score
    {
		setbkcolor(BLACK);
        setcolor(GREEN);
        settextstyle(FONT,HORIZ_DIR,7);
        outtextxy(screen_left+150,300,"WIN");
    }
    else
    {
		setbkcolor(BLACK);
        setcolor(GREEN);
        settextstyle(FONT,HORIZ_DIR,7);
        outtextxy(screen_mid+150,300,"WIN");
    }
	g_o=1;
	fprintf(score_list," %d - %d \n",l,r);
    delay(1000);						// delay after WIN
    l=r=0;							// score 0-0
    cleardevice();
}


int main( )
{
    initwindow(screen_end, screen_bottom, "Pong Demo");
	begin:
	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	first_page();
	cleardevice();
    background();
	if(screen_right-screen_left>1150)
		det=DELAY1;
	else
		det=DELAY2;
	while(1)
    {	

		if(de>det)
			de--;
		setcolor(WHITE);
		setlinestyle(DASHED_LINE,3,1);
		line(screen_mid,screen_top,screen_mid,screen_bottom);

        bat_create();
		
		ball_create();

        delay(de);

        ball_clear();

        bat_clear();

        ball_limit_control();

		score();
        if(l==high_score || r==high_score)
			game_over();
		if(g_o==1)
		{
			bar(0,0,screen_end, screen_bottom);
			setbkcolor(BLACK);
			same_screen:
			setcolor(CYAN);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			settextstyle(FONT,HORIZ_DIR,4);
			outtextxy(midx,midy,"Press 'S' to continue and 'F' to exit");
			delay(200);
			choice=getch();
			if(choice=='s' || choice == 'S')
			{
				g_o=0;
				cleardevice();
				background();
				continue;
			}
			else if(choice=='f' || choice=='F')
			{	
				fclose(score_list);
				cleardevice();
				break;
			}

			else if(choice=='a' || choice=='A')
			{	
				cleardevice();
				g_o=0;
				goto begin;
			}
			else //user pressed some other key, so they will see the same screen
			{
				goto same_screen;
			}
		}
    }
    return 0;
}


void first_page()
{
	start_pong();
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(GREY);
    settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(midx,340,"Use the mouse for Right Bat Control");
    
	settextjustify(LEFT_TEXT, TOP_TEXT);
	outtextxy(screen_left,460,"Press '1' to use 'UP' & 'DOWN' key for Left Bat Control");
	outtextxy(screen_left,520,"Press '2' to define your own alphanumeric keys for Left Bat Control");

	control_l=getch();

	if(control_l=='2')
	{
		cleardevice();
		start_pong();
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(100,300,"Choose your alphanumeric key to move left bat upwards");
		while((left_bat_up=getch())==13);
		left_up[0]=left_bat_up;
		left_up[1]=0;
		if(left_bat_up==32)
			outtextxy(900,300,"Space Bar");
		else
			outtextxy(900,300,left_up);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(100,400,"Choose your alphanumeric key to move left bat downwards");
		left_bat_down=getch();
		left_down[0]=left_bat_down;
		left_down[1]=0;
		if(left_bat_down==32)
			outtextxy(900,400,"Space Bar");
		else
			outtextxy(900,400,left_down);
		delay(400);
	}

	else 
	{
		cleardevice();
		left_bat_up=72;
		left_bat_down=80;
		strcpy(left_up,"");
		strcpy(left_down,"Down Arrow");

		start_pong();
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(midx-(midx/2),300,"Move Up - Up Arrow ");
		outtextxy(midx-(midx/2),350,"Move Down - Down Arrow");

		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setcolor(BLACK);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE+1);
		outtextxy(midx,525,"Press a key if you're ready to roll!");
		getch();  
		getch();  
		delay(1000);
	}
	setbkcolor(BLACK);
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
    outtextxy(midx+250,180,"Demo version");
	settextjustify(LEFT_TEXT, TOP_TEXT);
}

