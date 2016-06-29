
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
		outtextxy(screen_left/2,screen_bottom/2,left_score);
		outtextxy(screen_end-(screen_left/2),screen_bottom/2,right_score);
	}

	else if(score_pos==3) /* score at bottom */
	{
		outtextxy(screen_left/2,screen_bottom-100,left_score);
		outtextxy(screen_end-(screen_left/2),screen_bottom-100,right_score);
	}
}

void score_card() 
{
	int x,y;
	int choice;
	int wid=(screen_y-205)/10;
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_x,screen_y);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(font);
    settextstyle(BOLD_FONT,HORIZ_DIR,9);
    outtextxy(screen_x/2,100,"SCORECARD VIEW");
	setfillstyle(SOLID_FILL,GREY);
	bar(0,150,screen_x,155);
	bar(0,200,screen_x,205);
	bar(0,205+(screen_y-200)/3,menu_x1,210+(screen_y-200)/3);
	bar(0,screen_y-(screen_y-200)/3,menu_x1,screen_y+5-(screen_y-200)/3);
	bar(0,screen_y-5,screen_x,screen_y);
	bar(menu_x1,150,menu_x1+5,screen_y);
	bar(menu_x2,150,menu_x2+5,screen_y);
	setcolor(font);
	setbkcolor(bk);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x1/2,185,"OPTIONS");
	outtextxy(menu_x1/2,205+(screen_y-200)/6,"SELECT SCOREBOARD COLOR");
	outtextxy(menu_x1/2,205+(screen_y-200)/3+(screen_y-200)/6,"SELECT BAT STYLE");
	outtextxy(menu_x1/2,screen_y-(screen_y-200)/3+(screen_y-200)/6,"BACK");
	
	starter:
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>0 && x<menu_x1 && y>200  && y<205+(screen_y-200)/3)
	{
		choice=1;
		setcolor(font);
		setfillstyle(SOLID_FILL,font);
		fillellipse(menu_x1/2,205+(screen_y-200)/12,10,10);
		setbkcolor(bk);
		setcolor(font);
		outtextxy(menu_x1+(menu_x1)/2,185,"SCOREBOARD COLOR");
		setfillstyle(SOLID_FILL,COLOR(157,149,115)); //Beige 100%
		bar(menu_x1+5,205,menu_x2,205+wid);
		setfillstyle(SOLID_FILL,COLOR(221,207,153)); //Sandstone
		bar(menu_x1+5,205+wid+1,menu_x2,205+2*wid);
		setfillstyle(SOLID_FILL,COLOR( 138,136,125)); // Gray 60%
		bar(menu_x1+5,205+2*wid+1,menu_x2,205+wid*3);
		setfillstyle(SOLID_FILL,COLOR(88,87,84)); //Black 80%
		bar(menu_x1+5,205+wid*3+1,menu_x2,205+wid*4);
		setfillstyle(SOLID_FILL,COLOR( 140,21,21)); //Cardinal red
		bar(menu_x1+5,205+wid*4+1,menu_x2,205+wid*5);
		setfillstyle(SOLID_FILL,COLOR(21, 52, 80)); //Elephant Midnight Blue
		bar(menu_x1+5,205+wid*5+1,menu_x2,205+wid*6);
		setfillstyle(SOLID_FILL,COLOR(56, 46, 28)); //Bistre
		bar(menu_x1+5,205+wid*6+1,menu_x2,205+wid*7);
		setfillstyle(SOLID_FILL,COLOR(173, 116, 96) ); //Santa fe
		bar(menu_x1+5,205+wid*7+1,menu_x2,205+wid*8);
		setfillstyle(SOLID_FILL,COLOR(198, 199, 140)); //Pine glade
		bar(menu_x1+5,205+wid*8+1,menu_x2,205+wid*9);
		setfillstyle(SOLID_FILL,COLOR(231, 195, 156)); //Cashmere 
		bar(menu_x1+5,205+wid*9+1,menu_x2,205+wid*10);
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN));
		getmouseclick(WM_LBUTTONDOWN, x, y);

		score_back=getpixel(x,y);

		setfillstyle(SOLID_FILL,score_back);
		bar(menu_x1/2- 40,210+(screen_y-200)/3-75,menu_x1/2+ 40,210+(screen_y-200)/3-25);
		setcolor(bk);
		setfillstyle(SOLID_FILL,bk);
		fillellipse(menu_x1/2,205+(screen_y-200)/12,10,10);
	}
	if (x>0 && x<menu_x1 && y>205+(screen_y-200)/3 && y<screen_y-(screen_y-200)/3 || choice==1)
	{
		choice=2;
		setcolor(font);
		setfillstyle(SOLID_FILL,font);
		fillellipse(menu_x1/2,205+(screen_y-200)/3+(screen_y-200)/12,10,10);
		setbkcolor(bk);
		setcolor(font);
		outtextxy(menu_x2+(menu_x1)/2,185,"BAT STYLE");
		setbkcolor(score_back);
		setfillstyle(0,bat_col); 
		bar(menu_x2+5,205,screen_x,205+wid);
		setfillstyle(1,bat_col);
		bar(menu_x2+5,205+wid+1,screen_x,205+2*wid);
		setfillstyle(2,bat_col); 
		bar(menu_x2+5,205+2*wid+1,screen_x,205+wid*3);
		setfillstyle(3,bat_col);
		bar(menu_x2+5,205+wid*3+1,screen_x,205+wid*4);
		setfillstyle(4,bat_col); 
		bar(menu_x2+5,205+wid*4+1,screen_x,205+wid*5);
		setfillstyle(5,bat_col);
		bar(menu_x2+5,205+wid*5+1,screen_x,205+wid*6);
		setfillstyle(6,bat_col); 
		bar(menu_x2+5,205+wid*6+1,screen_x,205+wid*7);
		setfillstyle(11,bat_col); 
		bar(menu_x2+5,205+wid*7+1,screen_x,205+wid*8);
		setfillstyle(8,bat_col); 
		bar(menu_x2+5,205+wid*8+1,screen_x,205+wid*9);
		setfillstyle(9,bat_col); 
		bar(menu_x2+5,205+wid*9+1,screen_x,205+wid*10);
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONDOWN));
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if(x>=menu_x2+5 && x<=screen_x)
		{
			bat_fill=(y-205-1)/wid;
			if(bat_fill==7)
				bat_fill=11;
		}
		setbkcolor(score_back);
		setfillstyle(bat_fill,bat_col);
		bar(menu_x1/2- 40,screen_y+5-(screen_y-200)/3-75,menu_x1/2+ 40,screen_y+5-(screen_y-200)/3-25);
		setfillstyle(SOLID_FILL,bk);
		bar(menu_x1+5,155,screen_x-5,screen_y-5);
		setfillstyle(SOLID_FILL,GREY);
		bar(menu_x1+5,200,screen_x,205);
		bar(menu_x2,150,menu_x2+5,screen_y);
		setcolor(bk);
		setfillstyle(SOLID_FILL,bk);
		fillellipse(menu_x1/2,205+(screen_y-200)/3+(screen_y-200)/12,10,10);
		goto starter;
	}
	else if (x>0 && x<menu_x1 && y>(screen_y-(screen_y-200)/3) && y<screen_end)
	{	
		choice=3;
		return ;
	}
	else if (x>menu_x1)
		goto starter;
}

void leaderboard(int n, int p)
{
	char scorer[1000];
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(menu_x2+5,205,menu_x3,screen_y-5); 
	setbkcolor(bk);
	setcolor(font);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x1,menu_y1,"CLICK ANYWHERE TO RETURN TO MENU");
	sprintf(scorer,"Best %d Results for Player %d",n,p);
	outtextxy(menu_x2+menu_x1/2,185,scorer); 
	for(m=0;m<n && m<=j[p];m++)
	{
		outtextxy(menu_x2+menu_x1/2,240+((screen_y-240)/n)*m,top[p][m]); 
	}
	r=0;
	l=0;
	//clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN));
}

void score_check(int n, int p) 
{
	m=0;
	struct record
	{
		int p1;
		int p2;
		int dif[3];
		char name[100];
	} list[550],temp;
	int rec1[1000][20],rec2[1000][20],x1[1000]={0},x2[1000]={0},ind,maxd[3],mind[3],num,last=0;
	int i,k,y,numx;
	fclose(score_list);
	score_list=fopen("score log.fs","r"); //CHeck
	fseek(score_list,0L,0);
	for(i=0;;i++)
	{
		fscanf(score_list,"%d %d %[^\n]s",&list[i].p2,&list[i].p1,list[i].name);//p2 = left, p1=right
		list[i].dif[1]=list[i].p1-list[i].p2;
		list[i].dif[2]=list[i].p2-list[i].p1;
		if(feof(score_list))
		{
			break;
		}
	}
	fclose(score_list);
	score_list=fopen("score log.fs","w");
	maxd[1]=-1;
	maxd[2]=-1;
	mind[1]=1050;
	mind[2]=1050;
	for(k=0;k<i;k++) // i is the number of total records
	{
		if(list[k].dif[1]>=0)
		{
			ind=list[k].dif[1]; //difference for player 1
			rec1[ind][x1[ind]++]=k;
			if(ind >maxd[1])
				maxd[1]=ind;
            if(ind <mind[1])
                mind[1]=ind;
		}
		if(list[k].dif[2]>=0)
		{
			ind=list[k].dif[2];
			rec2[ind][x2[ind]++]=k;
			if(ind >maxd[2])
				maxd[2]=ind;
            if(ind <mind[2])
                mind[2]=ind;
		}
	}
	for(k=maxd[1],j[1]=0;k>=mind[1] && j[1]<n;k--)
	{
        for(num=0;num<x1[k];num++)
        {
            for(numx=0;numx<x1[k]-1;numx++)
            {
                ind=rec1[k][numx];
                if(list[rec1[k][numx]].p1<list[rec1[k][numx+1]].p1)
                {
                    temp=list[rec1[k][numx]];
                    list[rec1[k][numx]]=list[rec1[k][numx+1]];
                    list[rec1[k][numx+1]]=temp;
                }
            }
        }
        for(num=0;num<x1[k] && j[1]<n;num++,j[1]++)
        {
            ind=rec1[k][num];
            fprintf(score_list,"%d %d %s\n",list[ind].p2,list[ind].p1,list[ind].name);            
			sprintf(top[1][j[1]],"%s %d - %d",list[ind].name,list[ind].p1,list[ind].p2);
        }
	}

	for(k=maxd[2],j[2]=0;k>=mind[2] && j[2]<n;k--)
	{
        for(num=0;num<x2[k];num++)
        {
            for(numx=0;numx<x2[k]-1;numx++)
            {
                ind=rec2[k][numx];
                if(list[rec2[k][numx]].p2<list[rec2[k][numx+1]].p2)
                {
                    temp=list[rec2[k][numx]];
                    list[rec2[k][numx]]=list[rec2[k][numx+1]];
                    list[rec2[k][numx+1]]=temp;
                }
            }
        }
        for(num=0;num<x2[k] && j[2]<n;num++,j[2]++)
        {
            ind=rec2[k][num];
			fprintf(score_list,"%d %d %s\n",list[ind].p2,list[ind].p1,list[ind].name);            
			sprintf(top[2][j[2]],"%s %d - %d",list[ind].name,list[ind].p2,list[ind].p1);
        }
	}
	if(used ==2 && p==2 )
	{
		last=list[j[2]-1].dif[2];
		if((l-r)<last)
			elim=1;
		if( j[2]<n)
			elim=0;
	}
	else if(used ==2 && p==1 )
	{
		last=list[j[1]-1].dif[1];
		printf("%d\n",last);
		if((r-l)<last)
			elim=1;
		if( j[1]<n)
			elim=0;
	}
	if(j[p]<n)
	{
		if(j[p]==0)
			sprintf(top[p][j[p]],"Sorry, But you never won with us");
		else
			sprintf(top[p][j[p]],"Sorry you won only %d times",j[p]);
	}
	fclose(score_list);
	if(used!=2)
		leaderboard(n,p);
}


void user_input(int us)
{
	char nameinput[100];
	int bk= COLOR(255,255,240);
	setbkcolor(score_back);
	settextjustify(CENTER_TEXT, TOP_TEXT);
	setcolor(score_col);
	settextstyle(BOLD_FONT,HORIZ_DIR,6);
	sprintf(nameinput,"PLAYER %d is the winner",us);
	outtextxy(screen_x/2,screen_bottom+2,nameinput);

	int color=COLOR(255,255,240);
	int d=(screen_x-450)/4;
	int h=150;
	int x,y;
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	bar(0,screen_bottom+50,screen_x,screen_bottom+100);
	setbkcolor(color);
	settextjustify(LEFT_TEXT, CENTER_TEXT);
	setcolor(score_back);
	settextstyle(FONT,HORIZ_DIR,FONT_SIZE);
	outtextxy(h/2,screen_bottom+80,"ENTER YOUR NAME:");
	int l=h/2 + textwidth("ENTER YOUR NAME:")+20;
	int i;
	rewind( stdin );
	for(i=0;;i++)
	{
		username[i]=getch();
		if(username[i]=='\b')
		{
			if(i>0)
				i-=2; // if there is at least two valid letter, we go two spaces back & then because of the loop, i++.so the last letter gets eliminated
			else if(i==0)
			{
				username[i]=0; // when you don't have any character and you still press backspace, the string is NULL
				i=i-1; // i=i-1 , so after the loop i=0;
			}
			setfillstyle(SOLID_FILL,color);
			bar(l,screen_bottom+50,l+textwidth(username),screen_bottom+100);
			printf("%d\n",i);
		}
		else if(username[i]=='\r')
			break;
		username[i+1]=0;
		outtextxy(l,screen_bottom+80,username);
	}
	puts(username);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,getmaxwidth(),getmaxheight());
}


void score_menu()
{
	int x,y,n,p;
	int bk= COLOR(255,255,240);
	int font=COLOR(255,165,0);
	setfillstyle(SOLID_FILL,bk);
	bar(0,0,screen_x,screen_y);
	setbkcolor(bk);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(font);
    settextstyle(BOLD_FONT,HORIZ_DIR,8);
    outtextxy(screen_x/2,100,"BEST RECORDS");
	setfillstyle(SOLID_FILL,GREY);
	bar(0,150,screen_x,155);
	bar(0,200,screen_x,205);
	bar(0,menu_y1,screen_x,menu_y1+5);
	bar(0,screen_y-5,screen_x,screen_y);
	bar(menu_x1,150,menu_x1+5,screen_y);
	bar(menu_x2,150,menu_x2+5,screen_y);
	setcolor(font);
	setbkcolor(bk);
	settextstyle(FONT,HORIZ_DIR,3);
	outtextxy(menu_x1/2,185,"Select Player");
	outtextxy(menu_x1/2,200+menu_ymid,"Player 1");
	outtextxy(menu_x1/2,menu_y1+menu_ymid,"Player 2");

	player_select:
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>0 && x<menu_x1 && y>200  && y<menu_y1)
	{
		p=1;
		setcolor(COLOR(255,165,0));
		setfillstyle(SOLID_FILL,COLOR(255,165,0));
		fillellipse(100,200+menu_ymid-5,10,10);
	}
	else if (x>0 && x<menu_x1 && y>menu_y1 && y<screen_y)
	{
		p=2;
		setcolor(COLOR(255,165,0));
		setfillstyle(SOLID_FILL,COLOR(255,165,0));
		fillellipse(100,menu_y1+menu_ymid-10,10,10);
	}
	else 
		goto player_select;

	outtextxy(menu_x1+(menu_x1)/2,185,"Number of Records");
	outtextxy(menu_x1+(menu_x1)/2,200+menu_ymid,"5");
	outtextxy(menu_x1+(menu_x1)/2,menu_y1+menu_ymid,"10");
	
	record_select:
	clearmouseclick(WM_LBUTTONDOWN);
	while(!ismouseclick(WM_LBUTTONDOWN))
	{
		delay(100);
	}
	getmouseclick(WM_LBUTTONDOWN, x, y);

	if(x>menu_x1 && y>200 && x<menu_x2 && y< menu_y1)
		n=5;
	else if (x>menu_x1 && y>menu_y1 && x<menu_x2 && y<screen_y)
		n=10;
	else
		goto record_select;
	setfillstyle(SOLID_FILL,bk);
	bar(0,155,menu_x2,screen_y-5);
	outtextxy(menu_x1,menu_y1,"CLICK ANYWHERE TO RETURN TO MENU");
	used=1;
	score_check(n,p);
}