// pong version 11.02
//Added Menu, only 1 option works
#include "graphics.h"
#include<stdio.h>
void first_page();
void start_pong();
void menu();
void select_menu(int x , int y);
void create_menu();
void score_check(int n, int p);
void score_menu();
void about();
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
#define screen_right 1100  /*end of black screen*/
#define screen_bottom 700 /*bottom of black screen*/
#define screen_end screen_right+screen_left  /* end line of screen...value of screen_end should be a multiple of 6 */
#define high_score 3//set the highest score
#define FONT SANS_SERIF_FONT
#define FONT_SIZE 4
#define D_E 35
#define D_H 20
#define SPEED 50 // serve speed
#define GREY COLOR(105,105,105)
#define MENU_C COLOR(240,255,240)
#define menu_x1 400
#define menu_x2 800
#define menu_x3 screen_end 
#define	menu_y1 350
#define	menu_y2 screen_bottom
int midx,midy,m,flag;//m=number of top scores available,flag sets the controls when we enter the game for the first time 
int p1[55],p2[55],dif[5][55];
int screen_mid=(screen_end)/2; // #define screen_mid screen_end/2 /*middle of the screen, where the net is */
int ball_y=300,ball_x=600,input_key,left_baty,right_baty,f,g,l,r,g_o=0,dev=SPEED,det,i,de,t;	// all variables are declared here
// value of f & g controls the limit of the motion of ball leftward-rightwards & ups-down respectively
// l & r for the score of left & right side respectively...g_o=1 means game over.
char left_score[3],right_score[3],choice,control_l,l_u,l_d,left_up[10],left_down[10];	//choice decides if the player will continue or not]
//left_up prints the up key for left player & l_u stores the up key for left player
int left_bat_up, left_bat_down;
char top[50][10];
FILE *score_list=fopen("score log.txt","a");

void background()
{
	setfillstyle(SOLID_FILL,BLACK);
	bar(0,0,screen_end,screen_bottom);
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
        delay(500);			
    }
    else if(ball_x>=bat_pos_right+bat_width+20)
    {									//similarly BALL misses the right bat...
        f=1;
		dev=SPEED;
        ball_x=screen_mid;
        l++;
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
	fprintf(score_list," %d %d \n",l,r);
    delay(1000);						// delay after WIN
    l=r=0;							// score 0-0
    cleardevice();
}

void difficulty()
{
	int a,x,y;
	int c=COLOR(210,231,4);
	setfillstyle(SOLID_FILL,c);
	bar(menu_x1,0,menu_x2,menu_y1); 
	setcolor(GREY);
	setfillstyle(SOLID_FILL,COLOR(255,250,205) );
	bar(menu_x1,menu_y1/2-5,menu_x2,menu_y1/2+5);//The barrier
	setbkcolor(c);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(menu_x1+menu_x1/2,menu_y1/4,"EASY"); 
	outtextxy(menu_x1+menu_x1/2,menu_y1-menu_y1/4,"HARD"); 
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);
	if((x>menu_x1 && x<menu_x2) && (y>0 && y<menu_y1/2))//Easy
		det=D_E;
	else if((x>menu_x1 && x<menu_x2) && (y>menu_y1/2 && y<menu_y1)) //Hard
		det=D_H;
}

void score_check(int n, int p)
{
	m=0;
	char l[1000];
	int i,j,x,k,max,maxi,y;
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
		sprintf(top[m++],"Sorry you played only %d times",i);
	fclose(score_list);

	score_list=fopen("score log.txt","a");

	create_menu();
	int c=COLOR(234,253,2);
	setfillstyle(SOLID_FILL,c);
	bar(menu_x2,menu_y1,menu_x3,menu_y2); 
	setbkcolor(c);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,3);
	sprintf(l,"Best %d Results for Player %d",n,p);
	outtextxy(menu_x2+menu_x1/2,menu_y1+20,l); 
	for(j=0;j<m;j++)
	{
		outtextxy(menu_x2+menu_x1/2,menu_y1+45+((menu_y1-50)/n)*(j),top[j]); 
	}
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);
	select_menu(x,y);
} 

void score_menu()
{
	int x,y,n,p;
	int c=COLOR(234,253,2);
	setfillstyle(SOLID_FILL,c);
	bar(menu_x1,menu_y1,menu_x3,menu_y2);
	setbkcolor(c);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x1+(menu_x1)/2,menu_y1+30,"Select Player");

	/*Player 1 */
	setfillstyle(SOLID_FILL,COLOR(210,231,3));
	bar(menu_x1,menu_y1+40,menu_x2,menu_y1+40+(menu_y1-40)/2);
	setbkcolor(COLOR(210,231,3));
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x1+(menu_x1)/2,menu_y1-20+(menu_y1-40)/2,"Player 1");

	/*Player 2 */
	setfillstyle(SOLID_FILL,COLOR(154,205,50));
	bar(menu_x1,menu_y1+40+(menu_y1-40)/2,menu_x2,menu_y2);
	setbkcolor(COLOR(154,205,50));
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x1+(menu_x1)/2,menu_y2-(menu_y1)/4+20,"Player 2");

	/*The barrier */
	setfillstyle(SOLID_FILL,COLOR(255,250,205));
	bar(menu_x2-5,menu_y1,menu_x2,menu_y2);

	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>menu_x1 && y>menu_y1+40 && x<menu_x2 && y< (menu_y1+40+(menu_y1-40)/2))
		p=1;
	else if (x>menu_x1 && menu_y1+40+(menu_y1-40)/2 && x<menu_x2 && y< menu_y2)
		p=2;
	setbkcolor(c);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x2+(menu_x1)/2,menu_y1+30,"Number of Records");

	/*5 Records */
	setfillstyle(SOLID_FILL,COLOR(210,231,3));
	bar(menu_x2,menu_y1+40,menu_x3,menu_y1+40+(menu_y1-40)/2);
	setbkcolor(COLOR(210,231,3));
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x2+(menu_x1)/2,menu_y1-20+(menu_y1-40)/2,"5");

	/*10 Records */
	setfillstyle(SOLID_FILL,COLOR(154,205,50));
	bar(menu_x2,menu_y1+40+(menu_y1-40)/2,menu_x3,menu_y2);
	setbkcolor(COLOR(154,205,50));
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x2+(menu_x1)/2,menu_y2-(menu_y1)/4+20,"10");
	
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>menu_x2 && y>menu_y1+40 && x<menu_x3 && y< (menu_y1+40+(menu_y1-40)/2))
		n=5;
	else if (x>menu_x2 && menu_y1+40+(menu_y1-40)/2 && x<menu_x3 && y< menu_y2)
		n=10;
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
	while(1)
    {	
		setcolor(WHITE);
		setlinestyle(DASHED_LINE,3,1);
		line(screen_mid,screen_top,screen_mid,screen_bottom);


       		/* Changes Start Here */
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
	start_pong();
	setcolor(COLOR(255,165,50));
	setfillstyle(SOLID_FILL,COLOR(255,165,0));
	fillellipse(screen_left/2,315,10,10);
	fillellipse(screen_left/2,375,10,10);
	setcolor(COLOR(240,232,200));
	setfillstyle(SOLID_FILL,COLOR(240,232,170));
	fillellipse(screen_left/2,495,10,10);
	fillellipse(screen_left/2,555,10,10);//y+15
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(screen_left,300,"Use the mouse for Right Bat Control");
	outtextxy(screen_left,360,"Use 'UP' & 'DOWN' key for Left Bat Control");
	outtextxy(screen_left,480,"Press 'Space Bar' to define custom keys for Left Bat Control");
	outtextxy(screen_left,540,"Press 'M' for Menu");

	control_l=getch();

	if(control_l==32)
	{
		cleardevice();
		start_pong();
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(100,300,"Choose a key to move left bat upwards");
		while((left_bat_up=getch())==13);
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

	else if(control_l=='m' || control_l=='M')
	{
		menu();
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
	int c,text; //c=color,text=text position
	int text_color = COLOR(85,85,85);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfillstyle(SOLID_FILL,COLOR(255,255,240));
	bar(0,0,screen_end,screen_bottom);
	text=menu_x1/2;

	/* Game Mode */
	c=COLOR(192,214,3);
	setfillstyle(SOLID_FILL,c);
	bar(0,0,menu_x1,menu_y1); 
	setbkcolor(c);
	setcolor(text_color);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(text,menu_y1/2,"GAME MODE");
	
	/*Difficulty */
	c=COLOR(210,231,4);
	setfillstyle(SOLID_FILL,c);
	bar(menu_x1,0,menu_x2,menu_y1); 
	setbkcolor(c);
	setcolor(text_color);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(menu_x1+text,menu_y1/2,"DIFFICULTY");

	/* SETTINGS */
	c=COLOR(157,231,3);
	setfillstyle(SOLID_FILL,c);
	bar(menu_x2,0,menu_x3,menu_y1); 
	setbkcolor(c);
	setcolor(text_color);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(menu_x2+text,menu_y1/2,"SETTINGS");

	/* INSTRUCTIONS */
	c=YELLOW;
	setfillstyle(SOLID_FILL,c);
	bar(0,menu_y1,menu_x1,menu_y2); 
	setbkcolor(c);
	setcolor(text_color);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(text,menu_y1+(menu_y1/2),"ABOUT");

	/*Play */
	c=COLOR(255,215,0);
	setfillstyle(SOLID_FILL,c);
	bar(menu_x1,menu_y1,menu_x2,menu_y2); 
	setbkcolor(c);
	setcolor(COLOR(70,13,242));
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(screen_mid+10,menu_y1+(menu_y1/2),"PLAY ");

	/*HIGH SCORES*/
	c=COLOR(234,253,2);
	setfillstyle(SOLID_FILL,c);
	bar(menu_x2,menu_y1,menu_x3,menu_y2); 
	setbkcolor(c);
	setcolor(text_color);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(menu_x2+text,menu_y1+(menu_y1/2),"HIGH SCORES");

}

void select_menu(int x , int y)
{
	if((x>0 && x<menu_x1) && (y>0 && y<menu_y1))
	{
		printf("Game Mode\n");
	}
	else if((x>menu_x1 && x<menu_x2) && (y>0 && y<menu_y1))
	{
		printf("Difficulty\n");
		difficulty();
	}
	else if((x>menu_x2 && x<menu_x3) && (y>0 && y<menu_y1))
	{
		printf("Settings\n");
	}
	else if((x>0 && x<menu_x1) && (y>menu_y1 && y<menu_y1))
	{
		printf("About\n");
		//about();
	}
	else if((x>menu_x1 && x<menu_x2) && (y>menu_y1 && y<menu_y2))
	{
		printf("Play\n");
	}
	else if((x>menu_x2 && x<menu_x3) && (y>menu_y1 && y<menu_y2))
	{
		printf("Score\n");
		score_menu();
	}
} 

void about()
{
	start_pong();
	delay(1000);
	setcolor(COLOR(255,165,50));
	setfillstyle(SOLID_FILL,COLOR(255,165,0));
	fillellipse(screen_left/2,315,10,10);
	fillellipse(screen_left/2,375,10,10);
	setcolor(COLOR(240,232,200));
	setfillstyle(SOLID_FILL,COLOR(240,232,170));
	fillellipse(screen_left/2,495,10,10);
	fillellipse(screen_left/2,555,10,10);//y+15
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(screen_left,300,"Trivia : Pong is considered as the Mother of all Arcade Games ");
	outtextxy(screen_left,360,"Instructions");
	outtextxy(screen_left,480,"Historically, The only instructions for how to play the game were:");
	outtextxy(screen_left,540,"Avoid missing ball for high score.");
	delay(3000);
/*	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	menu(); */
}
