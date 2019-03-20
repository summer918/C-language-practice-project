#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>

time_t start,end;
int hour = 0, minl = 0, sec = 0,time_1=0,end_1=0;//时间
int c1=0;

void recite(char word[4][26],int flag);//打印文字
void menu();//主菜单
void display1();//打印结果
void main();

static void setPos(int x,int y)
{

   COORD point = {x,y};//光标要设置的位置x,y
   HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
   SetConsoleCursorPosition(HOutput, point);//设置光标位置
}


void color(short x) //自定义函根据参数改变颜色   
{  
    if(x>=0 && x<=15)//参数在0-15的范围颜色  
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //只有一个参数，改变字体颜色   
    else//默认的颜色白色  
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
}  


void time1()
{
		while(sec>60)
		{
			minl++;
			sec=sec-60;
		}
		if(minl==60)
		{
			minl=0;
			hour++;
		}
		if(hour==24)
			hour=0; 
}
//打印文章
void look(char *st,int flag)
{
	FILE *fp;
	char word[4][26];
	int col=0,row=0;
	memset(word,0,sizeof(char)*4*26);
	if((fp=fopen(st,"r+"))==NULL)
	{
		printf("can't open this file\n");
		exit(0);
	}
	while(row<4)
	{
		for(col=0;col<25;col++)
		{
			if(fscanf(fp,"%c",&word[row][col])!=EOF)
			{}
		}
		row++;
	}
	fclose(fp);
    recite(word,flag);
}
//模板样式
void zuanshi(char word[][26])
{
	int i=0;
	printf("\n\n\n");
	printf("\t\t\t       ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t\t       ┃      金山打字通                     ┃ \n");
	printf("\t\t\t       ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	for(i=0;i<4;i++)
	{
	printf("\t\t\t       ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t\t       ┃%s                          \n",word[i]);
	printf("\t\t\t       ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\t\t\t       ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t\t       ┃                            \n");
	printf("\t\t\t       ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	}
	
	
	

	
	
	
}







//打字模块
void recite(char word[4][26],int flag)
{
    char word_1[25][26];
	int k=0,row=0,r=1,col=0,h=0;
	c1=0;
	memset(word_1,0,sizeof(char)*100);
	for(sec=1;sec<=3;sec++)
	{
		printf("\t\t\t\t%d",sec);
		Sleep(1000);
		system("cls");
	}
   printf("\t\t\t\t●现在开始\n\n");
	system("cls");//清屏	
	start=time(NULL);
	sec=hour=minl=0;
	col=0;
	zuanshi(word);
	for(k=0;k<4;k++)
	{
			setPos(20,9+h);
			h+=6;
	   if(!flag)
	   {
		   if(minl==time_1)
		   {
			   system("cls");
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
	   printf("\n\t\t\t\t");
		        
	   for(col=0;col<25;col++,row++)
	   {
		 
		   scanf("%c",&word_1[k][col]);
		   if(word[k][col]==word_1[k][col])
		   {   color(2);
			   c1++;
		   }
		   else
			   color(4);
	   }
		
		end=time(NULL);
	    sec=(int)difftime(end,start);
		
	}
	system("cls");
	display1();

}


	
//打印分数模块
void display1()
{
	
	printf("\n\n\n\t\t\t\t\t●◆正确率:%.3f\n",(c1/100.0)*100);
	printf("\t\t\t\t\t●◆用时：\n");
	time1();
	printf("\t\t\t\t\t\t__________________\n");
    printf("\t\t\t\t\t\t%02d:%02d:%02d   \n",hour, minl, sec);//%02d输出长度为2，不足2前面补0
    printf("\t\t\t\t\t\t_________________\n\n");
    if(c1==100)
		printf("\t\t\t\t\t●◆你已达到10级！●◆");
	else
		printf("\t\t\t\t\t●◆baby,还要继续努力哦!●◆\n");
	system("pause");
    //system("cls");
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
	case 1:{str="word_1.txt";look(str,flag);break;}
	case 2:{str="word2.txt";look(str,flag);break;}
	case 3:{str="word3.txt";look(str,flag);break;}
	case 4:{str="word4.txt";look(str,flag);break;}
	case 5:{str="word5.txt";look(str,flag);break;}
	case 6:{str="word6.txt";look(str,flag);break;}
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

void tshi_2()
{
	printf("\t\t\t\t_____________________________________________________________________\n");
	printf("\t\t\t\t|   温馨提示：中文输入请                                             |\n");
	printf("\t\t\t\t|             自行改变输入法,越往下难度越高                          |\n");
	printf("\t\t\t\t|____________________________________________________________________|\n\n\n");
}
//中文目录
void chin_menu()
{
	int i;
	tshi_2();
	Sleep(3000);
	system("cls");
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
	printf("\t\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n");
	printf("\t\t\t\t▎       1  Success                     ▎\n\n");
	printf("\t\t\t\t▎       2  Love                        ▎\n\n");
	printf("\t\t\t\t▎       3  A Beautiful Flower          ▎\n\n");
	printf("\t\t\t\t▎       4  Spirit                      ▎\n\n");
	printf("\t\t\t\t▎       5  A Wild Guess                ▎\n\n");
	printf("\t\t\t\t▎       6  TO Borrow an Ox             ▎\n\n");
	printf("\t\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n");
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
	fflush(stdin);
	scanf("%d",&choice1);
	system("cls");
	printf("\n\n\t\t\t\t请输入你要挑战的分钟数(整数)：");
	scanf("%d",&time_1);
	system("cls");
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
	fflush(stdin);
}

//选择文章
void choose(int  choice1)
{
	switch(choice1)
	{
		           case 1:chin_menu();break;
		           case 2:eng_menu();break;
				   default:menu();break;
	}
}

//主菜单
void menu()
{
	int N;
	int  choice,choice1;
	srand(time(NULL));
	while(1)
	{
	printf("\n\n\n\n\t\t\t□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf("\t\t\t□                           欢迎进入打字程序                               □\n");
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
	fflush(stdin);
	scanf("%d",&choice);
	system("cls");
	switch(choice1)
	{
	      case 1:{
		           N=rand()%6;
			     switch(choice)
				 {
            	      case 1:ch_1(N,1);break;
	        	      case 2:ch_2(N,1);break;
				 };
			        
				   }break;
		case 2:choose(choice);break;
		case 3:challeng();break;
		default:main();break;
	}
	system("cls");
	}
		
	
	
}

void tshi()
{
	printf("\n\n\n\n\t\t\t\t_____________________________________________________________________\n");
	printf("\t\t\t\t|   温馨提示：在操作中按0回到主菜单，输入正确的数字进入相应的程序    |\n");
	printf("\t\t\t\t|              输入单词后按enter键继续                               |\n");
	printf("\t\t\t\t|____________________________________________________________________|\n");
	printf("\n\n\n\n\t\t\t\t\t\t----------指导老师：曹琼");
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
	int i;
    tshi();
	for(i=0;i<5;i++)
	{
		
			
			system("color 04");	
			Sleep(20);
			system("color 05");
		    Sleep(20);
		    system("color 06");
			Sleep(20);
	
	}
	
	Sleep(1000);
	system("cls");
	menu();
}


