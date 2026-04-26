#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
//定义结构体
struct Person {
    char *name;
    int age;
    int height;
    int weight;
};
//创建结构体内部的具体内容
struct Person *Person_create(char *name, int age, int height, int weight)
{
    //分配内存
    struct Person *who = (struct Person *)malloc(sizeof(struct Person));
    //判断who是否为空，空的话退出
    assert(who != NULL);
    //访问结构体内部的变量，并且更改
    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;
    //返回结构体指针
    return who;
}
//创建结构体数组：
struct Person people[2];

void Person_destroy(struct Person *who)
{
    assert(who != NULL);
    //释放内存，不过要先释放内部的指针
    free(who->name);
    //最后释放结构体本人
    free(who);
}

void Person_print(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person *joe = Person_create(
            "Joe Alex", 32, 64, 140);

    struct Person *frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // destroy them both so we clean up
    //joe = NULL;
    Person_destroy(joe);
    Person_destroy(frank);
    people[0].name = "Joe Alex";
    people[0].age = 32;
    people[0].height = 140;
    people[0].weight = 64;
    people[1].name = "Frank Blank";
    people[1].age = 20;
    people[1].height = 180;
    people[1].weight = 72;
    
    return 0;
}