#ifndef CONF_H_INCLUDED
#define CONF_H_INCLUDED
struct form
{
    int len;
    char name_c[50];
    char name_e[50];
    char type;
};

struct config
{
    int form_max;
    struct form *form_n;
    int npage;
    int wei;
    int k_is_pingjun;
    int k_is_add;
    int per_pingjun;
    int per_add;
    int is_pingjun[20];
    int is_add[20];
    int len_pingjun;
    int len_add;
    char s_is_pingjun[20];
    char s_is_add[20];
    char maintitle[50];
    char add[50];
    char print[50];
    char serch[50];
    char delete[50];
    char update[50];
    char is_cal[50];
    char exit[50];
};

struct config_s_t
{
    char arr[200];
    char zuo[100];
    char you[100];
};

void read_all(char *S);
void read_one(char *S,char *zuo,char *you);

#endif // CONF_H_INCLUDED
