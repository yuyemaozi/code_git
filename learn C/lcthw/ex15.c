#include <stdio.h>
void indexing_print(int *ages,char *names[],int count){
        for(int i = 0; i < count; i++) {
        printf("函数1: %s has %d years alive.\n",
                names[i], ages[i]);
    }
}
void cur_print(int count,int *cur_age,char **cur_name){
        for(int i = 0; i < count; i++) {
        printf("函数2: %s has %d years alive.\n",
                *(cur_name + i),*(cur_age + i));
    }
}
void cur_arr_print(int count,int *cur_age,char **cur_name){
    for(int i = 0; i < count; i++) {
        printf("函数3: %s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }
}
void stupid_print(int ages[],char *names[],int count){
    int *cur_age;
    char **cur_name;
        for(cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++)
    {
        printf("函数4:%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }
}
int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };
    

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for(i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }
    //逆循环
    for(i = count - 1; i >= 0; i--) {
        printf("逆序: %s has %d years alive.\n",
                names[i], ages[i]);
    }
    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;
    //指针：
    for(i = 0; i < count; i++) {
        printf("指针：%s has %d years alive.\n",
                *(cur_name + i),*(cur_age + i));
    }

    printf("---\n");


    // second way using pointers
    for(i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }
    //逆循环
    for(i = 0,cur_age = &ages[4],cur_name = &names[4]; i < count;i++){
        printf("序逆:%s is %d years old.\n",
                *(cur_name-i), *(cur_age-i));
    }
    //数组：
    for(i = 0;i < count;i++){
        printf("数组: %s is %d years old.\n",
                names[i],ages[i]);
    }

    printf("---\n");

    // third way, pointers are just arrays
    for(i = 0,cur_age = ages,cur_name = names; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }
    //逆循环
    for(i = count - 1;i >= 0;i--){
        printf("逆序: %s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stupid complex way
    for(cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }
    //逆循环
    for(cur_name = &names[4],cur_age = &ages[4];(cur_age - ages) >= 0;cur_name--,cur_age--){
        printf("逆序:%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }
    //尝试

    //cur_age = (int *)names;
    //printf("%s",*cur_age);

    //访问参数
        printf("方法1：\n");
        for (i = 1; i < argc; i++) {
            printf("argv[%d] = %s\n", i, argv[i]);
    }
        printf("方法2：\n");
        for (i = 1; i < argc; i++) {
            printf("argv[%d] = %s\n", i, *(argv + i));
        }
        char **cur_argv = &argv[1];
        printf("方法3：\n");
        for (i = 1; (cur_argv - argv) < argc; cur_argv++,i++){
            printf("argv[%d] = %s\n",i,*cur_argv);
        }
        //访问指针地址
        char **cur = names;
        for(i = 0; i < count;i++,cur++){
            printf("指针地址:%p\n",*cur);
        }
        cur_age = ages;
        cur_name = names;
        indexing_print(ages,names,count);
        cur_print(count,cur_age,cur_name);
        cur_arr_print(count,cur_age,cur_name);
        stupid_print(ages,names,count);
        //方法一：
        i = 0;
        while(i < count){
            printf("%s has %d years alive.\n",
                names[i], ages[i]);
                i++;
        }
        //方法二：
        i = 0;
        while(i < count){
            printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
                i++;
        }
        //方法三:
        i = 0;
        cur_age = ages;
        cur_name = names;
        while(i < count){
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
                i++;
        }
        //方法四：
        while((cur_age - ages) < count){
            printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
            cur_name++;
            cur_age++;
        }
    return 0;
}