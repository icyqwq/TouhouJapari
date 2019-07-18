/***************************MapEditor*************************/
/*Version:			Beta 									 */
/*LastTestDate:		2017/8/21								 */
/*Editor:			TongYihan 16160500301					 */
/*Email:			icyqwq@gmail.com / tongyihan@pcb.moe	 */
/******************************m******************************/
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <unistd.h>
#include <stdlib.h>

#define WindowSize_L		1155
#define WindowSize_H		660
#define EditorScope			135
#define EditObject_Amount	13	//�༭��֧�ֵĶ���������Ŀ 
#define Block_Amount		10	//�ϰ���������Ŀ
#define Enemy_Amount		1	//�ж�����������Ŀ 
#define Editor_Row			11
#define Editor_Column		17
#define PAGE				8	//ҳ���� 
#define AREA_SelectBlock_0		5,5,65,65		//x1,y1,x2,y2
#define AREA_SelectBlock_1		5,70,65,130
#define AREA_SelectBlock_2		5,135,65,195
#define AREA_SelectBlock_3		5,200,65,260
#define AREA_SelectBlock_4		5,265,65,325
#define AREA_SelectBlock_5		5,330,65,390
#define AREA_SelectBlock_6		5,395,65,455
#define AREA_SelectBlock_7		70,5,130,65
#define AREA_SelectBlock_8		70,70,130,130
#define AREA_SelectBlock_9		70,135,130,195
#define AREA_Cerulean_Blue		70,200,130,260	
#define AREA_Cerulean_Pink		70,265,130,325	
#define AREA_Japari_mantou		70,330,130,390	
#define AREA_GUI_RightArrow		100,535,130,566
#define AREA_GUI_LeftArrow		5,535,35,566
#define AREA_GUI_Save			53,535,82,565
#define Coordinate_Preview		36,590

#define Cerulean_Blue_Length	50
#define Cerulean_Blue_Width		60
#define Cerulean_Blue_Damage	-100
#define Cerulean_Pink_Length	50
#define Cerulean_Pink_Width		60
#define Cerulean_Pink_Damage	-100

#define MouseSelect_Block		Mouse_NowSelect >= 0 && Mouse_NowSelect < Block_Amount
#define MouseSelect_Enemy		Mouse_NowSelect >= Block_Amount && Mouse_NowSelect < EditObject_Amount

typedef struct Object_Parameter{
	int x;
	int y;
	int Length;
	int Width;
	int type;
	int page;
	int number;
	int Damage;
	Object_Parameter *prev;
	Object_Parameter *next;
}Object_Parameter;

Object_Parameter *Linklist_Head = NULL;
Object_Parameter *Linklist_End = NULL;
Object_Parameter *Linklist_New = NULL;

PIMAGE Object_Type[EditObject_Amount];
PIMAGE Block_Clear;
PIMAGE GUI_RightArrow;
PIMAGE GUI_LeftArrow;
PIMAGE GUI_Save;
PIMAGE GUI_NumberClear;
PIMAGE Change_PageSave[PAGE];

FILE* stream;
mouse_msg Mouse = {0};

char StringSave[10];
bool EditorArea_Status[PAGE][Editor_Row][Editor_Column];
int Page_BlockAmount[PAGE];//ҳ������
int Page_EnemyAmount[PAGE];
int Edit_Page = 0;
int EditArea_Column = 200;
int EditArea_Row = 0;
int EditSelect_Number = -1;
int Animation_EditselectX = EditorScope+1;
int Animation_EditselectY = 1;
int LastSelect = -2;
int Mouse_NowSelect = -2;
int Mouse_RLflag = 0;//-1 Left	1 Right  0 NULL
bool Mouse_isEditor = 0; //1 Editor

Object_Parameter* Linklist_Creat(void);
void Linklist_Printf(Object_Parameter*);
void Linklist_Delete(int,int,bool);
void Graphics_Init(void);
void Graphics_AuxiliaryGrid(int);
bool Check_MouseLocation(int,int,int,int);
int Check_MouseChosen(void);
void Process_MouseChosen(void);
void LinklistData_Save(Object_Parameter*);
bool Change_Page(bool);
Object_Parameter** MapFile_Read(void);

/************************************/
/*�������� main 					*/
/*��  �ܣ� ������			 		*/
/*��  ���� 		 					*/
/*����ֵ�� 		 					*/
/************************************/
int main()
{
	
	Graphics_Init();
	Graphics_AuxiliaryGrid(60);
	Sleep(10);
	
	Linklist_Head = Linklist_Creat();
	Linklist_End = Linklist_Head;
	
	while(1){
		Process_MouseChosen();
//		printf("%d\t%d\t%d\t[%d,%d]\n",EditSelect_Number,Mouse_NowSelect,Mouse_RLflag,EditArea_Column,EditArea_Row);
		Sleep(1);
	}
	
	getch();
}

/************************************/
/*�������� Graphics_Init			*/
/*��  �ܣ� ͼ��ϵͳ��ʼ��		 	*/
/*��  ���� 		 					*/
/*����ֵ�� 		 					*/
/************************************/
void Graphics_Init(void)
{
	int i;
	setinitmode(0);
	initgraph(WindowSize_L,WindowSize_H);
	setcaption("MapEditor");
	setbkcolor(BLACK);
	setfillcolor(EGERGB(190,190,190));
	setbkmode(TRANSPARENT);
	setfont(20,0,"����",0,0,1000,0,0,0);
	setcolor(EGERGB(0,0,128));
	setlinestyle(SOLID_LINE,0,3);

	for(i=0;i<EditObject_Amount;i++)
		Object_Type[i] = newimage();
	for(i=0;i<PAGE;i++)
		Change_PageSave[i] = newimage();
		
	Block_Clear = newimage();
	GUI_RightArrow = newimage();
	GUI_LeftArrow = newimage();
	GUI_Save = newimage();
	GUI_NumberClear = newimage();
	
	getimage_pngfile(Object_Type[0],"ScenesImage\\block_img0.png");
	getimage_pngfile(Object_Type[1],"ScenesImage\\block_img1.png");
	getimage_pngfile(Object_Type[2],"ScenesImage\\block_img2.png");
	getimage_pngfile(Object_Type[3],"ScenesImage\\block_img3.png");
	getimage_pngfile(Object_Type[4],"ScenesImage\\block_img4.png");
	getimage_pngfile(Object_Type[5],"ScenesImage\\block_img5.png");
	getimage_pngfile(Object_Type[6],"ScenesImage\\block_img6.png");
	getimage_pngfile(Object_Type[7],"ScenesImage\\block_img7.png");
	getimage_pngfile(Object_Type[8],"ScenesImage\\block_img8.png");
	getimage_pngfile(Object_Type[9],"ScenesImage\\block_img9.png");
	getimage_pngfile(Object_Type[10],"EditorImage\\Cerulean_Blue.png");
	getimage_pngfile(Object_Type[11],"EditorImage\\Cerulean_Pink.png");
	getimage_pngfile(Object_Type[12],"EditorImage\\japari.png");
	getimage_pngfile(GUI_RightArrow,"EditorImage\\RightArrow.png");
	getimage_pngfile(GUI_LeftArrow,"EditorImage\\LeftArrow.png");
	getimage_pngfile(GUI_Save,"EditorImage\\Save.png");
	
	bar(0,0,EditorScope,WindowSize_H);
	putimage_withalpha(NULL,Object_Type[0],5,5);		//���0 
	putimage_withalpha(NULL,Object_Type[1],5,70);		//���1
	putimage_withalpha(NULL,Object_Type[2],5,135);		//���2
	putimage_withalpha(NULL,Object_Type[3],5,200);		//���3
	putimage_withalpha(NULL,Object_Type[4],5,265);		//���4
	putimage_withalpha(NULL,Object_Type[5],5,330);		//���5
	putimage_withalpha(NULL,Object_Type[6],5,395);		//���6
	putimage_withalpha(NULL,Object_Type[7],70,5);		//���7
	putimage_withalpha(NULL,Object_Type[8],70,70);		//���8
	putimage_withalpha(NULL,Object_Type[9],70,135);		//���9
	putimage_withalpha(NULL,Object_Type[10],70,200);	//���10
	putimage_withalpha(NULL,Object_Type[11],70,265);	//���11
	putimage_withalpha(NULL,Object_Type[12],70,330);	//���12
	putimage_withalpha(NULL,GUI_LeftArrow,5,535);		//���15
	putimage_withalpha(NULL,GUI_RightArrow,100,535);	//���16
	putimage_withalpha(NULL,GUI_Save,53,535);			//���17

	line(33,587,33,653);
	line(33,587,99,587);
	line(33,653,99,653);
	line(99,587,99,653);
	
	getimage(GUI_NumberClear,0,465,50,20);
	outtextxy(5,490,"X");
	outtextxy(70,490,"Y");
	outtextxy(5,465,"PAGE:");
	sprintf(StringSave,"%d",Edit_Page);
	outtextxy(65,465,StringSave);
}

/************************************/
/*��������Graphics_AuxiliaryGrid	*/
/*��  �ܣ����Ƹ�������			 	*/
/*��  ����������					*/
/*����ֵ�� 		 					*/
/************************************/
void Graphics_AuxiliaryGrid(int Spacing)
{
	int Grid;
	setcolor(EGERGB(255,255,254));
	setlinestyle(SOLID_LINE,0,1);
	for(Grid=EditorScope;Grid<WindowSize_L;Grid+=Spacing){
		line(Grid,0,Grid,WindowSize_H);
	}
	for(Grid=0;Grid<WindowSize_H;Grid+=Spacing){
		line(EditorScope,Grid,WindowSize_L,Grid);
	}
	getimage(Block_Clear,EditorScope,0,60,60);
	for(Grid=0;Grid<PAGE;Grid++)
		getimage(Change_PageSave[Grid],EditorScope,0,WindowSize_L,WindowSize_H);
	setcolor(EGERGB(0,0,128));
}

/************************************/
/*��������Check_MouseLocation		*/
/*��  �ܣ�ȷ������Ƿ�������	 	*/
/*��  ��������						*/
/*����ֵ��1�ڵ�ǰ���� 0���ڵ�ǰ����	*/
/************************************/
bool Check_MouseLocation(int x1,int y1,int x2,int y2)
{
	if(Mouse.x>=x1)
		if(Mouse.x<=x2)
			if(Mouse.y>=y1)
				if(Mouse.y<=y2)
					return(1);
	return(0);
}

/************************************/
/*��������Check_MouseChosen			*/
/*��  �ܣ�ȷ�����ѡ�������	 	*/
/*��  ����							*/
/*����ֵ��ѡ��������				*/
/*		  -1 �༭��		-2 δѡ��	*/ 
/************************************/
int Check_MouseChosen(void)
{
	setfillcolor(0xBEBEBE);
	while(mousemsg())
	{
		Mouse = getmouse();
	}
	
	if(Mouse.x<=EditorScope)
	{
		Mouse_isEditor = 0;
		if(Check_MouseLocation(AREA_SelectBlock_0)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 0;
			putimage_withalpha(NULL,Object_Type[0],Coordinate_Preview);
			return(0);
		}
			
		if(Check_MouseLocation(AREA_SelectBlock_1)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 1;
			putimage_withalpha(NULL,Object_Type[1],Coordinate_Preview);
			return(1);
		}
			
		if(Check_MouseLocation(AREA_SelectBlock_2)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 2;
			putimage_withalpha(NULL,Object_Type[2],Coordinate_Preview);
			return(2);
		}
			
		if(Check_MouseLocation(AREA_SelectBlock_3)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 3;
			putimage_withalpha(NULL,Object_Type[3],Coordinate_Preview);
			return(3);
		}
			
		if(Check_MouseLocation(AREA_SelectBlock_4)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 4;
			putimage_withalpha(NULL,Object_Type[4],Coordinate_Preview);
			return(4);
		}
		if(Check_MouseLocation(AREA_SelectBlock_5)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 5;
			putimage_withalpha(NULL,Object_Type[5],Coordinate_Preview);
			return(5);
		}
			
		if(Check_MouseLocation(AREA_SelectBlock_6)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 6;
			putimage_withalpha(NULL,Object_Type[6],Coordinate_Preview);
			return(6);
		}
			
		if(Check_MouseLocation(AREA_SelectBlock_7)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 7;
			putimage_withalpha(NULL,Object_Type[7],Coordinate_Preview);
			return(7);
		}
			
		if(Check_MouseLocation(AREA_SelectBlock_8)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 8;
			putimage_withalpha(NULL,Object_Type[8],Coordinate_Preview);
			return(8);
		}
					
		if(Check_MouseLocation(AREA_SelectBlock_9)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 9;
			putimage_withalpha(NULL,Object_Type[9],Coordinate_Preview);
			return(9);
		}
		
		if(Check_MouseLocation(AREA_Cerulean_Blue)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 10;
			putimage_withalpha(NULL,Object_Type[10],Coordinate_Preview);
			return(10);
		}
		
		if(Check_MouseLocation(AREA_Cerulean_Pink)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 11;
			putimage_withalpha(NULL,Object_Type[11],Coordinate_Preview);
			return(11);
		}
		
		if(Check_MouseLocation(AREA_Japari_mantou)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 12;
			putimage_withalpha(NULL,Object_Type[12],Coordinate_Preview);
			return(12);
		}
			
		if(Check_MouseLocation(AREA_GUI_LeftArrow)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Change_Page(0);
			Mouse_NowSelect = 15;
			return(15);
		}
			
		if(Check_MouseLocation(AREA_GUI_RightArrow)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Change_Page(1);
			Mouse_NowSelect = 16;
			return(16);
		}

		if(Check_MouseLocation(AREA_GUI_Save)&&Mouse.is_left())
		{
			floodfill(Coordinate_Preview,EGERGB(0,0,128));
			Mouse_NowSelect = 17;
			LinklistData_Save(Linklist_Head);
			return(17);
		}
			
		return(-2);
	}
	else{
		int number=0;
		Mouse_isEditor = 1;
		if(Mouse.is_down()){
			if(Mouse.is_left())
				Mouse_RLflag = -1;
			if(Mouse.is_right())
				Mouse_RLflag = 1;
			}
			else
				Mouse_RLflag = 0;
		EditArea_Column = Mouse.x-EditorScope;
		EditArea_Row = Mouse.y;
		EditArea_Column /= 60;
		EditArea_Row /= 60;
		EditSelect_Number = EditArea_Row * Editor_Column + EditArea_Column;
		
		number = EditArea_Column*60;
		sprintf(StringSave,"%d",number);
		putimage(20,490,GUI_NumberClear);
		outtextxy(20,490,StringSave);
		number = EditArea_Row*60;
		sprintf(StringSave,"%d",number);
		putimage(85,490,GUI_NumberClear);
		outtextxy(85,490,StringSave);
		
		return(-1);
	}
}

/************************************/
/*��������Process_MouseChosen		*/
/*��  �ܣ����������Ϣ				*/
/*��  ����							*/
/*����ֵ��							*/
/************************************/
void Process_MouseChosen(void)
{	
	Check_MouseChosen();
	
	if(Mouse_isEditor)
	{
		if(Mouse_RLflag == -1 && Mouse_NowSelect>=0 && Mouse_NowSelect<EditObject_Amount)
		{
			if(!EditorArea_Status[Edit_Page][EditArea_Row][EditArea_Column]&&Page_BlockAmount[Edit_Page]<64)
			{
				EditorArea_Status[Edit_Page][EditArea_Row][EditArea_Column] = 1;
				 
				if(MouseSelect_Block)
				{
					Linklist_New = Linklist_Creat();
					Linklist_New->x = EditArea_Column*60+EditorScope;
					Linklist_New->y = EditArea_Row*60;
					Linklist_New->Length = 60;
					Linklist_New->Width = 60;
					Linklist_New->number = EditSelect_Number;
					Linklist_New->type = Mouse_NowSelect;
					Linklist_New->Damage = 0;
					Linklist_New->page = Edit_Page;
					Linklist_New->prev = Linklist_End;
					Linklist_End->next = Linklist_New;
					Linklist_End = Linklist_New;
	
					Page_BlockAmount[Edit_Page]++;
					printf("Created a Block Object[%d]  Page:%d\tX:%d\tY:%d\tLocation:%d\tType:%d\n",Page_BlockAmount[Edit_Page],Linklist_New->page,Linklist_New->x-EditorScope,Linklist_New->y,Linklist_New->number,Linklist_New->type);
					putimage_withalpha(NULL,Object_Type[Mouse_NowSelect],Linklist_New->x,Linklist_New->y);
				}
				
				if(MouseSelect_Enemy)
				{
					Linklist_New = Linklist_Creat();
					Linklist_New->x = EditArea_Column*60+EditorScope;
					Linklist_New->y = EditArea_Row*60;
					Linklist_New->number = EditSelect_Number;
					Linklist_New->type = Mouse_NowSelect;
					Linklist_New->page = Edit_Page;
					Linklist_New->prev = Linklist_End;
					Linklist_End->next = Linklist_New;
					Linklist_End = Linklist_New;
					Page_EnemyAmount[Edit_Page]++;
					
					//�ж����������趨 
					switch(Mouse_NowSelect)
					{
						case 10://��ɫ������
							Linklist_New->Length = Cerulean_Blue_Length;
							Linklist_New->Width = Cerulean_Blue_Width;
							Linklist_New->Damage = Cerulean_Blue_Damage;
							putimage_withalpha(NULL,Object_Type[Mouse_NowSelect],Linklist_New->x,Linklist_New->y);
							break;
						case 11://��ɫ������
							Linklist_New->Length = Cerulean_Pink_Length;
							Linklist_New->Width = Cerulean_Pink_Width;
							Linklist_New->Damage = Cerulean_Pink_Damage;
							putimage_withalpha(NULL,Object_Type[Mouse_NowSelect],Linklist_New->x,Linklist_New->y);
							break;
						case 12://��������ͷ
							Linklist_New->Length = 60;
							Linklist_New->Width = 82;
							Linklist_New->Damage = -100;
							putimage_withalpha(NULL,Object_Type[Mouse_NowSelect],Linklist_New->x,Linklist_New->y);
							break;
						default:printf("#400 Process_MouseChosen ERROR! %d\n",Mouse_NowSelect);
					}
					printf("Created a Enemy Object[%d]  Page:%d\tX:%d\tY:%d\tLocation:%d\tType:%d\n",Page_EnemyAmount[Edit_Page],Linklist_New->page,Linklist_New->x-EditorScope,Linklist_New->y,Linklist_New->number,Linklist_New->type);
				}
				
			}
		}
		else if(Mouse_RLflag == 1&&EditorArea_Status[Edit_Page][EditArea_Row][EditArea_Column])
		{
			EditorArea_Status[Edit_Page][EditArea_Row][EditArea_Column] = 0;
			Page_BlockAmount[Edit_Page]--;
			Linklist_Delete(EditSelect_Number,Edit_Page,1);
//			Linklist_Printf(Linklist_Head);
		}
	}
}

/************************************/
/*��������Linklist_Printf			*/
/*��  �ܣ���ӡ����					*/
/*��  ��������ͷָ��				*/
/*����ֵ��							*/
/************************************/
void Linklist_Printf(Object_Parameter* Head)
{
	unsigned int i=0,j=0,k=0;
	Object_Parameter *Linklist_ptr=Head;
	while(Linklist_ptr->next!=NULL)
	{
		i++;
		Linklist_ptr = Linklist_ptr->next;
		if(Linklist_ptr->Damage == 0)
		{
			printf("Block Object[%d]  Page:%d\tX:%d\tY:%d\tLength:%d\tLocation:%d\tType:%d\n",j,Linklist_ptr->page,Linklist_ptr->x-EditorScope,Linklist_ptr->y,Linklist_ptr->Length,Linklist_ptr->number,Linklist_ptr->type);		
			j++;
		}
		else
		{
			printf("Enemy Object[%d]  Page:%d\tX:%d\tY:%d\tLength:%d\tLocation:%d\tType:%d\n",k,Linklist_ptr->page,Linklist_ptr->x-EditorScope,Linklist_ptr->y,Linklist_ptr->Length,Linklist_ptr->number,Linklist_ptr->type);		
			k++;
		}
	}
}

/************************************/
/*��������Linklist_Creat			*/
/*��  �ܣ�����һ��������			*/
/*��  ����							*/
/*����ֵ��							*/
/************************************/
Object_Parameter* Linklist_Creat(void)
{
	Object_Parameter *Linklist_ptr;
	Linklist_ptr=(Object_Parameter*)malloc(sizeof(Object_Parameter));
    if(Linklist_ptr==NULL){
    	printf("\nLinklist Creat ERROR\n");
        return(NULL);
    }
    Linklist_ptr->number = -1;
    Linklist_ptr->page = -1;
    Linklist_ptr->type = -1;
    Linklist_ptr->x = -1;
    Linklist_ptr->y = -1;
    Linklist_ptr->next = NULL;
    Linklist_ptr->prev = NULL;
    return(Linklist_ptr);
}

/************************************/
/*��������Linklist_Delete			*/
/*��  �ܣ�ɾ��һ��������			*/
/*��  �������λ��					*/
/*����ֵ��							*/
/************************************/
void Linklist_Delete(int Location,int _page,bool type)
{
	Object_Parameter *Linklist_Delete = Linklist_Head;
	
	//��λĿ�� 
	while(Linklist_Delete->next!=NULL)
	{
		Linklist_Delete = Linklist_Delete->next;
		if(Linklist_Delete->number == Location && Linklist_Delete->page == _page)
			break;
	}
	//ɾ�� 
	if(type)
		putimage(Linklist_Delete->x,Linklist_Delete->y,Block_Clear);
		
	if(Linklist_Delete->next == NULL)//��Ϊβ��� 
	{
		Linklist_End = Linklist_Delete->prev;
		Linklist_End->next = NULL;
		if(type)
			printf("Delete a Object %d Page:%d\tX:%d\tY:%d\tLocation:%d\tType:%d\n",Edit_Page,Linklist_Delete->page,Linklist_Delete->x-EditorScope,Linklist_Delete->y,Linklist_Delete->number,Linklist_Delete->type);
		else
			printf("Delete a Block Location:%d\tPage:%d\n",Linklist_Delete->number,Linklist_Delete->page);
		free(Linklist_Delete);
	}
	else
	{
		Linklist_Delete->next->prev = Linklist_Delete->prev;
		Linklist_Delete->prev->next = Linklist_Delete->next;
		if(type)
			printf("Delete a Object %d Page:%d\tX:%d\tY:%d\tLocation:%d\tType:%d\n",Edit_Page,Linklist_Delete->page,Linklist_Delete->x-EditorScope,Linklist_Delete->y,Linklist_Delete->number,Linklist_Delete->type);
		else
			printf("Delete a Block Location:%d\tPage:%d\n",Linklist_Delete->number,Linklist_Delete->page);
		free(Linklist_Delete);
	}
}

/************************************/
/*��������LinklistData_Save			*/
/*��  �ܣ�������������      		*/
/*��  ��������ͷָ��				*/
/*����ֵ��							*/
/************************************/
void LinklistData_Save(Object_Parameter *Head)
{
	printf("Storing Data......\n");
	unsigned int i = 0,j = 0,page = 0;
	bool MoveFlag = 1;
	Object_Parameter *Linklist_ptr = Head;
	Object_Parameter *Pointer = Head;
	Object_Parameter *Delete_ptr;
	Linklist_Printf(Linklist_Head);
	stream = fopen("Stage1.map","w+");
		
	Linklist_Printf(Linklist_Head);
	
	//�ļ�ͷ��д��ҳ�� 
	for(i=0;i<PAGE;i++)
	{
		if(Page_BlockAmount[i]==0)
			break;
		else
			page++;
	}
	fprintf(stream,"%d\n",page);

	//����ϲ��㷨
	for(i=0;i<page;i++)
	{	
		for(j=EditorScope;j<WindowSize_L;j+=60)
		{
			while(Pointer->next != NULL)	//��λָ���ƶ���ĩβʱ�˳�ѭ�� 
			{
				Pointer = Pointer->next;	//���ƶ�λָ�� 

				if(Pointer->x == j && Pointer->page == i)	//����λָ����ָ����X����Ϊ��ǰ�У����ڵ�ǰҳ 
				{	
					while(Linklist_ptr->next != NULL)		//����ָ���ƶ���ĩβʱ�˳�ѭ�� 
					{
						Linklist_ptr = Linklist_ptr->next;	//���Ƽ���ָ�� 

						if(Linklist_ptr->page == Pointer->page	//��ҳ����ͬ
						&& Linklist_ptr->type == Pointer->type	//��������ͬ 
						&& Linklist_ptr->y == Pointer->y		//����ͬһ���� 
						&& Linklist_ptr->x == Pointer->x + Pointer->Length)//������
						{
							Pointer->Length += Linklist_ptr->Length;//���¶�λָ����ָ���鳤�� 
							Linklist_Delete(Linklist_ptr->number,Linklist_ptr->page,0);	//ɾ����� 
							Page_BlockAmount[i]--;			//���±�ҳ������Ŀ 
							
							Linklist_ptr = Head;	//��λ����ָ�� 
						}
					}
					Linklist_ptr = Head;	//��λ����ָ�� 
				}
			}
			Pointer	= Head;		//��λ��λָ��
		}
	}
	Linklist_ptr = Head;	//��λ����ָ�� 
	
	//д��ÿҳ�ķ����� 
	for(i=0;i<page;i++)
	{
		printf("Page:%d\tAmount:%d\n",i,Page_BlockAmount[i]);
		fprintf(stream,"%d ",Page_BlockAmount[i]);
	}
	fprintf(stream,"\n");
	
	//д�뷽������ 
	i=0;j=0;
	while(Linklist_ptr->next!=NULL)
	{	
		Linklist_ptr = Linklist_ptr->next;
		
		if(Linklist_ptr->page == j)
		{
			if(Linklist_ptr->Damage==0)//�ǵж����� 
			{
				i++;
				fprintf(stream,"%d,%d,%d,%d,%d,%d,%d ",Linklist_ptr->page,Linklist_ptr->x-EditorScope,Linklist_ptr->y,Linklist_ptr->Length,Linklist_ptr->Width,Linklist_ptr->type,Linklist_ptr->Damage);
			}
		}
		
		if(i == Page_BlockAmount[j])
		{
			i=0;
			Linklist_ptr = Head;//��λָ��
			if(j<page)
				j++;
			else
				break;
		}
	}
	
	
	Linklist_ptr = Head;//��λָ��
	
	fprintf(stream,"\n");
	//д��ÿҳ�ĵж�������
	 for(i=0;i<page;i++)
	{
		printf("Page:%d\tAmount:%d\n",i,Page_EnemyAmount[i]);
		fprintf(stream,"%d ",Page_EnemyAmount[i]);
	}
	fprintf(stream,"\n");
	
	//д��ж��������� 
	i=0;j=0;
	while(Linklist_ptr->next!=NULL)
	{	
		Linklist_ptr = Linklist_ptr->next;
		
		if(Linklist_ptr->page == j)
		{
			if(Linklist_ptr->Damage<0)//�ж����� 
			{
				i++;
				fprintf(stream,"%d,%d,%d,%d,%d,%d,%d ",Linklist_ptr->page,Linklist_ptr->x-EditorScope,Linklist_ptr->y,Linklist_ptr->Length,Linklist_ptr->Width,Linklist_ptr->type,Linklist_ptr->Damage);
			}
		}
		
		if(i == Page_EnemyAmount[j])
		{
			i=0;
			Linklist_ptr = Head;//��λָ��
			if(j<page)
				j++;
			else
				break;
		}
	}
	
	fclose(stream);
	MapFile_Read();
	Sleep(1000);
	printf("Complete.\n");
}

/************************************/
/*��������MapFile_Read				*/
/*��  �ܣ���ȡ��ͼ�ļ�     			*/
/*��  ����							*/
/*����ֵ���ṹ������ָ��			*/
/************************************/
Object_Parameter** MapFile_Read(void)
{
	Object_Parameter **MapData_Block;		//ָ������ 
	Object_Parameter *Readlist_StructureHead;	//�ṹ������ 
	int *Page_BlockAmount;
	int page=0,i=0,j=0,n=0;
	
	printf("Read the map file...\n");
	stream = fopen("Stage1.map","r");
	
	fscanf(stream,"%d",&page);
	printf("%d\n",page);
	MapData_Block = new Object_Parameter*[page];
	Page_BlockAmount = new int[page];
	
	for(i=0;i<page;i++)
	{
		fscanf(stream,"%d",&Page_BlockAmount[i]);
		printf("%d ",Page_BlockAmount[i]);
	}
	printf("\n");
	for(i=0;i<page;i++)
	{
		if(Page_BlockAmount[i]!=0)
			MapData_Block[i] = new Object_Parameter[Page_BlockAmount[i]];
	}
	
	for(i=0;i<page;i++)
	{
		for(j=0;j<Page_BlockAmount[i];j++)
		{
			n=fscanf(stream,"%d,%d,%d,%d,%d,%d,%d",&MapData_Block[i][j].page,&MapData_Block[i][j].x,&MapData_Block[i][j].y,&MapData_Block[i][j].Length,&MapData_Block[i][j].Width,&MapData_Block[i][j].type,&MapData_Block[i][j].Damage);
			if(n!=7)
			{
				printf("\nREAD FILE ERROR!\n");
				break;
			}
			printf("Loading Block[%d][%d]:Page %d,X %d,Y %d,Length %d,Width %d,type %d,Flag %d\n",i,j,MapData_Block[i][j].page,MapData_Block[i][j].x,MapData_Block[i][j].y,MapData_Block[i][j].Length,MapData_Block[i][j].Width,MapData_Block[i][j].type,MapData_Block[i][j].Damage);
		}
	}
	fclose(stream);
	Sleep(1000);
	printf("Complete.\n");
	return(MapData_Block);
}

/************************************/
/*��������Change_Page				*/
/*��  �ܣ���ҳ      				*/
/*��  ������ҳ���� 0- 1+			*/
/*����ֵ���������					*/
/************************************/
bool Change_Page(bool Direction)
{
	if(Edit_Page==0&&!Direction || Edit_Page==PAGE-1&&Direction)
		return(0);
	
	getimage(Change_PageSave[Edit_Page],EditorScope,0,WindowSize_L,WindowSize_H);
	if(Direction)
	{
		Edit_Page++;
		putimage(EditorScope,0,Change_PageSave[Edit_Page]);
	}
	else if(!Direction)
	{
		Edit_Page--;
		putimage(EditorScope,0,Change_PageSave[Edit_Page]);
	}
	sprintf(StringSave,"%d",Edit_Page);
	putimage(65,465,GUI_NumberClear);
	outtextxy(65,465,StringSave);
	Sleep(1000);
	return(1);
}

