#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conf.h"
FILE *FP;
extern struct config myconfig;
int make_code(char *target)
{
FP=fopen(target,"w+");
if(FP==NULL)
{
    printf("�޷������ļ� %s,�˳�",target);
    getchar();
    return 0;
}
fprintf(FP,"\
/***\n\
Automatic generation by make_admin_sys\n\
@author : veekxt@gmail.com\n\
***/\n\
");
//ͷ�ļ���һЩ��####################################
fprintf(FP,"\
#include <stdio.h>\n\
#include <stdlib.h>\n\
#include <string.h>\n\
#include <conio.h>  //if linux should be #include <curses.h>\n\
#define CLS system(\"cls\")    //windows cmd����\n\
int NPAGE=%d;                //ÿһҳ��ʾ����\n\
//��ջ�����,Ҳ���������������ַ�������������һ�εġ������������\n\
#define rst_stdin(); \\\n\
{\\\n\
    char c;\\\n\
    while(( c= getchar()) != '\\n' && c!= EOF);\\\n\
}\n\
//������������һ�������Ǳ�������\n\
#define \\\n\
swap(type_t,a,b) \\\n\
{type_t tmp_s_w_a_p_h_ = (a);\\\n\
(a)=(b);\\\n\
(b)=tmp_s_w_a_p_h_;\\\n\
}\n\
\n\
",myconfig.npage);
//�ṹ��#######################################
fprintf(FP,"\
typedef struct node_s_t\n\
{\n\
");
for(int i=0;i<myconfig.form_max;i++)
{
    fprintf(FP,"    char %s[%d];\n",myconfig.form_n[i].name_e,1+myconfig.form_n[i].len);
}
fprintf(FP,"\
    struct node_s_t *next;\n\
}list_s,*list;\n\
");
//��ʼ�����ݵķ���
fprintf(FP,"\
//���ݳ�ʼ������\n\
void init_data(list N,int what)\n\
{\n\
    switch(what)\n\
    {\n\
");
fprintf(FP,"\
    case 0:\n\
");
for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,"\
        printf(\"������%s:\");\n\
        scanf(\"%%s\",N->%s);\n\
        rst_stdin();\n\
",myconfig.form_n[i].name_c,myconfig.form_n[i].name_e);
}
fprintf(FP,"\
        printf(\"¼��ɹ���,�������������\");\n\
        getch();\n\
        break;\n\
");
for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,"\
    case %d:\n\
        printf(\"������%s:\");\n\
        scanf(\"%%s\",N->%s);\n\
        rst_stdin();\n\
        printf(\"¼��ɹ���,�������������\");\n\
        getch();\n\
    break;\n\
",1+i,myconfig.form_n[i].name_c,myconfig.form_n[i].name_e);
}
fprintf(FP,"\
    }\n\
}\n\
");
//һЩͨ�÷���###########################################
fprintf(FP,"\
//�ж��Ƿ�Ϊ��\n\
int is_null(list L)\n\
{\n\
    return ((L->next==NULL)?1:0);\n\
}\n\
//�½�һ��������-\n\
list creat_list(void)\n\
{\n\
    list newlist = (list)malloc(sizeof(struct node_s_t));\n\
    newlist->next=NULL;\n\
    return newlist;\n\
}\n\
//��������-\n\
int len_list(list L)\n\
{\n\
    int len=0;\n\
    while(L->next!=NULL)\n\
    {\n\
        len++;\n\
        L=L->next;\n\
    }\n\
    return len;\n\
}\n\
//���������ڵ�-\n\
void swap_node(list a,list b)\n\
{\n\
    swap(list_s,*a,*b);\n\
    swap(list,a->next,b->next);\n\
}\n\
\n\
//β������һ���ڵ�-\n\
list insert_list(list L)\n\
{\n\
    list newlist = (list)malloc(sizeof(struct node_s_t));\n\
    while(L->next!=NULL)\n\
    {\n\
        L=L->next;\n\
    }\n\
    L->next=newlist;\n\
    newlist->next=NULL;\n\
    init_data(newlist,0);\n\
    return newlist;\n\
}\n\
\n\
//ɾ����L:��ͷ��N:Ҫɾ���Ľڵ�-\n\
void delete_list(list L,list N)\n\
{\n\
    while(L->next!=NULL)\n\
    {\n\
        if(L->next==N)\n\
        {\n\
            L->next=L->next->next;\n\
            free(N);\n\
            break;\n\
        }\n\
        L=L->next;\n\
    }\n\
}\n\
\n\
//���浽�ļ�-\n\
int save_to_file( list L )\n\
{\n\
\n\
    FILE * F = fopen( \"./list.dat\", \"wb\" ); //���ļ�\n\
    L = L->next;\n\
    if(F==NULL){puts(\"�ļ�����ʧ�ܣ�\");return 0;}\n\
    while( L != NULL )\n\
    {\n\
        fwrite( L, sizeof( list_s ), 1, F ); //д��\n\
        L = L->next;\n\
    }\n\
    fclose( F );\n\
    return 1;\n\
}\n\
\n\
//���ļ�����-\n\
void init_from_file( list L )\n\
{\n\
    list newn;\n\
    FILE *F;\n\
    if( ( F = fopen( \"./list.dat\", \"rb\" ) ) == NULL )\n\
    {\n\
        puts( \"�ļ�����ʧ�ܣ�\" );\n\
        return ;\n\
    }\n\
    while( 1 )\n\
    {\n\
        newn = ( list )malloc( sizeof( list_s ) );\n\
        fread( newn, sizeof( list_s ), 1, F );\n\
        if(feof( F ) != 0)break;\n\
        newn->next = NULL;\n\
        L->next=newn;\n\
        L=newn;\n\
    }\n\
    fclose( F );\n\
}\n\
");
//�ڵ����
fprintf(FP,"\n\
//��ʾһ������һ������ϵ�һ����Ŀ����\n\
void print_one(list N,int number)\n\
{\n\
    if(number==1)\n\
    {\n\
");
//nuber��һ����ʾ��һ����Ϣ
fprintf(FP,"        printf(\"");
for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,"%%-%ds",myconfig.form_n[i].len+1);
}

if(myconfig.k_is_pingjun>0)fprintf(FP,"%%-%ds",myconfig.len_pingjun+1);
if(myconfig.k_is_add>0)fprintf(FP,"%%-%ds",myconfig.len_add+1);

fprintf(FP,"\\n\"");
for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,",\"%s\"",myconfig.form_n[i].name_c);
}
if(myconfig.k_is_pingjun>0)fprintf(FP,",\"%s\"",myconfig.s_is_pingjun);
if(myconfig.k_is_add>0)fprintf(FP,",\"%d\"",myconfig.k_is_add);
fprintf(FP,");\n");

fprintf(FP,"\
    }\n\
");
//������printf("%-10s%-10s%-10s\n",number,N->name,N->xuehao,N->shuxue);
fprintf(FP,"    printf(\"");
//����%-5d%-10s%-10s%-10s
for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,"%%-%ds",myconfig.form_n[i].len+1);
}

if(myconfig.k_is_pingjun>0)fprintf(FP,"%%-%d.%df",myconfig.len_pingjun+1,myconfig.per_pingjun);
if(myconfig.k_is_add>0)fprintf(FP,"%%-%d.%df",myconfig.len_add+1,myconfig.per_add);

fprintf(FP,"\\n\"");
//����,number,N->name,N->xuehao,N->shuxue
for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,",N->%s",myconfig.form_n[i].name_e);
}
if(myconfig.k_is_pingjun>0)
{
    fprintf(FP,",");
    for(int i=0;i<myconfig.k_is_pingjun;i++)
    {
        char *tmp="+";
        if(i==0)fprintf(FP,"(");
        if(i==myconfig.k_is_pingjun-1)tmp="";
        fprintf(FP,"atof(N->%s)%s",myconfig.form_n[myconfig.is_pingjun[i]-1].name_e,tmp);
    }
    fprintf(FP,")/%d",myconfig.k_is_pingjun);
}

if(myconfig.k_is_add>0)
{
    fprintf(FP,",");
    for(int i=0;i<myconfig.k_is_add;i++)
    {
        char *tmp="+";
        if(i==0)fprintf(FP,"(");
        if(i==myconfig.k_is_add-1)tmp="";
        fprintf(FP,"atof(N->%s)%s",myconfig.form_n[myconfig.is_add[i]-1].name_e,tmp);
    }
    fprintf(FP,")");
}


fprintf(FP,");\n");
fprintf(FP,"\
}\n\
");
//��ʾ
fprintf(FP,"\n\
//��ʾһҳ��pageΪҳ��-\n\
void print_list_one_page(list L,int page)\n\
{\n\
    int i;\n\
    int page_to_num=(page-1)*NPAGE+1;\n\
    for(i=0;i<page_to_num&&L!=NULL;i++)\n\
    {\n\
        L=L->next;\n\
    }\n\
    for(i= page_to_num;i< page_to_num+NPAGE&&L!=NULL;i++)\n\
    {\n\
        print_one(L,1+i-page_to_num);\n\
        L=L->next;\n\
    }\n\
}\n\
");


fprintf(FP,"\n\
//����\n\
void sort_list(list L)\n\
{\n\
    int i,rule,flag;\n\
    int len=len_list(L);\n\
    printf(\"������������ѡ������ʽ�����������������ÿո����\\n\
");

for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,"%d-%s%c ",i+1,myconfig.form_n[i].name_c,(i==(myconfig.form_max-1))?' ':',');
}

int rule_c=myconfig.form_max;
/*
if(myconfig.k_is_pingjun>0)
{
    rule_c++;
    fprintf(FP,",%d-%s",rule_c,myconfig.s_is_pingjun);
}
*/
if(myconfig.k_is_add>0)
{
    rule_c++;
    fprintf(FP,",%d-%s",rule_c,myconfig.s_is_add);
}


fprintf(FP,"\
\\n1-����, 2-����\\n\");\n\
    scanf(\"%%d %%d\",&rule,&flag);\n\
    rst_stdin();\n\
    L=L->next;\n\
    //ð������\n\
    for(i=len-1;i>0;i--)\n\
    {\n\
        list m=L;\n\
        int j=0;\n\
        for(;j<i;j++,m=m->next)\n\
        {\n\
            char *tmp1,*tmp2;\n\
            switch(rule)\n\
            {\n\
");

for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,"                case %d:tmp1=m->%s;tmp2=m->next->%s;break;\n",i+1,myconfig.form_n[i].name_e,myconfig.form_n[i].name_e);
}
if(myconfig.k_is_add>0)
{
    fprintf(FP,"                case %d:\n\
                {\n\
                    char a_s[40],b_s[40];\n\
                    double a=\
",1+myconfig.form_max);

    for(int i=0;i<myconfig.k_is_add;i++)
    {
        char *tmp="+";
        if(i==0)fprintf(FP,"(");
        if(i==myconfig.k_is_add-1)tmp="";
        fprintf(FP,"atof(m->%s)%s",myconfig.form_n[myconfig.is_add[i]-1].name_e,tmp);
    }
    fprintf(FP,");\n\
                    double b=");
    for(int i=0;i<myconfig.k_is_add;i++)
    {
        char *tmp="+";
        if(i==0)fprintf(FP,"(");
        if(i==myconfig.k_is_add-1)tmp="";
        fprintf(FP,"atof(m->next->%s)%s",myconfig.form_n[myconfig.is_add[i]-1].name_e,tmp);
    }
    fprintf(FP,");\n");
    fprintf(FP,"\
                    sprintf(a_s,\"%%f\",a);\n\
                    sprintf(b_s,\"%%f\",b);\n\
                    tmp1=a_s;tmp2=b_s;\n\
                }\
");

}


fprintf(FP,"\n\
            }\n            if(");
int flag_first=1;
for(int i=0;i<myconfig.form_max;++i)
{
    if(myconfig.form_n[i].type=='n')
    {
        fprintf(FP,"%srule==%d",(flag_first==1?"":"||"),i+1);
        if(flag_first==1)flag_first=0;
    }
}

int rule_e=myconfig.form_max;
/*
if(myconfig.k_is_pingjun>0)
{
    rule_e++;
    fprintf(FP,"||rule==%d",rule_e);
}
*/
if(myconfig.k_is_add>0)
{
    rule_e++;
    fprintf(FP,"||rule==%d",rule_e);
}


fprintf(FP,")\n\
            {\n\
               if((flag==1 && atof(tmp1)>atof(tmp2)) || (flag==2 && atof(tmp1)<atof(tmp2)))\n\
                {\n\
                    swap_node(m,m->next);\n\
                }\n\
            }\n\
            else\n\
            {\n\
                if((flag==1 && strcmp(tmp1,tmp2)>0) || (flag==2 && strcmp(tmp1,tmp2)<0))\n\
                {\n\
                    swap_node(m,m->next);\n\
                }\n\
            }\n\
        }\n\
    }\n\
}\n\
");
fprintf(FP,"\n\
//����\n\
void serch_list(list L)\n\
{\n\
    int rule,flag,num=0;\n\
    char target[50];\n\
    printf(\"�����������֣���һ��ѡ�����Ĳ��ң��ڶ���ѡ��ȷ����ģ�������������ÿո����\\n\
");

for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,"%d-%s%c ",i+1,myconfig.form_n[i].name_c,(i==(myconfig.form_max-1))?' ':',');
}
fprintf(FP,"\
\\n1-��ȷ��2-ģ��\\n\");\n\
    scanf(\" %%d %%d\",&rule,&flag);\n\
    printf(\"������ؼ���:\\n\");\n\
    scanf(\" %%s\",target);rst_stdin();\n\
    puts(\"���ҽ��:\\n\");\n\
    for(L=L->next;L!=NULL;L=L->next)\n\
    {\n\
        char *tmp;\n\
        switch(rule)\n\
        {\n\
");


for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,"            case %d:tmp=L->%s;break;\n",i+1,myconfig.form_n[i].name_e);
}

fprintf(FP,"\
        }\n\
        if((flag==1 && strcmp(tmp,target)==0) || (flag==2 && strstr(tmp,target)!=NULL))\n\
        {\n\
");

fprintf(FP,"\
            print_one(L,++num);\n\
        }\n\
    }\n\
    printf(\"\\n�ҵ� %%d ����������˳�\",num);\n\
    getch();\n\
}\n\
");

fprintf(FP,"\n\
//��%s�в���ֵΪtarget�����Ľڵ㣬�����ؽڵ㣬��ɾ������ʹ��\n\
list serch_list_froms1(list s,const char *target)\n\
{\n\
    for(s=s->next;s!=NULL;s=s->next)\n\
    {\n\
        if(strcmp(target,s->%s)==0)\n\
        {\n\
            return s;\n\
        }\n\
    }\n\
    return NULL;\n\
}\n\
",myconfig.form_n[0].name_c,myconfig.form_n[0].name_e);



fprintf(FP,"\n\
//ɾ��\n\
void delete_list_menu(list L)\n\
{\n\
    char target[50];\n\
    list s;\n\
    int flag_suc=0;\n\
    puts(\"����������ɾ������Ϣ��%s\");\n\
    scanf(\"%%s\",target);rst_stdin();\n\
    if((s=serch_list_froms1(L,target))!=NULL)\n\
    {\n\
        delete_list(L,s);\n\
        flag_suc=1;\n\
    }\n\
    if(flag_suc==1)printf(\"ɾ���ɹ�,���������\");\n\
    else printf(\"δ�ҵ���Ӧ��Ŀ���������ݺ��������,���������\");\n\
    getch();\n\
}\n\
",myconfig.form_n[0].name_c);

fprintf(FP,"\n\
//����\n\
void update_list_menu(list L)\n\
{\n\
    char target[50];\n\
    list s;\n\
    int flag_suc=0,what;\n\
    puts(\"�����뽫Ҫ�޸ĵ�%s\");\n\
    scanf(\"%%s\",target);rst_stdin();\n\
    puts(\"�����޸�������Ϣ��\\n\
",myconfig.form_n[0].name_c);


for(int i=0;i<myconfig.form_max;++i)
{
    fprintf(FP,"%d-%s%c ",i+1,myconfig.form_n[i].name_c,(i==(myconfig.form_max-1))?' ':',');
}

fprintf(FP,"\
��0-����\");\n\
    scanf(\"%%d\",&what);rst_stdin();\n\
    if((s=serch_list_froms1(L,target))!=NULL)\n\
    {\n\
        init_data(s,what);\n\
        flag_suc=1;\n\
    }\n\
    if(flag_suc==0){printf(\"δ�ҵ���Ӧ��Ŀ���������ݺ��������,���������\");getch();}\n\
}\n\
");


fprintf(FP,"\n\
//�鿴�б�\n\
void print_list(list L)\n\
{\n\
    int page=1;\n\
    char ch;\n\
    int max_page=len_list(L)/NPAGE+(len_list(L)%NPAGE==0?0:1);\n\
    for(;;)\n\
    {\n\
        CLS;\n\
        //ͷ�б��\n\
        print_list_one_page(L,page);\n\
        printf(\"\\n==�� %%d ҳ\",page);\n\
        if(page==max_page)printf(\"��βҳ\");\n\
        printf(\"==\\n\");\n\
        printf(\"ʹ�á�-���͡�=����ҳ����s�����򣬡�0���ص����˵�\\n\");\n\
        ch=getch();\n\
        switch(ch)\n\
        {\n\
        case '-':\n\
            if(page>1)\n\
                --page;\n\
            break;\n\
        case '=':\n\
            if(page<max_page)\n\
                ++page;\n\
            break;\n\
        case '0':\n\
            return;\n\
            break;\n\
        case 's':\n\
            sort_list(L);\n\
            page=1;\n\
            break;\n\
        }\n\
    }\n\
}\n\
");

//���˵�
fprintf(FP,"\n\
//���˵�\n\
void main_menu( void ) //���������˵�\n\
{\n\
    printf( \"\\n\\t%s \\t\\n\" );\n\
    printf( \"*******************************\\n\\n\" );\n\
    printf( \"    1��%s\\n\" );\n\
    printf( \"    2��%s\\n\" );\n\
    printf( \"    3��%s\\n\" );\n\
    printf( \"    4��%s\\n\" );\n\
    printf( \"    5��%s\\n\" );\n\
",myconfig.maintitle,myconfig.add,myconfig.print,myconfig.serch,myconfig.delete,myconfig.update);
if(myconfig.is_cal[0]!=0)
{
fprintf(FP,"\
    printf( \"    6��%s\\n\" );\n\
",myconfig.is_cal);
}
fprintf(FP,"\
    printf( \"    0��%s\\n\\n\" );\n\
    printf( \"*******************************\\n\" );\n\
    printf( \"ѡ���ܱ�ţ�\" );\n\
}\n\
",myconfig.exit);

//������
fprintf(FP,"\
int main(void)\n\
{\n\
    int ch;\n\
    list L=creat_list();\n\
    init_from_file(L);\n\
    for(;;)\n\
    {\n\
        CLS;\n\
        main_menu();\n\
        scanf(\"%%d\",&ch);\n\
        rst_stdin();\n\
        switch(ch)\n\
        {\n\
            case 1:\n\
                CLS;\n\
                insert_list(L);\n\
                save_to_file(L);\n\
                break;\n\
            case 2:\n\
                CLS;\n\
                print_list(L);\n\
                break;\n\
            case 3:\n\
                CLS;\n\
                serch_list(L);\n\
                break;\n\
            case 4:\n\
                CLS;\n\
                delete_list_menu(L);\n\
                save_to_file(L);\n\
                break;\n\
            case 5:\n\
                CLS;\n\
                update_list_menu(L);\n\
                save_to_file(L);\n\
                break;\n\
            case 0:\n\
                save_to_file(L);\n\
                return 0;\n\
          }\n\
    }\n\
    return 0;\n\
}\n\
");
fclose(FP);
printf("������ %s \n",target);
return 1;
}
//ͳ�ƣ� ����%d����¼��int���͵�ƽ��ֵ��ƽ��&&������
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        read_all(argv[1]);
        if(make_code("sysmain.c")==0);
    }
    else
    {
        printf("δʹ�ò������������ʹ�õ�ǰĿ¼��config.txt\n");
        read_all("config.txt");
        make_code("sysmain.c");
        puts("������˳�");
        getchar();
        return 0;
    }
}
