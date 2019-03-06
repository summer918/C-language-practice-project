#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>

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
void ch(int no,int N,int flag);//根据不同年级，选择不同文件
void ch1(int no);//根据不同年级，选择不同文件浏览
void jump();
void challeng(int choice,int N);//挑战模块
void wrongtxt(struct studentread *head);//错题保存到文件
struct studentread * wrongread();//读出错题


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


//选择题数
void choose()
{
	
	printf("\t\t\t\t\t\n\n\n请输入你要背的单词数(1-20)：\n");
	setPos(20,10);
	scanf("%d",&num);
	
}

//浏览单词
void look(char *st)
{
	FILE *fp;
	char word[1024];
	memset(word,0,sizeof(char)*1024);
	if((fp=fopen(st,"r+"))==NULL)
	{
		printf("can't open this file\n");
		exit(0);
	}
	while(!feof(fp))
	{
		if(fscanf(fp,"%s",word)!=EOF)
		        printf("\t\t\t\t●%s\n",word);
	}
	fclose(fp);
}







//从文件中读出单词模块并创建链表
void read(char *str,int N,int flag)
{
	FILE *fp;
	int i=1;
//	thrd_t p_id;
//	struct mydata data={.hour=0,.min=0,.sec=0};
	struct studentread *p1,*head=(struct studentread *)malloc(sizeof(struct studentread));
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



//背单词模块
void recite(struct studentread *head,int N,int flag)
{
	int i=0,min,n=0,max;
	//mydata *pd=(mydata*)pdata;
	int r=0,c1=0;
	//double cpu_time;
	char string[200];
	struct studentread *p=head->next,*h_d=NULL;
	memset(string,0,sizeof(char)*200);
    hour=minl=sec=0;
	//thrd_join(pd->id,&result);
	if(flag)
	   choose();
	srand(time(NULL));
	i=rand()%(N/2-k)+1;
	k++;
	if(N==k)
		k=0;//以防k>N
	score=num;
	for(min=0;min<N-i;min++)
	{
		if(p!=NULL)
		  p=p->next;
		
	}
	h_d=p;
	max=strlen(p->word);
	printf("\n\n\t\t\t\t●三秒后开始\n\n");
	start=time(NULL);
    Sleep(3000);
   printf("\t\t\t\t●现在开始\n\n");
	system("cls");//清屏
	sec=3;
//	thrd_join(id,NULL);
	for(min=N-i;min<N-i+num;min++)
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
	   printf("\t\t\t\t★|%02d:%02d:%02d|",hour,minl,sec);
	   printf("\t★已背单词数量：%d\t正确个数：%d",n,c1);
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

		printf("\n\n\n\t\t\t\t●中文：%s\n",p->ch);
		printf("\t\t\t\t●请输入英文:");
		scanf("%s",string);
		if(strcmp(string,"0")==0)
		{
			printf("\n\n\n\t\t\t\t学习需要坚持！\n\n");
			menu();
			//break;
		}
		if(strcmp(string,p->word)==0)
		{
			printf("\t\t\t\t●回答正确！\n");
			c1++;
		}
		else
		{
			wrongtxt(p);
			printf("\t\t\t\t●回答错误!\n");
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
	if(flag)//普通练习模块的操作
	{
		printf("\t\t\t\t\t●◆让我们再重新复习一遍吧：\n");
    	for(i=0;i<num;i++)
		{
		printf("\t\t\t\t\t________________________________\n");
		printf("\t\t\t\t\t       %s               \t\t\t\n",h_d->word);
		printf("\t\t\t\t\t________________________________\t\t\t\n");
		printf("\t\t\t\t\t<1> 认识\t<2> 不认识");
		printf("\n\t\t\t\t\t请选择：");
		scanf("%d",&r);
		if(r==1)
		     h_d=h_d->next;
		else
		{
			printf("\t\t\t\t\t●中文：%s",h_d->ch);
		    h_d=h_d->next;
		}
		
		}
	}
	printf("\n\n\n");
	num=0;//以便下次从0开始
	
}


	
//打印分数模块
void display()
{
	printf("\t\t\t\t\t●◆总分:%.0f\n",score);
	if(score!=0)
	    printf("\t\t\t\t\t●◆正确率:%.3f\n",(score/num*1.0)*100);
	else
	    printf("\t\t\t\t\t●◆正确率:0.00\n");
	printf("\t\t\t\t\t●◆用时：\n");
	printf("\t\t\t\t\t\t__________________\n");
    printf("\t\t\t\t\t\t%02d:%02d:%02d   \n",hour, minl, sec);//%02d输出长度为2，不足2前面补0
    printf("\t\t\t\t\t\t_________________\n\n");
    if(num==score)
		printf("\t\t\t\t\t●◆baby，真棒!●◆\n");
	else
		printf("\t\t\t\t\t●◆baby,还要继续努力哦!●◆\n");
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
	if((fp=fopen("wrong.txt","w"))==NULL)
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

//浏览错题
void liulan()
{
	struct studentread *p,*head=NULL;
	head=wrongread();
	p=head->next;
	while(p!=NULL)
	{
		printf("\t\t\t\t\t●●●●●●●●●●●●●●●●●●●●\n");
		printf("\t\t\t\t\t●◆英文：%s                        ●◆\n",p->word);
		printf("\t\t\t\t\t●◆中文：%s                        ●◆\n",p->ch);
		printf("\t\t\t\t\t●●●●●●●●●●●●●●●●●●●●\n\n\n");
		p=p->next;
	}
}

//练习错题
void lianxi()
{
		struct studentread *p,*head=NULL,*p1;
		char word[20];
		int i=0,l=0;
		head=wrongread();
		p=head->next->next;
		while(p!=NULL)
		{
			printf("\t\t\t\t|中文：%s\n\n",p->ch);
			printf("\t\t\t\t|英文：");
			gets(word);
			if(strcmp(word,"0")==0)
			{
			printf("\n\n\n\t\t\t\t学习需要坚持！\n\n");
			menu();
			break;
			}
			if(strcmp(word,p->word)==0)
			{
				printf("\n\n\t\t\t\t●回答正确！\n");
				i++;
			}
			else
			{
				printf("\n\n\t\t\t\t●回答错误！\n");
				p1=p->next;
				free(p);
				p=p1;
				l++;
			}
			p=p->next;
		}
		
		printf("\n\n\t\t\t\t●●_____________________________●●\n");
		printf("\n\n\t\t\t\t●●消灭单词：%d |待消灭单词：%d ●●\n",i,l);
		printf("\n\n\t\t\t\t●●_____________________________●●\n\n");
		wrong_baocun(head);
}


   
//根据不同年级，选择不同文件
void ch(int no,int N,int flag)
{
	char *str;
	switch(no)
	{
    	case 1:str="word1.txt";num=20;read(str,N,flag);break;
		case 2:str="word2.txt";num=30;read(str,N,flag);break;
		case 3:str="word3.txt";num=40;read(str,N,flag);break;
		case 4:str="word4.txt";num=60;read(str,N,flag);break;
		case 5:str="word5.txt";num=80;read(str,N,flag);break;
		case 6:str="word6.txt";num=100;read(str,N,flag);break;
	}
	

}

//根据不同年级，选择不同文件浏览
void ch1(int no)
{
	char *str;
	switch(no)
	{
    	case 1:str="word1.txt";look(str);break;
		case 2:str="word2.txt";look(str);break;
		case 3:str="word3.txt";look(str);break;
		case 4:str="word4.txt";look(str);break;
		case 5:str="word5.txt";look(str);break;
		case 6:str="word6.txt";look(str);break;
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
void challeng(int choice1,int N)
{
	int i;
    printf("\t\t\t\t_____________________________________________________________________\n");
	printf("\t\t\t\t|   温馨提示：请选择不同的等级，在规定的时间中将题全部答对           |\n");
	printf("\t\t\t\t|____________________________________________________________________|\n\n\n");
	printf("\t\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n");
	printf("\t\t\t\t▎       1 青铜           ▎\n\n");
	printf("\t\t\t\t▎       2 白银           ▎\n\n");
	printf("\t\t\t\t▎       3 黄金           ▎\n\n");
	printf("\t\t\t\t▎       4 铂金           ▎\n\n");
	printf("\t\t\t\t▎       5 钻石           ▎\n\n");
	printf("\t\t\t\t▎       6 黄金           ▎\n\n");
	printf("\t\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n");
	printf("\t\t\t\t●◆欢迎进入挑战模块，祝你好运!●◆\n\n");
	printf("\t\t\t\t请选择：");
	scanf("%d",&i);
	switch(i)
	{
	  case 1:time_1=7;break;
      case 2:time_1=6;break;
	  case 3:time_1=5;break;
	  case 4:time_1=4;break;
	  case 5:time_1=3;break;
	  case 6:time_1=2;break;
	  default:printf("\t\t\t\t请输入正确的序号！\n\n");
	}
	printf("\t\t\t\t挑战马上开始啦\n\n");
	ch(choice1,i,0);
    jump();

}

//错题目录
void wrongmenu()
{
	int i;
	printf("\t\t\t\t\t                          --------------------\n");
	printf("\t\t\t\t\t                              1 浏览错题\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t\t\t                              2 练习错题\n");
	printf("\t\t\t\t\t                          --------------------\n\n\n");
	printf("\t\t\t\t请选择：");
	scanf("%d",&i);
	system("cls");
    switch(i)
	 {
        	case 1:liulan();
				   break;
	            	
	        case 2:lianxi();break;
			default:menu();break;
	}
}


//选择模块
void getchoice()
{
	printf("\t\t\t\t\t●◆●◆●◆●◆●◆●◆\n");
	printf("\t\t\t\t\t●1 背单词模式        ●\n\n");
    printf("\t\t\t\t\t●2 错题模式          ●\n\n");
	printf("\t\t\t\t\t●3 浏览单词          ●\n\n");
	printf("\t\t\t\t\t●4 挑战模式          ●\n\n");
	printf("\t\t\t\t\t●0 退出              ●\n\n");
	printf("\t\t\t\t\t●◆●◆●◆●◆●◆●◆\n\n\n");
	printf("\t\t\t\t\t请选择：\n");
}

//退出模块
void leave()
{
	printf("\t\t\t\t\t☆☆☆☆小主人，今天真棒，欢迎下次来学习！☆☆☆☆\n\n\n\n");
}
//主菜单
void menu()
{
	int choice,choice1,N;
	printf("\n\n\n\n\t\t\t□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf("\t\t\t□                           欢迎进入背单词程序                             □\n");
	printf("\t\t\t□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n\n");
	printf("\t\t\t\t●◆学习使你快乐，让我们一起快乐学习吧！●◆                \n");
	printf("\t\t\t\t\t▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n");
	printf("\t\t\t\t\t▎   1   小学              ▎\n\n");
	printf("\t\t\t\t\t▎   2   初中              ▎\n\n");
	printf("\t\t\t\t\t▎   3   高中              ▎\n\n");
	printf("\t\t\t\t\t▎   4   四级              ▎\n\n");
	printf("\t\t\t\t\t▎   5   六级              ▎\n\n");
	printf("\t\t\t\t\t▎   6   八级              ▎\n\n");
	printf("\t\t\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n");
	printf("\t\t\t\t请选择你的年级：\n");
	setPos(34,33);
	scanf("%d",&choice1);
	switch(choice1)
	{
    	case 1:N=100;break;
		case 2:N=1300;break;
		case 3:N=3500;break;
		case 4:N=350;break;
		case 5:N=350;break;
		case 6:N=350;break;
		default:menu();break;
	}
	system("cls");
	while(1)
	{
    getchoice();
	scanf("%d",&choice);
	system("cls");
	switch(choice)
	{
	case 1: ch(choice1,N,1);break;
	case 2: wrongmenu();break;
	case 3: ch1(choice1);break;
	case 4:challeng(choice1,N);break;
	case 0: leave();break;
    default:menu();break;
	}
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


