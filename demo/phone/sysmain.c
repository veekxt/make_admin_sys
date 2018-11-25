/***
Automatic generation by make_admin_sys
@author : veekxt@gmail.com
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>  //if linux should be #include <curses.h>
#define CLS system("cls")    //windows cmd清屏
int NPAGE=6;                //每一页显示数量
//清空缓冲区,也可用于跳过任意字符，但至少输入一次的“按下任意键”
#define rst_stdin(); \
{\
    char c;\
    while(( c= getchar()) != '\n' && c!= EOF);\
}
//变量交换，第一个参数是变量类型
#define \
swap(type_t,a,b) \
{type_t tmp_s_w_a_p_h_ = (a);\
(a)=(b);\
(b)=tmp_s_w_a_p_h_;\
}

typedef struct node_s_t
{
    char name[9];
    char age[3];
    char sex[3];
    char phone[12];
    char yb[7];
    struct node_s_t *next;
}list_s,*list;
//数据初始化方法
void init_data(list N,int what)
{
    switch(what)
    {
    case 0:
        printf("请输入姓名:");
        scanf("%s",N->name);
        rst_stdin();
        printf("请输入年龄:");
        scanf("%s",N->age);
        rst_stdin();
        printf("请输入性别:");
        scanf("%s",N->sex);
        rst_stdin();
        printf("请输入电话:");
        scanf("%s",N->phone);
        rst_stdin();
        printf("请输入邮编:");
        scanf("%s",N->yb);
        rst_stdin();
        printf("录入成功！,按下任意键返回");
        getch();
        break;
    case 1:
        printf("请输入姓名:");
        scanf("%s",N->name);
        rst_stdin();
        printf("录入成功！,按下任意键返回");
        getch();
    break;
    case 2:
        printf("请输入年龄:");
        scanf("%s",N->age);
        rst_stdin();
        printf("录入成功！,按下任意键返回");
        getch();
    break;
    case 3:
        printf("请输入性别:");
        scanf("%s",N->sex);
        rst_stdin();
        printf("录入成功！,按下任意键返回");
        getch();
    break;
    case 4:
        printf("请输入电话:");
        scanf("%s",N->phone);
        rst_stdin();
        printf("录入成功！,按下任意键返回");
        getch();
    break;
    case 5:
        printf("请输入邮编:");
        scanf("%s",N->yb);
        rst_stdin();
        printf("录入成功！,按下任意键返回");
        getch();
    break;
    }
}
//判断是否为空
int is_null(list L)
{
    return ((L->next==NULL)?1:0);
}
//新建一个空链表-
list creat_list(void)
{
    list newlist = (list)malloc(sizeof(struct node_s_t));
    newlist->next=NULL;
    return newlist;
}
//测量长度-
int len_list(list L)
{
    int len=0;
    while(L->next!=NULL)
    {
        len++;
        L=L->next;
    }
    return len;
}
//交换两个节点-
void swap_node(list a,list b)
{
    swap(list_s,*a,*b);
    swap(list,a->next,b->next);
}

//尾部插入一个节点-
list insert_list(list L)
{
    list newlist = (list)malloc(sizeof(struct node_s_t));
    while(L->next!=NULL)
    {
        L=L->next;
    }
    L->next=newlist;
    newlist->next=NULL;
    init_data(newlist,0);
    return newlist;
}

//删除，L:表头，N:要删除的节点-
void delete_list(list L,list N)
{
    while(L->next!=NULL)
    {
        if(L->next==N)
        {
            L->next=L->next->next;
            free(N);
            break;
        }
        L=L->next;
    }
}

//保存到文件-
int save_to_file( list L )
{

    FILE * F = fopen( "./list.dat", "wb" ); //打开文件
    L = L->next;
    if(F==NULL){puts("文件操作失败！");return 0;}
    while( L != NULL )
    {
        fwrite( L, sizeof( list_s ), 1, F ); //写入
        L = L->next;
    }
    fclose( F );
    return 1;
}

//从文件导入-
void init_from_file( list L )
{
    list newn;
    FILE *F;
    if( ( F = fopen( "./list.dat", "rb" ) ) == NULL )
    {
        puts( "文件操作失败！" );
        return ;
    }
    while( 1 )
    {
        newn = ( list )malloc( sizeof( list_s ) );
        fread( newn, sizeof( list_s ), 1, F );
        if(feof( F ) != 0)break;
        newn->next = NULL;
        L->next=newn;
        L=newn;
    }
    fclose( F );
}

//显示一条，第一条会加上第一行条目名称
void print_one(list N,int number)
{
    if(number==1)
    {
        printf("%-9s%-3s%-3s%-12s%-7s\n","姓名","年龄","性别","电话","邮编");
    }
    printf("%-9s%-3s%-3s%-12s%-7s\n",N->name,N->age,N->sex,N->phone,N->yb);
}

//显示一页，page为页数-
void print_list_one_page(list L,int page)
{
    int i;
    int page_to_num=(page-1)*NPAGE+1;
    for(i=0;i<page_to_num&&L!=NULL;i++)
    {
        L=L->next;
    }
    for(i= page_to_num;i< page_to_num+NPAGE&&L!=NULL;i++)
    {
        print_one(L,1+i-page_to_num);
        L=L->next;
    }
}

//排序
void sort_list(list L)
{
    int i,rule,flag;
    int len=len_list(L);
    printf("输入两个数字选择排序方式和正倒序，两个数字用空格隔开\n1-姓名, 2-年龄, 3-性别, 4-电话, 5-邮编  \n1-正序, 2-倒序\n");
    scanf("%d %d",&rule,&flag);
    rst_stdin();
    L=L->next;
    //冒泡排序
    for(i=len-1;i>0;i--)
    {
        list m=L;
        int j=0;
        for(;j<i;j++,m=m->next)
        {
            char *tmp1,*tmp2;
            switch(rule)
            {
                case 1:tmp1=m->name;tmp2=m->next->name;break;
                case 2:tmp1=m->age;tmp2=m->next->age;break;
                case 3:tmp1=m->sex;tmp2=m->next->sex;break;
                case 4:tmp1=m->phone;tmp2=m->next->phone;break;
                case 5:tmp1=m->yb;tmp2=m->next->yb;break;

            }
            if(rule==2)
            {
               if((flag==1 && atof(tmp1)>atof(tmp2)) || (flag==2 && atof(tmp1)<atof(tmp2)))
                {
                    swap_node(m,m->next);
                }
            }
            else
            {
                if((flag==1 && strcmp(tmp1,tmp2)>0) || (flag==2 && strcmp(tmp1,tmp2)<0))
                {
                    swap_node(m,m->next);
                }
            }
        }
    }
}

//查找
void serch_list(list L)
{
    int rule,flag,num=0;
    char target[50];
    printf("输入两个数字，第一个选择在哪查找，第二个选择精确还是模糊，两个数字用空格隔开\n1-姓名, 2-年龄, 3-性别, 4-电话, 5-邮编  \n1-精确，2-模糊\n");
    scanf(" %d %d",&rule,&flag);
    printf("请输入关键字:\n");
    scanf(" %s",target);rst_stdin();
    puts("查找结果:\n");
    for(L=L->next;L!=NULL;L=L->next)
    {
        char *tmp;
        switch(rule)
        {
            case 1:tmp=L->name;break;
            case 2:tmp=L->age;break;
            case 3:tmp=L->sex;break;
            case 4:tmp=L->phone;break;
            case 5:tmp=L->yb;break;
        }
        if((flag==1 && strcmp(tmp,target)==0) || (flag==2 && strstr(tmp,target)!=NULL))
        {
            print_one(L,++num);
        }
    }
    printf("\n找到 %d 条，任意键退出",num);
    getch();
}

//从姓名中查找值为target参数的节点，并返回节点，供删除函数使用
list serch_list_froms1(list s,const char *target)
{
    for(s=s->next;s!=NULL;s=s->next)
    {
        if(strcmp(target,s->name)==0)
        {
            return s;
        }
    }
    return NULL;
}

//删除
void delete_list_menu(list L)
{
    char target[50];
    list s;
    int flag_suc=0;
    puts("请输入你想删除的信息的姓名");
    scanf("%s",target);rst_stdin();
    if((s=serch_list_froms1(L,target))!=NULL)
    {
        delete_list(L,s);
        flag_suc=1;
    }
    if(flag_suc==1)printf("删除成功,任意键返回");
    else printf("未找到对应项目，请检查数据和你的输入,任意键返回");
    getch();
}

//更新
void update_list_menu(list L)
{
    char target[50];
    list s;
    int flag_suc=0,what;
    puts("请输入将要修改的姓名");
    scanf("%s",target);rst_stdin();
    puts("你想修改哪项信息：\n1-姓名, 2-年龄, 3-性别, 4-电话, 5-邮编  ，0-所有");
    scanf("%d",&what);rst_stdin();
    if((s=serch_list_froms1(L,target))!=NULL)
    {
        init_data(s,what);
        flag_suc=1;
    }
    if(flag_suc==0){printf("未找到对应项目，请检查数据和你的输入,任意键返回");getch();}
}

//查看列表
void print_list(list L)
{
    int page=1;
    char ch;
    int max_page=len_list(L)/NPAGE+(len_list(L)%NPAGE==0?0:1);
    for(;;)
    {
        CLS;
        //头列标记
        print_list_one_page(L,page);
        printf("\n==第 %d 页",page);
        if(page==max_page)printf("，尾页");
        printf("==\n");
        printf("使用“-”和“=”翻页，“s”排序，“0”回到主菜单\n");
        ch=getch();
        switch(ch)
        {
        case '-':
            if(page>1)
                --page;
            break;
        case '=':
            if(page<max_page)
                ++page;
            break;
        case '0':
            return;
            break;
        case 's':
            sort_list(L);
            page=1;
            break;
        }
    }
}

//主菜单
void main_menu( void ) //函数：主菜单
{
    printf( "\n\t电话薄 \t\n" );
    printf( "*******************************\n\n" );
    printf( "    1、添加联系人\n" );
    printf( "    2、输出所有联系人\n" );
    printf( "    3、查找联系人\n" );
    printf( "    4、删除联系人\n" );
    printf( "    5、修改联系人信息\n" );
    printf( "    0、退出系统\n\n" );
    printf( "*******************************\n" );
    printf( "选择功能编号：" );
}
int main(void)
{
    int ch;
    list L=creat_list();
    init_from_file(L);
    for(;;)
    {
        CLS;
        main_menu();
        scanf("%d",&ch);
        rst_stdin();
        switch(ch)
        {
            case 1:
                CLS;
                insert_list(L);
                save_to_file(L);
                break;
            case 2:
                CLS;
                print_list(L);
                break;
            case 3:
                CLS;
                serch_list(L);
                break;
            case 4:
                CLS;
                delete_list_menu(L);
                save_to_file(L);
                break;
            case 5:
                CLS;
                update_list_menu(L);
                save_to_file(L);
                break;
            case 0:
                save_to_file(L);
                return 0;
          }
    }
    return 0;
}
