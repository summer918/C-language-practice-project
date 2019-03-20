#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
int flag=0,x=0,book=0,m=1;// m 记录读者编号//做标记
char zh[13],cod[13],code[13];//密码
int number;//已借阅数量
int choice;
//图书信息管理
struct admin
{
	int no;//图书编号
	char book[30];//书名
	char edname[20];//作者名
	char no1;//分类号
	char pub[40];//出版单位
	char time[20];//出版时间
	int num;//库存数量
	int price;//价格
	struct admin *next;
};
//读者信息管理
struct reader
{
	int num;//编号
	char num1[20];//借阅号
    char name[20];//姓名
	int max;//最大借阅额度
	int num2;//已借阅数量
	char code[12];//读者密码
	struct reader *next;
};
//管理员信息记录
struct admin_infor
{
	char name[20];
	int year;
	int day;
	int mon;
};
	
//借阅信息查询
struct brrow
{
	char name[20];//读者名字
	char edname[20];//借阅书名
	char writer[20];//作者
	int year;
	int day;
	int mon;
	struct brrow *next;
};
//还书信息查询
struct giveback
{
	char edname[100];//归还书籍名
	char name[20];//读者姓名
	char writer[20];//作者
	int year;
	int day;
	int mon;
	struct giveback *next;
};

//存储账号
struct zhang
{
	char zh[13];
	char code[13];
	struct zhang *next;
};


/*       管理员功能--图书信息管理     */
void main();//主函数
struct admin *getNode();//创建链表并读入图书信息
void getNode1(struct admin *p);//修改图书数据
struct admin * creat();//录入图书信息
void Save(struct admin * list);//将图书内容保存到文件
struct admin *Initial_list2();//从文件中读取数据，以初始化有头结点的链表
void add(struct admin *list,struct admin *node);//添加图书
void lookup1(struct admin *list,char *book);//查询图书,按书名查询
void lookup2(struct admin *list,char *edname);//查询图书,按作者名查询
void lookup3(struct admin *list,char *pub);//查询图书,按出版单位查询
void lookup4(struct admin *list,char *time);//查询图书,按出版时间查询
void freeList(struct admin *list);//删除全部图书
void display(struct admin *list);//浏览图书
void mod(struct admin *head);//修改图书
void deleteNodeByNo2(struct admin *list,char *name);//删除图书
//借阅信息查询
void brrowread(struct reader *p,struct admin *p_1,int year,int mon,int day);
struct brrow * brr();
void look_up_1(struct brrow *list,char *book_name);
void look_up_2(struct brrow *list,char *book_name);
void look_up_3(struct brrow *list,char *book_name);
void brrower_menu();
//还书信息查询
 void returnread(struct reader *p,struct admin *p_1);
struct giveback * back();
void backlook_up1(struct giveback *list,char *book_name);
void backlook_up2(struct giveback *list,char *book_name);
void backlook_up3(struct giveback *list,char *book_name);
void back_menu();
static void setPos(int x,int y);
void menueadmin1();//管理员页面--图书
void menueadmin2();//管理员页面--读者
void listWithHead();//管理员--图书的程序，进入不同的程序
void listWithHead1();//管理员--读者的程序，进入不同的程序
void ch();//选择模块



	
/*       管理员功能--读者信息管理     */
void admincode(int m);//登录页面
struct zhang * zhang_1(struct zhang *list);//读出账号
struct reader *getNode2();//创建链表并读入读者信息
struct reader *  creat1(char *name_1,char *num_1);//录入图书读者信息
void Save2(struct reader *list);//将读者信息保存到文件
void Save1(struct reader *p1);
void add1(struct reader *list,struct reader *node);//添加读者
struct reader *Initial_list();//从文件中读取数据，以初始化有头结点的链表
struct reader * look2(struct reader *list,char *name);//按读者查询借阅情况
void freeList1(struct reader *list);//删除全部读者信息
void display1(struct reader *list);//浏览读者信息
void mod1(struct reader *head);//修改读者信息
void deleteNodeByNo(struct reader  *list,char *name);//删除读者信息
void freelist2(struct reader *list);//释放读者链表内存
void denji();//注册页面

/*           读者功能                 */
void borrow();//借阅图书
void find();//查询图书
struct reader * look_1(struct reader *list,char *index);
void find_1();//根据借阅号查询图书
void  return_book();//归还图书
void revise_code();//修改密码
void reader();//读者页面
void choice_read(char *nam,char *num);//读者选择模块
void menu();
/*为方便起见，图书管理程序全部采用有头结点的链表*/


/*                            管理员功能--图书信息管理               */
//创建链表并读入图书信息
struct admin *getNode()
{
	struct admin *p=NULL;
	p=(struct admin *)malloc(sizeof(struct admin));
	memset(p,0,sizeof(struct admin));
	printf("\t\t\t ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n");
	printf("\t\t\t ☆☆图书编号:");
	scanf("%d",&p->no);
	printf("\t\t\t ☆☆书名:");
	fflush(stdin);
	gets(p->book);
	printf("\t\t\t ☆☆作者:");
	fflush(stdin);
	gets(p->edname);
	printf("\t\t\t ☆☆分类号:");
	scanf("%c",&p->no1);
	printf("\t\t\t ☆☆出版单位:");
	fflush(stdin);
	gets(p->pub);
	printf("\t\t\t ☆☆出版时间:");
	fflush(stdin);
	gets(p->time);
	printf("\t\t\t ☆☆库存量 & 价格:");
	scanf("%d%d",&p->num,&p->price);
	printf("\t\t\t ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n\n");
	return p;
}

//修改图书数据
void getNode1(struct admin *p)
{
	printf("\t\t\t ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n");
	printf("\t\t\t ☆☆tinput new 编号:");
	scanf("%d",&p->no);
	printf("\t\t\t ☆☆input new 书名:");
	fflush(stdin);
	gets(p->book);
	printf("\t\t\t ☆☆input new 作者:");
	fflush(stdin);
	gets(p->edname);
	printf("\t\t\t ☆☆input new 分类号:");
	scanf("%c",&p->no1);
	printf("\t\t\t ☆☆input new 出版单位:");
	fflush(stdin);
	gets(p->pub);
	printf("\t\t\t ☆☆input new 出版时间:");
	fflush(stdin);
	gets(p->time);
	printf("\t\t\t ☆☆input new 库存量 & 价格:");
	scanf("%d%d",&p->num,&p->price);
	printf("\t\t\t ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n\n");
}


//利用头插法创建有头结点的链表
//录入图书信息
struct admin * creat()
{
	struct admin *head=(struct admin *)malloc(sizeof(struct admin));
	
	struct admin *node=NULL;

	memset(head,0,sizeof(struct admin));//清空内存残余
	printf("\n\n\t\t\t\t温馨提示：当全部输入0的时候录入图书结束\n");
	while(1)
	{
		node=getNode();
		if(node->no==0)
			break;//当图书编号为0时输入结束
	    node->next=head->next;
		head->next=node;
	}
	return head;
}

//将图书内容保存到文件
void Save(struct admin * list)
{
	struct admin *p = list->next;
	FILE * fp = NULL;
    struct admin_infor w;
	time_t time_s;
	struct tm *time_sl;
	time_s=time(&time_s);
	time_sl=localtime(&time_s);
	system("cls");
	memset(w.name,0,sizeof(char)*20);
	if((fp=fopen("worker.txt","w+"))==NULL)
	{
		printf("\t\t\t\t保存失败，请重试！");
		exit(0) ;
	}
	printf("\n\n\n");
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃         管理员 姓名：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃                    \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	setPos(20,7);
	scanf("%s",w.name);
	w.year=time_sl->tm_year+1900;
	w.mon=time_sl->tm_mon+1;
	w.day=time_sl->tm_mday;
	fwrite(&w,sizeof(struct admin_infor),1,fp);

	
	while( p != NULL)
	{
		fwrite(p,sizeof(struct admin),1,fp);
		p = p->next;
	}
    	system("cls");
	fclose(fp);     
}



//从文件中读取数据，以初始化有头结点的链表
struct admin *Initial_list2()
{
	FILE *fp;
	struct admin *p = NULL;
	struct admin *list = NULL;
    struct admin_infor w;
	list=(struct admin *)malloc(sizeof(struct admin));
	memset(list,0,sizeof(struct admin));

	if((fp=fopen("worker.txt","r"))==NULL)
	{
		printf("open file failed!\n");
		return NULL;
	}
	  fread(&w,sizeof(struct admin_infor),1,fp);
	while(!feof(fp))
	{
		if((p = (struct admin *)malloc(sizeof(struct admin))) == NULL)
		{
			printf("\t\t\t\t内存不足，请释放内存之后重试！");	
			return NULL;
		}	
		memset(p,0,sizeof(struct admin));
		if(fread(p,sizeof(struct admin),1,fp)!=0)
		{
		
    	   p->next=list->next;
    	   list->next=p;
				
		}
	}
    
	fclose(fp);

	return list;
}

//添加图书
void add(struct admin *list,struct admin *node)
{
	struct admin *p=list;
	while(p->next!=NULL&&p->next->no<node->no)
		p=p->next;
	node->next=p->next;
	p->next=node;
}

//查询图书,按书名查询
void lookup1(struct admin *list,char *book)
{
	struct admin *p=list->next;
	if(p==NULL)
	{
		printf("现在还没有图书！\n");
	}
	while(p!=NULL)	
	{
		if(strcmp(p->book,book)==0)
		     break;
		   p=p->next;
	}
	if(p==NULL)
		printf("\n\n\t\t\t\t图书馆现在没有这本书！\n\n");
	else
	{   printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
		printf("\t\t\t☆☆编号:%d                              ☆☆\n",p->no);
		printf("\t\t\t☆☆书名:%s                              ☆☆\n",p->book);
		printf("\t\t\t☆☆作者:%s                              ☆☆\n",p->edname);
	    printf("\t\t\t☆☆分类号:%c                            ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
	}
	system("pause");
        
}


//查询图书,按作者名查询
void lookup2(struct admin *list,char *edname)
{
	struct admin *p=list->next;
	if(p==NULL)
		printf("现在还没有图书！\n");
	while(p!=NULL)	
	{
		if(strcmp(p->edname,edname)==0)
		{
        printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
		printf("\t\t\t☆☆编号:%d                              ☆☆\n",p->no);
		printf("\t\t\t☆☆书名:%s                              ☆☆\n",p->book);
		printf("\t\t\t☆☆作者:%s                              ☆☆\n",p->edname);
	    printf("\t\t\t☆☆分类号:%c                            ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
	//	break;
		}
		p=p->next;
	}
	/*if(p==NULL)
		printf("\n\n\t\t\t\t图书馆现在没有这本书！\n\n");*/
	system("pause");
        
	    
}

//查询图书,按出版单位查询
void lookup3(struct admin *list,char *pub)
{
	struct admin *p=list->next;
	if(p==NULL)
		printf("现在还没有图书！\n");
	while(p!=NULL)	
	{
		if(strcmp(p->pub,pub)==0)
		{
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
		printf("\t\t\t☆☆编号:%d                              ☆☆\n",p->no);
		printf("\t\t\t☆☆书名:%s                              ☆☆\n",p->book);
		printf("\t\t\t☆☆作者:%s                              ☆☆\n",p->edname);
	    printf("\t\t\t☆☆分类号:%c                           ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
		}
		p=p->next;
	}
	if(p==NULL)
		printf("\n\n\t\t\t\t图书馆现在没有这本书！\n\n");
	system("pause");
        
	    
}


//查询图书,按出版时间查询
void lookup4(struct admin *list,char *time)
{
	struct admin *p=list->next;
	if(p==NULL)
		printf("现在还没有图书！\n");
	while(p!=NULL)	
	{
		if(strcmp(p->time,time)==0)
		{
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
		printf("\t\t\t☆☆编号:%d                              ☆☆\n",p->no);
		printf("\t\t\t☆☆书名:%s                              ☆☆\n",p->book);
		printf("\t\t\t☆☆作者:%s                              ☆☆\n",p->edname);
	    printf("\t\t\t☆☆分类号:%c                            ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
		}
		p=p->next;
	}
	/*if(p==NULL)
		printf("\n\n\t\t\t\t图书馆现在没有这本书！\n\n");*/
	system("pause");
        
	     
}
void ask_for(struct admin *list)
{
	int i;
	char book_name[20];
	system("color BC");
	printf("\t\t\t ▁▁▁▁▁▁▁▁▁▁▁▁▁\n");
	printf("\t\t\t ▎ 1 按书名查询图书       ▎\n\n");
	printf("\t\t\t ▎ 2 按作者名名查询图书   ▎\n\n");
	printf("\t\t\t ▎ 3 按出版单位查询图书   ▎\n\n");
	printf("\t\t\t ▎ 4 按出版时间查询图书   ▎\n\n");
	printf("\t\t\t ▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n");
	printf("\t\t\t你可以选择如上功能：\n");
	scanf("%d",&i);
	system("cls");
	switch(i)
	{
	   case 1:setPos(5,10);printf("\t\t\t请输入图书：");fflush(stdin);gets(book_name);printf("\n\n");lookup1(list,book_name);break;
	   case 2:setPos(5,10);printf("\t\t\t请输入图书作者：");fflush(stdin);gets(book_name);printf("\n\n");lookup2(list,book_name);break;
	   case 3:setPos(5,10);printf("\t\t\t请输入出版单位：");fflush(stdin);gets(book_name);printf("\n\n");lookup3(list,book_name);break;
       case 4:setPos(5,10);printf("\t\t\t请输入出版时间：");fflush(stdin);gets(book_name);printf("\n\n");lookup4(list,book_name);break;
	   default:menu();break;
	}
}

//删除全部图书
void freeList1()
{
	FILE *fp;
	if((fp=fopen("worker.txt","w"))==NULL)
	{
		printf("open file failed!\n");
		exit(0);
	}
	fclose(fp);
	
}

//释放内存
void freelist(struct admin *list)
{
	struct admin *p=list->next;
	struct admin *temp=NULL;
	while(p!=NULL)
	{
		temp=p->next;
		free(p);
		p=temp;
	}
}
//浏览图书
void display(struct admin *list)
{
	struct admin *p=list->next;
	FILE *fp;
	system("color B5");
	struct admin_infor w;
	if((fp=fopen("worker.txt","r"))==NULL)
	{
		printf("open file failed!\n");
		exit(0);
	}
	setPos(1,0);
	fread(&w,sizeof(struct admin_infor),1,fp);
	printf("\n\n\n");
	printf("\t\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t\t┃         管理员 姓名：%s           \n",w.name );
	printf("\t\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\t\t\t┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t\t┃         日期：%d.%d.%d           \n",w.year,w.mon,w.day);
	printf("\t\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	if(p==NULL)
		printf("现在还没有图书！\n");
	while(p!=NULL)
	{
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
		printf("\t\t\t☆☆编号:%d                              ☆☆\n",p->no);
		printf("\t\t\t☆☆书名:%s                              ☆☆\n",p->book);
		printf("\t\t\t☆☆作者:%s                              ☆☆\n",p->edname);
	    printf("\t\t\t☆☆分类号:%c                            ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
		p=p->next;
	}
	system("pause");
}

//修改图书
struct admin * look(struct admin *list,char *edname)//查找要修改的图书
{
	struct admin *p=list->next;
	system("color E2");
	if(p==NULL)
		printf("\n\n\t\t\t\t现在还没有图书！\n");
	while(p!=NULL)	
	{
		if(strcmp(p->book,edname)==0)
		{printf("\n\n\t\t\t请查看原始数据：\n");
			printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
		   printf("\t\t\t☆☆编号:%d                              ☆☆\n",p->no);
	     	printf("\t\t\t☆☆书名:%s                              ☆☆\n",p->book);
		   printf("\t\t\t☆☆作者:%s                              ☆☆\n",p->edname);
	       printf("\t\t\t☆☆分类号:%c                            ☆☆\n",p->no1);
		   printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		   printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		   printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		   printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
		   return p;
		}
		p=p->next;
	}
	return NULL;
}

void mod(struct admin *head)
{
	struct admin *newnode=NULL,*list=head;
	char edname[30];
	printf("\n\n\nplease input 书名:\n");
	fflush(stdin);
    gets(edname);
	newnode=look(list,edname);
	if(newnode!=NULL)
	     getNode1(newnode);
	else
		printf("\t\t\t\t没有这本书\n\n");
}





//删除图书
void deleteNodeByNo2(struct admin *list,char *name)
{
	struct admin *p=list;
	struct admin *temp;	
    if(p->next==NULL)
		printf("\t\t\t\t现在还没有图书！\n");
	while(p->next!=NULL)
	{
		if(strcmp(p->next->book,name)==0)
		{
			temp=p->next;
			p->next=p->next->next;
			free(temp);
			printf("\t\t\t\t删除成功！\n");
			return ;
		}
		p=p->next;
	}
	printf("\t\t\t\t没有这个书，删除失败！\n");
}



//借阅信息查询
//将借阅信息写入文件
void brrowread(struct reader *p,struct admin *p_1,int year,int mon,int day)
{
	FILE *fp;
	struct brrow *p1=NULL;
	p1=(struct brrow *)malloc(sizeof(struct brrow ));
	memset(p1,0,sizeof(struct brrow ));
    if((fp=fopen("brrower.txt","a+"))==NULL)
	{
		printf("\t\t\t\t写入文件失败，请重试！");
		exit(0);
	}
	strcpy(p1->edname,p_1->book);
	strcpy(p1->name,p->name);
	strcpy(p1->writer,p_1->edname);
	p1->year=year;
	p1->day=day;
	p1->mon=mon;
	fwrite(p1,sizeof(struct brrow ),1,fp);
	fclose(fp);
}
//将借阅信息从文件中读出
struct brrow * brr()
{
	struct brrow *p=NULL,*head=NULL;
	FILE *fp;
	head=(struct brrow *)malloc(sizeof(struct brrow));
	memset(head,0,sizeof(struct brrow));
    if((fp=fopen("brrower.txt","r+"))==NULL)
	{
		printf("\t\t\t\t读出文件失败，请重试！");
		exit(0);
	}
	while(!feof(fp))
	{
		p=(struct brrow *)malloc(sizeof(struct brrow));
		memset(p,0,sizeof(struct brrow));
		if(fread(p,sizeof(struct brrow),1,fp)!=0)
		{
			p->next=head->next;
			head->next=p;
		}
		else
			free(p);
	}
	return head;
	fclose(fp);
}
//遍历所有借阅信息链表
//按图书查询
void look_up_1(struct brrow *list,char *book_name)
{
	struct brrow *p1=list->next;
	system("color E4");
		system("cls");
	if(p1==NULL)
		printf("现在还没有借阅信息！\n");
	while(p1!=NULL)
	{
		if(strcmp(p1->edname,book_name)==0)
		{
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
			printf("\t\t\t\t      读者：%s \n\n",p1->name);
			printf("\t\t\t\t      图书：%s \n\n",p1->edname);
			printf("\t\t\t\t      作者：%s \n\n",p1->writer);
			printf("\t\t\t\t      借阅时间：%d.%d.%d \n\n",p1->year,p1->mon,p1->day);
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n\n\n\n");
		}
		p1=p1->next;
	}
	system("pause");
}
//按作者查询
void look_up_2(struct brrow *list,char *book_name)
{
	struct brrow *p1=list->next;
		system("cls");
	if(p1==NULL)
		printf("现在还没有借阅信息！\n");
	while(p1!=NULL)
	{
		if(strcmp(p1->writer,book_name)==0)
		{
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
			printf("\t\t\t\t      读者：%s \n\n",p1->name);
			printf("\t\t\t\t      图书：%s \n\n",p1->edname);
			printf("\t\t\t\t      作者：%s \n\n",p1->writer);
			printf("\t\t\t\t      借阅时间：%d.%d.%d \n\n",p1->year,p1->mon,p1->day);
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n\n\n\n");
		}
		p1=p1->next;
	}
	system("pause");
}


//按读者查询
void look_up_3(struct brrow *list,char *book_name)
{
	struct brrow *p1=list->next;
	system("cls");
	if(p1==NULL)
		printf("\t\t\t\t现在还没有借阅信息！\n");
	while(p1!=NULL)
	{
		if(strcmp(p1->name,book_name)==0)
		{
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
			printf("\t\t\t\t      读者：%s \n\n",p1->name);
			printf("\t\t\t\t      图书：%s \n\n",p1->edname);
			printf("\t\t\t\t      作者：%s \n\n",p1->writer);
			printf("\t\t\t\t      借阅时间：%d.%d.%d \n\n",p1->year,p1->mon,p1->day);
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n\n\n\n");
		}
		p1=p1->next;
	}
	system("pause");
}	

//按时间查询
void look_up_4(struct brrow *list)
{
	struct brrow *p1=list->next;
	int year,mon,day,year1,mon1,day1;
	system("cls");
	printf("\n\n\n");
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        请输入起始时间(当前年份以内)：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        年：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	setPos(31,7);
	scanf("%d",&year);
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        月：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	setPos(31,9);
	scanf("%d",&mon);
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        日：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    setPos(31,11);
	scanf("%d",&day);
	system("cls");
	printf("\n\n\n");
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        请输入终止时间：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        年：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	setPos(31,7);
	scanf("%d",&year1);
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        月：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	setPos(31,9);
	scanf("%d",&mon1);
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        日：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    setPos(31,11);
	scanf("%d",&day1);
	system("cls");
	if(p1==NULL)
		printf("\t\t\t\t现在还没有借阅信息！\n");
	while(p1!=NULL)
	{
		if(p1->year>=year&&p1->year<=year1&&p1->mon>=mon&&p1->mon<=mon1&&p1->day>=day&&p1->day<=day1)
		{
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
			printf("\t\t\t\t      读者：%s \n\n",p1->name);
			printf("\t\t\t\t      图书：%s \n\n",p1->edname);
			printf("\t\t\t\t      作者：%s \n\n",p1->writer);
			printf("\t\t\t\t      借阅时间：%d.%d.%d \n\n",p1->year,p1->mon,p1->day);
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n\n\n\n");
		}
		p1=p1->next;
	}
	system("pause");
}	

//查询借阅信息
void brrower_menu()
{
	int i=0;
	char book_name[20];
	struct brrow *list;
	list=brr();
	printf("\n\n\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("\t\t\t\t\t▎ 1 按图书查询借阅信息   ▎\n\n");
	printf("\t\t\t\t\t▎ 2 按作者查询借阅信息   ▎\n\n");
	printf("\t\t\t\t\t▎ 3 按读者查询借阅信息   ▎\n\n");
	printf("\t\t\t\t\t▎ 4 按时间查询借阅信息   ▎\n\n");
	printf("\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	setPos(10,16);
	printf("请选择如上查询：");
	scanf("%d",&i);
	system("cls");
	switch(i)
	{
	   case 1:printf("\n\n\t\t\t请输入图书：\n");fflush(stdin);gets(book_name);look_up_1(list,book_name);break;
	   case 2:printf("\n\n\t\t\t请输入图书作者：\n");fflush(stdin);gets(book_name);look_up_2(list,book_name);break;
	   case 3:printf("\n\n\t\t\t请输入读者：\n");fflush(stdin);gets(book_name);look_up_3(list,book_name);break;
	   case 4:look_up_4(list);break;
	   default:menu();break;
	}
   	system("cls");
}

	
//还书信息查询
//将还书信息读入文件
void returnread(struct reader *p,struct admin *p_1)
{
	FILE *fp;
	struct giveback *p1=NULL;
	time_t end;
	struct tm *data;
	end=time(&end);
	p1=(struct giveback *)malloc(sizeof(struct giveback ));
	memset(p1,0,sizeof(struct giveback));
	data=localtime(&end);
    if((fp=fopen("book_back.txt","a+"))==NULL)
	{
		printf("\t\t\t\t写入文件失败，请重试！");
		exit(0);
	}
	strcpy(p1->name,p->name);
	strcpy(p1->edname,p_1->book);
	strcpy(p1->writer,p_1->edname);
	p1->year=data->tm_year+1900;
	p1->mon=data->tm_mon+1;
	p1->day=data->tm_mday;
	fwrite(p1,sizeof(struct giveback),1,fp);
	fclose(fp);
}
//将还书信息从文件中读出
struct giveback * back()
{
	struct giveback *p1=NULL,*head_1=NULL;
	FILE *fp;
	head_1=(struct giveback  *)malloc(sizeof(struct giveback));
	memset(head_1,0,sizeof(struct giveback ));
    if((fp=fopen("book_back.txt","r+"))==NULL)
	{
		printf("读出文件失败，请重试！");
		exit(0);
	}
	while(!feof(fp))
	{
		p1=(struct giveback  *)malloc(sizeof(struct giveback));
		memset(p1,0,sizeof(struct giveback ));
		if(fread(p1,sizeof(struct giveback),1,fp)!=0)
		{
			p1->next=head_1->next;
			head_1->next=p1;
		}
		else
			free(p1);
	}
	return head_1;
	fclose(fp);
}
//遍历所有还书信息链表
//按图书查询
void backlook_up1(struct giveback *list,char *book_name)
{
	struct giveback *p1=list->next;
		system("cls");
	if(p1==NULL)
		printf("\t\t\t\t现在还没有还书信息！\n");
	while(p1!=NULL)
	{
		if(strcmp(p1->edname,book_name)==0)
		{
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
			printf("\t\t\t\t      读者：%s \n\n",p1->name);
			printf("\t\t\t\t      图书：%s \n\n",p1->edname);
			printf("\t\t\t\t      作者：%s \n\n",p1->writer);
			printf("\t\t\t\t      还书时间：%d.%d.%d \n\n",p1->year,p1->mon,p1->day);
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n\n\n\n");
		}
		p1=p1->next;
	}
	system("pause");
}
//按作者查询
void backlook_up2(struct giveback *list,char *book_name)
{
	struct giveback *p1=list->next;
		system("cls");
	if(p1==NULL)
		printf("\t\t\t\t现在还没有还书信息！\n");
	while(p1!=NULL)
	{
		if(strcmp(p1->writer,book_name)==0)
		{
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
			printf("\t\t\t\t      读者：%s \n\n",p1->name);
			printf("\t\t\t\t      图书：%s \n\n",p1->edname);
			printf("\t\t\t\t      作者：%s \n\n",p1->writer);
			printf("\t\t\t\t      还书时间：%d.%d.%d \n\n",p1->year,p1->mon,p1->day);
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n\n\n\n");
		}
		p1=p1->next;
	}
	system("pause");
}
//按读者查询
void backlook_up3(struct giveback *list,char *book_name)
{
	struct giveback *p1=list->next;
		system("cls");
	if(p1==NULL)
		printf("\t\t\t\t现在还没有还书信息！\n");
	while(p1!=NULL)
	{
		if(strcmp(p1->name,book_name)==0)
		{
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
			printf("\t\t\t\t      读者：%s \n\n",p1->name);
			printf("\t\t\t\t      图书：%s \n\n",p1->edname);
			printf("\t\t\t\t      作者：%s \n\n",p1->writer);
			printf("\t\t\t\t      还书时间：%d.%d.%d \n\n",p1->year,p1->mon,p1->day);
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n\n\n\n");
		}
		p1=p1->next;
	}
	system("pause");
}	

//根据时间查询还书信息
void backlook_up_4(struct giveback *list)
{
	int year,mon,day,year1,mon1,day1;
	struct giveback *p1=list->next;
	system("cls");
	printf("\n\n\n");
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        请输入起始时间：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        年：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	setPos(31,7);
	scanf("%d",&year);
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        月：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	setPos(31,9);
	scanf("%d",&mon);
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        日：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    setPos(31,11);
	scanf("%d",&day);
	system("cls");
	printf("\n\n\n");
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        请输入终止时间：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        年：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	setPos(31,7);
	scanf("%d",&year1);
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        月：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	setPos(31,9);
	scanf("%d",&mon1);
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        日：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    setPos(31,11);
	scanf("%d",&day1);
	system("cls");
	if(p1==NULL)
		printf("\t\t\t\t现在还没有还书信息！\n");
	while(p1!=NULL)
	{
		if(p1->year>=year&&p1->year<=year1&&p1->mon>=mon&&p1->mon<=mon1&&p1->day>=day&&p1->day<=day1)
		{
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
			printf("\t\t\t\t      读者：%s \n\n",p1->name);
			printf("\t\t\t\t      图书：%s \n\n",p1->edname);
			printf("\t\t\t\t      作者：%s \n\n",p1->writer);
			printf("\t\t\t\t      还书时间：%d.%d.%d \n\n",p1->year,p1->mon,p1->day);
			printf("\t\t\t\t▽▽▽▽▽▽▽▽▽▽▽▽▽\n\n\n\n");
		}
		p1=p1->next;
	}
	system("pause");
}

//查询还书信息
void back_menu()
{
	int i=0;
	char book_name[20];
	struct giveback *list;
	list=back();
	printf("\n\n\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("\n\t\t\t\t\t▎ 1 按图书查询还书信息   ▎\n");
	printf("\n\t\t\t\t\t▎ 2 按作者查询还书信息   ▎\n");
	printf("\n\t\t\t\t\t▎ 3 按读者查询还书信息   ▎\n");
	printf("\n\t\t\t\t\t▎ 4 按时间查询还书信息   ▎\n");
	printf("\n\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	setPos(10,12);
	printf("请选择如上查询：");
	scanf("%d",&i);
	printf("\n");
	system("cls");
	switch(i)
	{
	   case 1:printf("\n\n\t\t\t\t请输入图书：");fflush(stdin);gets(book_name);backlook_up1(list,book_name);break;
	   case 2:printf("\n\n\t\t\t\t请输入图书作者：");fflush(stdin);gets(book_name);backlook_up2(list,book_name);break;
	   case 3:printf("\n\n\t\t\t\t请输入读者：");fflush(stdin);gets(book_name);backlook_up3(list,book_name);break;
	   case 4:backlook_up_4(list);break;
	   default:admincode(1);break;
	}
		system("cls");

}






/*                     管理员功能--读者信息管理        */
//创建链表并读入读者信息
/*struct reader *getNode2(char *name_1,char *num_1)
{
	struct reader *p1=NULL;
	p1=(struct reader *)malloc(sizeof(struct reader));
	memset(p1,0,sizeof(struct reader));
	p1->num=m;
	m++;
	strcpy(p1->num1,num_1);
	strcpy(p1->name,name_1);
	p1->max=5;
	p1->num2=book;
	strcpy(p1->code,cod);
	return p1;
}*/

//修改读者数据
void getNode3(struct reader *p1)
{
	printf("\n\n\n\t\t\t\t◇◇◇input new 编号：");
	scanf("%d",&p1->num);
	printf("\t\t\t\t◇◇◇input new 借阅号:");
	scanf("%s",p1->num1);
	printf("\t\t\t\t◇◇◇input new 姓名:");
	fflush(stdin);
	gets(p1->name);
	printf("\t\t\t\t◇◇◇input new 最大借阅额度:");
	scanf("%d",&p1->max);
	printf("\t\t\t\t◇◇◇input new 已借阅数量:");
	scanf("%d",&p1->num2);
	printf("\t\t\t\t◇◇◇input new 密码:");
	fflush(stdin);
	gets(p1->code);
}

struct reader * getNode4()
{
     struct reader *p1=NULL;
	p1=(struct reader *)malloc(sizeof(struct reader));
	memset(p1,0,sizeof(struct reader));
	printf("\n\n\n\t\t\t\t◇◇◇input  编号：");
	scanf("%d",&p1->num);
    printf("\t\t\t\t◇◇◇input  借阅号:");
	scanf("%s",p1->num1);
	printf("\t\t\t\t◇◇◇input  姓名:");
	fflush(stdin);
	gets(p1->name);
	printf("\t\t\t\t◇◇◇input  最大借阅额度:");
	scanf("%d",&p1->max);
	printf("\t\t\t\t◇◇◇input  已借阅数量:");
	scanf("%d",&p1->num2);
	printf("\t\t\t\t◇◇◇input  密码:");
	fflush(stdin);
	gets(p1->code);
	return p1;
}

//利用头插法创建有头结点的链表
//录入图书读者信息
struct reader * creat1(char *name_1,char *num_1)
{
	struct reader *p1=NULL;
	p1=(struct reader *)malloc(sizeof(struct reader));
	memset(p1,0,sizeof(struct reader));
	p1->num=m;
	m++;
	strcpy(p1->num1,num_1);
	strcpy(p1->name,name_1);
	p1->max=5;
	p1->num2=0;
	strcpy(p1->code,cod);
	return p1;
		
}

//将读者信息保存到文件
void Save1(struct reader *p1)
{
	 
	FILE * fp = NULL;

	if((fp=fopen("reader.txt","a+"))==NULL)
	{
		printf("\t\t\t\t写入文件失败，请重试！");
		return ;
	}
    fwrite(p1,sizeof(struct reader),1,fp);

	fclose(fp);     
}


//将所有读者信息保存进入文件
void Save2(struct reader *list)
{
	struct reader *p=list->next;
	FILE * fp = NULL;

	if((fp=fopen("reader.txt","w"))==NULL)
	{
		printf("\t\t\t\t写入文件失败，请重试！");
		return ;
	}
	while(p!=NULL)
	{
		//puts(p->name);
		//Sleep(100);
		fwrite(p,sizeof(struct reader),1,fp);
		p=p->next;
	}
	fclose(fp);
	//system("pause");
}


//添加读者
void add1(struct reader *list,struct reader *node)
{
	struct reader *p1=list;	

	while(p1->next!=NULL)
		p1=p1->next;
		
	node->next=p1->next;
	p1->next=node;
	printf("\t\t\t\t添加成功！\n");
	Sleep(1000);
}



//从文件中读取数据，以初始化有头结点的链表
struct reader *Initial_list()
{
	FILE *fp = NULL;
	struct reader *p1 = NULL;
	struct reader *list = NULL;

	list=(struct reader *)malloc(sizeof(struct reader));
	memset(list,0,sizeof(struct reader));

	if((fp=fopen("reader.txt","r+"))==NULL)
	{
		printf("open file failed!\n");
		return NULL;
	}

	while(!feof(fp))
	{
	     p1= (struct reader *)malloc(sizeof(struct reader));
		memset(p1,0,sizeof(struct reader));
		if(fread(p1,sizeof(struct reader),1,fp)!=0)
		{
		    p1->next=list->next;
			list->next=p1;
		}
	}
    
	fclose(fp);

	return list;
}

//删除全部读者信息
void delta_2()
{
	FILE *fp = NULL;
	if((fp=fopen("reader.txt","w+"))==NULL)
	{
		printf("open file failed!\n");
	    exit(0);
	}
		fclose(fp);
}






//浏览读者信息
void display1(struct reader *list)
{
	struct reader *p1=list->next;
	setPos(1,0);
	if(p1==NULL)
		printf("\t\t\t\t\t◇◇现在还没有读者信息！◇◇◇\n");
	while(p1!=NULL)
	{
		printf("\n\n\t\t\t\t◇◇◇◇编号：%-5d借阅号：%s\n\n",p1->num,p1->num1);
	    printf("\t\t\t\t◇◇◇◇姓名：%s\n\n",p1->name);
	    printf("\t\t\t\t◇◇◇◇最大借阅额度：%-5d已借阅数量：%-5d\n\n",p1->max,p1->num2);
		printf("\t\t\t\t◇◇◇◇密码：%s\n\n\n\n",p1->code);
		p1=p1->next;
	}
	system("pause");
}

//修改读者信息
struct reader  * visit(struct reader  *list,char *name)//查找要修改的读者
{
	struct reader *p1=list->next;
	if(p1==NULL)
	{
		printf("现在还没有读者信息！\n");
		return NULL;
	}
	while(p1!=NULL)	
	{
		if(strcmp(p1->num1,name)==0)
		{
			printf("\n\n\n\t\t\t\t请查看之前的读者信息：\n");
			printf("\t\t\t\t◇◇◇◇编号：%-5d借阅号：%s\n\n",p1->num,p1->num1);
	        printf("\t\t\t\t◇◇◇◇姓名：%s\n\n",p1->name);
	        printf("\t\t\t\t◇◇◇◇最大借阅额度：%-5d已借阅数量：%-5d\n\n",p1->max,p1->num2);
		    printf("\t\t\t\t◇◇◇◇密码：%s\n\n\n\n",p1->code);
			return p1;
		}
		p1=p1->next;
	}
	if(p1==NULL)
		printf("\t\t\t\t没有这个读者\n\n");
	return NULL;
	
}

void mod1(struct reader *head)
{
	struct reader *newnode=NULL,*list=head;
	FILE *fp;
	struct zhang *p;
	char name[30];
	if((fp=fopen("账号.txt","a+"))==NULL)
	{
		printf("can't open this file!\n");
		exit(0);
	}
	printf("\n\n\t\t\t\tplease input 读者学号:\n");
	fflush(stdin);
    gets(name);
	printf("\n");
	system("cls");
	newnode=visit(list,name);
	if(newnode!=NULL)
	{
		system("pause");
	    system("cls");
    	getNode3(newnode);
	    p = (struct zhang *)malloc(sizeof(struct zhang));
	    memset(p,0,sizeof(struct zhang));
	    strcpy(p->code,newnode->code);
	    strcpy(p->zh,newnode->num1);
	    fwrite(p,sizeof(struct zhang),1,fp);
	}
	fclose(fp);
}





//删除读者信息
void deleteNodeByNo(struct reader  *list,char *name)
{
	struct reader  *p=list;
	struct reader  *temp;
	if(p==NULL)
		printf("\n\n\n\t\t\t现在还没有读者信息！\n");

	while(p->next!=NULL)
	{
		if(strcmp(p->next->num1,name)==0)
		{
			temp=p->next;
			p->next=p->next->next;
			free(temp);
			printf("\n\n\n\t\t\t删除成功！\n");
			system("pause");
			return ;
		}
		p=p->next;
	}
	printf("\n\n\n\t\t\t没有这个读者，删除失败！\n");
	system("pause");
}




//读者登录页面信息
void d_f()
{
	char nam[20],num[20];
	struct reader *list=NULL;
	system("color 74");
	memset(nam,0,sizeof(char)*20);
	memset(num,0,sizeof(char)*20);
	printf("\n\n\t\t\t\t◎◎◎◎请输入你的姓名：");
	fflush(stdin);
	gets(nam);
	printf("\n\n\t\t\t\t◎◎◎◎请输入你的借阅号（学号）：");
	fflush(stdin);
	gets(num);
	system("cls");
	choice_read(nam,num);
		system("pause");
   
}
	

//读者--查询图书
void find()
{
	struct admin *loo=NULL;
	char boo[100];
	loo=Initial_list2();
	system("color B5");
	printf("\n\n\n\n\t\t\t\t◎◎请输入你要查询的图书:");
	fflush(stdin);
	gets(boo);
	lookup1(loo,boo);
}

//根据借阅号查询
struct reader * look_1(struct reader *list,char *index)
{
	struct reader *p=list->next;
	while(p!=NULL)	
	{
		if(strcmp(p->num1,index)==0)
		    return  p;
		p=p->next;
	}
	return NULL;
}

void find_1(struct reader *p1)
{
	//struct reader *list=NULL,*p;
	//list=Initial_list();
//	p=look_1(list,zh);
	//p=creat1(nam,num);
	system("color BD");
	printf("\n\n\t\t\t\t◎◎姓名 ：%s                                ◎◎\n",p1->name);
	printf("\n\n\t\t\t\t◎◎最大借阅额度：%d           已借阅数量：%d◎◎\n",p1->max,p1->num2);
	system("pause");
}
	

//读者--借阅图书
void borrow(struct reader *p)
{
	//struct reader *p;//,*br=NULL;
	struct admin *list=NULL,*p_1=NULL;
	int k,i,h,year,mon=0,flag=0;
	time_t time_s;
	struct tm *time_sl;
	time_s=time(&time_s);
	time_sl=localtime(&time_s);
	book=0;
	//br=Initial_list();
	list=Initial_list2();
	//p=creat1(nam,num);
	p_1=list->next;
	/*while(p!=NULL)
	{
	    if(strcmp(p->num1,zh)==0)
			break;
		p=p->next;
	}*/
	system("color E9");
	if(p->max>p->num2)
	{
		printf("\n\n\n\t\t\t\t\t◎◎你还能借阅%d本书◎◎\n\n",(p->max)-(p->num2));
		printf("\t\t\t\t\t◎◎请输入你要借阅几本书：");
		//setPos(15,4);
	    scanf("%d",&h);
		for(k=0;k<h;k++)
		{
	     	system("cls");
			printf("\n\n\n\t\t\t\t\t◎◎请输入你要借阅的图书编号：");
			setPos(35,4);
			scanf("%d",&i);
		    while(p_1!=NULL)
			{
	           if(p_1->no==i)
			      break;
		       p_1=p_1->next;
			}
			if(p_1!=NULL)
			{
			  p_1->num=p_1->num-1;//修改图书库存
			  p->num2+=h;//修改读者已借阅数量
			   brrowread(p,p_1,time_sl->tm_year+1900,time_sl->tm_mon+1,time_sl->tm_mday);//向借阅表上添加新的内容
			   printf("\n\n\n\t\t\t\t\t◎◎借阅成功！◎◎\n");
			   Sleep(1000);
			   //Save1(p);
			   flag=1;//做标记，如果借阅成功输出借阅时间
			}
			else
				printf("\t\t\t\t\t很抱歉，现在图书馆没有这本书\n\n\n");
		}
	
	if((time_sl->tm_mon+1)==12)
	{
		year=(time_sl->tm_year)+1900+1;
		mon=1;
	}
	else
	{
		year=time_sl->tm_year+1900;
		mon=time_sl->tm_mon+2;
	}
	if(flag)
	{
		printf("\n\n\t\t\t\t\t========================================\n");
	    printf("\t\t\t\t\t 借阅时间：%d.%d.%d | 还书时间：%d.%d.%d\n",(time_sl->tm_year+1900),time_sl->tm_mon+1,time_sl->tm_mday,year,mon,time_sl->tm_mday);
    	printf("\t\t\t\t\t========================================\n\n\n");
	}
	}
	else
		printf("\t\t\t\t\t◎◎很抱歉你已到借阅数量上限!◎◎\n");
	system("pause");
}


//修改借阅信息--更新
void brrowrite_1(struct brrow *list)
{
	FILE *fp;
	struct brrow *p=list->next;
    if((fp=fopen("brrower.txt","w+"))==NULL)
	{
		printf("\t\t\t\t写入文件失败，请重试！");
		exit(0);
	}
	while(p!=NULL)
	{
		fwrite(p,sizeof(struct brrow),1,fp);
		p=p->next;
	}
	fclose(fp);
}


//计算还书时间的金额问题
void money(int year,int mon,int day)
{
  time_t time_s;
  struct tm *time_sl;
  time_s=time(&time_s);
  time_sl=localtime(&time_s);//还书时间
  int n;
  int add_1=0,add_2=0;
  int count[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  for(n=0;n<mon-1;n++)
		add_1+=count[n];
	add_1+=day;//加上天数
	for(n=0;n<time_sl->tm_mon;n++)
		add_2+=count[n];
	add_2+=(time_sl->tm_mday);//加上天数
	add_2-=add_1;//总天数相减
	int day1=0;
	for(n=year;n<(time_sl->tm_year+1900);n++)
	{
		if(n%400==0||(n%100!=0)&&(n%4==0))
			add_2++;
		day1++;//计算两者之间闰年的天数
	}
	add_2+=365*day1;//两者相差天数
	if(abs(add_2)>30)
    {
	printf("\n\n\n");
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃        请偿还金额：           \n" );
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃       %.2f元           \n",abs(add_2)*0.1);
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃       请刷卡           \n");
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	Sleep(2000);
	printf("\t\t ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t ┃      支付成功!（*@ο@*）           \n");
	printf("\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	Sleep(1000);
	}
}


//还书功能
void  return_book(struct reader *p1)
{
	struct brrow *list=NULL,*p=NULL,*p_2=NULL;
	struct admin *p_1=NULL,*list1=NULL;
	int book1,k=0;
	char book_name[20];
    list=brr();//从借阅文件中读出信息
	list1=Initial_list2();//从图书文件中读出信息
	p=list->next;
	p_1=list1->next;
	while(p!=NULL)
	{
	      if(strcmp(p->name,p1->name)==0)
		  {
			  printf("\n\n\t\t\t\t◎待归还书籍：%s\n\n",p->edname);
			  k=1;
		  }
		   p=p->next;
	}//在借阅表上查询
	if(k!=1)
		printf("\n\n\t\t\t\t现在还没有可归还的书籍！\n");
	else
	{
		printf("\n\n\n\t\t\t\t◎◎◎◎请输入你要归还的图书数量：\n");
	scanf("%d",&book1);
	if(book1<0||book1>=5)
		main();
	p1->num2=(p1->num2)-book1;//修改读者已借阅数量
    for(k=0;k<book1;k++)
	{
	     	system("cls");
			p=list;//重新还回头结点
			printf("\n\n\t\t\t\t◎◎◎◎请输入第%d本归还的书名：\n",k+1);
			setPos(29,4);
		    scanf("%s",book_name);
			while(p->next!=NULL)
			{
	            if(strcmp(p->next->edname,book_name)==0)
				{
					money(p->next->year,p->next->mon,p->next->day);//计算需要还的金额
					returnread(p1,p_1);//向还书表中添加新的内容
			        printf("\t\t\t\t◎◎还书成功！◎◎\n");
				   //Save1(p1);
				   Sleep(1000);
					p_2=p->next;
				    p->next=p->next->next;//从借阅表上删除内容
				    free(p_2);
				}
				else
		            p=p->next;
				
			}//在借阅表上查询,并删除借阅信息
			while(p_1!=NULL)
			{
				if(strcmp(p_1->book,book_name)==0)
			      break;
		        p_1=p_1->next;
			}
			if(p_1!=NULL)
			{
			    
			    p_1->num=p_1->num+1;//修改图书库存
			}
			printf("\n\n");
	}
	brrowrite_1(list);
	}
	system("pause");
	
}

//修改密码--管理员
void revise_code1()
{
	char code_1[13];
	FILE *fp;
	int i=0;
	//struct reader *p=list;
	struct zhang *p1;
	memset(code_1,0,sizeof(char));
	if((fp=fopen("管理员账号.txt","a+"))==NULL)
	{
		printf("Can't open this file!\n");
		exit(0);
	}
	while(1)
	{
		printf("\n\n\n\t\t\t\t◎◎◎◎请输入你之前的密码:");
	    scanf("%s",code_1);
    	if(strcmp(code_1,cod)==0)
		{
			printf("\n\t\t\t\t◎◎◎◎输入你的新密码：");
			while(!(isspace(code[i]=getch())))
			 {
			      printf("*");
	              i++;
			 }
	 	code[i]='\0';
		printf("\n\n"); 
		printf("\n\t\t\t\t◎◎◎◎请再次输入你的新密码：");
		i=0;
	  while(!(isspace(cod[i]=getch())))
		{
			printf("*");
	        i++;
		}
	  	cod[i]='\0';
	    if(strcmp(code,cod)==0)
		   {
		        printf("\n\t\t\t\t◎◎修改密码成功！◎◎\n");
		        break;
		   }
	       else
		   {
			   printf("\n\t\t\t\t◎◎新密码前后不一致，请重新输入！◎◎\n");
			   continue;
		   }
		}
	}
	p1=(struct zhang *)malloc(sizeof(struct zhang));
	memset(p1,0,sizeof(struct zhang));
	strcpy(p1->zh,zh);
	strcpy(p1->code,code);
	fwrite(p1,sizeof(struct zhang),1,fp);
	fclose(fp);
}




//修改密码
void revise_code(struct reader *list)
{
	char code_1[13];
	FILE *fp;
	int i=0,fl=0;
	struct reader *p=list;
	struct zhang *p1;
	memset(code_1,0,sizeof(char));
	if((fp=fopen("账号.txt","a+"))==NULL)
	{
		printf("Can't open this file!\n");
		exit(0);
	}
	while(1)
	{
		printf("\n\n\n\t\t\t\t◎◎◎◎请输入你之前的密码:");
	    scanf("%s",code_1);
    	if(strcmp(code_1,cod)==0)
		{
			printf("\n\t\t\t\t◎◎◎◎输入你的新密码：");
			 while(!(isspace(cod[i]=getch())))
			 {
			      printf("*");
				  if(cod[i]==8)
				  {
					  printf("\n\n\n\t\t\t\t◎◎◎◎请输入你之前的密码:%s",code_1);
					  	printf("\n\t\t\t\t◎◎◎◎输入你的新密码：");
						for(fl=0;fl<i-1;fl++)
							printf("*");
						i--;
				  }

	            else
	              i++;
			 }
	 	cod[i]='\0';
		printf("\n\n"); 
		printf("\n\t\t\t\t◎◎◎◎请再次输入你的新密码：");
		i=0;
	  while(!(isspace(code[i]=getch())))
		{
			printf("*");
			if(cod[i]==8)
			{
			printf("\n\n\n\t\t\t\t◎◎◎◎请输入你之前的密码:%s",code_1);
			printf("\n\t\t\t\t◎◎◎◎输入你的新密码：");
				for(fl=0;fl<i;fl++)
					printf("*");
			printf("\n\t\t\t\t◎◎◎◎请再次输入你的新密码：");
				for(fl=0;fl<i-1;fl++)
					printf("*");
				i--;
			}
			else
	          i++;
		}
	  	code[i]='\0';
	       if(strcmp(code,cod)==0)
		   {
		        printf("\n\t\t\t\t◎◎修改密码成功！◎◎\n");
		        break;
		   }
	       else
		   {
			   printf("\n\t\t\t\t◎◎新密码前后不一致，请重新输入！◎◎\n");
			   continue;
		   }
		}
	}
	p1=(struct zhang *)malloc(sizeof(struct zhang));
	memset(p1,0,sizeof(struct zhang));
	strcpy(p1->zh,zh);
	strcpy(p1->code,code);
	fwrite(p1,sizeof(struct zhang),1,fp);

	while(p->next!=NULL)
	{
		if(strcpy(p->next->num1,zh)==0)
		{
			 strcpy(p->next->code,cod);
			 break;
		}
		p=p->next;
	}
	fclose(fp);
}



//读者页面
void reader()
{
	printf("\n\n\n\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t\t\t\t▎1 借书功能              ▎\n\n\n");
	printf("\t\t\t\t\t▎2 还书功能              ▎\n\n\n");
	printf("\t\t\t\t\t▎3 查询图书              ▎\n\n\n");
	printf("\t\t\t\t\t▎4 修改密码              ▎\n\n\n");
	printf("\t\t\t\t\t▎5 查询自己的相关信息    ▎\n\n\n");
	printf("\t\t\t\t\t▎0 退出程序              ▎\n\n\n");
	printf("\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇\n\n");
	printf("\t\t\t请选择：\n");

}

//释放读者链表内存
void freelist2(struct reader *list)
{
	struct reader *p=list->next,*p1;
	while(p!=NULL)
	{
		p1=p->next;
		free(p);
		p=p1;
	}
}

//选择模块
void choice_read(char *nam,char *num)
{
	int choice,i=0;
	struct reader *p1=NULL,*list=NULL;
	list=Initial_list();
    p1=list->next;
	while(p1!=NULL)
	{
		if(strcmp(p1->num1,num)==0)//查找是否有这个读者
		{//puts(p1->num1);
		break;}
		p1=p1->next;
	}
	if(p1==NULL)
	{
		i=1;//做标记
		p1=creat1(nam,num);//如果读者表上没有该读者就添加
	}
	while(1)
	{
	reader();
	setPos(20,25);
	scanf("%d",&choice);
	system("cls");
	switch(choice)
	{
	  case 1:borrow(p1);break;
	  case 2:return_book(p1);break;
	  case 3:find();break;
	  case 4:revise_code(p1);break;
	  case 5:find_1(p1);break;
	  default:break;//保存文件并退出
		 
	}
	if(choice==0)
	{
	   if(i==1)
	      Save1(p1);//如果没有这个读者就保存
        else
		{
			Save2(list);//如果有，就更新数据
	       freelist2(list);//释放内存
		}
	    main();
		break;
	}
		system("cls");

	
	
	}
		system("pause");

}

//管理员页面--图书
void menueadmin1()
{
	
	printf("\n\n\n\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("\t\t\t\t▎1 删除图书             ▎\n\n");
	printf("\t\t\t\t▎2 添加图书             ▎\n\n");
	printf("\t\t\t\t▎3 查询图书             ▎\n\n");
	printf("\t\t\t\t▎4 浏览图书             ▎\n\n");
	printf("\t\t\t\t▎5 修改图书             ▎\n\n");
	printf("\t\t\t\t▎6 借阅信息查询         ▎\n\n");
	printf("\t\t\t\t▎7 还书信息查询         ▎\n\n");
	printf("\t\t\t\t▎8 删除全部图书         ▎\n\n");
	printf("\t\t\t\t▎9 修改密码             ▎\n\n");
	printf("\t\t\t\t▎0 退出程序             ▎\n\n");
	printf("\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("请选择功能：\n");
}
//管理员页面--读者
void menueadmin2()
{
	printf("\n\n\n\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("\t\t\t\t\t▎1 删除读者信息                ▎\n\n");
	printf("\t\t\t\t\t▎2 添加读者信息                ▎\n\n");
	printf("\t\t\t\t\t▎3 浏览读者信息                ▎\n\n");
	printf("\t\t\t\t\t▎4 修改读者信息(可重置密码)    ▎\n\n");
	printf("\t\t\t\t\t▎5 删除全部读者信息            ▎\n\n");
	printf("\t\t\t\t\t▎6 修改密码                    ▎\n\n");
	printf("\t\t\t\t\t▎0 退出程序                    ▎\n\n");
	printf("\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("请选择功能：\n");
}




//管理员--图书的程序，进入不同的程序
void listWithHead()
{
	int option,i,k;
	char name[20];
    struct admin *node=NULL;
	struct admin *list=NULL;
  /*if(flag==0)
	{
		list=creat();
		Save(list);
		flag++;
	}*/
	
	while(1)
	{    
		list=Initial_list2();//从文件中读出图书信息
	    menueadmin1();
		scanf("%d",&option);
		system("cls");
		switch(option)
		{
		 case 1:
			 
			printf("\n\n\t\t\t\t\t请输入你要删除图书的数量：\n");
			setPos(40,3);
			scanf("%d",&i);
			system("cls");
			for(k=0;k<i;k++)
			{
		    	printf("\n\t\t\t\t\t请输入你要删除的书名：\n");
		    	fflush(stdin);
			   gets(name);
			   deleteNodeByNo2(list,name);
			}
			break;
		case 2:
			printf("\n\n\t\t\t\t\t请输入你要添加图书的数量：\n");
			setPos(40,3);
			scanf("%d",&i);
			system("cls");
			for(k=0;k<i;k++)
			{
		    	node=getNode();
			   add(list,node);
			}
			break;
		case 3:
			ask_for(list);
			break;
		case 4:
			display(list);
			break;
		case 5:
			printf("\n\n\t\t\t\t\t请输入你要修改图书的数量：\n");
			setPos(40,3);
			scanf("%d",&i);
			system("cls");
			for(k=0;k<i;k++)
			   mod(list);
			break;
		case 6:
			brrower_menu();
			break;
	    case 7:
		    back_menu();
			break;
		case 8:
		    freeList1();
			break;
		case 9:
			revise_code1();
			break;
		default:freelist(list);ch();
			break;

		}
		system("cls");
		Save(list);//保存到文件
	}
		//system("pause");
}


//管理员--读者的程序，进入不同的程序
void listWithHead1()
{

    char name[30];
	int option,k,i;
    struct reader *node;
	struct reader *list=NULL;
	while(1)
	{
		list=Initial_list();//从文件读出读者信息
		if(list->next==NULL)
		{
			printf("\n\n\n\t\t\t现在还没有读者！\n");
			Sleep(1000);
			system("cls");
			i=0;
		
		}
    	menueadmin2();
		scanf("%d",&option);
		system("cls");
		switch(option)
		{
		case 1:
			 
			 printf("\n\n\t\t\t\t\t请输入你要删除读者的数量：\n");
			 setPos(40,3);
			scanf("%d",&i);
			system("cls");
			for(k=0;k<i;k++)
			{
				
				printf("\n\n\t\t\t\t\t请输入第%d个读者的借阅号：\n",k+1);
			//	setPos(2,9);
		    	fflush(stdin);
			    gets(name);
			    deleteNodeByNo(list,name);
			}
			break;
		case 2:
			
			printf("\n\n\t\t\t\t\t请输入你要添加读者的数量：\n");
			setPos(40,3);
			scanf("%d",&i);
				system("cls");
			for(k=0;k<i;k++)
			{
			    node=getNode4();
			    add1(list,node);
			}
			break;
		case 3:
		     display1(list);
			break;
		case 4:
			
			 printf("\n\n\t\t\t\t\t请输入你要修改读者的数量：\n");
			 setPos(40,3);
			scanf("%d",&i);
			system("cls");
			for(k=0;k<i;k++)
		    	mod1(list);
			break;
		case 5:
			 freelist2(list);
			break;
		case 6:
			revise_code(list);
			break;
		default: freelist2(list);
			     ch();
			     break;
		
		}
		Save2(list);//将读者保存到文件
		system("cls");
	}
}

//选择模块--管理员
void ch()
{
	int choice;
	printf("\n\n\n\n\t\t\t\t\t▲▲▲▲▲▲▲▲▲▲▲▲▲\n");
    printf("\t\t\t\t\t▎     ①   图书信息管理 ▎\n");
	printf("\t\t\t\t\t▎     ②   读者信息管理 ▎\n");
	printf("\t\t\t\t\t▲▲▲▲▲▲▲▲▲▲▲▲▲\n");
	printf("\n\n\n\t\t\t\t\t请选择：");
	setPos(37,25);
	scanf("%d",&choice);
	system("cls");
	switch(choice)
	{
	     case 1:listWithHead();break;
       	case 2:listWithHead1();break;
		default:main();break;
	}
		system("pause");
}

//寻找目标账号
struct zhang *find_6(struct zhang *list)
{
    struct zhang *p=list->next;
	while(p!=NULL)
	{
		if(strcmp(p->zh,zh)==0&&strcmp(p->code,cod)==0)
		{
				return p;
		}
			p=p->next;
	}
	return NULL;
}

//读出账号--读者
struct zhang *  read_zhang()
{
	//	char zhanghao[13];
	struct zhang *p;
    //int i,r;
	struct zhang *list=NULL;
	FILE *fp;
	list = (struct zhang *)malloc(sizeof(struct zhang));
	memset(list,0,sizeof(struct zhang));
	if((fp=fopen("账号.txt","r"))==NULL)
	{
		printf("open file failed!\n");
		exit(0);
	}
	while(!feof(fp))
	{
		p = (struct zhang *)malloc(sizeof(struct zhang));
		memset(p,0,sizeof(struct zhang));
		if(fread(p,sizeof(struct zhang),1,fp)!=0)
		{
    	   p->next=list->next;
    	   list->next=p;
				
		}
		else
			free(p);
	} 
	fclose(fp);
	return list;
	
}

//读出账号--管理员
struct zhang *  read_zhang_1()
{
	//	char zhanghao[13];
	struct zhang *p;
	int i=0;
    //int i,r;
	struct zhang *list=NULL;
	FILE *fp;
	list = (struct zhang *)malloc(sizeof(struct zhang));
	memset(list,0,sizeof(struct zhang));
	if((fp=fopen("管理员账号.txt","r"))==NULL)
	{
		printf("open file failed!\n");
		exit(0);
	}

	while(!feof(fp))
	{
		p = (struct zhang *)malloc(sizeof(struct zhang));
		memset(p,0,sizeof(struct zhang));
		if(fread(p,sizeof(struct zhang),1,fp)!=0)
		{
    	   p->next=list->next;
    	   list->next=p;
				
		}
		else
			free(p);
	} 
	fclose(fp);
    return list;
	
}


//登录页面
void admincode(int m2)
{

    int i,r,fl=0;
    struct zhang *list=NULL,*p=NULL;
	memset(zh,0,sizeof(char)*13);
	if(!m2)
	    list=read_zhang();
	else
		list=read_zhang_1();
	while(1)
	{
		
		printf("\n\n\n\t\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆登录☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n");
		printf("\t\t\t\t┏                                                          ┓\n");
		setPos(0,8);
		if(fl==1)//删除密码操作
		{
			printf("\n\t\t\t\t\t           账号:%s",zh);
			 setPos(0,11);
			printf("\n\n\t\t\t\t\t           密码:");
			for(fl=0;fl<i-1;fl++)
			   printf("*");
			fl=0;
	
			i--;
		
		}
		else
	       {
			   i=0;
			   printf("\n\t\t\t\t\t           账号:");
	           scanf("%s",zh);
               setPos(0,11);
	           printf("\n\n\t\t\t\t\t           密码:");
		       fflush(stdin);
		       memset(cod,0,sizeof(char)*13);
		}
	    while(!(isspace(cod[i]=getch())))
		{
			printf("*");
			if(cod[i]==8)
				break;
	        i++;
		}
		if(cod[i]==8)
		{
			system("cls");
			cod[i]='\0';
			fl=1;
			continue;
		}
		cod[i]='\0';
		printf("\n\n\t\t\t\t┗                                                           ┛\n");
		p=find_6(list);
		if(p!=NULL)
		{
			    printf("                            ★★★登录成功！★★★\n");
		        system("cls");
		        menu();
		        break;
		}
	   else
	   {
		 system("cls");
		 r++;
		 printf("\n\n\t\t\t\t★★★账号或者密码错误！★★★\n");
		 if(!m2)
		 {
			 printf("\n\n\t\t\t\t★★是否已经注册？\n\n");
		    printf("\t\t\t\t<1> 是\t<2> 否\n");
	        printf("\t\t\t\t请选择：");
	       scanf("%d",&i);
		 
		 //system("pause");
     	 system("cls");
         if(i==2)
		 {
			 denji();//没有注册
			 system("cls");
			 break;
		 }
		 }
		 if(r==5)
		 {
			 printf("\t\t\t\t请15秒后重新登录！\n\n");
			 Sleep(15000);
		 }
		 
	   }
	 
	}
//	fclose(fp);
}

//注册页面
void denji()
{
	int i=0,fl=0,j=0;
	FILE *fp;
	struct zhang *p;
    if((fp=fopen("账号.txt","a+"))==NULL)
	{
		printf("open file failed!\n");
		exit(0);
	}
	while(1)
	{
		printf("\n\n\n\n\n\t\t\t\t    ☆☆☆☆☆☆☆☆☆☆☆☆☆☆注册☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	    printf("\t\t\t\t\t┏                                                          ┓\n");
		fflush(stdin);
		if(fl==1)//删除密码操作
		{
			printf("\n\t\t\t\t\t           账号:%s",zh);
			 setPos(0,11);
			printf("\n\n\t\t\t\t\t           密码:");
			for(fl=0;fl<i-1;fl++)
			   printf("*");
		    fl=0;
	        i--;
		}
		else
		{
		memset(zh,0,sizeof(char)*13);
		printf("\t\t\t\t\t\t\t    账号:");
		gets(zh);
		i=0;
		printf("\n\n\t\t\t\t\t\t\t    密码:");
		memset(code,0,sizeof(char)*13);
		}
	 while(!(isspace(code[i]=getch())))
		{
		  if(code[i]==8)//读到删除键就退出循环
			 break;
			printf("*");
	        i++;
		}
	    if(code[i]==8)//读到删除键继续
		{
			fl=1;
			system("cls");
			cod[i]='\0';
			continue;
		}
		
	 	code[i]='\0';
	    printf("\n\n");
	    j=0;
	    printf("\t\t\t\t\t\t\t    再次输入你的密码:");
	    fflush(stdin);
		memset(cod,0,sizeof(char)*13);
	  while(!(isspace(cod[j]=getch())))
		{
		    printf("*");
		  if(cod[j]==8)
		  {
			  system("cls");
			  	printf("\n\n\n\n\n\t\t\t\t    ☆☆☆☆☆☆☆☆☆☆☆☆☆☆注册☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	            printf("\t\t\t\t\t┏                                                          ┓\n");
		        fflush(stdin);
			    printf("\n\t\t\t\t\t           账号:%s",zh);
			    setPos(0,11);
		    	printf("\n\n\t\t\t\t\t         密码:");
		    	for(fl=0;fl<i;fl++)
			         printf("*");
			 printf("\n\n\t\t\t\t\t\t\t       再次输入你的密码:");
			 for(fl=0;fl<j-1;fl++)
			    printf("*");
		      j--;
		  }
			  
		else
	        j++;
		}
	 
	  	cod[j]='\0';
	   printf("\t\t\t\t\t┗                                                               ┛\n");
	    if(strcmp(code,cod)==0)
		{	
			p = (struct zhang *)malloc(sizeof(struct zhang));
		     memset(p,0,sizeof(struct zhang));
			 strcpy(p->code,cod);
			 strcpy(p->zh,zh);
			 fwrite(p,sizeof(struct zhang),1,fp);
			fclose(fp);
			printf("\t\t\t\t\t\t★★★注册成功★★★\n\n");
	        printf("\t\t\t\t\t\t★★★请登录  ★★★ \n\n");
			system("cls");
		
			admincode(0);
			break;
		}
		
		else
		{
			system("cls");
			printf("\t\t\t\t\t\t★★★密码不一致!重新注册★★★\n\n");
		}
		
	} 
	
}

//主菜单
void menu()
{
    system("color BC");
	printf("\n\n\n\n\n\t\t\t\t□□□□□□□□□█□█□█□█□█□█□█□█□□□□□□□□\n\n");
	printf("\t\t\t\t           欢迎进入重庆理工大学图书管理系统\n\n");
	printf("\t\t\t\t□□□□□□□□□█□█□█□█□█□█□█□█□□□□□□□□\n");
	switch(choice)
	{
	case 1:ch();break;
	case 2:d_f();break;
    default:main();break;
	}
	system("pause");

}


//光标函数
static void setPos(int x,int y)
{

COORD point = {x,y};//光标要设置的位置x,y
HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
SetConsoleCursorPosition(HOutput, point);//设置光标位置
}

void tshi()
{
	printf("\n\n\n\n\t\t\t\t ___________________________________________________________________\n");
	printf("\t\t\t\t|    温馨提示：在操作过程中按0退出程序,输入正确的数字进入相应程序   |\n");
	printf("\t\t\t\t|               注册账号为学号或者工号,管理员账号和初识密码已定     |\n");
	printf("\t\t\t\t|___________________________________________________________________|\n\n");
	printf("\n\n\n\n\t\t\t\t\t\t-------指导老师：曹琼");
}




void main()
{
     int i;
    system("color B6");	
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
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t▲▲▲▲▲▲▲▲▲▲▲▲▲\n");
    printf("\t\t\t\t\t▎     ①  管理员        ▎\n");
	printf("\t\t\t\t\t▎     ②  读者          ▎\n");
	printf("\t\t\t\t\t▲▲▲▲▲▲▲▲▲▲▲▲▲\n");
	printf("\n\n\n\t\t\t请选择你的身份：");
	setPos(49,12);
	scanf("%d",&choice);
	if(choice!=1)
	{
	system("cls");
	system("color B1");
     printf("\n\n\t\t\t\t是否已经注册？\n\n");
	printf("\t\t\t\t<1> 是\t<2> 否\n");
	printf("\t\t\t\t请选择：");
	scanf("%d",&i);
	system("cls");
     if(i==2)
		 denji();
	 else
         admincode(0);
	}
	else
	{   system("cls");
		admincode(1);
	}
	
system("pause");
	
}







