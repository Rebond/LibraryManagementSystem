#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#define N 20

//0主函数相关函数
void login();		            //图书馆登录界面
void home_Page();	            //主界面

//1新增图书函数
void add_book();		        //新增图书

//2图书输出显示函数
void shuchu();		            //图书全部输出显示

//3图书查询相关函数
void search_book_meau();		//图书查询菜单
void search_by_num();	        //编号查询
void search_by_name();	        //名称查询
void search_by_author();	    //作者查询

//4图书删除相关函数
void deletbook_meau();		    //图书删除菜单
void deletbook_by_num();	    //按编号删除
void deletbook_by_name();       // 按名称删除

//5图书修改相关函数
void xiugaibook_meau();		    //图书修改菜单
void xiugaibook_by_num();	    //按图书编号修改
void xiugaibook_by_name();      //按图书名称修改

//6图书排序函数
void sort_book();			    //图书排序

//7用户相关函数
void users_meau();              //用户主菜单
void users_Create();            //用户注册
void users_Login();             //用户登录
void users_zhizuorenyuan();     //项目制作人员
void users_retBook();           //归还图书
void users_broBook();           //用户借书
void main_Meau_Gaimi();		    //修改登录启动图书馆密码

//8退出函数
void main_quit();		        //退出程序

//9其他函数，变量，结构体
void save();                //存入文件
void load();                //读取文件
int xianshi(int i);         //显示图书信息
unsigned long suiji();      //新建图书是随机生成图书号——无符号长整形
int M=0;                    //实际的图书总数
char c;                     //输入任意键
int isLogin=0;              //用来判断用户是否登录，0表示未登录
char guanli[10]="guanli";              //管理员密码，才能使用的功能
char username[15]="jxnu",pwd1[100];	    //username[15]原始账号，用于pwd1修改密码时的比较
char userName1[N],userPassword1[N];     //用于借书和还书以及登录存放用户账号密码
void isGuanli();             //管理员使用函数

struct booklibrary{
	unsigned long num;
	char id;		//图书编号
	char bookName[N];	//名字
	char author[N]; 	//作者
	char isbn[N];		//ISBN号
	char chuBan[N];	//出版单位
	char chuBanAge[N]; 	//出版时间
	char bookPrice[N];	//图书单价
};
struct user{    //存放用户名密码的结构体
	char pwd[20];
}us;
struct booklibrary book[100];

/*----------------主函数块----------------*/
void main(){    //主函数
    login();
    //home_Page();
}
void login(){	//登录界面
	int i=0,k=0,j;
	FILE *fp;
	if((fp=fopen("图书馆密码.txt","r"))==NULL){
		strcpy(us.pwd,"123456"); }      //如果文件打开错误初始密码
	fscanf(fp,"%s",&us.pwd);
	char username1[15];                 //定义与原始密码相比较的变量
	//system("color 8f");		   //系统函数，color显示颜色,8灰色，f是亮白色
	printf("\n\n");
	printf("\t 系统默认用户名：jxnu,密码：123456\n");
	printf("\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t┃**********************************************************┃\n");
	printf("\t┃***┏━━━━━━━━━━━━━━━━━━━━━━━━┓***┃\n");
	printf("\t┃***┃************************************************┃***┃\n");
	printf("\t┃***┃***                                         ****┃***┃\n");
	printf("\t┃***┃***         欢迎使用图书管理信息系统        ****┃***┃\n");
	printf("\t┃***┃***                                         ****┃***┃\n");
	printf("\t┃***┃***                                         ****┃***┃\n");
	printf("\t┃***┃***               18级计科四班              ****┃***┃\n");
	printf("\t┃***┃***                                         ****┃***┃\n");
	printf("\t┃***┃***                2020年10月               ****┃***┃\n");
	printf("\t┃***┃***                                         ****┃***┃\n");
	printf("\t┃***┃************************************************┃***┃\n");
	printf("\t┃***┗━━━━━━━━━━━━━━━━━━━━━━━━┛***┃\n");
	printf("\t┃**********************************************************┃\n");
	printf("\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	for(i=0;i<3;i++){
	printf("\n\t请输入用户名:");
	gets(username1);
	printf("\t请输入进入图书馆密码:");
	for(j=0;j<100;j++){
		pwd1[j]=getch();
		if(pwd1[j]=='\r')   //回车结束输入密码
            break;
		printf("*");
    }
	pwd1[j]='\0';
	if((strcmp(username,username1)==0)&&(strcmp(us.pwd,pwd1)==0)){
		printf("\n\t您已经成功登录");
		k=1;
		for(i=0;i<20;i++){printf(".");Sleep(100);	}
        system("cls");//清屏
        home_Page();			//跳转到主界面
        break;
	}
    else{
        if(2-i>0)
            printf("\n\t用户名或密码无效，请珍惜你仅剩%d次机会，重新输入:\n",2-i);
        if(2-i==0)
            printf("\n\t很抱歉用户名或密码任然错误，登录次数已用完，欢迎下次再来~");
    }
    continue;
    }
	if(k==0)
	printf("\n\t连续输入错误3次，即将退出程序......\n");
	Sleep(2000);			//程序暂停函数（单位毫秒），本次暂停2000毫秒
	return;         //连续三次错误跳转退出界面
}
void home_Page() {	//程序主界面
	int cmd;
	time_t T;  //获取系统时间
	struct tm * timenow;
	time ( &T );
	timenow = localtime ( &T );
    while(1){
		printf("\n\n");
		printf("\t 当前系统时间是: %s",asctime (timenow) );
		printf("\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t┃ ╔════════════════════════════╗ ┃\n");
		printf("\t┃ ║           欢 迎 使 用 图 书 管 理 信 息 系 统          ║ ┃\n");
		printf("\t┃ ╚════════════════════════════╝ ┃\n");
		printf("\t┃ ***********************************************************  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ *         1.录入图书信息   *      2.浏览图书信息          *  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ ***********************************************************  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ *         3.图书信息查询   *      4.图书信息删除          *  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ ***********************************************************  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ *         5.图书信息修改   *      6.图书信息排序          *  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ ***********************************************************  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ *         7.用户相关系统   *      8.退出信息系统          *  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ ***********************************************************  ┃\n");
		printf("\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		printf("\t请选择功能 1 - 8 :");
        scanf("%d",&cmd);
		getchar();
		system("cls");
        switch(cmd){
           	case 1:add_book();break;
			case 2:shuchu();break;
			case 3:search_book_meau();break;
			case 4:deletbook_meau();break;
			case 5:xiugaibook_meau();break;
			case 6:sort_book1();break;
			case 7:users_meau();break;
			case 8:main_quit();break;
			default:printf("\n 非法操作!\n");}
			system("pause");//冻结屏幕，任意键结束
			system("cls");
        }
}

/*----------------模块1:增加图书----------------*/
void add_book(){//添加图书
	load();
	int m,i,j;
	printf(" ═════════════════ \n");
    printf(" ********** 录入图书信息 **********    \n");
    printf(" ═════════════════  \n");
	for(i=0;i<4;i++){          //连续输入4次擦很超过图书内存范围就会退出程序
        printf("请输入需要添加的图书数量：");
        scanf("%d",&j);
        if(j<100-M){//M实际图书数量
            m=j;
            break;
        }
        printf("\t该系统只能存放 100 本以内的图书信息,剩余%d 本空间,请重新输入\n",100-M);

    }
	if(i==4){
        printf("输入的图书数量超过范围\n");
        exit(0);
    }
	M=M+m;
	for(i=0;i<m;i++){
		printf("输入第%d 个图书名称: ",i+1);
		scanf("%s",book[M+i-m].bookName);
		printf("输入第%d 个图书作者:",i+1);
		scanf("%s",book[M+i-m].author);
		printf("输入第%d 个图书ISBN号:",i+1);
		scanf("%s",book[M+i-m].isbn);
		printf("输入第%d 个出版单位:",i+1);
		scanf("%s",book[M+i-m].chuBan);
		printf("输入第%d 个出版时间:",i+1);
		scanf("%s",book[M+i-m].chuBanAge);
		printf("输入第%d 个图书单价:",i+1);
		scanf("%s",book[M+i-m].bookPrice);
		book[M+i-m].num=suiji();
		printf("该图书的编号被系统定为:%lu\n",book[M+i-m].num);
    }
	save();//保持文件
}

/*----------------模块2:显示所有图书----------------*/
void shuchu()//显示所有图书信息
{
	load();
	int i;//循环变量
	printf(" 所有图书相关信息\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("序列  图书号  图书名称 图书作者 图书ISBN     出版单位       出版时间 图书单价\n");
	for(i=0;i<M;i++){
        printf("%2d ",i+1);
        printf("  %-9lu%-10s%-8s%-10s%-20s%-9s%-7s\n",book[i].num,book[i].bookName,book[i].author,
        book[i].isbn,book[i].chuBan,book[i].chuBanAge,book[i].bookPrice);
	}
}

/*----------------模块3:图书搜索----------------*/
void search_book_meau()//查询菜单
{
        int num,i;
		printf("\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("\t┃ ╔════════════════════════════╗ ┃\n");
		printf("\t┃ ║             欢 迎 进 入 图 书 信 息 查 询 模 块         ║ ┃\n");
		printf("\t┃ ╚════════════════════════════╝ ┃\n");
		printf("\t┃ ***********************************************************  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ *       1.按图书编号查询   *      2.按图书名称查询        *  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ ***********************************************************  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ *       3.按图书作者查询   *      4.返回主菜单界面        *  ┃\n");
		printf("\t┃ *                          *                              *  ┃\n");
		printf("\t┃ ***********************************************************  ┃\n");
		printf("\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		printf("\t请选择功能 1 - 4 :");
		fflush(stdin);
		scanf("%d",&num);
		switch(num){
			case 1:search_by_num();break;
			case 2:search_by_name();break;
			case 3:search_by_author();break;
			case 4:{
			    system("cls");
                home_Page();
                break;
            }
			default:
			    printf("\n\t非法操作!\n");
			    printf("\t查询菜单返回中");
			    for(i=0;i<20;i++){printf(".");Sleep(100);	}
			    //system("pause");
			    system("cls");
                search_book_meau();
		}
}
void search_by_num()//按图书编号查询
{
	load();
	int i,j=0,k;
	unsigned long n;
	printf("输入需要查找的图书编号:");
	scanf("%lu",&n);
    printf("查询中");
    for(k=0;k<15;k++){printf(".");Sleep(100);}
	for(i=0;i<M;i++)
        if(n==book[i].num){
            xianshi(i);
            j++;
        }
	if(j==0)
        printf("查询的该图书编号不存在");
	printf("\n按任意键返回\n");
	c=getch();
	system("cls");
	search_book_meau();
}
void search_by_name()//按图书名称查询
{
	int i,j=0,k;
	char c1[10];//*
	load();
	printf("输入需要查找的图书名称:");
	getchar();
	gets(c1);
    printf("查询中");
    for(k=0;k<15;k++){printf(".");Sleep(100);}
	for(i=0;i<M;i++)
        if(strcmp(c1,book[i].bookName)==0){
            xianshi(i);
            j++;
    }
	if(j==0)
        printf(" 没有查找到此图书名称的信息!!!");
	printf("\n按任意键返回\n");    //这两句作用就等于system(pause)
	c=getch();                     //这两句作用就等于system(pause),getch按下某个字符时，函数自动读取，无需按回车
	system("cls");
	search_book_meau();
}
void search_by_author()//按图书作者查询
{
	int i,j=0,k;
	char c1[10];
	load();
	printf("输入需要查找的图书作者:");
	getchar();
	gets(c1);
    printf("查询中");
    for(k=0;k<15;k++){printf(".");Sleep(100);}
	for(i=0;i<M;i++)
        if(strcmp(c1,book[i].author)==0){
            xianshi(i);
            j++;
        }
	if(j==0)
        printf(" 没有查找到此图书作者的信息!!!");
	printf("\n按任意键返回\n");
	c=getch();
	system("cls");
	search_book_meau();
}

/*-----------------模块4:图书删除----------------*/
void deletbook_meau(){		//删除主菜单
	int num,i;
    printf("\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("\t┃ ╔════════════════════════════╗ ┃\n");
    printf("\t┃ ║             欢 迎 进 入 图 书 信 息 删 除 模 块         ║ ┃\n");
    printf("\t┃ ╚════════════════════════════╝ ┃\n");
    printf("\t┃ ***********************************************************  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ *       1.按图书编号删除   *      2.按图书名称删除        *  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ ***********************************************************  ┃\n");
    printf("\t┃ *                     3.返回主菜单界面                    *  ┃\n");
    printf("\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\t请输入你的选择1-3:");
    fflush(stdin);
    scanf("%d",&num);
    switch(num){

        case 1:deletbook_by_num();break;
        case 2:deletbook_by_name();break;
        case 3:{system("cls");home_Page();break;}
        default:
            printf("\n\t非法操作!\n");
            printf("\t删除菜单返回中");
            for(i=0;i<20;i++){printf(".");Sleep(100);	}
            //system("pause");
            system("cls");
            deletbook_meau();
}
}
void deletbook_by_num(){	//根据编号删除
	load();
	isGuanli();
	int i,j=0,k;
	char c1;//是否删除变量
	unsigned long n;
	printf("输入需要删除的图书编号:");
	scanf("%lu",&n);
	for(i=0;i<M;i++)
        if(n==book[i].num){
        xianshi(i);
        k=i;//记录下标
        j++;	break;	}
	if(j==0){
        printf("该图书编号不存在");
        k=-1;
        printf("\n按任意键返回\n");
        c=getch();
        system("cls");
        deletbook_meau();
	}
	printf("确认删除?是 输入 y 或 Y。不是按任意键\n");
	getchar();
	scanf("%c",&c1);
	if(c1=='y'||c1=='Y'){
        for(i=k;i<M-1;i++)
        book[i]=book[i+1];
        M=M-1;
        save();
        printf("删除成功\n");
    }
	printf("按任意键返回\n");
	c=getch();
	system("cls");
	deletbook_meau();
}
void deletbook_by_name(){	//根据图书名称删除
	load();
	isGuanli();
	int i,j=0,k;
	char c1;//是否删除变量
	char bookName1[N];	//名字    //*
	printf("输入需要删除的图书名称:");
	scanf("%s",bookName1);
	for(i=0;i<M;i++)
        if(strcmp(bookName1,book[i].bookName)==0){
            xianshi(i);
            k=i;
            j++;
            break;
        }
	if(j==0){
        printf("该图书名称不存在\n");
        k=-1;
        printf("按任意键返回\n");
        c=getch();
        system("cls");
        deletbook_meau();
	}
	printf("确认删除?是 输入 y 或 Y。不是按任意键\n");
	getchar();
	scanf("%c",&c1);
	if(c1=='y'||c1=='Y'){
        for(i=k;i<M-1;i++)
            book[i]=book[i+1];
        M=M-1;
        save();
        printf("删除成功\n");
    }
	printf("按任意键返回\n");
	c=getch();
	system("cls");
	deletbook_meau();
}


/*-----------------模块5:图书信息修改----------------*/
void xiugaibook_meau(){	//修改菜单
	int num,i;
    printf("\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("\t┃ ╔════════════════════════════╗ ┃\n");
    printf("\t┃ ║             欢 迎 进 入 图 书 信 息 修 改 模 块        ║ ┃\n");
    printf("\t┃ ╚════════════════════════════╝ ┃\n");
    printf("\t┃ ***********************************************************  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ *       1.按图书编号修改   *      2.按图书名称修改        *  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ ***********************************************************  ┃\n");
    printf("\t┃ *                     3.返回主菜单界面                    *  ┃\n");
    printf("\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\t请输入你的选择1-3:");
    fflush(stdin);
    scanf("%d",&num);
    switch(num){
        case 1:xiugaibook_by_num();break;
        case 2:xiugaibook_by_name();break;
        case 3:{
            system("cls");
            home_Page();
            break;}
        default:
            printf("\n\t非法操作!\n");
            printf("\t修改菜单返回中");
            for(i=0;i<20;i++){printf(".");Sleep(100);	}
            //system("pause");
            system("cls");
            xiugaibook_meau();
    }
}
void xiugaibook_by_num(){	//根据编号修改
	load();
	isGuanli();
	int i,j=0,k;//k查找到后把编号给K
	char c2; //是否修改
	unsigned long n;
	printf("输入需要修改的图书编号:");
	scanf("%lu",&n);
	for(i=0;i<M;i++)
	if(n==book[i].num){
        xianshi(i);
        k=i;
        j++;
        break;
    }
	if(j==0){
        printf("该图书编号不存在\n");
        k=-1;
        printf("\n按任意键返回\n");
        c=getch();
        system("cls");
        xiugaibook_meau();
    }
	i=k;
	printf("输入新的图书名称: ");
	scanf("%s",book[i].bookName);
	printf("输入新的图书作者:");
	scanf("%s",book[i].author);
	printf("输入新的图书ISBN号:");
	scanf("%s",book[i].isbn);
	printf("输入新的出版单位:");
	scanf("%s",book[i].chuBan);
	printf("输入新的出版时间:");
	scanf("%s",book[i].chuBanAge);
	printf("输入新的图书单价:");
	scanf("%s",book[i].bookPrice);
	printf("确认修改?是 输入 y 或 Y。不是按任意键\n");
	getchar();
	scanf("%c",&c2);
	if(c2=='y'||c2=='Y'){
        save();
        printf("修改成功！\n");
        printf("\n按任意键返回\n");
        c=getch();system("cls");	xiugaibook_meau();
	}
	else{
        printf("\n按任意键返回\n");
        c=getch();system("cls");	xiugaibook_meau();
	}
}
void xiugaibook_by_name(){	//根据图书名称修改
	isGuanli();
	load();
	int i,j=0,k;//k查找到后把编号给K
	char c2;//是否修改
	char bookName1[20];	//名字
	printf("输入需要修改的图书名称:");
	scanf("%s",bookName1);
	for(i=0;i<M;i++)
	if(strcmp(bookName1,book[i].bookName)==0){
        xianshi(i);
        k=i;
        j++;
        break;
    }
	if(j==0){
        printf("该图书名称不存在\n");
        k=-1;
        printf("\n按任意键返回\n");
        c=getch();
        system("cls");
        xiugaibook_meau();
    }
	i=k;
	printf("输入新的图书名称: ");
	scanf("%s",book[i].bookName);
	printf("输入新的图书作者:");
	scanf("%s",book[i].author);
	printf("输入新的图书ISBN号:");
	scanf("%s",book[i].isbn);
	printf("输入新的出版单位:");
	scanf("%s",book[i].chuBan);
	printf("输入新的出版时间:");
	scanf("%s",book[i].chuBanAge);
	printf("输入新的图书单价:");
	scanf("%s",book[i].bookPrice);
	printf("确认修改?是 输入 y 或 Y。不是按任意键\n");
	getchar();
	scanf("%c",&c2);
	if(c2=='y'||c2=='Y'){
		save();
		printf("\n修改成功！");
		printf("\n按任意键返回\n");
		c=getch();
		system("cls");
		xiugaibook_meau();
	}
	else{
		printf("\n按任意键返回\n");
		c=getch();
		system("cls");
		xiugaibook_meau();
		}
}


/*----------------模块6:图书整理排序----------------*/
void sort_book(){//图书信息排序
	load();
	int i,j,t=0;//t测试是否排序成功
	struct booklibrary temp;
	for(i=0;i<M-1;i++){
		for(j=0;j<M-i-1;j++){
			if(book[j].num>book[j+1].num){//简单排序，MAX往后挪
				temp=book[j];
				book[j]=book[j+1];
				book[j+1]=temp;	t=1;
            }
        }
    }
	printf("欢迎进入图书排序模块，本系统按照图书编号由小到大排序！\n");
	printf("---------------------------------------------------------\n");
	printf("正在排序");
	for(i=0;i<21;i++){
		printf(".");
		Sleep(100);		}
	if(t==1){
		printf("\n排序完成！请按任意键返回查看！");
		save(); //排序成功后保存文件
	}
	else
        printf("\n排序失败！可能是因为已经排序过了，请按任意键返回！");
    c=getch();
    system("cls");
    home_Page();
}
void sort_book1(){//图书信息排序
	load();
	int i=M,j,t=0;//t测试是否排序成功
	struct booklibrary temp;
	bool flag=1;
	while(flag&&i>1)
    {
        flag=0;
        for(j=0;j<i-1;j++)
            if(book[j].num>book[j+1].num){
				temp=book[j];
				book[j]=book[j+1];
				book[j+1]=temp;
                t=1;
                flag=1;
            }
            i--;
    }
	printf("欢迎进入图书排序模块，本系统按照图书编号由小到大排序！\n");
	printf("---------------------------------------------------------\n");
	printf("正在排序");
	for(i=0;i<21;i++){
		printf(".");
		Sleep(100);		}
	if(t==1){
		printf("\n排序完成！请按任意键返回查看！");
		save(); //排序成功后保存文件
	}
	else
        printf("\n排序失败！可能是因为已经排序过了，请按任意键返回！");
    c=getch();
    system("cls");
    home_Page();
}

/*----------------模块7:用户相关----------------*/
void users_meau()//用户相关菜单
{
	int num,i;
    printf("\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("\t┃ ╔════════════════════════════╗ ┃\n");
    printf("\t┃ ║             欢 迎 进 入 图 书 用 户 相 关  系  统      ║ ┃\n");
    printf("\t┃ ╚════════════════════════════╝ ┃\n");
    printf("\t┃ ***********************************************************  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ *       1.图书馆用户注册   *      2.图书馆用户登录        *  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ ***********************************************************  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ *       3.图书馆用户注销   *      4.项目  制作 人员       *  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ ***********************************************************  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ *       5.用  户  借  书   *      6.用  户  还  书        *  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ ***********************************************************  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ *       7.修改图书馆密码   *      8.返 回 主 菜 单        *  ┃\n");
    printf("\t┃ *                          *                              *  ┃\n");
    printf("\t┃ ***********************************************************  ┃\n");
    printf("\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n\t请选择功能 1 - 8 :");
    fflush(stdin);
    scanf("%d",&num);
    switch(num){
        case 1:users_Create();break;
        case 2:users_Login();break;
        case 3:users_delite();break;
        case 4:users_zhizuorenyuan();break;
        case 5:users_broBook();break;
        case 6:users_retBook();break;
        case 7:main_Meau_Gaimi();break;
        case 8:system("cls");home_Page();break;
    default:
        printf("\n\t非法操作!\n");
        printf("\t用户相关菜单返回中");
        for(i=0;i<20;i++){printf(".");Sleep(100);	}
        //system("pause");
        system("cls");
        users_meau();
		}
}
void users_Create()//用户注册
{
    int i;
	FILE *zhanghaoFp;//文件指针
	char  zhanghao[N];
	char password[N],password1[N];
	if ((zhanghaoFp=fopen("账号密码.txt","a"))==NULL)
	{
      printf("file open error!\n");
      exit(0);
    }
	while(1)
	{
        printf("\n\n请输入注册的账号(九位数)、密码(六位数)");
	    printf("\n请输入账号:");
	    scanf("%s",zhanghao);
	    printf("请输入密码:");
	    scanf("%s",password);
	    system("pause");
	    //system("cls");
        printf("再次输入密码:");
        scanf("%s",password1);
	    if(strcmp(password,password1)==0)
	    {
	        printf("创建中");
            //system("cls");

	        fprintf(zhanghaoFp,"%s %s\n",zhanghao,password);
	        fclose(zhanghaoFp);
            for(i=0;i<20;i++){printf(".");Sleep(100);}//先创建后提示成功***
	   		printf("创建成功");
	        printf("\n返回用户系统,");
            system("pause");
            system("cls");
		    users_meau();}
        else
        {
            system("pause");
            //system("cls");
            printf("\n\n两次输入密码不一致,请重新输入");
            break;}
   }
}
void users_delite(){
    FILE *fp;
    FILE *fp1;
    int i=0,j;
    char zhuxiao[20];
    char zhanghao[20],mima[20];
    isGuanli();
    printf("可注销账号如下:\n");
    fp=fopen("账号密码.txt","r");
    fp1=fopen("temp.txt","w");
    printf("账号       密码\n");
    while(fscanf(fp,"%s %s",zhanghao,mima)!=EOF){
        printf("%s %s\n",zhanghao,mima);
    }
    printf("请输入需要注销的账号\n");
    fflush(stdin);
    gets(zhuxiao);
    //printf("%s",zhuxiao);
    rewind(fp);//指针回到文件头
    while(fscanf(fp,"%s %s",zhanghao,mima)!=EOF){
        if(strcmp(zhuxiao,zhanghao)==0)
            continue;
        fprintf(fp1,"%s %s\n",zhanghao,mima);
    }
    printf("账号%s注销中",zhuxiao);
    for(i=0;i<20;i++){printf(".");Sleep(100);}
    printf("注销成功\n");
    fclose(fp);
    fclose(fp1);
    remove("账号密码.txt");
    rename("temp.txt","账号密码.txt");
    printf("\n返回用户菜单");
    system("pause");
    system("cls");
    users_meau();

}
void users_Login()//用户登录
{
    int i=0,j=0;
	int aa=0;//登录状态
	char userNameCheck1[N],userPasswordCheck1[N];
	int cc;
	FILE *fp;
	if((fp=fopen("账号密码.txt","r"))==NULL){
		printf("File open error!\n");
		exit(0);
	}
    printf("\n请输入登录账号：");
	scanf("%s",userName1);
    printf("请输入登录密码：");
    for(j=0;j<N+2;j++){
		userPassword1[j]=getch();
		if(userPassword1[j]=='\r')   //回车结束输入密码
            break;
		printf("*");
    }
    userPassword1[j]='\0';
	while(1){
        while(!feof(fp)){//feof文末为0
            fscanf(fp,"%s%s",userNameCheck1,userPasswordCheck1);
            if((strcmp(userName1,userNameCheck1)==0)&&(strcmp(userPassword1,userPasswordCheck1)==0)){
                    printf("\n登录中");
                	for(i=0;i<21;i++){
                        printf(".");
                        Sleep(100);		}
                printf("登录成功!\n");
                isLogin=1;
                fclose(fp);
                printf("返回主菜单,");
                system("pause");
                system("cls");
                home_Page();
                aa=1;
            }
        }
        if(aa==0){
            //system("cls");
            printf("\n输入错误，重新输入请按1，按任意(除去回车)键返回上一级");
            printf("\n请输入你的选择 ：");
            scanf("%d",&cc);
            if(cc==1)
                users_Login();
            if(cc!=1){
                system("cls");
                users_meau();
            }
        }
	}
}
void users_zhizuorenyuan(){//项目制作人员
    load();
    FILE *users_fp;
    int i;
    char zhi_school[20]={'\0'},zhi_class[20]={'\0'},zhi_name[20]={'\0'},zhi_id[20]={'\0'};
    if((users_fp=fopen("制作人员信息.txt","r")==NULL)){
        system("pause");
        system ("cls");
        users_meau();
    }
    users_fp=fopen("制作人员信息.txt","r");
    system("cls");
    printf("\n\n制作人员如下:\n");
    printf("   学   校  \t班级\t 姓名\t\t学号\n");
    while(fscanf(users_fp,"%s%s%s%s",zhi_school,zhi_class,zhi_name,zhi_id)!=EOF){
                printf("%-13s%-11s%-10s%-13s\n",zhi_school,zhi_class,zhi_name,zhi_id);
    }
    fclose(users_fp);
    system("pause");
    printf("即将返回上一层");
    for(i=0;i<20;i++){printf(".");Sleep(100);}
    system("cls");
    users_meau();
}
void users_broBook(){//用户借书函数
    FILE *fpb;
    int isBro=0,i,j,broTian;//broTian表示的是借书天数
    char bro_name[20];
    system("cls");
    shuchu();
    if((fpb=fopen("借书信息.txt","a")==NULL))
    {
        printf("文件打开失败！即将返回上一级。");
        Sleep(2000);
        system("cls");
        users_meau();
    }
    fpb=fopen("借书信息.txt","a");
    printf("请输入借书的书名:\n");
    scanf("%s",&bro_name);
    load();
    for(i=0;i<M;i++)
    {
        if(strcmp(bro_name,book[i].bookName)==0){
            isBro=1;break;
        }
    }
    if(isBro==0){
        printf("没有该书，即将返回上一级。");
        for(i=0;i<20;i++){printf(".");Sleep(100);	}
        system("cls");
        users_meau();
    }
    if(isBro==1){
        printf("请输入借书天数\n");
        scanf("%d",&broTian);
        fprintf(fpb,"%s\t%s\t%d天\n",userName1,bro_name,broTian);
        fflush(fpb);
        for(j=i;j<M-1;j++)
            book[j]=book[j+1];
        M=M-1;
        save();
        printf("借书成功\n\n剩余可借图书如下\n");
        shuchu();
        system("pause");
        printf("即将返回上一层");
        for(i=0;i<20;i++){printf(".");Sleep(100);}
        system("cls");
        users_meau();
    }
    fclose(fpb);
}
void users_retBook(){
    int i=0;
    char c[30];
    load();
    printf("请输入需要归还的图书:\n");
    fflush(stdin);
    gets(c);
    printf("%s归还中",c);
    for(i=0;i<20;i++){printf(".");Sleep(100);}
    printf("归还成功\n");
    printf("返回上一层");
    system("pause");
    system("cls");
    users_meau();
}



/*---------------模块8:退出结束程序----------------*/
void main_quit(){	//退出程序
	system("cls");
	printf("\n\n\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t┃ ***********************************************************┃\n");
	printf("\t┃ *                       谢谢使用本程序                    *┃\n");
	printf("\t┃ ***********************************************************┃\n");
	printf("\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n");
	isLogin=0;
	exit(0);
}

/*-------------其他函数----------------*/
void save(){	//文件存盘
	FILE *fp;
	int i;
	if((fp=fopen("图书信息.txt","w"))==NULL){
        printf("文件打开错误！\n");
        exit(0);
    }
	for(i=0;i<M;i++)
        fwrite(&book[i],sizeof(struct booklibrary),1,fp);
	fclose(fp);	}
void load(){//磁盘信息读入到内存
    if(isLogin==0)
    {
        int x;
        printf("\n您还没登录，请选择1:注册账号 2:登录账号 任意键将返回主菜单");
        //Sleep(2000);
        //exit(0);
        printf("\n请输入选择: ");
        scanf("%d",&x);
        if(x==1){
            system("pause");
            system("cls");
            users_Create();
        }
        if(x==2){
            system("pause");
            system("cls");
            users_Login();
        }
        //system("cls");
        else{
            system("pause");
            system("cls");
            home_Page();
        }
    }
    if(isLogin==1)
    {
        FILE *fp;
        int i;
        if((fp=fopen("图书信息.txt","r"))==NULL){
            printf("文件打开错误!\n");
            exit(0);	}
        for(i=0;!feof(fp);i++)
        {
            fread(&book[i],sizeof(struct booklibrary),1,fp);
        }
        fclose(fp);
        M=i-1;
    }
}
unsigned long suiji(){//生成随机的图书号
	unsigned long h;
	srand(time(NULL));
	h=rand()%1000+2020000;
	return h;	}
void main_Meau_Gaimi(){	//修改密码程序
	int j;
	FILE *fp;
	isGuanli();
	if((fp=fopen("图书馆密码.txt","w"))==NULL){
		printf("文件打开错误！");
		exit(0);
    }
	printf("\n请输入您的原始密码:\n");
	fflush(stdin); 		//清除缓冲
	for(j=0;j<100;j++){
		us.pwd[j]=getch();
		if(us.pwd[j]=='\r')
		break;
		printf("*");
    }
    us.pwd[j]='\0';
	if((strcmp(us.pwd,pwd1)==0)){
		printf("\n请输入您要修改的密码\n");
		for(j=0;j<100;j++){
            us.pwd[j]=getch();
            if(us.pwd[j]=='\r')
                break;
            printf("*");
        }
		us.pwd[j]='\0';
		fflush(stdin); 		//清除缓冲
		printf("\n请再次确认你的密码\n");
		for(j=0;j<100;j++){
            pwd1[j]=getch();
            if(pwd1[j]=='\r')
                break;
            printf("*");
        }
		pwd1[j]='\0';
		if((strcmp(us.pwd,pwd1)==0)){
            fprintf(fp,"%s",&us.pwd);
            fclose(fp);
			printf("\n密码修改成功，请重新登录。");
			fprintf(fp,"%s",&us.pwd);
			Sleep(2000);
			system("cls");
			login();
        }
		else {
			printf("\n两次密码不符合，本次服务到此结束！");
			printf("\n按任意键返回\n");
			c=getch();
			system("cls");
			home_Page();
		}
    }
	else{
		printf("\n密码输入错误！\n\n");
		printf("\n\n按任意键返回\n");
		c=getch();
		system("cls");
		home_Page();
		}
}
int xianshi(int i){
	int j=0;
	printf("\n满足要求的所有图书相关信息\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("序列  图书号  图书名称 图书作者 图书ISBN     出版单位       出版时间 图书单价\n");
	printf("%2d ",j+1);
	printf("  %-9lu%-10s%-8s%-10s%-20s%-9s%-7s\n",book[i].num,book[i].bookName,book[i].author,
        book[i].isbn,book[i].chuBan,book[i].chuBanAge,book[i].bookPrice);
	return 0;
}
void isGuanli(){
    int i=0;
    char guanli1[20];
    printf("请输入管路员密码:\n");
    fflush(stdin);
    gets(guanli1);
    if(strcmp(guanli1,guanli)==0)
    {
        printf("管理员密码验证中");
        for(i=0;i<20;i++){printf(".");Sleep(100);}
        printf("\n管理员密码正确，欢迎使用\n");
    }
    if(strcmp(guanli1,guanli)!=0)
    {
        printf("管理员密码错误,主菜单返回中");
        for(i=0;i<20;i++){printf(".");Sleep(100);}
        system("cls");
        home_Page();
    }
}
