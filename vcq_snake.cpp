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
struct look{int x,y;}q;//С���λ�� 
int lk[200][200];//���� 
int Top=2,Down=23,Right=2,Left=20;//����߽� 
int i,j,k;//������ѭ���� 
double t,nowy=0;// 
int ty=1,tn,tm=0;//ty��Ͱ�м�ȱ�ڵĸ߶ȣ�tn��Ͱ���ֵ����ڣ�tm������ѭ��tn�� 
int ch;//���ܵ����� 
int life=3; //���������� 
int buff=0,bufftime=0; //�޵�buff��buffʱ�� 
int loadtime=0;
void lkclear()//���¿�ʼʱ����Ҫ���� 
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
void gravity()//С������ 
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
    if(lk[q.x][q.y]==2&&bufftime==0)//���µ���ײ������ 
  	{
  		life--;
 	 	bufftime=20;
	}
    lk[q.x][q.y]=1;
    
}
void tong()//������һ��Ͱ���ֵ�λ�� 
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
void put()//������� 
{
    gotoxy(0,0);
/*	for(i=Top;i<=Down;i++)
		lk[Right][i]=0;*/
    for(i=Top;i<=Down;i++)
    {
        for(j=Right;j<=Left;j++)
        {
            if(j==Left||j==Right||i==Top||i==Down)//���߽� 
            {            	
				color(7);
				printf("XX");
            }               
			          
            else if(lk[j][i]==2)//��Ͱ 
			{
  				if(lk[j-1][i]==1&&bufftime==0)//����ǰײ������ 
  				{
  					life--;
  					bufftime=20;
  				}
    			lk[j][i]=0;	//Ͱ�Զ����� 
				lk[j-1][i]=2;
				color(4);	
                printf("��");  
            }		
			else if(lk[j][i]==1)//��С�� 
            {
            	lk[j-1][i]=3;//С�����ɧɧ��β�� 
            	if(buff)//�޵�buff 
            		color(14);	
            	else	
			 		color(10);			
				printf("��");
            }  	   
			else if(lk[j][i]==3)//��ɧɧ��β�� 
            {            	
				if(buff)
            		color(14);	
            	else	
			 		color(10);			
				printf("CC");
            	lk[j][i]=0;//β��Ҳ���Զ����� 
            	lk[j-1][i]=3;
            }  	       
            else
                printf("  ");
        }
        color(11);
        if(i==Top+2)
        	printf("��ֱ�ٶ�%2.2lf",-t);//���������ʵ��û��ʲô�� 
        else if(i==Top+4)
        {
			color(10);
			for(int temp=2;temp<=life;temp++)
				printf("��");
			printf("                    "); 
        }
		else if(i==Top+6)
			printf("ͨ������%3d",tm);
        else if(i==Top+8)
			printf("�޵�Buff%3d",bufftime);
		else if(i==Top+10)
			printf("�ո��Ϸɣ�s�����棬d����ͣ",bufftime);
        printf("\n");
    }
}
void Buff()
{
    if(bufftime>0)//����ѭ����bufftime�ͻ���٣�Ȼ��buff��û�� 
    {
    	buff=1;
    	bufftime--;
    }    	
    else
    {
    	buff=0;
    }
    	
}
void out()//���������һ������ 
{
    gravity();
    Buff(); 
    put();
    if(tn>=10)//ͰҪ����ʱ��ų���һ�������Թ�һ��ŵ���һ�� 
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
        	printf("��ͣ��..���������\n");
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
    printf("       a:��ʼ��Ϸ     s���򿪴浵    d��߷�      ");
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
	printf("�÷֣�%3d",tm);
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
