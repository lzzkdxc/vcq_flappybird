#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
void gotoxy(int x, int y)
{
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}
void hidecursor()
{
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
void getkey()
{
	
}
void color(unsigned short c)
{
	HANDLE app=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(app,c);
}
//////////////////////////////////////////////////////////////////////////////
struct look{int x,y;}q;//小鸟的位置 
int lk[200][200];//画面 
int Top=2,Down=23,Right=2,Left=20;//画面边界 
int i,j,k;//用来做循环的 
double t,nowy=0;// 
int ty=1,tn,tm=0;//ty是桶中间缺口的高度，tn是桶出现的周期，tm是用来循环tn的 
int ch;//接受的输入 
int life=3; //生命的条数 
int buff=0,bufftime=0; //无敌buff和buff时间 
int loadtime=0;
void lkclear()//重新开始时画面要清屏 
{
	for(i=Top;i<=Down;i++)
    {
        for(j=Right;j<=Left;j++)
        {
            lk[i][j]=0;
        }
    }
}
void save()
{
	FILE *fp=fopen("data\\save.txt","w");
	for(i=Top;i<=Down;i++)
    {
        for(j=Right;j<=Left;j++)
        {
        	fprintf(fp,"%d ",lk[j][i]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"%d %d %d %d %d\n",tm,life,bufftime,q.x,q.y);
    fclose(fp);
} 
void gravity()//小鸟重力 
{
    lk[q.x][q.y]=0;
    if(ch==1)
        t=-3;
       q.y=q.y+t/5;
       if(q.y>Down)
           q.y=Down-1;
    else if(q.y<Top)
        q.y=Top+1;
    else
        t+=2;
    ch=0;
    if(lk[q.x][q.y]==2&&bufftime==0)//向下掉落撞到柱子 
  	{
  		life--;
 	 	bufftime=20;
	}
    lk[q.x][q.y]=1;
    
}
void tong()//设置下一个桶出现的位置 
{
    ty=rand()%10+4;
    for(i=Top;i<=Down;i++)
    {
        for(j=Right;j<=Left;j++)
        {
            if((i<=ty||i>=ty+7)&&(j==Left-2||j==Left-1))
                lk[j][i]=2;
        }
    }
}
void put()//输出画面 
{
    gotoxy(0,0);
/*	for(i=Top;i<=Down;i++)
		lk[Right][i]=0;*/
    for(i=Top;i<=Down;i++)
    {
        for(j=Right;j<=Left;j++)
        {
            if(j==Left||j==Right||i==Top||i==Down)//画边界 
            {            	
				color(7);
				printf("XX");
            }               
			          
            else if(lk[j][i]==2)//画桶 
			{
  				if(lk[j-1][i]==1&&bufftime==0)//鸟向前撞到柱子 
  				{
  					life--;
  					bufftime=20;
  				}
    			lk[j][i]=0;	//桶自动左移 
				lk[j-1][i]=2;
				color(4);	
                printf("■");  
            }		
			else if(lk[j][i]==1)//画小鸟 
            {
            	lk[j-1][i]=3;//小鸟身后骚骚的尾气 
            	if(buff)//无敌buff 
            		color(14);	
            	else	
			 		color(10);			
				printf("鸟");
            }  	   
			else if(lk[j][i]==3)//画骚骚的尾气 
            {            	
				if(buff)
            		color(14);	
            	else	
			 		color(10);			
				printf("CC");
            	lk[j][i]=0;//尾气也会自动左移 
            	lk[j-1][i]=3;
            }  	       
            else
                printf("  ");
        }
        color(11);
        if(i==Top+2)
        	printf("垂直速度%2.2lf",-t);//这个数据其实并没有什么用 
        else if(i==Top+4)
        {
			color(10);
			for(int temp=2;temp<=life;temp++)
				printf("鸟");
			printf("                    "); 
        }
		else if(i==Top+6)
			printf("通过个数%3d",tm);
        else if(i==Top+8)
			printf("无敌Buff%3d",bufftime);
		else if(i==Top+10)
			printf("空格上飞，s键保存，d键暂停",bufftime);
        printf("\n");
    }
}
void Buff()
{
    if(bufftime>0)//随着循环，bufftime就会减少，然后buff就没了 
    {
    	buff=1;
    	bufftime--;
    }    	
    else
    {
    	buff=0;
    }
    	
}
void out()//输出，这是一个大函数 
{
    gravity();
    Buff(); 
    put();
    if(tn>=10)//桶要过段时间才出现一个，所以过一会才调用一次 
    {
        tong();
        tn=0;
        tm++;
    }    
    tn++;
}
void in()
{
    if(kbhit())
    {
        char keyin=getch();
		if(keyin==' ')
            ch=1;
        else if(keyin=='s')
            save();
        else if(keyin=='d')
        {
        	printf("暂停中..任意键继续\n");
        	getch();
        }
        	
    }    

}

void draw()
{
	printf("\n");        
	printf("                  ;;;;;;;;,,,;;;;;.\n");                                                                                                                                                              
    printf("                ;oxdddddddkXN0xxxxc,.\n");                                                                                                                                                           
    printf("              cko.       .'d0:    ,xd;.\n");                                                                                                                                                         
    printf("            :Xd          kl..       'od;.\n");                                                                                                                                                        
    printf("       .cooooONKdo;       Xx.      'l;..dO, \n");                                                                                                                                                      
    printf("      loc:::::::::co;     Xx.      ;0o..xX;  \n");                                                                                                                                                     
    printf("      XO          .oo:    0x;'.    .:; .xX;  \n");                                                                                                                                                     
    printf("      XO            ;KO   .lxxc........'kXc... \n ");                                                                                                                                                  
    printf("      XO            ,KO     ..:xkkkkkkkkO0kxxl'.\n ");                                                                                                                                                 
    printf("       0kkd.      ;xl;'    .dO:..............:0x. \n");                                                                                                                                                
    printf("         lc:cccccclo,    .od:'';ccccccccccccccl:. \n");                                                                                                                                                
    printf("           dNkoool.      .cdc,;cooooooooood0Wo  \n");                                                                                                                                                  
    printf("           ck:'.           .oOo'.'....'''''lO: \n");                                                                                                                                                   
    printf("             cOo.............,kX0xxxxxxxxxd'  \n");                                                                                                                                                    
    printf("               :kOOOOOOOOOOOO0Od:.   \n");                                                                                                                                                             
    printf("                ''''''''''''''.    \n");  
    printf("       a:开始游戏     s：打开存档    d最高分      ");
}

void start()
{
    hidecursor();
	q.y=5;
    q.x=7;
    srand((unsigned int)time(NULL));
    life=4;
    tm=0;
    bufftime=10;
    lkclear();          
}
void finish()
{
	printf("得分：%3d",tm);
	Sleep(2000);
	int a[11]={0},m;
	FILE *fp=fopen("data\\list.txt","r");
	i=1;
	while(fscanf(fp,"%d",&a[i])!=EOF)
		i++;
    fclose(fp);
    for(i=10;i>=1;i--)
    	if(tm>a[i])
    		m=i;
    for(i=10;i>=m+1;i--)
    	a[i]=a[i-1];
    a[m]=tm;
    FILE *fp2=fopen("data\\list.txt","w");
	for(i=1;i<=10;i++)
    {
		fprintf(fp2,"%d\n",a[i]);
    }
    fclose(fp2);
}

void play()
{
	if(loadtime==0)
		start();
	loadtime=0;
    while(life)
    {        
        in();
		Sleep(50);
        out();
    }   
    finish();
}
void list()
{
	int temp;
	FILE *fp=fopen("data\\list.txt","r");
	system("cls"); 
    for(j=1;j<=10;j++)
    {
    	fscanf(fp,"%d",&temp);
    	printf("%2d,%d\n",j,temp);
	}
    fclose(fp);
}
void load()
{
	FILE *fp=fopen("data\\save.txt","r");
	for(i=Top;i<=Down;i++)
    {
        for(j=Right;j<=Left;j++)
        {
        	fscanf(fp,"%d",&lk[j][i]);
		}
	} 
	fscanf(fp,"%d%d%d%d%d",&tm,&life,&bufftime,&q.x,&q.y);
    fclose(fp);
    loadtime=1;
    play();
}
int main()
{
	while(1)
	{
		draw();
		int in=getch();
		system("cls"); 
		if(in=='a')
			play(); 
		else if(in=='s')
    		load();
    	else if(in=='d')
    		list();
		
	}	 
}
