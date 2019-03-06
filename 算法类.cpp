/***********************************/
/*     时间：2019.2.10    作者：向敏     */
/*     学号：11803990624           */
/***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#define _STDC_WANT_LIB_EXT1_1


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
	printf("\n\n\n\t\t\t\t★最终得分：%d\t\t",c1*10);
	printf("正确个数：%d\t\t",c1);
    printf("错误个数：%d\n",c2);
	if(c1!=0)
	  printf("\t\t\t\t★正确率：%.2f",((c1*10.0)/(all*10))*100);
	else
      printf("\t\t\t\t正确率：0");
    //calendar_end=time(NULL);
	//end=clock();
	//cpu_time=(double)(end-start)/CLOCKS_PER_SEC;
	//printf("\n\t\t\t\t★CPU用时：%.3lf秒\t\t",cpu_time);
	printf("\n\t\t\t\t★完成用时：%02d:%02d:%02d\n\n",hour,minl,sec);
	if(c1*10==(all*10)&&c1!=0)
		printf("\t\t\t\t★宝贝真棒！下次继续努力哦\n");
	else if(c1*10==0)
		printf("\t\t\t\t★宝贝应该努力了哦\n");
	else
        printf("\t\t\t\t★宝贝不要灰心，还差一点点就满分了\n");
}
//产生随机数1或2
int getnode()
{
	srand(time(NULL));
	return rand()%2+1;
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
	if((fp=fopen("time.txt","a+"))==NULL)
	{
		printf("can't open this file!");
		exit(0);
	}
	 
		fprintf(fp,"%-5d%-3d%-3d%-3d%-3d%-3d%f",time_p->tm_year+1900,time_p->tm_mon+1,time_p->tm_mday,time_p->tm_hour,time_p->tm_min,time_p->tm_sec,((all*10.0)/(c1*10))*100);//记录当前用户所做的时间点
	fclose(fp);


}
//读出时间
void timer_read()
{
	FILE *fp;
	float t;
	int year=0,mon=0,day=0,hour=0,min=0,sec=0;
	if((fp=fopen("time.txt","r"))==NULL)
	{
		printf("can't open this file!");
		exit(0);
	}
	printf("\n\n\n\n\t\t\t\t                     ¤  历史记录  ¤\n");
	printf("\n\n\n\n\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	while(!feof(fp))
	{
		if(fscanf(fp,"%d%d%d%d%d%d%f",&year,&mon,&day,&hour,&min,&sec,&t)!=EOF)
		    printf("\t\t\t\t|时间：%d.%d.%d %02d:%02d:%02d\t正确率：%.3f|\n",year,mon,day,hour,min,sec,t);
	}
	printf("\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	fclose(fp);
}




//选择题数
void choice_3()
{
	
	printf("\n\n\t\t\t\t请输入你要做的题数(1-%d):\n",k);
	setPos(10,7);
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
	if(flag_1)
	   choice_3();
	//choice1(num);
	printf("\n\n\t\t\t\t●三秒后开始\n\n");
	start=time(NULL);//开始时间
    Sleep(3000);
   printf("\t\t\t\t●现在开始\n\n");
	system("cls");//清屏
	sec=3;
	while(i<=all)
	{
		choice1(num);//产生随机数
		p=rand()%k-1;//产生下标随机数
		a=num[index];
		b=num[p];
       while(a+b>k&&index<k-1)//使两者相加小于选择的题的范围k
	   {
		   	a=num[index];
			p=rand()%k-1;
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
	int a=-1,b=0,sum1,d,i=1,k=1,r;
	char sign1='-';
	int num[100],index,flag=1,p=0;
	index=0;
	x=c1=c2=0;
	start=time(NULL);//开始时间
	srand(time(NULL));
	if(flag_1)
	   choice_3();
	printf("\n\n\t\t\t\t●三秒后开始\n\n");
	start=time(NULL);//开始时间
    Sleep(3000);
   printf("\t\t\t\t●现在开始\n\n");
	system("cls");//清屏
	sec=3;
	//choice1(num);
	while(i<=all)
	{
		   choice1(num);
	       a=num[index];
		   	p=rand()%k-1;
		   b=num[p];	
		while(a<b&&index<k-1)//使两者相减不小于0
		{
			
           a=num[index];
		   p=rand()%k-1;
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
	scanf("%d",&sum1);
	printf("\n");
	
	if(sum==sum1)
	{
		printf("\t\t\t\t★回答正确\t");
		c1++;
	}
	else 
	{
		printf("\t\t\t\t★回答错误！\t");
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
	 word=head->next;
	 while(word!=NULL)
	 {
		 printf("\t\t\t\t<%d> %d%c%d%c%d%c%d\n",i,word->a,word->a1,word->b,word->a2,word->c,word->a3,word->sum);
		 i++;
		 word=word->next;
	 }
}

//练习错题
void exertise()
{
	struct infortxt *word,*head=NULL,*p1;
	int i=1,sum1,row=0;
    head=wrongread();
	word=head->next->next;
	start=time(NULL);
	c1=x=0;
	while(word!=NULL)
	 {
		time1();
		x++;
		 printf("\t\t\t\t\t<%d> %d%c%d%c%d%c\n",i,word->a,word->a1,word->b,word->a2,word->c,word->a3);
		 setPos(54,12-row);
		 row=7;//移动光标
		 scanf("%d",&sum1);
		 if(sum1==word->sum)
		 {
			 printf("\t\t\t\t\t★回答正确\n\n");
			 c1++;
		 }
		 else
		 {
			 printf("\t\t\t\t\t★回答错误!\n\n");
			 p1=word->next;
			 free(word);
			 word=p1;
		 }
		end=time(NULL);
	   sec=(int)difftime(end,start);
	   system("cls");
		 i++;
		 word=word->next;
	 }
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
	printf("\t\t\t\t\t======================\n");
	printf("\t\t\t\t\t[请在%d分钟内完成%d道题]\n\n",time_1,all);
	printf("\t\t\t\t\t======================\n\n");
	printf("\t\t\t\t\t马上开始做题：\n\n");
}


//挑战部分--对第一部分的选择
void choice_2(int age)
{
	int d;
	double timer=0.0;
	d=getnode();
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
	int age;
	printf("                       ----------------------------------------------------  \n");
	printf("                       |温馨提示：                                          |\n");
	printf("                       |  请输入正确的数字，进入不同的挑战模块              |\n");
    printf("                       ----------------------------------------------------  \n");
	printf("\n\n\n");
	printf("\t\t\t[     青铜   1         ]\n");
	printf("\n\n");
	printf("\t\t\t[     白银   2         ]\n");
	printf("\n\n");
	printf("\t\t\t[     黄金   3         ]\n");
	printf("\n\n");
	printf("\t\t\t[     钻石   4         ]\n");
	printf("\n\n");
	printf("\t\t\t[     王者   5         ]\n");
	printf("\n\n");
	printf("\t\t\t请选择要挑战的等级：\n");
	scanf("%d",&age);
	switch(age)
	   {
        	case 1:time_1=10;k=20;all=20;choice_2(age);break;
	        case 2:time_1=8;k=40;all=30;choice_2(age);break;
			case 3:time_1=6;k=60;all=40;choice_2(age);break;
			case 4:time_1=4;k=80;all=50;choice_2(age);break;
			case 5:time_1=2;k=100;all=60;choice_2(age);break;
			default:menu();break;
			
	   }

}

void tshi()
{
	printf("                           \t -------------------------------------\n");
	printf("                           \t|温馨提示：                          |\n");
	printf("                           \t|  在操作过程中按0键返回主菜单     |\n");
    printf("                           \t-------------------------------------\n");
	printf("\n");
	printf("\n");
}

/*******************主菜单********************************************/
void showmenu()
{
	printf("                           ***********************************************************************\n");
	printf("\n");
	printf("\n");
	printf("                                      ||||||欢迎进入小学生100以内三位整数加减法|||||\n");
    printf("\n");
	printf("\n");
    printf("                           ***********************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("                                            $$练习模块   1 $$\n");
	printf("\n");
	printf("\n");
	printf("                                            $$错题模块   2 $$\n");
	printf("\n");
	printf("\n");
	printf("                                            $$挑战模块   3 $$\n");
	printf("\n");
	printf("\n");
	printf("                                            $$无尽模块   4 $$\n");
	printf("\n");
	printf("\n");
	printf("                                            $$历史记录   5 $$\n");
	printf("                           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("\n");
	printf("\n");
	printf("请选择：\n");
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
	printf("                          --------------------------------------------------------------------------\n");
	printf("                                                         ☆ 1 浏览错题\n");
	printf("\n");
	printf("\n");
	printf("                                                         ☆ 2 练习错题\n");
	printf("                          --------------------------------------------------------------------------\n");
	printf("请选择：");
	i=getchoice();
	wrongread();
    switch(i)
	 {
        	case 1:wrong_look();
				   break;
	            	
	        case 2:exertise();break;
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
	
	printf("\t\t\t\t★请输入你要做题的大小范围(1-100)：\n");
	setPos(15,3);
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
	int choice;
    all=x=0;
	system("color 2D");
	tshi();
	while(1)
	{
		
		//calendar_start=time(NULL);//用户开始时间
		k=0;
		//start=clock();//处理器运行时间
		showmenu();
	  choice=getchoice();
	  system("cls");
       switch(choice)
	   {
        	case 1:
				choose();
				    d=getnode();
                   switch(d)
				   {
	                    case 1:doAdd(1);break;
	                    case 2:doSub(1);break;
				   };
				   break;
	            	
	        case 2:wrongmenu();break;
			case 3:challeng();break;
			case 4:
				k=100;
				all=10000000;
				d=getnode();
                switch(d)
				 {
	                    case 1:doAdd(0);break;
	                    case 2:doSub(0);break;
				 };
				break;
			case 5:timer_read();break;
			default:menu();break;
			
	   }
	  timer();
	}

}
void main()
{
	menu();
	system("pause");
}



