/***********************************/
/*     时间：2019.2.10    作者：向敏     */
/*     学号：11803990624           */
/***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#define _STDC_WANT_LIB_EXT1_1
#pragma comment(lib, "Winmm.lib")


int x=0;//统计已做的题数
int c1=0,c2=0;//全局变量，统计错误和正确的个数
time_t start=0,end=0;
//time_t calendar_start,calendar_end;
int all=0,k=0;//all-题数，k-题的范围
int time_1=0;//挑战时间限制
int hour=0,minl=0,sec=0;//记录时间

struct infortxt
{
	int a;
	char a1;
	int b;
	char a2;
	int c;
	char a3;
	int sum;
	struct infortxt *next;
};


void showmenu();//主菜单
void menu();
int  getchoice();//选择模块
void  choice1(int num[]);//产生不重复的随机数
void  choice_3();//选择题数
void sysExit();//退出模块
void wrongtext(int a,char a1,int b,char a2,int c,int sum);//将错题保存到文件
void cause(int c1,int c2,int all);//统计成绩
int getnode();//产生随机数1或2
void doAdd(int flag_1);//加法模块
void doSub(int flag_1);//减法模块
void doAdd1(int *num,int all,int a,int b,int sum,char sign1);//第二部分加法模块
void doSub1(int *num,int all,int a,int b,int sum1,char sign1);//第二部分减法模块
void caculate(int all,int a,int b,int c,int sum,char sign,char sign1);//计算模块
struct infortxt * wrongread();//查看错题模块
void challeng();//挑战模块
void jump();//挑战评语
void chioce_2(int age);//对第一部分的选择
void time_jump(int age,double timer);//挑战时间的评分
void choice_2(int age);//挑战部分--对第一部分的选择
void timer();


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

//隐藏光标
void HideCursor()
{
CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//失败声音
void pf1()
{
		// 打开音乐
    mciSendString("open 失败.mp3 alias mymusic", NULL, 0, NULL);

// 播放音乐
    mciSendString("play mymusic", NULL, 0, NULL);

       Sleep(1500);
// 停止播放并关闭音乐
           mciSendString("stop mymusic", NULL, 0, NULL);
           mciSendString("close mymusic", NULL, 0, NULL);
}


//成功声音
void pf2()
{
		// 打开音乐
    mciSendString("open 战斗胜利.mp3 alias mymusic", NULL, 0, NULL);

// 播放音乐
    mciSendString("play mymusic", NULL, 0, NULL);

       Sleep(1500);

// 停止播放并关闭音乐
           mciSendString("stop mymusic", NULL, 0, NULL);
           mciSendString("close mymusic", NULL, 0, NULL);
}

//进入系统声音
void pf3()
{
		// 打开音乐
    mciSendString("open 3530.mp3 alias mymusic", NULL, 0, NULL);

// 播放音乐
    mciSendString("play mymusic", NULL, 0, NULL);

       Sleep(4000);

// 停止播放并关闭音乐
           mciSendString("stop mymusic", NULL, 0, NULL);
           mciSendString("close mymusic", NULL, 0, NULL);
}

//记录时间
void time1()
{	
	
	while(sec>60)
	  {
		   minl++;
		   sec=sec-60;
	  }
	   if(minl>60)
	   {
		   hour++;
		   minl=0;
	   }
	   if(hour>24)
		   hour=0;
	   printf("\n\n\n\t\t\t\t★|%02d:%02d:%02d|",hour,minl,sec);
	   printf("\t★已做题数量：%d\t★正确个数：%d\n\n",x,c1);
}


/*******************打印分数模块*************************************/
void cause(int c1,int c2,int all)
{
//	double cpu_time=0.0;
	system("color B4");
	printf("\n\n\n\t\t\t\t★最终得分：%d\t\t",c1*10);
	//printf("正确个数：%d\t\t",c1);
    printf("错误个数：%d\n",c2);
	if(c1!=0)
	  printf("\t\t\t\t★正确率：%.2f",((c1*10.0)/(all*10))*100);
	else
      printf("\t\t\t\t★正确率：0");
    //calendar_end=time(NULL);
	//end=clock();
	//cpu_time=(double)(end-start)/CLOCKS_PER_SEC;
	//printf("\n\t\t\t\t★CPU用时：%.3lf秒\t\t",cpu_time);
	//printf("\n\t\t\t\t★完成用时：%02d:%02d:%02d\n\n",hour,minl,sec);
	time1();
	if(c1*10==(all*10)&&c1!=0)
		printf("\t\t\t\t★宝贝真棒！下次继续努力哦\n");
	else if(c1*10==0)
		printf("\t\t\t\t★宝贝应该努力了哦\n");
	else
        printf("\t\t\t\t★宝贝不要灰心，还差一点点就满分了\n");
	system("pause");
}
//产生随机数1或2
int getnode()
{
	srand(time(NULL));
	return rand()%2+1;
}

//三秒钟开始
void time_2()
{
	for(sec=1;sec<=3;sec++)
	{
		if(sec==1)
			color(4);
		else if(sec==2)
			color(5);
		else
			color(6);
		printf("\n\n\n\n\t\t\t\t\t\t-*%d",sec);
		Sleep(1000);
		system("cls");
	}
	printf("\n\n\n\n\t\t\t\t\tReady!\n");
	Sleep(800);
	system("cls");
	printf("\n\n\n\n\t\t\t\t\tGo!\n");
	Sleep(800);
	system("cls");
}

//产生不重复的数
void  choice1(int *num)
{
	int w,t;
	int i;
	srand(time(NULL));
	for(i=0;i<k;i++)
		  num[i]=i;
	for(i=0;i<k;i++)
	 {
		  w=rand()%(k-i)+i;
		  t=num[i];
		  num[i]=num[w];
		  num[w]=t;
	}
}

//记录时间
void timer()
{
	FILE *fp;
	time_t time_str;
	struct tm *time_p;
	time_str=time(&time_str);
	time_p=localtime(&time_str);
	//printf("%d %d %d %d:%d:%d",(time_p->tm_year)+1900,time_p->tm_mon+1,time_p->tm_mday,time_p->tm_hour,time_p->tm_min,time_p->tm_sec);
	if((fp=fopen("time.txt","ab+"))==NULL)
	{
		printf("can't open this file!");
		exit(0);
	}
	 
		fprintf(fp,"%-6d%-4d%-4d%-4d%-4d%-4d%-4d",time_p->tm_year+1900,time_p->tm_mon+1,time_p->tm_mday,time_p->tm_hour,time_p->tm_min,time_p->tm_sec,((c1*10)/(all*10))*100);//记录当前用户所做的时间点
	fclose(fp);


}

//读出时间
void timer_read()
{
	FILE *fp;
	int t;
	int year=0,mon=0,day=0,hour=0,min=0,sec=0;
	system("color C");
	if((fp=fopen("time.txt","r"))==NULL)
	{
		printf("can't open this file!");
		exit(0);
	}
	color(3);
	 printf("\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	 printf("\t\t┃                 ╮(￣▽ ￣)╭  历史记录\n");
	 printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	while(!feof(fp))
	{
		if(fscanf(fp,"%d%d%d%d%d%d%d",&year,&mon,&day,&hour,&min,&sec,&t)!=EOF)
		{
			if(t==100)
				color(1);
			else if(t>=70)
				color(5);
			else if(t>=60)
				color(6);
			else
				color(4);
			  printf("\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	          printf("\t\t┃时间：%d.%d.%d %02d:%02d:%02d\t正确率：%d                                \n",year,mon,day,hour,min,sec,t);  
	          printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		}
	}
	fclose(fp);
	system("pause");
}




//选择题数
void choice_3()
{
	
	printf("\n\n\t\t\t\t★请输入你要做的题数(1-%d):\n",k);
	setPos(40,7);
    scanf("%d",&all);
	system("cls");
	
}

/******************加法模块*******************************************/
void doAdd(int flag_1)
{
	int a=100,b=1,sum,d,i=1,r;
	int index=0,p=0;
	int num[100],flag=1;
	char sign1='+';
	x=c1=c2=0;
	srand(time(NULL));
	if(flag_1==1)
	   choice_3();
	system("color E4");
	printf("\n\n\t\t\t\t●三秒后开始\n\n");
	 time_2();
	start=time(NULL);//开始时间
	sec=0;
	while(i<=all)
	{
  // 打开音乐
    mciSendString("open 3530.mp3 alias mymusic", NULL, 0, NULL);

    // 播放音乐
    mciSendString("play mymusic", NULL, 0, NULL);
		choice1(num);//产生随机数
		p=rand()%(k-1);//产生下标随机数
		a=num[index];
		b=num[p];
       while(a+b>k&&index<k-1)//使两者相加小于选择的题的范围k
	   {
		   	a=num[index];
			p=rand()%(k-1);
		    b=num[p];
		   index++;
		   flag=0;
		   
	   }
	   if(index==k-1&&a+b>k)//如果找遍都不满足就重新开始循环
	   {
		   index=0;
		   continue;
		  
	   }
       d=getnode();
	   sum=a+b;
	    if(!flag_1)//挑战时间限制
	   {
		   if(minl==time_1)
		   {
			   color(4);
			    printf("\n\n\t\t\t\t★挑战失败！★\n\n");
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
	   switch(d)
	   {
	      case 1:doAdd1(num,all,a,b,sum,sign1);break;
	      case 2:doSub1(num,all,a,b,sum,sign1);break;
	   }
	  i++;
	  
	  if(flag)
		index++;
	}
	
}
/******************减法模块*******************************************/
void doSub(int flag_1)
{
	int a=-1,b=0,sum1,d,i=1,r;
	char sign1='-';
	int num[100],index,flag=1,p=0;
	index=0;
	x=c1=c2=0;
	system("color E4");
	start=time(NULL);//开始时间
	srand(time(NULL));
	if(flag_1==1)
	   choice_3();
	printf("\n\n\t\t\t\t●三秒后开始\n\n");
    time_2();
	sec=0;
	start=time(NULL);//开始时间
	while(i<=all)
	{
			// 打开音乐
    mciSendString("open 3530.mp3 alias mymusic", NULL, 0, NULL);

// 播放音乐
    mciSendString("play mymusic", NULL, 0, NULL);
		   choice1(num);
	       a=num[index];
		   	p=rand()%(k-1);
		   b=num[p];	
		while(a<b&&index<k-1)//使两者相减不小于0
		{
			
           a=num[index];
		   p=rand()%(k-1);
		   b=num[p];
		   index++;
		   flag=0;
		}
		 if(index==k-1&&a<b)//如果找遍都不满足就重新开始循环
		 {
			 index=0;
			 continue;
		 }
    sum1=a-b;
	d=getnode();
	if(!flag_1)
	 {
		   if(minl==time_1)
		   {
			    printf("\n\n\t\t\t\t★挑战失败!…(⊙_⊙;)… ○\n\n");
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
	switch(d)
	{
	   case 1:doAdd1(num,all,a,b,sum1,sign1);break;
	   case 2:doSub1(num,all,a,b,sum1,sign1);break;
	}
	i++;
	if(flag)//如果两者相减一次满足条件，则下标index+1
		index++;
	}
	
}
/******************第二部分加法模块*******************************************/
void doAdd1(int *num,int all,int a,int b,int sum,char sign1)
{
	int c=0,sum1,i=0;
	char sign='+';
	c=num[i];
	while(sum+c>k)
	{
		if(i==k)//当寻遍所有的数都没有发现满足条件则重新生成随机数，从头开始寻找
		{
			choice1(num);
			i=0;
			continue;
		}
		
      c=num[i++];
	}
	
	sum1=sum+c;
	time1();
	x++;//已做题数

	printf("\n\t\t\t\t\t<%d> %d%c%d+%d=",x,a,sign1,b,c);
	caculate(all,a,b,c,sum1,sign,sign1);
	
}
/******************第二部分减法模块*******************************************/
void doSub1(int num[],int all,int a,int b,int sum1,char sign1)
{
	int c=0,sum,i=0;
	char sign='-';
	c=num[i];
	while(sum1-c<0)
	{
	
		if(i==k)//当寻遍所有的数都没有发现满足条件则重新生成随机数，从头开始寻找
		 {
			choice1(num);
			i=0;
		}
        c=num[i++];
	}
	sum=sum1-c;
	time1();
	x++;//已做题数
	printf("\n\t\t\t\t\t<%d> %d%c%d-%d=",x,a,sign1,b,c);//输出表达式
	caculate(all,a,b,c,sum,sign,sign1);
	
}
/*******************判断模块**********************************************/
void caculate(int all,int a,int b,int c,int sum,char sign,char sign1)
{
	int sum1;
	char i;
	scanf("%d",&sum1);
	if(sum1==0)
	{
		 HideCursor();
		printf("\n\n\t\t\t是否退出程序\n");
		printf("\n\t\t\t<1>是\t<2>否\n");
		i=getch();
		if(i==49)
			menu();
	}
	printf("\n");
	
	if(sum==sum1)
	{
	
			// 停止播放并关闭音乐
           mciSendString("stop mymusic", NULL, 0, NULL);
           mciSendString("close mymusic", NULL, 0, NULL);
		   pf2();
		   color(5);
		   printf("\t\t\t\t★回答正确≧◇≦\t");
		   Sleep(100);
	
		c1++;
	}
	else 
	{
	
			// 停止播放并关闭音乐
           mciSendString("stop mymusic", NULL, 0, NULL);
           mciSendString("close mymusic", NULL, 0, NULL);
		pf1();
		color(4);
		printf("\t\t\t\t★回答错误!(*+﹏+*)~@\t");
		 Sleep(100);
	    wrongtext(a,sign1,b,sign,c,sum);
		c2++;
	}
	   end=time(NULL);
	   sec=(int)difftime(end,start);
	system("cls");
	if(all==x)
	cause(c1,c2,all);
	
}
/*******************错题本********************************************/
//错题保存模块
void wrongtext(int a,char a1,int b,char a2,int c,int sum)
{
	FILE *fp;
	char d='=';
	if((fp=fopen("error.txt","a+"))==NULL)
	{
		printf("can't open this file!");
		exit(0);
	}
	fprintf(fp,"%d%c%d%c%d%c%-5d",a,a1,b,a2,c,d,sum);
	fclose(fp);
}

//将错题全部保存到文件中
void wrong_baocun(struct infortxt *head)
{
      FILE *fp;
	struct infortxt *word;
	word=head->next;
	if((fp=fopen("error.txt","w"))==NULL)
	{
		printf("can't open this file!");
		exit(0);
	}
	while(word!=NULL)
	{
			fprintf(fp,"%d%c%d%c%d%c%-5d",word->a,word->a1,word->b,word->a2,word->c,word->a3,word->sum);
			word=word->next;
	}
	fclose(fp);
	system("pause");
	showmenu();
}

//从文件中读出错题
struct infortxt * wrongread()
{
	 FILE *fp;
	struct infortxt *word,*head=NULL;
   head=(struct infortxt*)malloc(sizeof(struct infortxt));
	memset(head,0,sizeof(struct infortxt));
	if((fp=fopen("error.txt","r"))==NULL)
	{
		printf("can't open this file!");
		exit(0);
	}
	
	while(!feof(fp))
	{	
		word=(struct infortxt*)malloc(sizeof(struct infortxt));
		memset(word,0,sizeof(struct infortxt));
		if(fscanf(fp,"%d%c%d%c%d%c%d",&word->a,&word->a1,&word->b,&word->a2,&word->c,&word->a3,&word->sum)!=EOF)
		{
			word->next=head->next;
			head->next=word;
		}
    	      
	}
	fclose(fp);
	return head;
}
//查看错题
void wrong_look()
{
     struct infortxt *word,*head=NULL;
	 int i=1;
	 head=wrongread();
	 system("color 5");
	 word=head->next;
	 if(word==NULL)
		 printf("\n\n\t\t\t\t现在还没有错题！\n\n");
	 printf("\n\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	 printf("\t\t┃                    错题本    \n");
	 printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	 while(word!=NULL)
	 {
		 if(i%2==0)
			 color(3);
		 else
			 color(4);
		 printf("\n\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	     printf("\t\t┃                  <%d> %d%c%d%c%d%c%d      \n",i,word->a,word->a1,word->b,word->a2,word->c,word->a3,word->sum);
	     printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		 if(i%8==0)
		 {
			 system("pause");
			 system("cls");
			  printf("\n\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	           printf("\t\t┃                    错题本    \n");
	           printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

			 
		 }
		 i++;
		 word=word->next;
	 }
	 //system("pause");
}

//练习错题
void exertise()
{
	system("color 9");
	struct infortxt *word,*head=NULL,*p1;
	int i=1,sum1,row=0;
    head=wrongread();
	word=head;
	start=time(NULL);
	c1=x=0;
	if(word->next==NULL)
		 printf("\n\n\t\t\t\t现在还没有错题!:-P\n\n");
	while(word->next!=NULL)
	 {
		time1();
		x++;
		 printf("\t\t\t\t\t<%d> %d%c%d%c%d%c\n",i,word->next->a,word->next->a1,word->next->b,word->next->a2,word->next->c,word->next->a3);
		 setPos(54,5);
		 //移动光标
		 scanf("%d",&sum1);
		 if(sum1==word->next->sum)
		 {
			 color(5);
			 printf("\t\t\t\t\t★回答正确≧◇≦\n\n");
			 pf2();
			 //Sleep(1000);
			 c1++; 
			 word=word->next;
		 }
		 else
		 {
			 color(4);
			 printf("\t\t\t\t\t★回答错误!(×_×)\n\n");
			 pf1();
			 //Sleep(1000);
			 p1=word->next;
			 word->next=word->next->next;
			 free(p1);
		 }
		end=time(NULL);
	   sec=(int)difftime(end,start);
	   system("cls");
		 i++;//做题个数
		
	 }
	system("color B5");
	printf("\n\n\n\t\t\t\t★★★★★★★★★★★★★★★★★★★\n");
	printf("\t\t\t\t★消灭题数：%d\t待消灭题数：%d      ★\n",c1,x-c1);
	printf("\t\t\t\t★★★★★★★★★★★★★★★★★★★\n");
	wrong_baocun(head);

}




//挑战评语
void jump()
{
	if(minl<time_1&&c1==all)
		printf("\t\t\t\t\t挑战成功！\n");
	 else 
         printf("\t\t\t\t\t很遗憾，挑战失败！\n");
}

void tshi_1()
{
	system("color 81");
	printf("\t\t\t\t\t======================\n");
	printf("\t\t\t\t\t[请在%d分钟内完成%d道题]\n\n",time_1,all);
	printf("\t\t\t\t\t======================\n\n");
	Sleep(2000);
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t马上开始做题：\n\n");
}


//挑战部分--对第一部分的选择
void choice_2(int age)
{
	int d;
	double timer=0.0;
	d=getnode();
	system("cls");
	switch(d)
	{
	         case 1:
				    tshi_1(); 
				    doAdd(0);
			    //	calendar_end=time(NULL);
			    	//timer=difftime(end,start)/60.0;
				    jump();
					break;
	         case 2:tshi_1();
				    doSub(0);
					//calendar_end=time(NULL);
				    //timer=difftime(end,start)/60.0;
				   jump();
					break;
	}
				  
}
//挑战模块
void challeng()
{
	char age;
	system("color 4");
	printf("                       +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n");
	printf("                       |温馨提示：                                               |\n");
	printf("                       |  请输入正确的数字,越往下难度越高，进入不同的挑战模块    |\n");
    printf("                       +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\n\n");
	color(2);
	printf("\t\t\t[     青铜   1         ]\n");
	printf("\n\n");
	color(3);
	printf("\t\t\t[     白银   2         ]\n");
	printf("\n\n");
	color(4);
	printf("\t\t\t[     黄金   3         ]\n");
	printf("\n\n");
	color(5);
	printf("\t\t\t[     钻石   4         ]\n");
	printf("\n\n");
	color(6);
	printf("\t\t\t[     王者   5         ]\n");
	printf("\n\n");
	printf("\t\t\t请选择要挑战的等级：\n");
    age=getch();
	switch(age)
	   {
        	case 49:time_1=10;k=20;all=10;choice_2(age);break;
	        case 50:time_1=8;k=40;all=15;choice_2(age);break;
			case 51:time_1=6;k=60;all=20;choice_2(age);break;
			case 52:time_1=4;k=80;all=25;choice_2(age);break;
			case 53:time_1=2;k=100;all=30;choice_2(age);break;
			default:menu();break;
			
	   }
	system("cls");

}

void tshi()
{
	printf("\n\n\n");
	printf("\t\t\t\t==================================================================== \n");
	printf("\t\t\t\t|温馨提示：(￣(工)￣)                                               |\n");
	printf("\t\t\t\t|  在操作过程中请输入数字，按0退出程序                              |\n");
    printf("\t\t\t\t|其他输入，可能会出现意想不到的事情                                 |\n");
    printf("\t\t\t\t====================================================================\n");
	printf("\n\n\n\t\t\t\t\t              ------指导老师：曹琼");
	printf("\n");
	//Sleep(3000);
}

/*******************主菜单********************************************/
void showmenu()
{
	printf("                           ===============================================================\n");
	printf("\n");
	printf("                                      ||||||欢迎进入小学生100以内三位整数加减法|||||\n");
    printf("\n");
    printf("                           ===============================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                           ◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆\n");
	printf("                                            ▓练习模块   1 \n");
	printf("\n");
	printf("                                            ▓错题模块   2 \n");
	printf("\n");
	printf("                                            ▓挑战模块   3 \n");
	printf("\n");
	printf("                                            ▓无尽模块   4 \n");
	printf("\n");
	printf("                                            ▓历史记录   5 \n");
	printf("                           ◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆\n");
	printf("\n");
	//printf("请选择：\n");
}

//退出模块
void sysExit()
{
	printf("再见啦！baby\n");
}

//错题目录
void wrongmenu()
{
	 char i;
     system("color B6");                    
     printf("\n\n\n\t\t\t\t            (oo) \n\n");
     printf("\t\t\t\t   /-------\\/☆ 1 浏览错题\n\n"); 
     printf("\t\t\t\t / |         || \n\n"); 
     printf("\t\t\t*    ||----||      ☆ 2 练习错题\n\n");
     printf("\t\t\t\t     ~~    ~~  \n\n");
	  printf("\t\t\t\t请选择：");
	  setPos(35,16);
	i=getch();
	system("cls");
    switch(i)
	 {
        	case 49:wrong_look();
				   break;
	            	
	        case 50:exertise();break;
			default:menu();break;
	}
}

//选择模块
int getchoice()
{
	int d;
    scanf("%d",&d);
	fflush(stdin);
	return d;
}


void choose()
{
	
	printf("\n\n\t\t\t\t★请输入你要做题的大小范围(1-100)：\n");
	setPos(40,3);
	scanf("%d",&k);
}

//线程问题
/* int in_gore(void *pdata)
{
	 int hour = 0, min = 0, sec = 0;
    while (1)
	{
        Sleep(1000);//暂停1s
        system("cls");//清屏
        sec++;
        if (sec == 60){
            min++;
            sec = 0;
        }
        if (min == 60){
            hour++;
            min = 0;
        }
        if (hour == 24){
            hour = 0;
        }
        printf("%02d:%02d:%02d\n", hour, min, sec);
        //%02d输出长度为2，不足2前面补0
    }
    return 0;
}*/



//主菜单
void menu()
{
	int d;
	char choice;
    all=x=0;
	system("color B2");
    system("cls");
	while(1)
	{
		
		//calendar_start=time(NULL);//用户开始时间
		k=0;
		//start=clock();//处理器运行时间
		system("cls");
		system("color B5");
		showmenu();
	  choice=getch();
	  system("cls");
       switch(choice)
	   {
        	case 49:
				choose();
				d=getnode();
                   switch(d)
				   {
	                    case 1:doAdd(1);break;
	                    case 2:doSub(1);break;
				   };
				   break;
	            	
	        case 50:wrongmenu();break;
			case 51:challeng();break;
			case 52:
				k=100;
				all=10000000;
				d=getnode();
                switch(d)
				 {
	                    case 1:doAdd(4);break;
	                    case 2:doSub(4);break;
				 };
				break;
			case 53:timer_read();break;
			default:menu();break;
			
	   }
     if(choice!=5)
	   timer();//记录时间
	}


}
void main()
{
	int i;
	tshi();
//	pf();
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
	menu();
	system("pause");
}



