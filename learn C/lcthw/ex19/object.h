#ifndef _object_h
#define _object_h

//ifndef和endif联合使用，意思是只要_object_h没有被定义过，就执行这之间的内容，进行结构体的定义和函数申明

//这是一个枚举变量
typedef enum {
    NORTH, SOUTH, EAST, WEST
} Direction;

//object结构体，面向对象编程，这个程序的所有对象的行为在这里
typedef struct {
    char *description;
    //解释一下为什么都是void类型的指针，因为有不同的结构体指针会传过来，在函数内部将指针进行类型转换
    int (*init)(void *self);
    void (*describe)(void *self);
    void (*destroy)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

//object.c中的函数的申明
int Object_init(void *self); //对象建立函数
void Object_destroy(void *self); //对象释放函数
void Object_describe(void *self); //对象描述函数，打印结构体中的char *description
void *Object_move(void *self, Direction direction); //对象移动函数
int Object_attack(void *self, int damage); //伤害函数
void *Object_new(size_t size, Object proto, char *description); //创建新对象的函数

//宏定义 NEW（T，N），会被转化为后面的内容，T和N相应替换
#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

#endif