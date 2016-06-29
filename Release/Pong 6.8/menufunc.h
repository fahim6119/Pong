
void about()
{
	int x,y;
	start_pong();
	setcolor(COLOR(255,165,50));
	setfillstyle(SOLID_FILL,COLOR(255,165,0));
	fillellipse(screen_left/2,215+(menu_ymid/2),10,10);
	fillellipse(screen_left/2,215+menu_ymid,10,10);
	fillellipse(screen_left/2,215+(menu_ymid*3)/2,10,10);
	setcolor(COLOR(240,232,200));
	setfillstyle(SOLID_FILL,COLOR(240,232,170));
	draw_triangle(screen_left/2+10,212+menu_ymid*2,3);
	draw_triangle(screen_left/2+10,212+(menu_ymid*5)/2,3);
	draw_triangle(screen_left/2+10,212+menu_ymid*3,3);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(screen_left,200+menu_ymid/2,"Pong(1972) by Atari is considered the Mother of Arcade Games");
	outtextxy(screen_left,200+menu_ymid,"You can set the Game Point from the Menu");
	outtextxy(screen_left,200+(menu_ymid*3)/2,"Instructions -");
	outtextxy(screen_left+20,200+menu_ymid*2,"Historically,The only instruction to play the game is: Avoid missing ball for high score.");
	outtextxy(screen_left+20,200+(menu_ymid*5)/2,"Time Challenge: The Higher scorer in the Time limit wins the game");
	outtextxy(screen_left+20,200+menu_ymid*3,"Press ESC to Pause and Resume the Game");
	
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(FONT,HORIZ_DIR,3);
	int backx=textwidth("BACK");
	int backy=textheight("BACK");
	setfillstyle(SOLID_FILL,GREY);
	bar(screen_x/2-backx/2-10,200+(7*menu_ymid)/2-10,screen_x/2+backx/2+10,200+(7*menu_ymid)/2+backy+10);
	
	setbkcolor(GREY);
	setcolor(WHITE);
	outtextxy(screen_x/2-backx/2,200+(7*menu_ymid)/2,"BACK");
	again:
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN,x,y);
	if(x>screen_x/2-backx/2-10 && y>200+(7*menu_ymid)/2-10 && x<screen_x/2+backx/2+10 && y<200+(7*menu_ymid)/2+backy+10)
		return;
	else 
		goto again;
}

void background()
{
	setfillstyle(SOLID_FILL,BLACK);
	bar(0,0,screen_end,screen_bottom);
    setfillstyle(SOLID_FILL,score_back);
    bar(0,screen_top,screen_left,screen_y);
    bar(screen_right,screen_top,screen_x,screen_y); 
	bar(0,screen_bottom,screen_right,screen_y);
}

void create_menu() 
{
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_x,screen_y);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(font);
    settextstyle(BOLD_FONT,HORIZ_DIR,10);
    outtextxy(midx,150,"MENU");
	setfillstyle(SOLID_FILL,GREY);
	bar(0,200,screen_x,205);
	bar(0,menu_y1,screen_x,menu_y1+5);
	bar(0,screen_y-5,screen_x,screen_y);
	bar(menu_x1,200,menu_x1+5,screen_y);
	bar(menu_x2,200,menu_x2+5,screen_y);
	setcolor(font);
	setbkcolor(bk);
	settextstyle(FONT,HORIZ_DIR,3);

	outtextxy(menu_x1/2,200+menu_ymid,"SET GAME SCREEN SIZE");
	outtextxy(menu_x1+menu_x1/2,200+menu_ymid,"PLAY TIME CHALLENGE");
	outtextxy(menu_x2+menu_x1/2,200+menu_ymid,"LEADERBOARD");
	outtextxy(menu_x1/2,menu_y1+menu_ymid,"GAME POINT");
	outtextxy(menu_x1+menu_x1/2,menu_y1+menu_ymid,"PLAY PONG");
	outtextxy(menu_x2+menu_x1/2,menu_y1+menu_ymid,"BACK");
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

void first_page()
{
	int color=COLOR(210,231,3);
	int d=(screen_x-450)/4;
	int h=150;
	int x,y;
	start_pong();
	draw_triangle(screen_left-30,315,5);
	draw_triangle(screen_left-30,375,5);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(screen_left,300,"Use the mouse for Right Bat Control");
	outtextxy(screen_left,360,"Use 'UP' & 'DOWN' key for Left Bat Control");
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	//hexagon length 150, height 80
	bar(d,450,d+h,500); 
	bar(2*d+h,450,2*d+2*h,500);
	bar(3*d+2*h,450,3*d+3*h,500);
	setbkcolor(color);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(GREY);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(d+h/2,475,"MENU");
	outtextxy(2*d+h+h/2,475,"PLAY");
	outtextxy(3*d+2*h+h/2,475,"SETTINGS");

	starter:
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>d && x<d+h  && y>=450 && y<=500)
		control_l=1;
	else if (x>2*d+h && x<(2*d+2*h) && y>=450 && y<=500)
		control_l=2;
	else if(x>3*d+2*h && x<(3*d+3*h)  && y>=450 && y<=500)
		control_l=3;
	else 
		goto starter;
	if(control_l==1)
	{
		menu();
	}
	else if(control_l==3)
	{
		settings_menu();
	}
	else
		return;
	setbkcolor(BLACK);
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

void select_menu(int x , int y) 
{
	int space,wid,hei ; 
	int bk= COLOR(255,255,240);
	if((x>0 && x<menu_x1) && (y>200 && y<menu_y1))
	{
		printf("Set game screen\n");//set game screen
		setfillstyle(SOLID_FILL,bk);
		bar(0,205,menu_x1,menu_y1); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(0,200+menu_ymid,menu_x1,200+menu_ymid+5);//The barrier
		bar(menu_x1/2,200,menu_x1/2 + 5,menu_y1);
		setbkcolor(bk);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(menu_x1/4,menu_ytop,"600 * 480"); 
		outtextxy(menu_x1-menu_x1/4,menu_ytop,"800 * 640"); 
		outtextxy(menu_x1/4,menu_y1- menu_ymid/2,"750 * 500"); 
		outtextxy(menu_x1-menu_x1/4,menu_y1- menu_ymid/2,"900 * 600"); 
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y); 

		if((x>0 && x<menu_x1/2) && (y>200 && y<200+menu_ymid))/*600 * 480 = 5:4*/
		{
			wid=600;
			hei=480;
		}
		else if((x>0 && x<menu_x1/2) && (y>200+menu_ymid && y<menu_y1))/*800 * 640 = 5:4*/
		{
			wid=800;
			hei=640;
		}
		else if((x>menu_x1/2 && x<menu_x1) && (y>200 && y<200+menu_ymid)) /*750 * 500 = 3:2 */
		{
			wid=750;
			hei=500;
		}
		else if((x>menu_x1/2 && x<menu_x1) && (y>200+menu_ymid && y<menu_y1))/*900 * 600 = 3:2*/
		{
			wid=900;
			hei=600;
		} 
		space= (screen_x-wid)/2;
		screen_left=space;  /*start of black screen*/
		screen_right=screen_left+wid;  /*end of black screen*/
		screen_bottom=hei; /*bottom of black screen*/
		screen_end=screen_left+screen_right;
		screen_mid=screen_left+ wid/2;
		ball_y=screen_bottom/2,ball_x=screen_mid;
	}
	else if((x>menu_x1 && x<menu_x2) && (y>200 && y<menu_y1))
	{
		printf("Play TIME CHALLENGE\n");
		mode=2;
		high_score=999;
		setfillstyle(SOLID_FILL,bk);
		bar(menu_x1+5,205,menu_x2,menu_y1); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(menu_x1,200+menu_ymid,menu_x2,200+menu_ymid+5);//The barrier
		bar(menu_x1+menu_x1/2,200,menu_x1+menu_x1/2+5,menu_y1);
		setbkcolor(bk);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,3);
		outtextxy(menu_x1+menu_x1/4,menu_ytop,"30 seconds"); 
		outtextxy(menu_x2-menu_x1/4,menu_ytop,"60 seconds"); 
		outtextxy(menu_x1+menu_x1/4,menu_y1- menu_ymid/2,"150 seconds"); 
		outtextxy(menu_x2-menu_x1/4,menu_y1- menu_ymid/2,"450 seconds"); 
		int timec=0;
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if((x>menu_x1 && x<menu_x1+menu_x1/2) && (y>200 && y<200+menu_ymid))/*OPTION 1*/
			TIME=30;
		else if((x>menu_x1 && x<menu_x1+menu_x1/2) && (y>200+menu_ymid && y<menu_y1))/*OPTION 2*/
			TIME=60;
		else if((x>menu_x1+menu_x1/2 && x<menu_x2) && (y>200 && y<200+menu_ymid)) /*OPTION 3*/
			TIME=150;
		else if((x>menu_x1+menu_x1/2 && x<menu_x2) && (y>200+menu_ymid && y<menu_y1))/*OPTION 4*/
			TIME=450; 
		else 
			timec=1;
		if(timec==0)
		{
			time(&start_t);
			return;
		}
	}
	else if((x>menu_x2 && x<screen_x) && (y>200 && y<menu_y1))
	{
		printf("Leaderboard\n");
		score_menu();
	}
	/* Game Point Menu */
	else if((x>0 && x<menu_x1) && (y>menu_y1 && y<screen_y))
	{
		printf("GAME POINT\n");
		setfillstyle(SOLID_FILL,bk);
		bar(0,menu_y1+5,menu_x1,menu_y2); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(0,menu_y1+menu_ymid,menu_x1,menu_y1+menu_ymid+5);//The barrier
		bar(menu_x1/2,menu_y1,menu_x1/2 + 5,menu_y2);
		setbkcolor(bk);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(menu_x1/4,menu_y1+ menu_ymid/2,"5");
		outtextxy(menu_x1-menu_x1/4,menu_y1+ menu_ymid/2,"10"); 
		outtextxy(menu_x1/4,menu_y1+3*menu_ymid/2,"15"); 
		outtextxy(menu_x1-menu_x1/4,menu_y1+3*menu_ymid/2,"20"); 
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if((x>0 && x<menu_x1/2) && (y>menu_y1 && y<menu_y1+menu_ymid))/* Game Point 5 */
			high_score=5;
		else if((x>0 && x<menu_x1/2) && (y>menu_y1+menu_ymid && y<menu_y2))/* Game Point 15 */
			high_score=15;
		else if((x>menu_x1/2 && x<menu_x1) && (y>menu_y1 && y<menu_y1+menu_ymid)) /* Game Point 10 */
			high_score=10;
		else if((x>menu_x1/2 && x<menu_x1) && (y>menu_y1+menu_ymid && y<menu_y2))/* Game Point 20 */
			high_score=20;
		printf("%d\n",high_score);
	}
	else if((x>menu_x1 && x<menu_x2) && (y>menu_y1 && y<screen_y))
	{
		printf("Play\n");
		return;
	}
	else if((x>menu_x2 && x<screen_x) && (y>menu_y1 && y<screen_y))
	{
		first_page();
		return;
	}
	menu();
} 

void settings_menu()
{
	cleardevice();
	int x,y;
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_x,screen_y);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(font);
    settextstyle(BOLD_FONT,HORIZ_DIR,10);
    outtextxy(midx,150,"SETTINGS");
	setfillstyle(SOLID_FILL,GREY);
	bar(0,200,screen_x,205);
	bar(0,menu_y1,screen_x,menu_y1+5);// middle horizontal bar
	bar(0,screen_y-5,screen_x,screen_y); // bottom bar
	bar(menu_x1,200,menu_x1+5,screen_y);
	bar(menu_x2,200,menu_x2+5,screen_y);
	setcolor(font);
	setbkcolor(bk);
	settextstyle(FONT,HORIZ_DIR,3);

	outtextxy(menu_x1/2,200+menu_ymid,"ABOUT");
	outtextxy(menu_x1+menu_x1/2,200+menu_ymid,"SOUNDS");
	outtextxy(menu_x2+menu_x1/2,200+menu_ymid,"BAT SPEED");
	outtextxy(menu_x1/2,menu_y1+menu_ymid,"SCORE POSITION");
	outtextxy(menu_x1+menu_x1/2,menu_y1+menu_ymid,"SCORECARD VIEW");
	outtextxy(menu_x2+menu_x1/2,menu_y1+menu_ymid,"BACK");
	
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if((x>0 && x<menu_x1) && (y>200 && y<menu_y1))
	{
		printf("About\n");
		about();
	}
	else if((x>menu_x1 && x<menu_x2) && (y>200 && y<menu_y1))
	{
		printf("SOUNDS\n");
		setfillstyle(SOLID_FILL,bk);
		bar(menu_x1+5,205,menu_x2,menu_y1); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(menu_x1,200+menu_ymid,menu_x2,200+menu_ymid+5);//The barrier
		bar(menu_x1+menu_x1/2,200,menu_x1+menu_x1/2+5,menu_y1);
		setbkcolor(bk);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,3);
		outtextxy(menu_x1+menu_x1/4,menu_ytop,"MUTE"); 
		outtextxy(menu_x2-menu_x1/4,menu_ytop,"SOUND 1"); 
		outtextxy(menu_x1+menu_x1/4,menu_y1- menu_ymid/2,"SOUND 2"); 
		outtextxy(menu_x2-menu_x1/4,menu_y1- menu_ymid/2,"SOUND 3"); 
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if((x>menu_x1 && x<menu_x1+menu_x1/2) && (y>200 && y<200+menu_ymid))/*MUTE*/
			SOUND=0;
		else if((x>menu_x1 && x<menu_x1+menu_x1/2) && (y>200+menu_ymid && y<menu_y1))/*SOUND 1*/
			SOUND=55;
		else if((x>menu_x1+menu_x1/2 && x<menu_x2) && (y>200 && y<200+menu_ymid)) /*SOUND 2*/
			SOUND=85;
		else if((x>menu_x1+menu_x1/2 && x<menu_x2) && (y>200+menu_ymid && y<menu_y1))/*SOUND 3*/
			SOUND=150; 
	}
	else if((x>menu_x2 && x<screen_x) && (y>200 && y<menu_y1))
	{
		printf("BAT SPEED\n");
		setfillstyle(SOLID_FILL,bk);
		bar(menu_x2+5,205,menu_x3,menu_y1); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(menu_x2,200+menu_ymid,menu_x3,200+menu_ymid+5);//The barrier
		bar(menu_x2+menu_x1/2,200,menu_x2+menu_x1/2+5,menu_y1);
		setbkcolor(bk);
		setcolor(GREY);
		settextstyle(FONT,HORIZ_DIR,3);
		outtextxy(menu_x2+menu_x1/4,menu_ytop,"1x"); 
		outtextxy(menu_x3-menu_x1/4,menu_ytop,"1.2x"); 
		outtextxy(menu_x2+menu_x1/4,menu_y1- menu_ymid/2,"1.4x"); 
		outtextxy(menu_x3-menu_x1/4,menu_y1- menu_ymid/2,"1.75x"); 

		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if((x>menu_x2 && x<menu_x2+menu_x1/2) && (y>200 && y<200+menu_ymid))/*batspeed 100 */
			bat_speed=100;
		else if((x>menu_x2 && x<menu_x2+menu_x1/2) &&  (y>200+menu_ymid && y<menu_y1))/*batspeed 140 seconds*/
			bat_speed=140;
		else if((x>menu_x2+menu_x1/2 && x<menu_x3) && (y>200 && 200+menu_ymid)) /* batspeed 120 seconds */
			bat_speed=120;
		else if((x>menu_x2+menu_x1/2 && x<menu_x3) &&  (y>200+menu_ymid && y<menu_y1))/*batspeed 175 seconds */
			bat_speed=175;
	}
	else if((x>0 && x<menu_x1) && (y>menu_y1 && y<screen_y)) // Set Score Position
	{
		int x,y;
		int wid=(screen_y-205)/10;
		int bk= COLOR(255,255,240);
		int font=COLOR(255,165,0);
		setfillstyle(SOLID_FILL,bk);
		bar(0,menu_y1+5,menu_x1,menu_y2-5); 
		setcolor(GREY);
		setfillstyle(SOLID_FILL,GREY);
		bar(0,menu_y1+(menu_y2-menu_y1)/3,menu_x1,menu_y1+(menu_y2-menu_y1)/3+5);//horizontal barrier 1
		bar(0,menu_y1+2*(menu_y2-menu_y1)/3,menu_x1,menu_y1+2*(menu_y2-menu_y1)/3+5);//horizontal barrier 2
		setcolor(GREY);
		setbkcolor(bk);
		settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
		outtextxy(menu_x1/2,menu_y1+(menu_y2-menu_y1)/6+3,"TOP");
		outtextxy(menu_x1/2,menu_y1+(menu_y2-menu_y1)/2+3,"MIDDLE");
		outtextxy(menu_x1/2,menu_y2-(menu_y2-menu_y1)/6+3,"BOTTOM");
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN))
		{
			delay(100);
		}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if((x>0 && x<menu_x1) && (y>menu_y1 && y<menu_y1+(menu_y2-menu_y1)/3))/*TOP */
			score_pos=1;
		else if((x>0 && x<menu_x1) && (y>menu_y1+(menu_y2-menu_y1)/3 && y<2*(menu_y2-menu_y1)/3)) /* MIDDLE*/
			score_pos=2;
		else if((x>0 && x<menu_x1) && (y>2*(menu_y2-menu_y1)/3 && y<menu_y2))/*BOTTOM*/
			score_pos=3;
		printf("%d\n",score_pos);
	}
	else if((x>menu_x1 && x<menu_x2) && (y>menu_y1 && y<screen_y))
	{
		printf("SCORECARD VIEW\n");
		score_card();
	}
	else if((x>menu_x2 && x<menu_x3) && (y>menu_y1 && y<screen_y))
	{
		printf("BACK\n");
		first_page();
		return;
	}
	if(pausey!=1)
		settings_menu();
}
