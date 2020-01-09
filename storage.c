#include <stdio.h>
#define SIZE 5
typedef struct
{
        char name[20];
        char num[15];
        int age;
}student;
student stu[SIZE],buf[SIZE];


int main()
{
        FILE *fp;
        char filename[50],ch;
        printf("input your name, num, and age:\n");
        fscanf(stdin,"%s %s %d",&stu[0].name,&stu[0].num,&stu[0].age);

        printf("Please input your read filename:");
        scanf("%s",filename);
        if(!(fp=fopen(filename,"w")))
        {
                printf("Can not open %s",filename);
                return 1;
        }
        fprintf(fp,"name:%s num:%s age:%d",stu[0].name,stu[0].num,stu[0].age);
        fclose(fp);

        return 0;
}


