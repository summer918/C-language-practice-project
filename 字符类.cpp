#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib") 

int num=20,k=0;
time_t start,end;
int hour = 0, minl = 0, sec = 0,time_1=0;;
int score=0;

void choose();//选择题数
void getchoice();
//int in_gore(void *pdata);
void tshi();
void look(char *st);//浏览单词
void menu();
void leave();
void read(char *str,int N,int flag);//从文件中读出单词模块并创建链表
void recite(struct studentread *head,int N,int flag);//背单词模块
void display();//打印分数模块
void ch(char no,int N,int flag);//根据不同年级，选择不同文件
void ch1(char no);//根据不同年级，选择不同文件浏览
void jump();
void challeng(int N);//挑战模块
void wrongtxt(struct studentread *head);//错题保存到文件
struct studentread * wrongread();//读出错题
void pf1();//播放声音文件
void pf2();
void tshi_1();//提示挑战信息
void main();
void wrongmenu();//错题目录


struct studentread
{
	char word[200];//英文
	char ch[200];//中文
	struct studentread *next;
};

/*struct mydata
{
	thrd_t id;
	int hour;
	int min;
	int sec;
};*/

static void setPos(int x,int y)
{

   COORD point = {x,y};//光标要设置的位置x,y
   HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
   SetConsoleCursorPosition(HOutput, point);//设置光标位置
}

//隐藏光标
void HideCursor()
{
CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void color(short x) //自定义函根据参数改变颜色   
{  
    if(x>=0 && x<=15)//参数在0-15的范围颜色  
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //只有一个参数，改变字体颜色   
    else//默认的颜色白色  
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
}  

void zhuanshi()
{
	printf("\n\n\n\n\t\t\t\t●三秒后开始\n\n");
	Sleep(1500);
	system("cls");
	start=time(NULL);
	system("color 4");
	for(sec=1;sec<=3;sec++)
	{
		if(sec==1)
			color(4);
		else if(sec==2)
			color(5);
		else
			color(6);
		 printf("\n\n\n\n\n\t\t\t\t\t\t[%d]",sec);
		Sleep(1000);
		system("cls");
	}
	printf("\n\n\n\n\n\t\t\t\t\t\tReady\n");
	Sleep(600);
	system("cls");
	printf("\n\n\n\n\n\t\t\t\t\t\tGO\n");
	Sleep(600);
	system("cls");
	system("color B4");
	sec=0;
}

//计算时间
void time1()
{
	 while(sec>60)
	   {
		   minl++;
		   sec=sec-60;
	   }
	   if(minl==60)
	   {
		   hour++;
		   minl=0;
	   }
	   if(hour==24)
		   hour=0;
}

//选择题数
void choose()
{
	system("color B1");
	printf("\n\n\n\t\t\t\t\t请输入你要背的单词数(1-20)：\n");
	setPos(39,5);
	scanf("%d",&num);
	
}


//浏览单词
void look(char *st)
{
	FILE *fp;
	char word[1024];
	int i=0;
	system("color 9");
	memset(word,0,sizeof(char)*1024);
	if((fp=fopen(st,"r+"))==NULL)
	{
		printf("can't open this file\n");
		exit(0);
	}
      color(4);  
	 printf("\n\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	 printf("\t\t┃                    词汇王    \n");
	 printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	 printf("\n\n\n");
	 setPos(0,0);
	while(!feof(fp))
	{
		if(fscanf(fp,"%s",word)!=EOF)
		{
			if(i%2==0)
				 color(6); 
			else
				color(4);
		   printf("\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	       printf("\t\t┃             %s    \n",word);
	       printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		   i++;
		}
		
		   if(i%8==0)
		   {       system("pause");
			      system("cls");
			   	  printf("\n\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	               printf("\t\t┃                    词汇王    \n");
	               printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	               printf("\n\n\n");
			      
		   }
	}
	fclose(fp);
	system("pause");
}







//从文件中读出单词模块并创建链表
void read(char *str,int N,int flag)
{
	FILE *fp;
	int i=1;
	struct studentread *p1,*head=NULL;
	head=(struct studentread *)malloc(sizeof(struct studentread));
	memset(head,0,sizeof(struct studentread));
	if((fp=fopen(str,"r+"))==NULL)
	{
		printf("can't open this file\n");
		exit(0);
	}
	while(i<=N)
	{    
		p1=(struct studentread *)malloc(sizeof(struct studentread));
	    memset(p1,0,sizeof(struct studentread));
		if(fscanf(fp,"%s",p1->word)!=EOF&&fscanf(fp,"%s",p1->ch)!=EOF)
		{
		 
			p1->next=head->next;
			head->next=p1;
		}
		  
		i++;
	}
	fclose(fp);	

recite(head,N,flag);
}
//释放内存
void freelist(struct studentread *head)
{
	struct studentread *p=head->next,*p1;
	while(p!=NULL)
	{
		p1=p->next;
		free(p1);
		p=p1;
	}
}


//背单词模块
void recite(struct studentread *head,int N,int flag)
{
	int i=0,min,n=0,c1=0;
	char r;
	char string[200];
	struct studentread *p=head->next,*h_d=NULL;
	memset(string,0,sizeof(char)*200);
    hour=minl=sec=0;
	if(flag)
	   choose();//选择单词数
	zhuanshi();//开始前的提示
	srand(time(NULL));
	i=rand()%(N/2-k)+1;//产生随机数，随机生成单词
	k++;
	if(N==k)
		k=0;//以防k>N
	score=num;
	for(min=0;min<i;min++)
	{
		if(p!=NULL)
		  p=p->next;//找到位置为i的节点
		
	}
	h_d=p;
	for(min=0;min<num;min++)
	{
		time1();
	   printf("\n\n\t\t\t\t★|%02d:%02d:%02d|",hour,minl,sec);
	   printf("\t★已背单词数量：%d\t正确个数：%d",n,c1);
	   	// 打开音乐
    mciSendString("open 3530.mp3 alias mymusic", NULL, 0, NULL);

// 播放音乐
    mciSendString("play mymusic", NULL, 0, NULL);

	   if(!flag)
	   {
		   if(minl==time_1)
		   {
			   color(4);
			    printf("\n\n\n\t\t\t\t:-O挑战失败！\n");
			    printf("\n\t\t\t\t<1> 继续\t<2> 退出\n");
			    printf("\n\t\t\t\t\t请选择：");
		         scanf("%d",&r);
				 	if(r==2)
					{
						menu();
						break;
					}
		   }
	   }
         color(5);
		printf("\n\n\n\t\t\t\t●中文：%s\n\n",p->ch);
		color(10);
		printf("\t\t\t\t●请输入英文:");
		scanf("%s",string);
		printf("\n\n");
		// 停止播放并关闭音乐
         mciSendString("stop mymusic", NULL, 0, NULL);
         mciSendString("close mymusic", NULL, 0, NULL);
		if(strcmp(string,"0")==0)
		{
			system("cls");
			printf("\n\n\n\t\t\t\t＝　＝＃学习需要坚持！\n\n");
			Sleep(1000);
			system("cls");
			menu();
			break;
		}
		if(strcmp(string,p->word)==0)
		{
			pf2();
			color(3);
			printf("\t\t\t\t●回答正确≧◇≦\n");
			Sleep(100);
			c1++;
		}
		else
		{
			wrongtxt(p);
			pf1();
			color(4);
			printf("\t\t\t\t●回答错误T_T\n");
			Sleep(100);
			score-=1;
		}
	//	sec++;
		n++;
		end=time(NULL);
		sec=(int)difftime(end,start);
		memset(string,0,sizeof(char)*20);
		p=p->next;
		system("cls");
	}
	display();
	system("pause");
	system("cls");
	system("color 04");
	if(flag)//普通练习模块的操作
	{
		printf("\n\n\t\t\t\t\t●◆让我们再重新复习一遍吧：\n");
    	for(i=0;i<num;i++)
		{
			color(3);
		printf("\n\t\t\t\t\t________________________________\n");
		printf("\t\t\t\t\t       %s               \t\t\t\n",h_d->word);
		printf("\t\t\t\t\t________________________________\t\t\t\n");
		printf("\t\t\t\t\t<1> 认识\t<2> 不认识");
		printf("\n\t\t\t\t\t请选择：");
		r=getch();
		if(r==49)
		     h_d=h_d->next;
		else
		{
			color(4);
			printf("\n\t\t\t\t\t●中文：%s",h_d->ch);
			//system("pause");
		    h_d=h_d->next;
		}
		
		}
	}
	system("pause");
	system("cls");
		//freelist(head);//释放内存
	printf("\n\n\n");
	num=0;//以便下次从0开始
	
}


	
//打印分数模块
void display()
{
	system("color E4");
	printf("\n\n\t\t\t\t\t●◆总分:%d\n",score);
	if(score!=0)
	    printf("\t\t\t\t\t●◆正确率:%.3f\n",(score/num*1.0)*100);
	else
	    printf("\t\t\t\t\t●◆正确率:0.00\n");
	time1();
	printf("\t\t\t\t\t●◆用时：\n");
	printf("\t\t\t\t\t\t__________________\n");
    printf("\t\t\t\t\t\t%02d:%02d:%02d   \n",hour, minl, sec);//%02d输出长度为2，不足2前面补0
    printf("\t\t\t\t\t\t_________________\n\n");
    if(num==score)
		printf("\t\t\t\t\t<※baby，真棒!\n");
	else
		printf("\t\t\t\t\tT_Tbaby,还要继续努力哦!\n");
}

 

//错题保存到文件
void wrongtxt(struct studentread *h)
{
	FILE *fp;
	if((fp=fopen("wrong.txt","a+"))==NULL)
	{
		printf("can't open this file\n");
		exit(0);
	}
	fwrite(h,sizeof(struct studentread),1,fp);
	fclose(fp);
}


//保存全部错题
void wrong_baocun(struct studentread *head)
{
      FILE *fp;
	   struct studentread *p;
	   p=head->next;
	if((fp=fopen("wrong.txt","w+"))==NULL)
	{
		printf("can't open this file!");
		exit(0);
	}
	while(p!=NULL)
	{
			fwrite(p,sizeof(struct studentread),1,fp);
			p=p->next;
	}
	fclose(fp);
	freelist(head);//释放内存
	menu();

}

//读出错题
struct studentread * wrongread()
{
	struct studentread *p,*head=NULL;
	FILE *fp;
	head=(struct studentread *)malloc(sizeof(struct studentread));
	memset(head,0,sizeof(struct studentread));
	if((fp=fopen("wrong.txt","r+"))==NULL)
	{
		printf("can't open this file\n");
		exit(0);
	}
	while(!feof(fp))
	{
		p=(struct studentread *)malloc(sizeof(struct studentread));
	    memset(p,0,sizeof(struct studentread));
		if(fread(p,sizeof(struct studentread),1,fp)!=0)
		{
			p->next=head->next;
			head->next=p;
		}
	}
	fclose(fp);
	return head;
}

//清除所有错题
void qchu()
{
	FILE *fp;
	if((fp=fopen("wrong.txt","w+"))==NULL)
	{
		printf("can't open this file\n");
		exit(0);
	}
	fclose(fp);
	 printf("\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	 printf("\t\t┃             清除成功！\n");
	 printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	 Sleep(1000);
}

//浏览错题
void liulan()
{
	struct studentread *p,*head=NULL;
	int i=0;
	char k;
	head=wrongread();
	system("color 2");
	p=head->next;
	
	 printf("\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	 printf("\t\t┃            错题本\n");
	 printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	 printf("\n\n");
	 if(p==NULL)
     {
	 printf("\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	 printf("\t\t┃             无\n");
	 printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	 }
	while(p!=NULL)
	{
		if(i%2==0)
			 color(6); 
		else
			color(4);//变化字体颜色
     printf("\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	 printf("\t\t┃             英文：%s    \n",p->word);
	 printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	 printf("\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	 printf("\t\t┃             中文：%s    \n",p->ch);
	 printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	 i++;
	 scanf("%c",&k);
	 if(i%8==0)
	 {
	   system("pause"); 
		 system("cls");
     printf("\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	 printf("\t\t┃            错题本\n");
	 printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	 printf("\n\n");
		
	 }
		p=p->next;
	}
	system("pause");
	freelist(head);//释放内存
}
//练习错题
void lianxi()
{
		struct studentread *p,*head=NULL,*p1;
		char word[20];
		int i=0,l=0;
		head=wrongread();
		p=head;
		sec=0;
		start=time(NULL);
		while(p->next!=NULL)
		{
			 while(sec>60)
			 {
		       minl++;
		        sec=sec-60;
			 }
	       if(minl==60)
		   {
		       hour++;
		      minl=0;
		   }
	   if(hour==24)
		   hour=0;
	   printf("\t\t\t\t★|%02d:%02d:%02d|",hour,minl,sec);
	   printf("\t★错误个数：%d\t正确个数：%d\n\n\n",l,i);
	   color(5);
	   printf("\t\t\t\t  |中文：%s\n\n",p->next->ch);
	   color(10);
	   printf("\t\t\t\t  |英文：");
		gets(word);
			if(strcmp(word,"0")==0)
			{
			printf("\n\n\n\t\t\t\t学习需要坚持！\n\n");
			menu();
			break;
			}
			if(strcmp(word,p->next->word)==0)
			{
				color(3);
				printf("\n\n\t\t\t\t●回答正确≧◇≦\n");
				Sleep(1000);
				p1=p->next;
				p->next=p->next->next;
				free(p1);
				i++;
				p=p->next;
			}
			else
			{
				color(4);
				printf("\n\n\t\t\t\t●回答错误T_T\n");
				Sleep(1000);
				
				l++;
			}
			end=time(NULL);
	    	sec=(int)difftime(end,start);
			system("cls");
			
		}
		
		printf("\n\n\t\t\t\t●●_____________________________●●\n");
		printf("\n\n\t\t\t\t●●消灭单词：%d |待消灭单词：%d ●●\n",i,l);
		printf("\n\n\t\t\t\t●●_____________________________●●\n\n");
		Sleep(2000);
		wrong_baocun(head);
}


   
//根据不同年级，选择不同文件
void ch(char no,int N,int flag)
{
	char *str;
	
	switch(no)
	{
    	case 49:str="word1.txt";num=15;break;
		case 50:str="word2.txt";num=25;break;
		case 51:str="word3.txt";num=35;break;
		case 52:str="word4.txt";num=45;break;
		case 53:str="word5.txt";num=65;break;
		case 54:str="word6.txt";num=80;break;
	}
   
	if(!flag)
	{
		tshi_1();
		Sleep(3500);//挑战模块的提示
	}
	read(str,N,flag);

}

//根据不同年级，选择不同文件浏览
void ch1(char no)
{
	char *str;
	switch(no)
	{
    	case 49:str="word1.txt";look(str);break;
		case 50:str="word2.txt";look(str);break;
		case 51:str="word3.txt";look(str);break;
		case 52:str="word4.txt";look(str);break;
		case 53:str="word5.txt";look(str);break;
		case 54:str="word6.txt";look(str);break;
	}
}

//挑战评语
void jump()
{
	if(minl<time_1&&score==num&&hour==0)
				  printf("\t\t\t\t\t●◆挑战成功●◆\n");
    else 
                  printf("\t\t\t\t\t●◆很遗憾，挑战失败！●◆\n");

}


//挑战模块
void challeng(int N)
{
	char i;
	system("color D");
    printf("\t\t\t\t==========================================================================\n");
	printf("\t\t\t\t|   温馨提示：请选择不同的等级，越往下难度越大，在规定的时间中将题全部答对|\n");
	printf("\t\t\t\t|=========================================================================|\n\n\n");
	printf("\t\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n");
	color(3);
	printf("\t\t\t\t▎       1 青铜           ▎\n\n");
	color(4);
	printf("\t\t\t\t▎       2 白银           ▎\n\n");
	color(5);
	printf("\t\t\t\t▎       3 黄金           ▎\n\n");
	color(6);
	printf("\t\t\t\t▎       4 铂金           ▎\n\n");
	color(7);
	printf("\t\t\t\t▎       5 钻石           ▎\n\n");
	color(8);
	printf("\t\t\t\t▎       6 黄金           ▎\n\n");
	printf("\t\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n");
	color(9);
	printf("\t\t\t\t●◆欢迎进入挑战模块，祝你好运!●◆\n\n");
	printf("\t\t\t\t请选择：");
    i=getch();
	switch(i)
	{
	  case 49:time_1=7;break;
      case 50:time_1=6;break;
	  case 51:time_1=5;break;
	  case 52:time_1=4;break;
	  case 53:time_1=3;break;
	  case 54:time_1=2;break;
	  default:menu();break;
	}
	system("cls");
	Sleep(1000);
	system("cls");
	printf("\n\n\n\n\t\t\t\t挑战马上开始啦\n\n");
	ch(i,N,0);
    jump();
	 system("pause");

}

//错题目录
void wrongmenu()
{
	char i;
	int k;
	system("color B6") ;
	printf("\n\n\t\t\t\t   o__o \n\n");
    printf("\t\t\t\t   | @,@   1 浏览错题\n\n");
    printf("\t\t\t\t●(  )●   2 清除所有错题\n\n");    
    printf("\t\t\t\t    \\\\●● 3 练习错题\n\n");
    printf("\n");
	printf("\n");
	for(k=0;k<5;k++)
	{
		
			
			system("color 04");	
			Sleep(20);
			system("color 05");
		    Sleep(20);
		    system("color 06");
			Sleep(20);
	

	}//变换颜色
	system("color B6") ;
	printf("\t\t\t\t请选择：");
	i=getch();
	system("cls");
    switch(i)
	 {
        	case 49:liulan();
				   break;
	            	
	        case 50:lianxi();break;
			case 51:qchu();break;
			default:menu();break;
	}
	//system("cls");
	// system("pause");
}


//选择模块
void getchoice()
{
     system("color 1") ;
	 //system("cls");
	printf("\n\n\t\t\t\t\t___●◆●◆●◆●◆●◆●◆\n\n");
	color(4);
	printf("\t\t\t\t\t ●●\\\\  1 背单词模式         \n\n");
	color(3);
    printf("\t\t\t\t\t @ @ c   2 错题模式           \n\n");
	color(5);
	printf("\t\t\t\t\t\\\\~ /    3 浏览单词         \n\n");
	color(6);
	printf("\t\t\t\t\t         4 挑战模式            \n\n");
	color(7);
	printf("\t\t\t\t\t         0 退出              \n\n");
	color(8);
	printf("\t\t\t\t\t    ●◆●◆●◆●◆●◆●◆\n\n");
	printf("\t\t\t\t\t请选择：\n");
	setPos(46,17);
}

//退出模块
void leave()
{
	printf("\n\n\n\n\t\t\t\t\t☆☆☆☆小主人，今天真棒，欢迎下次来学习！☆☆☆☆\n\n\n\n");
}
//主菜单
void menu()
{
	char choice,choice1;
	int N;
	system("color 4");
	system("cls");
	printf("\n\t\t\t\t□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf("\t\t\t\t□                欢迎进入背单词程序            □\n");
	printf("\t\t\t\t□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	color(4);
	printf("\t\t\t\t■〓□学习使你快乐，让我们一起快乐学习吧！(￣▽ ￣)                \n\n");
	color(5);
	printf("\t\t\t\t     /\\`\\  /\\`\\      ▎   1   小学              ▎   \n\n");
	color(6);
    printf("\t\t\t\t     \\/\\ V /\\/\\      ▎   2   初中              ▎   \n\n"); 
    printf("\t\t\t\t        /6 6\\        ▎                         ▎\n\n");
	color(9); 
    printf("\t\t\t\t       (= Y =)       ▎   3   高中              ▎ \n\n");
   	printf("\t\t\t\t      /`'^'` \\       ▎   4   四级 ≧◇≦       ▎   \n\n");
	color(3);
   	printf("\t\t\t\t     / /      \\ \\    ▎                         ▎ \n\n");
	color(12);
   	printf("\t\t\t\t    (_/        \\_)   ▎   5   六级              ▎\n\n");
	color(14);
  	printf("\t\t\t\t     /            \\o ▎   6   八级              ▎    \n\n");
  	printf("\t\t\t\t  ___\\           /___  \n");
    printf("\t\t\t\t(((____/^\\____)))  \n\n");
	printf("\t\t\t\t请选择你的年级：\n");
	HideCursor();
	setPos(45,26);
	choice1=getch();
	switch(choice1)
	{
    	case 49:N=100;break;
		case 50:N=1300;break;
		case 51:N=3500;break;
		case 52:N=300;break;
		case 53:N=300;break;
		case 54:N=300;break;
		default:menu();break;
	}
	
	while(1)
	{
		system("cls");
       getchoice();
	   choice=getch();
	    system("cls");
	    switch(choice)
		{
           	case 49: ch(choice1,N,1);break;
	       case 50: wrongmenu();break;
           	case 51: ch1(choice1);break;
         	case 52:challeng(N);break;
         	case 48: main();break;
           default:main();break;
		}
		if(choice==48)
			break;
	}
	 system("pause");
}

//播放音乐
void pf1()
{
		// 打开音乐
    mciSendString("open 失败.mp3 alias mymusic", NULL, 0, NULL);

// 播放音乐
    mciSendString("play mymusic", NULL, 0, NULL);

       Sleep(2000);

// 停止播放并关闭音乐
           mciSendString("stop mymusic", NULL, 0, NULL);
           mciSendString("close mymusic", NULL, 0, NULL);
}

//播放音乐
void pf2()
{
		// 打开音乐
    mciSendString("open 战斗胜利.mp3 alias mymusic", NULL, 0, NULL);

// 播放音乐
    mciSendString("play mymusic", NULL, 0, NULL);

        Sleep(1700);

// 停止播放并关闭音乐
           mciSendString("stop mymusic", NULL, 0, NULL);
           mciSendString("close mymusic", NULL, 0, NULL);
}



void tshi()
{
	printf("\n\n\t\t\t\t_____________________________________________________________________\n");
	printf("\t\t\t\t|   温馨提示：在操作中按0回到主菜单，输入正确的数字进入相应的程序    |\n");
	printf("\t\t\t\t|              输入单词后按enter键继续                               |\n");
	printf("\t\t\t\t|____________________________________________________________________|\n\n");
	printf("\n\n\n\n\n\t\t\t\t\t\t-----指导老师：曹琼\n");
}


void tshi_1()
{
	printf("\n\n\n\n\t\t\t\t\t=========================\n");
	printf("\t\t\t\t\t[请在%d分钟内完成%d个单词]\n\n",time_1,num);
	printf("\t\t\t\t\t=========================\n\n");
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
	Sleep(3000);
	system("pause");
	//pf();
	menu();
	 system("pause");
}


