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
//图书信息管理
struct admin
{
	int no;//图书编号
	char book[30];//书名
	char edname[20];//作者名
	int no1;//分类号
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


/*       管理员功能--图书信息管理     */
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
void admincode();//登录页面
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
void admincode();//登录页面
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
	printf("\t\t\t ☆☆tinput no:");
	scanf("%d",&p->no);
	printf("\t\t\t ☆☆input bookname:");
	fflush(stdin);
	gets(p->book);
	printf("\t\t\t ☆☆input edname:");
	fflush(stdin);
	gets(p->edname);
	printf("\t\t\t ☆☆input no1:");
	scanf("%d",&p->no1);
	printf("\t\t\t ☆☆input pub:");
	fflush(stdin);
	gets(p->pub);
	printf("\t\t\t ☆☆input time:");
	fflush(stdin);
	gets(p->time);
	printf("\t\t\t ☆☆input num & price:");
	scanf("%d%d",&p->num,&p->price);
	printf("\t\t\t ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n\n\n");
	return p;
}

//修改图书数据
void getNode1(struct admin *p)
{
	printf("\t\t\t ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n");
	printf("\t\t\t ☆☆tinput new no:");
	scanf("%d",&p->no);
	printf("\t\t\t ☆☆input new edname:");
	fflush(stdin);
	gets(p->edname);
	printf("\t\t\t ☆☆input new no1:");
	scanf("%d",&p->no1);
	printf("\t\t\t ☆☆input new pub:");
	fflush(stdin);
	gets(p->pub);
	printf("\t\t\t ☆☆input new time:");
	fflush(stdin);
	gets(p->time);
	printf("\t\t\t ☆☆input new num & price:");
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
	printf("\t\t\t\t温馨提示：当输入0的时候录入图书结束\n");
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

	if((fp=fopen("worker.txt","w+"))==NULL)
	{
		printf("\t\t\t\t保存失败，请重试！");
		return ;
	}
	while( p != NULL)
	{
		fwrite(p,sizeof(struct admin),1,fp);
		p = p->next;
	}

	fclose(fp);     
}



//从文件中读取数据，以初始化有头结点的链表
struct admin *Initial_list2()
{
	FILE *fp;
	struct admin *p = NULL;
	struct admin *list = NULL;

	list=(struct admin *)malloc(sizeof(struct admin));
	memset(list,0,sizeof(struct admin));

	if((fp=fopen("worker.txt","r"))==NULL)
	{
		printf("open file failed!\n");
		return NULL;
	}
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
	    printf("\t\t\t☆☆分类号:%d                            ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
	}
        
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
	    printf("\t\t\t☆☆分类号:%d                            ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
	//	break;
		}
		p=p->next;
	}
	if(p==NULL)
		printf("\n\n\t\t\t\t图书馆现在没有这本书！\n\n");
        
	    
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
	    printf("\t\t\t☆☆分类号:%d                            ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
		}
		p=p->next;
	}
	if(p==NULL)
		printf("\n\n\t\t\t\t图书馆现在没有这本书！\n\n");
        
	    
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
	    printf("\t\t\t☆☆分类号:%d                            ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
		}
		p=p->next;
	}
	if(p==NULL)
		printf("\n\n\t\t\t\t图书馆现在没有这本书！\n\n");
        
	     
}
void ask_for(struct admin *list)
{
	int i;
	char book_name[20];
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
	   case 1:setPos(10,15);printf("\t\t\t请输入图书：");fflush(stdin);gets(book_name);printf("\n\n");lookup1(list,book_name);break;
	   case 2:setPos(10,15);printf("\t\t\t请输入图书作者：");fflush(stdin);gets(book_name);printf("\n\n");lookup2(list,book_name);break;
	   case 3:setPos(10,15);printf("\t\t\t请输入出版时间：");fflush(stdin);gets(book_name);printf("\n\n");lookup3(list,book_name);break;
       case 4:setPos(10,15);printf("\t\t\t请输入出版单位：");fflush(stdin);gets(book_name);printf("\n\n");lookup4(list,book_name);break;
	   default:menu();break;
	}
}

//删除全部图书
void freeList(struct admin *list)
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
	if(p==NULL)
		printf("现在还没有图书！\n");
	while(p!=NULL)
	{
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
		printf("\t\t\t☆☆编号:%d                              ☆☆\n",p->no);
		printf("\t\t\t☆☆书名:%s                              ☆☆\n",p->book);
		printf("\t\t\t☆☆作者:%s                              ☆☆\n",p->edname);
	    printf("\t\t\t☆☆分类号:%d                            ☆☆\n",p->no1);
		printf("\t\t\t☆☆出版社:%s                            ☆☆\n",p->pub);
		printf("\t\t\t☆☆出版时间:%s                          ☆☆\n",p->time);
		printf("\t\t\t☆☆库存量：%d   价格：%d                ☆☆\n",p->num,p->price);
		printf("\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n\n");
		p=p->next;
	}
}

//修改图书
struct admin * look(struct admin *list,char *edname)//查找要修改的图书
{
	struct admin *p=list->next;
	if(p==NULL)
		printf("\t\t\t\t现在还没有图书！\n");
	while(p!=NULL)	
	{
		if(strcmp(p->book,edname)==0)
			return p;
		p=p->next;
	}
	return NULL;
}

void mod(struct admin *head)
{
	struct admin *newnode=NULL,*list=head;
	char edname[30];
	printf("please input book:\n");
	fflush(stdin);
    gets(edname);
	newnode=look(list,edname);
	getNode1(newnode);
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
}
//按作者查询
void look_up_2(struct brrow *list,char *book_name)
{
	struct brrow *p1=list->next;
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
}
//按读者查询
void look_up_3(struct brrow *list,char *book_name)
{
	struct brrow *p1=list->next;
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
}	

//查询借阅信息
void brrower_menu()
{
	int i=0;
	char book_name[20];
	struct brrow *list;
	list=brr();
	printf("\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("\t\t\t\t\t▎ 1 按图书查询借阅信息   ▎\n\n");
	printf("\t\t\t\t\t▎ 2 按作者查询借阅信息   ▎\n\n");
	printf("\t\t\t\t\t▎ 3 按读者查询借阅信息   ▎\n\n");
	printf("\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	setPos(10,14);
	printf("请选择如上查询：");
	scanf("%d",&i);
	system("cls");
	switch(i)
	{
	   case 1:setPos(10,13);printf("\t\t\t请输入图书：\n");fflush(stdin);gets(book_name);look_up_1(list,book_name);break;
	   case 2:setPos(10,13);printf("\t\t\t请输入图书作者：\n");fflush(stdin);gets(book_name);look_up_2(list,book_name);break;
	   case 3:setPos(10,13);printf("\t\t\t请输入读者：\n");fflush(stdin);gets(book_name);look_up_3(list,book_name);break;
	   default:menu();break;
	}

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
}
//按作者查询
void backlook_up2(struct giveback *list,char *book_name)
{
	struct giveback *p1=list->next;
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
}
//按读者查询
void backlook_up3(struct giveback *list,char *book_name)
{
	struct giveback *p1=list->next;
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
	printf("\n\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	setPos(10,12);
	printf("请选择如上查询：");
	scanf("%d",&i);
	printf("\n");
	switch(i)
	{
	   case 1:setPos(10,16);printf("\t\t\t\t请输入图书：");fflush(stdin);gets(book_name);backlook_up1(list,book_name);break;
	   case 2:setPos(10,16);printf("\t\t\t\t请输入图书作者：");fflush(stdin);gets(book_name);backlook_up2(list,book_name);break;
	   case 3:setPos(10,16);printf("\t\t\t\t请输入读者：");fflush(stdin);gets(book_name);backlook_up3(list,book_name);break;
	   default:admincode();break;
	}

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
	
	printf("\t\t\t\t◇◇◇input  borrowing number:");
	scanf("%s",p1->num1);
	printf("\t\t\t\t◇◇◇input  name:");
	fflush(stdin);
	gets(p1->name);
	printf("\t\t\t\t◇◇◇input  max:");
	scanf("%d",&p1->max);
	printf("\t\t\t\t◇◇◇input  number of borrowed books:");
	scanf("%d",&p1->num2);
	printf("\t\t\t\t◇◇◇input  code:");
	fflush(stdin);
	gets(p1->code);
}

struct reader * getNode4()
{
     struct reader *p1=NULL;
	p1=(struct reader *)malloc(sizeof(struct reader));
	memset(p1,0,sizeof(struct reader));
     printf("\t\t\t\t◇◇◇input  borrowing number:");
	scanf("%s",p1->num1);
	printf("\t\t\t\t◇◇◇input  name:");
	fflush(stdin);
	gets(p1->name);
	printf("\t\t\t\t◇◇◇input  max:");
	scanf("%d",&p1->max);
	printf("\t\t\t\t◇◇◇input  num2:");
	scanf("%d",&p1->num2);
	printf("\t\t\t\t◇◇◇input  code:");
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

	if((fp=fopen("reader.txt","a"))==NULL)
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
		fwrite(p,sizeof(struct reader),1,fp);
		p=p->next;
	}
	fclose(fp);
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
void freeList1(struct reader *list)
{
	struct reader *p1=list->next;
	struct reader *temp=NULL;
	while(p1!=NULL)
	{
		temp=p1->next;
		free(p1);
		p1=temp;
	}
}

//浏览读者信息
void display1(struct reader *list)
{
	struct reader *p1=list->next;
	if(p1==NULL)
		printf("\t\t\t\t\t◇◇现在还没有读者信息！◇◇◇\n");
	while(p1!=NULL)
	{
		printf("\t\t\t\t◇◇◇◇编号：%-5d借阅号：%s\n\n",p1->num,p1->num1);
	    printf("\t\t\t\t◇◇◇◇姓名：%s\n\n",p1->name);
	    printf("\t\t\t\t◇◇◇◇最大借阅额度：%-5d已借阅数量：%-5d\n\n",p1->max,p1->num2);
		printf("\t\t\t\t◇◇◇◇密码：%s\n\n\n\n",p1->code);
		p1=p1->next;
	}
}

//修改读者信息
struct reader  * visit(struct reader  *list,char *name)//查找要修改的图书
{
	struct reader *p1=list->next;
	if(p1==NULL)
		printf("现在还没有读者信息！\n");
	while(p1!=NULL)	
	{
		if(strcmp(p1->name,name)==0)
			return p1;
		p1=p1->next;
	}
	return NULL;
}

void mod1(struct reader *head)
{
	struct reader *newnode=NULL,*list=head;
	char name[30];
	printf("please input name:\n");
	fflush(stdin);
    gets(name);
	newnode=visit(list,name);
	getNode3(newnode);
}





//删除读者信息
void deleteNodeByNo(struct reader  *list,char *name)
{
	struct reader  *p=list;
	struct reader  *temp;
	if(p==NULL)
		printf("\t\t\t现在还没有读者信息！\n");

	while(p->next!=NULL)
	{
		if(strcmp(p->next->name,name)==0)
		{
			temp=p->next;
			p->next=p->next->next;
			free(temp);
			printf("\t\t\t删除成功！\n");
			return ;
		}
		p=p->next;
	}
	printf("\t\t\t没有这个读者，删除失败！\n");
}




//读者登录页面信息
void d_f()
{
	char nam[20],num[20];
	struct reader *list=NULL;
	memset(nam,0,sizeof(char)*20);
	memset(num,0,sizeof(char)*20);
	printf("\n\n\t\t\t\t◎◎◎◎请输入你的姓名：");
	fflush(stdin);
	gets(nam);
	printf("\n\n\t\t\t\t◎◎◎◎请输入你的借阅号（学号）：");
	fflush(stdin);
	gets(num);
	choice_read(nam,num);
   
}
	

//读者--查询图书
void find()
{
	struct admin *loo=NULL;
	char boo[100];
	loo=Initial_list2();
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
	printf("\t\t\t\t◎◎姓名 ：%s                                ◎◎\n",p1->name);
	printf("\t\t\t\t◎◎最大借阅额度：%d           已借阅数量：%d◎◎",p1->max,p1->num2);
}
	

//读者--借阅图书
void borrow(struct reader *p)
{
	//struct reader *p;//,*br=NULL;
	struct admin *list=NULL,*p_1=NULL;
	int k,i,h,year,mon=0;
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
	if(p->max>p->num2)
	{
		printf("\t\t\t\t\t◎◎你还能借阅%d本书◎◎\n\n",(p->max)-(p->num2));
		printf("\t\t\t\t\t◎◎请输入你要借阅几本书：");
		setPos(15,4);
	    scanf("%d",&h);
		p->num2+=h;//修改读者已借阅数量
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
			{ p_1->num=p_1->num-1;//修改图书库存
			   brrowread(p,p_1,time_sl->tm_year+1900,time_sl->tm_mon+1,time_sl->tm_mday);//向借阅表上添加新的内容
			   printf("\n\n\n\t\t\t\t\t◎◎借阅成功！◎◎\n");
			   //Save1(p);
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
	printf("\n\n\t\t\t\t\t_________________________________________\n");
	printf("\t\t\t\t\t| 借阅时间：%d.%d.%d | 还书时间：%d.%d.%d|\n",(time_sl->tm_year+1900),time_sl->tm_mon+1,time_sl->tm_mday,year,mon,time_sl->tm_mday);
	printf("\t\t\t\t\t_________________________________________\n\n\n");
	}
	else
		printf("\t\t\t\t\t◎◎很抱歉你已到借阅数量上限!◎◎\n");
}

//还书功能
void  return_book(struct reader *p1)
{
	struct brrow *list=NULL,*p=NULL;
//	struct reader *p1=NULL,*br=NULL;
	struct admin *p_1=NULL,*list1=NULL;
	int book1,k;
	char book_name[20];
//	list=brr();//从借阅文件中读出信息
	//br=Initial_list();//从读者文件中读出信息
	list1=Initial_list2();//从图书文件中读出信息
	//p1=creat1(nam,num);
	//p=list->next;
	p_1=list1->next;
	/*while(p1!=NULL)
	{
	    if(strcmp(p1->num1,zh)==0)
			break;
		p1=p1->next;
	}*/
	printf("\n\n\n\t\t\t\t◎◎◎◎请输入你要归还的图书数量：\n");
	setPos(21,5);
	scanf("%d",&book1);
	p1->num2=p1->num2-book1;//修改读者已借阅数量
    for(k=0;k<book1;k++)
	{
		system("cls");
			printf("\t\t\t\t◎◎◎◎请输入你要归还的图书名：\n");
			setPos(21,5);
		       scanf("%s",book_name);
		/*	while(p!=NULL)
			{
	           if(strcmp(p->edname,book_name)==0)
			      break;
		        p=p->next;
			}*/
			while(p_1!=NULL)
			{
				if(strcmp(p_1->book,book_name)==0)
			      break;
		        p_1=p_1->next;
			}
			if(p_1!=NULL)
			{
			    returnread(p1,p_1);//向还书表中添加新的内容
			    p_1->num=p_1->num+1;//修改图书库存
			    printf("\t\t\t\t◎◎还书成功！◎◎\n");
				//Save1(p1);
			}
			else
				printf("\t\t\t\t现在没有书可还\n\n");
	}
	
}

//修改密码
void revise_code()
{
	char code_1[13];
	memset(code_1,0,sizeof(char));
	while(1)
	{
		printf("\n\n\n\t\t\t\t◎◎◎◎请输入你之前的密码:");
	    scanf("%s",code_1);
    	if(strcmp(code_1,code)==0)
		{
			printf("\n\t\t\t\t◎◎◎◎输入你的新密码：");
            scanf("%s",code);
	        printf("\n\t\t\t\t◎◎◎◎请再次输入你的新密码：");
	        scanf("%s",cod);
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

//选择模块
void choice_read(char *nam,char *num)
{
	int choice;
	struct reader *p1=NULL;
    p1=creat1(nam,num);
	while(1)
	{
	reader();
	setPos(25,33);
	scanf("%d",&choice);
	system("cls");
	switch(choice)
	{
	  case 1:borrow(p1);break;
	  case 2:return_book(p1);break;
	  case 3:find();break;
	  case 4:revise_code();break;
	  case 5:find_1(p1);break;
	  default:admincode();break;
	}
	//creat1(nam,num);
	
	}
}

//管理员页面--图书
void menueadmin1()
{
	
	printf("\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
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
	printf("\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("\t\t\t\t\t▎1 删除读者信息    ▎\n\n");
	printf("\t\t\t\t\t▎2 添加读者信息    ▎\n\n");
	printf("\t\t\t\t\t▎3 浏览读者信息    ▎\n\n");
	printf("\t\t\t\t\t▎4 修改读者信息    ▎\n\n");
	printf("\t\t\t\t\t▎5 删除全部读者信息▎\n\n");
	printf("\t\t\t\t\t▎6 修改密码        ▎\n\n");
	printf("\t\t\t\t\t▎0 退出程序        ▎\n\n");
	printf("\t\t\t\t\t◇◇◇◇◇◇◇◇◇◇◇\n");
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
			 setPos(30,20);
			printf("\t\t\t\t\t请输入你要删除图书的数量：\n");
			scanf("%d",&i);
			for(k=0;k<i;k++)
			{
		    	printf("\t\t\t\t\t请输入你要删除的书名：\n");
		    	fflush(stdin);
			   gets(name);
			   deleteNodeByNo2(list,name);
			}
			break;
		case 2:
			setPos(30,20);
			printf("\t\t\t\t\t请输入你要添加图书的数量：\n");
			scanf("%d",&i);
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
			setPos(30,20);
			printf("\t\t\t\t\t请输入你要修改图书的数量：\n");
			scanf("%d",&i);
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
		    freeList(list);
			break;
		case 9:
			revise_code();
			break;
		default:admincode();
			break;

		}
		Save(list);//保存到文件
	}
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
		menueadmin2();
		scanf("%d",&option);
		system("cls");
		switch(option)
		{
		case 1:
			 
			 printf("\t\t\t\t\t请输入你要删除读者的数量：\n");
			 setPos(2,6);
			scanf("%d",&i);
			for(k=0;k<i;k++)
			{
				
				printf("\t\t\t\t\t请输入第%d个读者的名字：\n",k+1);
				setPos(2,9);
		    	fflush(stdin);
			    gets(name);
			    deleteNodeByNo(list,name);
			}
			break;
		case 2:
			
			printf("\t\t\t\t\t请输入你要添加读者的数量：\n");
			setPos(2,6);
			scanf("%d",&i);
			for(k=0;k<i;k++)
			{
			    node=getNode4();
			    add1(list,node);
			}
			break;
		case 3:
		     display1(list);
			 system("pause");
			break;
		case 4:
			
			 printf("\t\t\t\t\t请输入你要修改读者的数量：\n");
			 setPos(2,6);
			scanf("%d",&i);
			for(k=0;k<i;k++)
		    	mod1(list);
			break;
		case 5:
			list=Initial_list();
		    freeList1(list);
			break;
		case 6:
			revise_code();
			break;
		default:admincode();
			break;
		
		}
		Save2(list);//将读者保存到文件
	}
}

void ch()
{
	int choice;
	printf("\n\n\n\n\t\t\t\t\t▲▲▲▲▲▲▲▲▲▲▲▲▲\n");
    printf("\t\t\t\t\t▎     ①   图书信息管理 ▎\n");
	printf("\t\t\t\t\t▎     ②   读者信息管理 ▎\n");
	printf("\t\t\t\t\t▲▲▲▲▲▲▲▲▲▲▲▲▲\n");
	printf("\n\n\n\t\t\t\t\t请选择：");
	setPos(33,12);
	scanf("%d",&choice);
	system("cls");
	switch(choice)
	{
	     case 1:listWithHead();break;
       	case 2:listWithHead1();break;
		default:admincode();break;
	}
}
//登录页面
void admincode()
{
	char zhanghao[13];
    int i;
	while(1)
	{	i=0;
		printf("\n\n\n\t\t\t\t\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆登录☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n");
		printf("\t\t\t\t\t┏                                                          ┓\n");
		setPos(0,8);
	    printf("\t\t\t\t\t\t           账号:");
	    scanf("%s",zhanghao);
		setPos(0,11);
	    printf("\n\n\t\t\t\t\t\t           密码:");
		fflush(stdin);
		memset(cod,0,sizeof(char)*12);
	    while(!(isspace(cod[i]=getch())))
		{
			printf("*");
	        i++;
		}
		cod[i]='\0';
		printf("\n\n\t\t\t\t\t┗                                                           ┛\n");
	   if(strcmp(code,cod)==0&&strcmp(zh,zhanghao)==0)
	   {
		   printf("                            ★★★登录成功！★★★\n");
		   system("cls");
		   menu();
		   break;
	   }
	 else 
	 {
		 system("cls");
		 printf("                               ★★★账号或者密码错误！★★★\n");
	 }
	 
	}
}

//注册页面
void denji()
{
	int i=0;
	while(1)
	{printf("\n\n\n\n\n\t\t\t\t    ☆☆☆☆☆☆☆☆☆☆☆☆☆☆注册☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	    printf("\t\t\t\t\t┏                                                          ┓\n");
		fflush(stdin);
		setPos(0,18);
		printf("\t\t\t\t\t\t\t    账号:");
		gets(zh);
		i=0;
		printf("\t\t\t\t\t\t\t    密码:");
	 while(!(isspace(code[i]=getch())))
		{
			printf("*");
	        i++;
		}
	 	code[i]='\0';
		printf("\n");
		i=0;
		setPos(0,20);
	    printf("\t\t\t\t\t\t\t    再次输入你的密码:");
		fflush(stdin);
	  while(!(isspace(cod[i]=getch())))
		{
			printf("*");
	        i++;
		}
	  	cod[i]='\0';
	   printf("\t\t\t\t\t┗                                                               ┛\n");
	    if(strcmp(code,cod)==0)
		{	printf("\t\t\t\t\t\t★★★注册成功★★★\n\n");
	        printf("\t\t\t\t\t\t★★★请登录  ★★★ \n\n");
			system("cls");
			admincode();
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
	int choice;
	printf("\n\n\n\t\t\t\t□□□□□□□□□█□█□█□█□█□█□█□█□□□□□□□□\n\n");
	printf("\t\t\t\t           欢迎进入重庆理工大学图书管理系统\n\n");
	printf("\t\t\t\t□□□□□□□□□█□█□█□█□█□█□█□█□□□□□□□□\n");
	printf("\n\n\n\n\t\t\t\t\t▲▲▲▲▲▲▲▲▲▲▲▲▲\n");
    printf("\t\t\t\t\t▎     ①  管理员        ▎\n");
	printf("\t\t\t\t\t▎     ②  读者          ▎\n");
	printf("\t\t\t\t\t▲▲▲▲▲▲▲▲▲▲▲▲▲\n");
	printf("\n\n\n\t\t\t请选择你的身份：");
	setPos(49,25);
	scanf("%d",&choice);
	system("cls");
	switch(choice)
	{
	case 1:ch();break;
	case 2:d_f();break;
    default:admincode();break;
	}
}

static void setPos(int x,int y)
{

COORD point = {x,y};//光标要设置的位置x,y
HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
SetConsoleCursorPosition(HOutput, point);//设置光标位置
}

void tshi()
{
	printf("\t\t\t\t ___________________________________________________________________\n");
	printf("\t\t\t\t|    温馨提示：在操作过程中按0退出程序,输入正确的数字进入相应程序   |\n");
	printf("\t\t\t\t|               注册账号为学号或者工号                                      |\n");
	printf("\t\t\t\t|___________________________________________________________________|\n\n");
}


void main()
{

	system("color 0C");	
	tshi();

denji();
		
	menu();

	
}





