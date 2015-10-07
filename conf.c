#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conf.h"

int is_all_space(char *S)
{
    //�����˴����ָ�룬��
    if(S==NULL)return 1;
    int len=strlen(S);
    int i=0;
    for(;i<len;i++)
    {
        if((S[i]!=' ')&&(S[i]!='\t'))break;
    }
    if(i==len)return 1;
    else return 0;
}

/*
�����ļ�����ʽ�磺

one : 12    #content
two : true

#��#��֮����ע�ͣ������
*/
struct config myconfig;
struct form con_form[20];

//��һ�ж�ȡ���Ժ�ֵ(S)�����Է���zuo��ֵ����you
void read_one(char *S,char *zuo,char *you)
{
    zuo[0]=you[0]=0;
    int len=strlen(S);
    int tmp=0;
    char *where=zuo;
    //����ַ���ȡ
    for(int i=0;i<len;i++)
    {
        //����ð��
        if(S[i]!=':')
        {
            //���Կհ׷�
            //if(S[i]==' '||S[i]=='\t')continue;
            //����ע��
            if(S[i]=='\n'|| S[i]=='#'|| S[i]=='\r')
            {
                where[tmp++]=0;
                break;
            }
            //������ȡ
            else
            where[tmp++]=S[i];
        }
        //��ð��
        else
        {
            //ð�ź�����ֵ����you�洢
            where[tmp++]=0;
            where=you;
            tmp=0;
        }
    }
    where[tmp++]=0;
}
//��ȡ�ļ������ó���
void read_all(char *S)
{
	FILE *f=fopen(S,"rb");
	if(f==NULL){printf("�����ļ���ȡ����,������˳�");getchar();exit(-1);}
    struct config_s_t x;
    myconfig.form_n=con_form;
    while(1)
    {
        //��ȡһ��
        fgets(x.arr,1000,f);
        if(feof(f)!=0)break;
        //��һ����ȡ
        read_one(x.arr,x.zuo,x.you);
        if(strcmp(x.zuo,"")==0 || x.you[0]==0)
		{
			continue;
		}
        //printf("\n���:--%s--\n�Ҷ�:--%s--",x.zuo,x.you);
        //�жϲ����ó���
        if(strcmp(x.zuo,"form")==0)
        {
            //char tmp[50]=x.you;
            char *tmp_c;
            tmp_c=strtok(x.you,",");
            int form_much=0;
            while(NULL!=tmp_c &&is_all_space(tmp_c)!=1)
            {
                sscanf(tmp_c,"%s %s %d %c",con_form[form_much].name_c,con_form[form_much].name_e,&con_form[form_much].len,&con_form[form_much].type);//myconfig.form_n[form_much].name_c,myconfig.form_n[form_much].name_e,&myconfig.form_n[form_much].len);
                form_much++;
                tmp_c=strtok(NULL,",");
            }
            myconfig.form_max=form_much;
        }
        else
        {
            if(is_all_space(x.you))x.you[0]='\0';
        }
        if(strcmp(x.zuo,"maintitle")==0)
        {
            sscanf(x.you,"%s",myconfig.maintitle);
        }
        else if(strcmp(x.zuo,"add")==0)
        {
            sscanf(x.you,"%s",myconfig.add);
        }
        else if(strcmp(x.zuo,"delete")==0)
        {
            sscanf(x.you,"%s",myconfig.delete);
        }
        else if(strcmp(x.zuo,"print")==0)
        {
            sscanf(x.you,"%s",myconfig.print);
        }
        else if(strcmp(x.zuo,"serch")==0)
        {
            sscanf(x.you,"%s",myconfig.serch);
        }
        else if(strcmp(x.zuo,"update")==0)
        {
            sscanf(x.you,"%s",myconfig.update);
        }
        else if(strcmp(x.zuo,"cal")==0)
        {
            sscanf(x.you,"%s",myconfig.is_cal);
        }
        else if(strcmp(x.zuo,"exit")==0)
        {
            sscanf(x.you,"%s",myconfig.exit);
        }
        else if(strcmp(x.zuo,"npage")==0)
        {
            sscanf(x.you,"%d",&myconfig.npage);
        }
        else if(strcmp(x.zuo,"s_is_pingjun")==0)
        {
            if(x.you[0]!=0)
            {
                sscanf(x.you,"%s %d %d",myconfig.s_is_pingjun,&myconfig.len_pingjun,&myconfig.per_pingjun);
            }
        }
        else if(strcmp(x.zuo,"s_is_add")==0)
        {
            if(x.you[0]!=0)
            {
                sscanf(x.you,"%s %d %d",myconfig.s_is_add,&myconfig.len_add,&myconfig.per_add);
            }
        }
        else if(strcmp(x.zuo,"is_pingjun")==0)
        {

            char *tmp=x.you;
            if(strcmp("",tmp)==0)
            {
                myconfig.k_is_pingjun=0;
                continue;
            }
            char *p=strtok(tmp,",");
            int n=0;
            myconfig.is_pingjun[n++]=atoi(p);
            for(;;)
            {
                p=strtok(NULL,",");
                if(p==NULL)break;
                myconfig.is_pingjun[n++]=atoi(p);
            }
            myconfig.k_is_pingjun=n;
        }
        else if(strcmp(x.zuo,"is_add")==0)
        {
            char *tmp=x.you;
            if(strcmp("",tmp)==0)
            {
                myconfig.k_is_add=0;
                continue;
            }
            char *p=strtok(tmp,",");
            int n=0;
            myconfig.is_add[n++]=atoi(p);
            for(;;)
            {
                p=strtok(NULL,",");
                if(p==NULL)break;
                myconfig.is_add[n++]=atoi(p);
            }
            myconfig.k_is_add=n;
        }
    }
}
