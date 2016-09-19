#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_t
{
	int num;
	char name[20];
	float score;
	struct list_t* next;
}list,*plist;

plist insert_tail(plist h)
{
	int n;
	char na[20];
	float sc;
    FILE* fp;
    fp = fopen("stu_infor","r");
	while(fscanf(fp,"%d %s %f",&n,na,&sc) != EOF)
    {
    	plist p = (plist)malloc(sizeof(list));
		plist t = (plist)malloc(sizeof(list));
		for(t = h ; t->next != NULL; t = t->next)
		{
			;
		}
		p->num = n;
		strcpy(p->name,na);
		p->score = sc;
		t->next = p;
		p->next = NULL;
    }
	fclose(fp);
	return h;
}

plist insert_paixu(plist h,plist q,plist s)
{
	for(s = h ; s->next != 0 ; s = s->next)
	{
		if(s->next->num > q->num)
		{
			q->next = s->next;
			s->next = q;
			break;
		}
	}
	if(s->next == NULL)
	{
		s->next = q;
		q->next =NULL;
	}
	return h;
}

void file_printf(plist h)
{
	FILE* fp;
	fp = fopen("stu_infor","w");
    plist t = NULL;
    t = h;
    for(;t->next != NULL;t = t->next)
    {
       fprintf(fp,"%d %s %.2f\n",t->next->num,t->next->name,t->next->score);
    }
    fclose(fp);
}

int add_stuinfor()
{
	int k,i,xuehao;
    float cj;
    char xm[20];
    plist h = (plist)malloc(sizeof(list));
 	h = insert_tail(h);
    printf("请输入要增加的信息个数：\n");
    scanf("%d",&k);
    for(i = 0;i < k;i++)
    {
    	printf("请输入要增加的信息（学号 姓名 成绩）：\n");
 		scanf("%d %s %f",&xuehao ,xm,&cj);
        plist q = (plist)malloc(sizeof(list));
        plist s = (plist)malloc(sizeof(list));
        q->num = xuehao;
        strcpy(q->name,xm);
        q->score = cj;
		h = insert_paixu(h,q,s);
	 }
     file_printf(h);
}

int delete_stuinfor(int xuehao)
{
	int n;
    char na[20];
    float sc;
	plist h = (plist)malloc(sizeof(list));
    h = insert_tail(h);
    plist q = (plist)malloc(sizeof(list));
    q = h;
 	for(;q->next != NULL;q = q->next)
	{
        if(q->next->num == xuehao)
        {
        	plist r = NULL;
            r = q->next;
			q->next = r->next;
			r->next = NULL;
			free(r);
			break;
        }
     }
	 if((q != NULL) && (q->next == NULL))
	 {
			printf("查无此人！！\n");
			return -1;
	 }
     file_printf(h);
}

int change_stuinfor()
{
	int n,x,cn;
    char na[20];
    float sc,csc;
    int xuehao;
    char cna[20];
    plist h = (plist)malloc(sizeof(list));
    h = insert_tail(h);
    printf("请输入要修改信息的学号：\n");
    scanf("%d",&xuehao);
    printf("请选择修改信息项目：1.学号/2.姓名/3.成绩");
    scanf("%d",&x);
    plist q = (plist)malloc(sizeof(list));
    q = h;
    for(;q->next != NULL;q = q->next)
    {
            if(q->next->num == xuehao)
            {
                switch (x)
                {
                    case 1:
                    {
                        printf("请输入修改后的学号：\n");
                        scanf("%d",&cn);
                        q->next->num = cn;
						plist r = (plist)malloc(sizeof(list));
						plist s = (plist)malloc(sizeof(list));
						plist t = (plist)malloc(sizeof(list));
						t = q->next;
						r->num = t->num;
						strcpy(r->name,t->name);
						r->score = t->score;
						q->next = t->next;
						free(t);
						h = insert_paixu(h,r,t);
						break;
                    }
                    case 2:
                    {
                        printf("请输入修改后的姓名：\n");
                        scanf("%s",cna);
                        strcpy(q->next->name,cna);
                        break;
                    }
                    case 3:
                    {
                        printf("请输入修改后的成绩：\n");
                        scanf("%f",&csc);
                        q->next->score = csc;
                        break;
                    }
                }
                break;
            }
    }
    if((q != NULL) && (q->next == NULL))
    {
        printf("查无此人！！\n");
		return -1;
    }
    file_printf(h);
}

int refer_stuinfor()
{
 	int n,i;
    char na[20];
	char xingming[20];
    float sc;
    int xuehao;
    plist h = (plist)malloc(sizeof(list));
    h = insert_tail(h);
	printf("请输入查询方式：1.学号/2.姓名\n");
	scanf("%d",&i);
	switch(i)
	{
		case 1:
		{
			printf("请输入要查询的学号：\n");
			scanf("%d",&xuehao);
			plist q = (plist)malloc(sizeof(list));
			q = h;
			for(;q->next != NULL;q = q->next)
			{
					if(q->next->num == xuehao)
					{
						printf("%d %s %f\n",q->next->num,q->next->name,q->next->score);
						break;
					}
			}
			if((q != NULL) && (q->next == NULL))
			{
				printf("查无此人！！\n");
			}
			break;
		}
		case 2:
		{	
			printf("请输入要查询的姓名：\n");
			scanf("%s",xingming);
			plist q = (plist)malloc(sizeof(list));
			q = h;
			for(;q->next != NULL;q = q->next)
			{
				if(strcmp(q->next->name,xingming) == 0)
				{
					printf("%d %s %f\n",q->next->num,q->next->name,q->next->score);
					break;
				}
			}
			if((q != NULL) && (q->next == NULL))
			{
				printf("查无此人！！\n");
			}
			break;
		}
	}
}

void printf_list()
{	
	int n,xuehao;
    char na[20];
    float sc;
    float sum = 0;
    int i = 0;
	float k = 0;
    float max = 0;
    float min;
    plist h = (plist)malloc(sizeof(list));
    h = insert_tail(h);
    plist q = (plist)malloc(sizeof(list));
    q = h;
    min = q->next->score;
    for( ; q->next != NULL ; q = q->next)
    {
        if(q->next->score > max)
        {
            max = q->next->score;
        }
        if(q->next->score < min)
        {
            min = q->next->score;
        }
		if(q->next->score >= 60)
		{
			k++;
		}
        sum = sum + q->next->score;
        i++;
        printf("%d %s %.2f\n",q->next->num,q->next->name,q->next->score);
    }
    printf("最高分为：%.2f\n",max);
    printf("最低分为：%.2f\n",min);
    printf("平均分为:%.2f\n",sum/i);
	printf("及格率为：%.2f\n",k/i);
	printf("\n");
}

int loading(int a)
{
	switch(a)
	{
		case 1:
		{
			char name[20];
			char pw[20];
			char np[20];
			int i = 0;
			printf("请输入用户名：\n");
			scanf("%s",name);
			printf("请输入密码：\n");
			scanf("%s",pw);
			strcat(name," ");
			strcat(name,pw);
			strcat(name,"\n");
			FILE* fp;
			fp = fopen("loading_teacher","r");
			if(fp == NULL)
			{
				return 0;
			}
			while(fgets(np,sizeof(np),fp) != NULL)
			{
				if(strcmp(name,np) != 0)
				{
					memset(np,0,sizeof(np));
					i++;	
					continue;
				}
				break;
			}
			fclose(fp);
			if( i == 5)
			{
				printf("输入的用户名或者密码有错误!!!\n");
				return 0;
			}
			printf("请输入操作指令：1.增加/2.删除/3.修改/4.查询\n");
			int b;
			scanf("%d",&b);
			switch(b)
			{
				case 1:
				{
					add_stuinfor();
					break;
				}
				case 2:
				{
					int xuehao;
					printf("请输入要删除的学号：\n");
      				scanf("%d",&xuehao);
					delete_stuinfor(xuehao);
					break;	
				}
				case 3:
				{
					change_stuinfor();
					break;
				}
				case 4:
				{
					refer_stuinfor();
					break;
				}
		  	}
			break;
		}
		case 2:
		{
			char name[20];
			int  mima;
			printf("请输入用户名：\n");
			scanf("%s",name);
			printf("请输入密码\n");
			scanf("%d",&mima);
			if(strcmp(name,"stuser") == 0 && mima == 123456)
			{
				refer_stuinfor();
			}
			else
				printf("通行证无效！！！\n");
			break;
		}				
	}			
}

int main()
{
	int a;
	char c;
	printf("请输入登录对象：1.老师/2.学生\n");
	scanf("%d",&a);
	printf("是否查询成绩水平：Y/N\n");
	c=getchar();
	c=getchar();
	if(c == 'Y' || c == 'y')
	{
		printf_list();
	}
	loading(a);			
	printf_list();
	return 0;
}
