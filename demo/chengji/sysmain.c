/***
Automatic generation by make_admin_sys
@author : veekxt@gmail.com
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>  //if linux should be #include <curses.h>
#define CLS system("cls")    //windows cmd����
int NPAGE=6;                //ÿһҳ��ʾ����
//��ջ�����,Ҳ���������������ַ�������������һ�εġ������������
#define rst_stdin(); \
{\
    char c;\
    while(( c= getchar()) != '\n' && c!= EOF);\
}
//������������һ�������Ǳ�������
#define \
swap(type_t,a,b) \
{type_t tmp_s_w_a_p_h_ = (a);\
(a)=(b);\
(b)=tmp_s_w_a_p_h_;\
}

typedef struct node_s_t
{
    char num[11];
    char name[7];
    char Math[6];
    char Chinese[6];
    char English[6];
    struct node_s_t *next;
}list_s,*list;
//���ݳ�ʼ������
void init_data(list N,int what)
{
    switch(what)
    {
    case 0:
        printf("������ѧ��:");
        scanf("%s",N->num);
        rst_stdin();
        printf("����������:");
        scanf("%s",N->name);
        rst_stdin();
        printf("��������ѧ:");
        scanf("%s",N->Math);
        rst_stdin();
        printf("����������:");
        scanf("%s",N->Chinese);
        rst_stdin();
        printf("������Ӣ��:");
        scanf("%s",N->English);
        rst_stdin();
        printf("¼��ɹ���,�������������");
        getch();
        break;
    case 1:
        printf("������ѧ��:");
        scanf("%s",N->num);
        rst_stdin();
        printf("¼��ɹ���,�������������");
        getch();
    break;
    case 2:
        printf("����������:");
        scanf("%s",N->name);
        rst_stdin();
        printf("¼��ɹ���,�������������");
        getch();
    break;
    case 3:
        printf("��������ѧ:");
        scanf("%s",N->Math);
        rst_stdin();
        printf("¼��ɹ���,�������������");
        getch();
    break;
    case 4:
        printf("����������:");
        scanf("%s",N->Chinese);
        rst_stdin();
        printf("¼��ɹ���,�������������");
        getch();
    break;
    case 5:
        printf("������Ӣ��:");
        scanf("%s",N->English);
        rst_stdin();
        printf("¼��ɹ���,�������������");
        getch();
    break;
    }
}
//�ж��Ƿ�Ϊ��
int is_null(list L)
{
    return ((L->next==NULL)?1:0);
}
//�½�һ��������-
list creat_list(void)
{
    list newlist = (list)malloc(sizeof(struct node_s_t));
    newlist->next=NULL;
    return newlist;
}
//��������-
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
//���������ڵ�-
void swap_node(list a,list b)
{
    swap(list_s,*a,*b);
    swap(list,a->next,b->next);
}

//β������һ���ڵ�-
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

//ɾ����L:��ͷ��N:Ҫɾ���Ľڵ�-
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

//���浽�ļ�-
int save_to_file( list L )
{

    FILE * F = fopen( "./list.dat", "wb" ); //���ļ�
    L = L->next;
    if(F==NULL){puts("�ļ�����ʧ�ܣ�");return 0;}
    while( L != NULL )
    {
        fwrite( L, sizeof( list_s ), 1, F ); //д��
        L = L->next;
    }
    fclose( F );
    return 1;
}

//���ļ�����-
void init_from_file( list L )
{
    list newn;
    FILE *F;
    if( ( F = fopen( "./list.dat", "rb" ) ) == NULL )
    {
        puts( "�ļ�����ʧ�ܣ�" );
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

//��ʾһ������һ������ϵ�һ����Ŀ����
void print_one(list N,int number)
{
    if(number==1)
    {
        printf("%-11s%-7s%-6s%-6s%-6s%-7s%-6s\n","ѧ��","����","��ѧ","����","Ӣ��","ƽ����","3");
    }
    printf("%-11s%-7s%-6s%-6s%-6s%-7.0f%-6.0f\n",N->num,N->name,N->Math,N->Chinese,N->English,(atof(N->Math)+atof(N->Chinese)+atof(N->English))/3,(atof(N->Math)+atof(N->Chinese)+atof(N->English)));
}

//��ʾһҳ��pageΪҳ��-
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

//����
void sort_list(list L)
{
    int i,rule,flag;
    int len=len_list(L);
    printf("������������ѡ������ʽ�����������������ÿո����\n1-ѧ��, 2-����, 3-��ѧ, 4-����, 5-Ӣ��  ,6-�ܷ�\n1-����, 2-����\n");
    scanf("%d %d",&rule,&flag);
    rst_stdin();
    L=L->next;
    //ð������
    for(i=len-1;i>0;i--)
    {
        list m=L;
        int j=0;
        for(;j<i;j++,m=m->next)
        {
            char *tmp1,*tmp2;
            switch(rule)
            {
                case 1:tmp1=m->num;tmp2=m->next->num;break;
                case 2:tmp1=m->name;tmp2=m->next->name;break;
                case 3:tmp1=m->Math;tmp2=m->next->Math;break;
                case 4:tmp1=m->Chinese;tmp2=m->next->Chinese;break;
                case 5:tmp1=m->English;tmp2=m->next->English;break;
                case 6:
                {
                    char a_s[40],b_s[40];
                    double a=(atof(m->Math)+atof(m->Chinese)+atof(m->English));
                    double b=(atof(m->next->Math)+atof(m->next->Chinese)+atof(m->next->English));
                    sprintf(a_s,"%f",a);
                    sprintf(b_s,"%f",b);
                    tmp1=a_s;tmp2=b_s;
                }
            }
            if(rule==3||rule==4||rule==5||rule==6)
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

//����
void serch_list(list L)
{
    int rule,flag,num=0;
    char target[50];
    printf("�����������֣���һ��ѡ�����Ĳ��ң��ڶ���ѡ��ȷ����ģ�������������ÿո����\n1-ѧ��, 2-����, 3-��ѧ, 4-����, 5-Ӣ��  \n1-��ȷ��2-ģ��\n");
    scanf(" %d %d",&rule,&flag);
    printf("������ؼ���:\n");
    scanf(" %s",target);rst_stdin();
    puts("���ҽ��:\n");
    for(L=L->next;L!=NULL;L=L->next)
    {
        char *tmp;
        switch(rule)
        {
            case 1:tmp=L->num;break;
            case 2:tmp=L->name;break;
            case 3:tmp=L->Math;break;
            case 4:tmp=L->Chinese;break;
            case 5:tmp=L->English;break;
        }
        if((flag==1 && strcmp(tmp,target)==0) || (flag==2 && strstr(tmp,target)!=NULL))
        {
            print_one(L,++num);
        }
    }
    printf("\n�ҵ� %d ����������˳�",num);
    getch();
}

//��ѧ���в���ֵΪtarget�����Ľڵ㣬�����ؽڵ㣬��ɾ������ʹ��
list serch_list_froms1(list s,const char *target)
{
    for(s=s->next;s!=NULL;s=s->next)
    {
        if(strcmp(target,s->num)==0)
        {
            return s;
        }
    }
    return NULL;
}

//ɾ��
void delete_list_menu(list L)
{
    char target[50];
    list s;
    int flag_suc=0;
    puts("����������ɾ������Ϣ��ѧ��");
    scanf("%s",target);rst_stdin();
    if((s=serch_list_froms1(L,target))!=NULL)
    {
        delete_list(L,s);
        flag_suc=1;
    }
    if(flag_suc==1)printf("ɾ���ɹ�,���������");
    else printf("δ�ҵ���Ӧ��Ŀ���������ݺ��������,���������");
    getch();
}

//����
void update_list_menu(list L)
{
    char target[50];
    list s;
    int flag_suc=0,what;
    puts("�����뽫Ҫ�޸ĵ�ѧ��");
    scanf("%s",target);rst_stdin();
    puts("�����޸�������Ϣ��\n1-ѧ��, 2-����, 3-��ѧ, 4-����, 5-Ӣ��  ��0-����");
    scanf("%d",&what);rst_stdin();
    if((s=serch_list_froms1(L,target))!=NULL)
    {
        init_data(s,what);
        flag_suc=1;
    }
    if(flag_suc==0){printf("δ�ҵ���Ӧ��Ŀ���������ݺ��������,���������");getch();}
}

//�鿴�б�
void print_list(list L)
{
    int page=1;
    char ch;
    int max_page=len_list(L)/NPAGE+(len_list(L)%NPAGE==0?0:1);
    for(;;)
    {
        CLS;
        //ͷ�б��
        print_list_one_page(L,page);
        printf("\n==�� %d ҳ",page);
        if(page==max_page)printf("��βҳ");
        printf("==\n");
        printf("ʹ�á�-���͡�=����ҳ����s�����򣬡�0���ص����˵�\n");
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

//���˵�
void main_menu( void ) //���������˵�
{
    printf( "\n\t�ɼ�����ϵͳ \t\n" );
    printf( "*******************************\n\n" );
    printf( "    1�������Ϣ\n" );
    printf( "    2���������\n" );
    printf( "    3��������Ϣ\n" );
    printf( "    4��ɾ����Ϣ\n" );
    printf( "    5���޸���Ϣ\n" );
    printf( "    0���˳�ϵͳ\n\n" );
    printf( "*******************************\n" );
    printf( "ѡ���ܱ�ţ�" );
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
