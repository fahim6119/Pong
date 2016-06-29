void ball_create()
{
		ball_clear();
        setcolor(ball_col);
        setfillstyle(SOLID_FILL,ball_col);
        fillellipse(ball_x,ball_y,ball_radius,ball_radius);
		prex=ball_x;
		prey=ball_y;
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
        fillellipse(prex,prey,ball_radius,ball_radius);
		setcolor(score_back);
		setfillstyle(SOLID_FILL,score_back);
		bar(0,screen_bottom,screen_x,screen_bottom+50);
}

void ball_limit_control() /*Seg 1 */
{

    if(ball_x>= bat_pos_left && ball_x -ball_radius <= bat_pos_left+bat_width && ball_y + ball_radius >= left_baty && ball_y - ball_radius <= left_baty + bat_size)	
        {
			if(ball_x>= bat_pos_left+bat_width/2 && ball_x -ball_radius <= bat_pos_left+bat_width)
				f=1;       //ball touches the left bat & direction of the ball is changed to rightward.
			if(ball_y-ball_radius<=left_baty && g==1) //ball is above the left bat
				g=0;
			else if(ball_y+ball_radius>= left_baty + bat_size && g==0)//ball is below the left bat
				g=1;

			if(ball_y-ball_radius<=left_baty || ball_y+ball_radius>= left_baty + bat_size) //corner case
			{
				if(dev>8)
					dev-=2; 
				ball_speed_x=10;
				ball_speed_y=6;
			}
			else if(ball_y-ball_radius>left_baty && ball_y+ball_radius < left_baty + bat_size) //
			{
				ball_speed_x=9;
				ball_speed_y=9;
			}
		}

	else if(ball_x+ball_radius>= bat_pos_right && ball_x<= bat_pos_right+bat_width && ball_y + ball_radius >= right_baty && ball_y - ball_radius <= right_baty + bat_size)	
        {
			if(ball_x<= bat_pos_right+bat_width/2 && ball_x +ball_radius >= bat_pos_right)
				f=0;       //ball touches the left bat & direction of the ball is changed to rightward.
			if(ball_y-ball_radius<=right_baty && g==1) //ball is above the left bat
				g=0;
			else if(ball_y+ball_radius>= right_baty + bat_size && g==0)//ball is below the left bat
				g=1;

			if(ball_y-ball_radius<=right_baty || ball_y+ball_radius>= right_baty + bat_size) //corner case
			{
				if(dev>8)
					dev-=2; 
				ball_speed_x=10;
				ball_speed_y=6;
			}
			else if(ball_y-ball_radius>right_baty && ball_y+ball_radius < right_baty + bat_size) //
			{
				ball_speed_x=9;
				ball_speed_y=9;
			}
		}

    if(ball_x<= bat_pos_left-20)	
    {									// BALL misses the left bat
        f=1;
		dev=SPEED;
		ball_speed_x=10;
		ball_speed_y=10;
        ball_x=screen_mid;						// BALL starts again from the mid position 
        r++; // one score is added to the right side
		ball_clear();
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
		ball_clear();
		if(SOUND!=0)
			Beep(SOUND,500);
		else 
			delay(500);
    }
	 
	if(ball_y-ball_radius<=screen_top)										
	{
		g=1; // if BALL touches the upper bound of window, direction is changed to downward
		ball_speed_x=8;
		ball_speed_x=7;
	}
    else if(ball_y+ball_radius>=screen_bottom)
	{
		g=0;
		ball_speed_x=8;
		ball_speed_x=5;
		setcolor(score_back);
		setfillstyle(SOLID_FILL,score_back);
		bar(0,screen_bottom,screen_end,screen_bottom+50);
	}
}



void bat_clear()
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    bar(bat_pos_left, screen_top, bat_pos_left+bat_width, left_baty);
    bar(bat_pos_left, left_baty+bat_size, bat_pos_left+bat_width, screen_bottom);
    bar(bat_pos_right, screen_top, bat_pos_right+bat_width, right_baty);
    bar(bat_pos_right, right_baty+bat_size,bat_pos_right+bat_width, screen_bottom);
}


void bat_create()
{
    while(kbhit())				//takes input for moving Bats
    {
		setcolor(BLACK);
		setfillstyle(SOLID_FILL,BLACK);
		bar(bat_pos_left,left_baty,bat_pos_left+bat_width,left_baty+bat_size); 
       input_key=getch();
	   if(input_key==27)
	   {
		   	pausey=1;
			pause();
			if(quit==1)
				return;
	   }
       if(input_key==left_bat_up && left_baty-bat_size>=0)
	        left_baty-=bat_speed;							//changing the postion of left bat
	   else if(input_key==left_bat_up && left_baty-bat_size<0)
	        left_baty=0;
	   else if(input_key==left_bat_down && left_baty+bat_size+bat_speed>screen_bottom)
			left_baty=screen_bottom-bat_size;
	   else if(input_key==left_bat_down && left_baty+bat_size<=screen_bottom) //screen limit =700, so last end of bat has to be inside 580 
			left_baty+=bat_speed;
	   rewind( stdin );
		setcolor(bat_col);
		setfillstyle(bat_fill,bat_col);
		bar(bat_pos_left,left_baty,bat_pos_left+bat_width,left_baty+bat_size); 
    }
	if(ismouseclick(WM_MOUSEMOVE))
		right_baty=mousey();
	if(right_baty>=screen_bottom-bat_size)
		right_baty=screen_bottom-bat_size;
	else if (pausey==1)
	{
		right_baty=bat_pause_y;
		pausey=0;
	}
	setcolor(bat_col);
    setfillstyle(bat_fill,bat_col);
	bar(bat_pos_left,left_baty,bat_pos_left+bat_width,left_baty+bat_size); 
	bar(bat_pos_right,right_baty,bat_pos_right+bat_width,right_baty+bat_size);
}


void pause()
{
	setcolor(bat_col);
    setfillstyle(bat_fill,bat_col);
	bar(bat_pos_left,left_baty,bat_pos_left+bat_width,left_baty+bat_size); 
	bar(bat_pos_right,right_baty,bat_pos_right+bat_width,right_baty+bat_size);
	bat_pause_y=right_baty;
	setbkcolor(score_back);
	settextjustify(CENTER_TEXT, TOP_TEXT);
	setcolor(score_col);
	settextstyle(BOLD_FONT,HORIZ_DIR,6);
	outtextxy(screen_end/2,screen_bottom+2,"GAME PAUSED");

	int color=COLOR(255,255,240);
	int d=(screen_x-450)/4;
	int h=150;
	int x,y;
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	bar(0,screen_bottom+50,screen_x,screen_bottom+100);
	setbkcolor(color);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(score_back);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(h/2,screen_bottom+80,"PRESS KEY :");
	outtextxy(d+h/2,screen_bottom+80,"QUIT (Q) ");
	outtextxy(2*d+h+h/2,screen_bottom+80,"RESUME (ESC)");
	outtextxy(3*d+2*h+h/2,screen_bottom+80,"SETTINGS (S) ");
	
	again:
	control_l=getch();

	if(control_l=='q' ||control_l=='Q')
		control_l=1;
	else if (control_l=='s' ||control_l=='S')
		control_l=2;
	else if (control_l==27)
		control_l=3;
	else 
		goto again;
	if(control_l==1)
	{
		quit=1;
		return;
	}
	else if(control_l==2)
	{
		writeimagefile("Paused.bmp",0,0,screen_x,screen_y);
		settings_menu();
		pausey=0;
		readimagefile("Paused.bmp",0,0,screen_x,screen_y);
		goto again;
	}
	setfillstyle(SOLID_FILL,score_back);
	bar(0,screen_bottom,screen_x,screen_y);
	bar(0,0,screen_left,screen_bottom);
	bar(screen_right,0,screen_x,screen_bottom);
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
	g_o=1;
    delay(1000);						// delay after WIN
	int us;
	if(l>r)
		us=2;
	else if(r>l)
		us=1;
	else if(l==r)
		return;
	used=2;
	score_check(10,us);
	printf("%d %d\n",elim,us);
	if(elim!=1)
	{
		score_list=fopen("score log.fs","a");
		user_input(us);
		fprintf(score_list,"%d %d %s\n",l,r,username);
		l=r=0;							// score 0-0
		SPEED=15;
		used=0;
		int bk= COLOR(255,255,240);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		setbkcolor(bk);
		setcolor(COLOR(255,165,0));
		settextstyle(BOLD_FONT,HORIZ_DIR,5);
		outtextxy(menu_x2+menu_x1/2,75,"LEADERBOARD");
		setfillstyle(SOLID_FILL,GREY);
		bar(menu_x2,150,screen_x,155);
		bar(menu_x2,150,menu_x2+5,screen_y);
		bar(menu_x2,200,screen_x,205);
		score_check(10,us);
		leaderboard(10,us);
	}

}

void play()
{
	if(screen_right-screen_left>550)
			det=D_H;
		else
			det=D_E;
		begin:
		first_page();
		delay(100);
		cleardevice();
		setbkcolor(BLACK);
		background();
		prex=screen_left+10,prey=screen_bottom+ball_radius;
		time(&start_t);
		while(1)
		{	
			setcolor(WHITE);
				setlinestyle(DASHED_LINE,3,1);
				line(screen_mid,screen_top,screen_mid,screen_bottom);

				//ball_clear();

				ball_movement(); //movement of ball

				bat_create();
				if(quit==1)
					goto gamer;
		
				bat_clear();

				ball_create();

				delay(dev);

				ball_limit_control();

				score();

				if(l==high_score || r==high_score)
					game_over();
						else if(mode==2)
				{
					timel();
					time_t timer=end_t-start_t; // returns the time between start and current time
					if(timel()==1) // returns 1 when time is up
					{
						game_over();
						mode=1;
						high_score=10;
					}
					timey=timez;//previous timez
					timez=TIME-timer; // countdown timer
					sprintf(timex,"%d",timez);
					// We will print the timer once every second, so timey-timez==1 
					if(score_pos==2 &&( timey-timez==1 ||timez==TIME) ) /* score at middle,so timer at bottom */
					{
						setcolor(score_back);
						setfillstyle(SOLID_FILL,score_back);
						bar(0,screen_bottom/2+75,screen_left,screen_bottom);
						bar(screen_right,screen_bottom/2+75,screen_end,screen_bottom); 
						setbkcolor(score_back);
						settextjustify(CENTER_TEXT, CENTER_TEXT);
						setcolor(COLOR(255,165,0));
						settextstyle(3,HORIZ_DIR,4);
						outtextxy(screen_left/2,screen_bottom-100,timex);
						outtextxy(screen_end-(screen_left/2),screen_bottom-100,timex);
					}
					else if( timey-timez==1 ||timez==TIME)  /* score not at middle  , so timer at Middle */
					{
						setcolor(score_back);
						setfillstyle(SOLID_FILL,score_back);
						bar(0,screen_bottom/2-100,screen_left,screen_bottom/2+100);
						bar(screen_right,screen_bottom/2-100,screen_end,screen_bottom/2+100); 
						setbkcolor(score_back);
						settextjustify(CENTER_TEXT, CENTER_TEXT);
						setcolor(COLOR(255,165,0));
						settextstyle(3,HORIZ_DIR,4);
						outtextxy(screen_left/2,screen_bottom/2,timex);
						outtextxy(screen_end-(screen_left/2),screen_bottom/2,timex);
					}
					settextjustify(CENTER_TEXT, CENTER_TEXT);
				}
				gamer:
				if(quit==1)
				{
					//last_page();
					quit=0; //  Quitting is complete
					l=0,r=0; // initialize the scores to 0
					g_o=1; // so that quit works as Game Over
					ball_x=screen_mid; // initialize the ball to the middle, so the next game starts from the middle
				}
				if(g_o==1)
				{
					g_o=0;
					goto begin;
				}
		
		}
	
}


void start_pong()
{
	int bk= COLOR(255,255,240);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_x,screen_y);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(COLOR(255,165,0));
    settextstyle(BOLD_FONT,HORIZ_DIR,10);
    outtextxy(screen_x/2,150,"PONG");

	settextjustify(RIGHT_TEXT, TOP_TEXT);
	setcolor(COLOR(154,205,50));
    settextstyle(FONT,HORIZ_DIR,4);
    outtextxy(screen_x/2+250,180,"Edition 6.8");
	settextjustify(RIGHT_TEXT, TOP_TEXT);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(screen_x-10,screen_y-100,"Designed and Developed By :");
	outtextxy(screen_x-10,screen_y-50,"Md.Shorifuzzaman and Fahim Arefin");
	settextjustify(LEFT_TEXT, TOP_TEXT);
	if(flag==0)
	{
		left_bat_up=72;
		left_bat_down=80;
	}
	flag=1;
}

int timel()
{
	double diff_t;
	int time_flag=0;
    time(&end_t);
    diff_t = difftime(end_t, start_t);
    if(diff_t-TIME==1)
		time_flag=1;
	return time_flag;
}

