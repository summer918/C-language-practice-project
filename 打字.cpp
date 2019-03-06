#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>

time_t start,end;
int hour = 0, minl = 0, sec = 0,time_1=0,end_1=0;//时间
int c1=0;

void recite(char word[],int flag);//打印文字
void menu();//主菜单
void display();//打印结果

static void setPos(int x,int y)
{

   COORD point = {x,y};//光标要设置的位置x,y
   HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
   SetConsoleCursorPosition(HOutput, point);//设置光标位置
}



//打印文章
void look(char *st,int flag)
{
	FILE *fp;
	char word[100];
	int i=0;
	memset(word,0,sizeof(char)*100);
	if((fp=fopen(st,"r+"))==NULL)
	{
		printf("can't open this file\n");
		exit(0);
	}
	while(i<100)
	{
		if(fscanf(fp,"%c",word+i)!=EOF)
		{
			i++;
		}
	}
	fclose(fp);
    recite(word,flag);
}









//打字模块
void recite(char word[],int flag)
{
    char word_1[100];
	int i=0,row=0,r=0,k,col=0;
	c1=0;
	memset(word_1,0,sizeof(char)*100);
	start=time(NULL);
    for(sec=1;sec<=3;sec++)
	{
		printf("\t\t\t\t%d",sec);
		Sleep(1000);
		system("cls");
	}
   printf("\t\t\t\t●现在开始\n\n");
	system("cls");//清屏
	sec=start;
	printf("\n\n\t\t\t\t");
	sec=0;
	for(i=0;i<100;i++)
	{
		if(sec==60)
		{
			minl++;
			sec=0;
		}
		if(minl==60)
		{
			minl=0;
			hour++;
		}
		if(hour==24)
			hour=0; 
       printf("\t\t●◆用时：%02d:%02d:%02d   \t",hour, minl, sec);//%02d输出长度为2，不足2前面补0
	   	printf("●◆正确率:%.3f\t●◆速率%.3f\n",(c1/100)*100,(i/100)*100);
	   if(!flag)
	   {
		   if(minl==time_1)
		   {
			    printf("\n\n\t\t\t\t挑战失败！\n\n");
			    printf("\n\n\t\t\t\t<1> 继续\t<2> 退出\n");
			    printf("\n\t\t\t\t\t请选择：");
		         scanf("%d",&r);
				 	if(r==2)
					{
						menu();
						break;
					}
		   }
	   }
	   printf("\t\t\t\t");
	   for(k=0;k<100;k++)
	   {
	    	printf("%c",word[k]);
		    if(k%25==0)
			  printf("\n\n\t\t\t\t");
	   }
       for(k=0;k<i;k++)
	   {
	    	printf("%c",word_1[k]);
		    if(k%25==0)
			  printf("\n\n\t\t\t\t");
	   }

	   setPos(27+row,4+col);
	   col+=1;
	   scanf("%c",word_1+i);
	   if(i%25==0)
	   {
		   printf("\n");
		   row+=1;
	   }
		if(word[i]==word_1[i])
		{
			c1++;
		}
		end=time(NULL);
		end_1=sec=(int)difftime(end,start);
		system("cls");
	}
	display();
}


	
//打印分数模块
void display()
{
	
	printf("\t\t\t\t\t●◆正确率:%.3f\n",(c1/100)*100);
	printf("\t\t\t\t\t●◆用时：\n");
	printf("\t\t\t\t\t\t__________________\n");
    printf("\t\t\t\t\t\t%02d:%02d:%02d   \n",hour, minl, sec);//%02d输出长度为2，不足2前面补0
    printf("\t\t\t\t\t\t_________________\n\n");
    if(c1==100)
		printf("\t\t\t\t\t●◆你已达到10级！●◆");
	else
		printf("\t\t\t\t\t●◆baby,还要继续努力哦!●◆\n");
}

 

//打字结果保持在文件中
void wrongtxt(char word_2[])
{
	FILE *fp;
	int i=0;
	if((fp=fopen("打字结果.txt","a+"))==NULL)
	{
		printf("can't open this file\n");
		exit(0);
	}
	while(i<100)
	{
		fprintf(fp,"%c",word_2[i]);
		i++;
	}
	fclose(fp);
}


   
//根据选择这个中文的文章，选择不同文件
void ch_1(int no,int flag)
{
	char *str;
	printf("\t\t\t\t挑战马上开始啦\n\n");
	switch(no)
	{
    	case 1:str="word1.txt";look(str, flag);break;
		case 2:str="word2.txt";look(str, flag);break;
		case 3:str="word3.txt";look(str, flag);break;
		case 4:str="word4.txt";look(str, flag);break;
		case 5:str="word5.txt";look(str, flag);break;
		case 6:str="word6.txt";look(str, flag);break;
	}
	

}

//根据选择英文的文章，选择不同文件
void ch_2(int no,int flag)
{
	char *str;
	printf("\t\t\t\t挑战马上开始啦\n\n");
	switch(no)
	{
    	case 1:str="eword1.txt";look(str, flag);break;
		case 2:str="eword2.txt";look(str, flag);break;
		case 3:str="eword3.txt";look(str, flag);break;
		case 4:str="eword4.txt";look(str, flag);break;
		case 5:str="eword5.txt";look(str, flag);break;
		case 6:str="eword6.txt";look(str, flag);break;
	}
	

}

//中文目录
void chin_menu()
{
	int i;
	printf("\t\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n");
	printf("\t\t\t\t▎       1 没有比脚更长的路           ▎\n\n");
	printf("\t\t\t\t▎       2 缘起不灭                   ▎\n\n");
	printf("\t\t\t\t▎       3 破瓮救人                   ▎\n\n");
	printf("\t\t\t\t▎       4 春意,暗香                  ▎\n\n");
	printf("\t\t\t\t▎       5 你的世界我最美             ▎\n\n");
	printf("\t\t\t\t▎       6 阳春三月                   ▎\n\n");
	printf("\t\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  \n\n");
	printf("\t\t\t\t请选择文章：");
	scanf("%d",&i);
	ch_1(i,1);
}
//英文目录
void eng_menu()
{
	int i;
	printf("\t\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n");
	printf("\t\t\t\t▎       1 青铜           ▎\n\n");
	printf("\t\t\t\t▎       2 白银           ▎\n\n");
	printf("\t\t\t\t▎       3 黄金           ▎\n\n");
	printf("\t\t\t\t▎       4 铂金           ▎\n\n");
	printf("\t\t\t\t▎       5 钻石           ▎\n\n");
	printf("\t\t\t\t▎       6 黄金           ▎\n\n");
	printf("\t\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n");
	printf("\t\t\t\t请选择文章：");
	scanf("%d",&i);
	ch_2(i,1);
}



//挑战评语
void jump()
{
	if(minl<time_1&&c1==100)
				  printf("\t\t\t\t\t●◆挑战成功●◆\n");
    else 
                  printf("\t\t\t\t\t●◆很遗憾，挑战失败！●◆\n");
}


//挑战模块
void challeng()
{
	int choice1;
    printf("\t\t\t\t_____________________________________________________________________\n");
	printf("\t\t\t\t|   温馨提示：请选择不同的等级，在规定的时间中全部打印完，中文输入请 |\n");
	printf("\t\t\t\t|             自行改变输入法,越往下难度越高                          |\n");
	printf("\t\t\t\t|____________________________________________________________________|\n\n\n");
	printf("\t\t\t\t●◆欢迎进入挑战模块，祝你好运!●◆\n\n");

	printf("\t\t\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁ \n\n");
	printf("\t\t\t\t\t▎   1   拼音打字              ▎\n\n");
	printf("\t\t\t\t\t▎   2   英语打字              ▎\n\n");
	printf("\t\t\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔ \n\n");
	printf("\t\t\t\t请选择：\n");
	scanf("%d",&choice1);	
	printf("\n\n\t\t\t\t请输入你要挑战的分钟数：");
	scanf("%d",&time_1);
	switch(choice1)
	{
    	case 1:chin_menu();break;
		case 2: eng_menu();break;
		default:menu();break;
	}
	
	
    jump();

}


//选择模块
void getchoice()
{
	printf("\t\t\t\t\t●◆●◆●◆●◆●◆●◆●◆\n\n");
	printf("\t\t\t\t\t●   1 随机模式           ●\n\n");
    printf("\t\t\t\t\t●   2 选择模式           ●\n\n");
	printf("\t\t\t\t\t●   3 挑战模式           ●\n\n");
	printf("\t\t\t\t\t●   0 退出               ●\n\n");
	printf("\t\t\t\t\t●◆●◆●◆●◆●◆●◆●◆\n\n\n");
	printf("\t\t\t\t\t请选择：\n");
}

//选择文章
void choose(int choice1)
{
	switch(choice1)
		{
		           case 1:chin_menu();break;
		           case 2:eng_menu();break;
	 }
}

//主菜单
void menu()
{
	int choice,choice1,N;
	srand(time(NULL));
	printf("\n\n\n\n\t\t\t□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf("\t\t\t□                           欢迎进入打字程序                             □\n");
	printf("\t\t\t□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n\n");
	printf("\t\t\t\t●◆学习使你快乐，让我们一起快乐学习吧！●◆                \n\n\n");
	getchoice();//选择模块
	scanf("%d",&choice1);
	system("cls");
	printf("\t\t\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n");
	printf("\t\t\t\t\t▎   1   拼音打字              ▎\n\n");
	printf("\t\t\t\t\t▎   2   英语打字              ▎\n\n");
	printf("\t\t\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n");
	printf("\t\t\t\t请选择：\n");
	scanf("%d",&choice);
	system("cls");
	switch(choice1)
	{
    	case 1:N=rand()%6;
			switch(choice)
			{
            	case 1:ch_1(N,1);break;
	        	case 2:ch_2(N,1);break;
			}
			break;
		case 2:choose(choice);
		case 3:challeng();break;
		default:menu();break;
	}
}

void tshi()
{
	printf("\t\t\t\t_____________________________________________________________________\n");
	printf("\t\t\t\t|   温馨提示：在操作中按0回到主菜单，输入正确的数字进入相应的程序    |\n");
	printf("\t\t\t\t|              输入单词后按enter键继续                               |\n");
	printf("\t\t\t\t|____________________________________________________________________|\n\n\n");
}

//线程问题
/*int in_gore(void *pdata)
{
	mydata * pd=(mydata*)pdata;
    while (1)
	{
        Sleep(1000);//暂停1s
        system("cls");//清屏
        pd->sec=pd->sec+1;
        if (pd->sec == 60)
		{
            pd->min=pd->min+1;
            pd->sec = 0;
        }
        if (pd->min == 60)
		{
             pd->hour=pd->hour+1;
            pd->min = 0;
        }
        if (pd->hour == 24){
            pd->hour = 0;
        }
        printf("\t\t\t\t\t\t%02d:%02d:%02d\n", pd->hour, pd->min, pd->sec);
        //%02d输出长度为2，不足2前面补0
    }
    return 0;
}*/

void main()
{
	system("color 0C");
	tshi();
	menu();
}


