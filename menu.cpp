#include <stdio.h>
#include <graphics.h>

mouse_msg mouse = {0};
bool mouse_isleft;

bool get_mouse_select(int left,int top,int right,int bottom)
{
	if(mouse.x>=left && mouse.x<=right && mouse.y>=top && mouse.y<=bottom)
		return(1);
	else
		return(0);
}

int main()
{
	setinitmode(INIT_ANIMATION);
	initgraph(300,500);
	setbkcolor(WHITE);
	
	while(is_run())
	{
		while(mousemsg())
		{
			mouse = getmouse();
			mouse_isleft = mouse.is_left();
		}
	
		setfillcolor(BLUE);
		bar(20,20,280,120);
		bar(20,140,280,240);
		bar(20,260,280,360);
		bar(20,380,280,480);
		
		if(get_mouse_select(20,20,280,120))
		{
			setfillcolor(RED);
			bar(20,20,280,120);
			
			if(mouse_isleft)
			{
				mouse_isleft=0;
				setfillcolor(GREEN);
				bar(20,20,280,120);
				Sleep(1000);
			}
		}
		if(get_mouse_select(20,140,280,240))
		{
			setfillcolor(RED);
			bar(20,140,280,240);
			
			if(mouse_isleft)
			{
				mouse_isleft=0;
				setfillcolor(GREEN);
				bar(20,140,280,240);
				Sleep(1000);
			}
		}
		if(get_mouse_select(20,260,280,360))
		{
			setfillcolor(RED);
			bar(20,260,280,360);
			
			if(mouse_isleft)
			{
				mouse_isleft=0;
				setfillcolor(GREEN);
				bar(20,260,280,360);
				Sleep(1000);
			}
		}
		if(get_mouse_select(20,380,280,480))
		{
			setfillcolor(RED);
			bar(20,380,280,480);
			
			if(mouse_isleft)
			{
				mouse_isleft=0;
				setfillcolor(GREEN);
				bar(20,380,280,480);
				Sleep(1000);
			}
		}
		
		delay_fps(60);
		cleardevice();
	}
}
