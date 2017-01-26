#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<math.h>

union REGS i,o;
void graph();

void mouse()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
}
void hidemouse()
{
	i.x.ax=2;
	int86(0x33,&i,&o);
}

void getpos(int *a , int *b, int *button)
{
	i.x.ax=3;
	int86(0x33,&i,&o);

	*a=o.x.cx;
	*b=o.x.dx;
	*button=o.x.bx;
}

void restrict()
{
	i.x.ax=7;
	i.x.cx=110;
	i.x.dx=640;
	int86(0x33,&i,&o);
	i.x.ax=8;
	i.x.cx=1;
	i.x.dx=480;
	int86(0x33,&i,&o);
}

int drawcolor(int x,int y)
{
	int a;
	if(x>=525 && x<=550)
	{
		if(y>=300 && y<=325)
			a=1;
		if(y>=330 && y<=355)
			a=4;
		if(y>=360 && y<=385)
			a=7;
		if(y>=390 && y<=415)
			a=10;
		if(y>=420 && y<=445)
			a=13;
	}
	if(x>=555 && x<=580)
	{
		if(y>=300 && y<=325)
			a=2;
		if(y>=330 && y<=355)
			a=5;
		if(y>=360 && y<=385)
			a=8;
		if(y>=390 && y<=415)
			a=11;
		if(y>=420 && y<=445)
			a=14;
	}
	if(x>=585 && x<=610)
	{
		if(y>=300 && y<=325)
			a=3;
		if(y>=330 && y<=355)
			a=6;
		if(y>=360 && y<=385)
			a=9;
		if(y>=390 && y<=415)
			a=12;
		if(y>=420 && y<=445)
			a=15;
	}
	return a;
}

void draw()
{
	int x,y,a=1,b,z=1;
	int x1,y1,x2,y2;
	char c;
	while(!kbhit())
	{
		mouse();
		getpos(&x,&y,&b);
		while(b==1)
		{
			if(x>=525 && x<=575)
			{
				if(y>=5 && y<=55)
					a=1;
				if(y>=60 && y<=110)
					a=2;
				if(y>=115 && y<=165)
					a=3;
				if(y>=170 && y<=220)
					a=7;
			}

			if(x>=580 && x<=630)
			{
				if(y>=5 && y<=55)
					a=4;
				if(y>=60 && y<=110)
					a=5;
				if(y>=115 && y<=165)
					a=6;
				if(y>=170 && y<=220)
					a=8;
			}

			z=drawcolor(x,y);

			setcolor(z);
			setfillstyle(1,z);
			getpos(&x2,&y2,&b);
			if(a==1)
			{
				getpos(&x1,&y1,&b);
				x2=x1;
				y2=y1;
				while(b==1)
				{
					hidemouse();
					line(x1,y1,x2,y2);
					x1=x2;
					y1=y2;
					getpos(&x2,&y2,&b);
				}
			}
			if(a==2)
			{
				if(b==0)
					line(x,y,x2,y2);
			}
			if(a==3)
			{
				if(b==0)
				{
					hidemouse();
					rectangle(x,y,x2,y2);
				}
			}
			if(a==4)
			{
				if(b==0)
				{
					hidemouse();
					bar(x,y,x2,y2);
				}
			}
			if(a==5)
			{
				while(b==1)
				{
					getpos(&x1,&y1,&b);
					hidemouse();
					putpixel(x1,y1,z);
				}
			}
			if(a==6)
			{
				if(b==0)
				{
					hidemouse();
					ellipse(x,y,0,360,abs(x2-x),abs(y2-y));
				}
			}
			if(a==7)
			{
				clearviewport();
				graph();
			}
			if(a==8)
			{
				setfillstyle(1,0);
				setcolor(0);
				while(b==1)
				{
					getpos(&x2,&y2,&b);
					fillellipse(x2,y2,6,6);
				}
			}
		}
	}
}





void graph()
{
	int i,j,x,y,c=1;
	x=getmaxx();
	y=getmaxy();
	setcolor(15);
	line(520,0,520,480);
	for(i=5;i<=170;i+=55)
	{
		rectangle(525,i,575,i+50);
		rectangle(580,i,630,i+50);
	}
	setcolor(3);
	settextstyle(10,0,3);
	outtextxy(210,1,"PAINT");
	line(210,50,310,50);
	setcolor(3);
	setfillstyle(1,3);
	settextstyle(0,0,1);
	outtextxy(535,20,"FREE");
	outtextxy(535,30,"HAND");
	outtextxy(586,80,"PIXEL");
	outtextxy(530,190,"CLEAR");
	outtextxy(585,190,"ERASE");
	bar(585,20,625,40);
	line(530,70,570,100);
	rectangle(530,130,570,150);
	ellipse(605,140,0,360,20,10);

	for(j=300;j<=420;j+=30)
	{

		for(i=525;i<=590;i+=30)
		{
			setfillstyle(1,c++);
			bar(i,j,i+25,j+25);
		}
	}

	setviewport(0,0,520,y,2);
	draw();
}



void main()
{
	int gd=DETECT,gm;
	clrscr();
	initgraph(&gd,&gm,"C:\\turboc3\\bgi");
	graph();
	getch();
}