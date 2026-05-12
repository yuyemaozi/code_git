#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

//相应函数的定义
void Object_destroy(void *self)
{
    //由于传递的是指向结构体的空指针，无法访问结构体内部元素，这里进行转化
    Object *obj = self;
    //释放对应对象的内存
    if(obj) {
        if(obj->description) free(obj->description);
        free(obj);
    }
}

//打印对应对象内部的描述
void Object_describe(void *self)
{
    Object *obj = self;
    printf("%s.\n", obj->description);
}

int Object_init(void *self)
{
    // do nothing really
    return 1;
}

void *Object_move(void *self, Direction direction)
{
    printf("You can't go that direction.\n");
    return NULL;
}

int Object_attack(void *self, int damage)
{
    printf("You can't attack that.\n");
    return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
    // setup the default functions in case they aren't set
    //保证所生成的对象结构体内部的函数都接上对应函数，即使这个结构体不需要，要接上这个函数内部的函数
    if(!proto.init) proto.init = Object_init;
    if(!proto.describe) proto.describe = Object_describe;
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.attack) proto.attack = Object_attack;
    if(!proto.move) proto.move = Object_move;

    // this seems weird, but we can make a struct of one size,
    // then point a different pointer at it to "cast" it
    //为对应结构体申明内存，再将这个结构体复制过去
    Object *el = calloc(1, size);
    *el = proto;

    // copy the description over
    // 将这个对象的描述创建
    el->description = strdup(description);

    // initialize it with whatever init we were given
    if(!el->init(el)) {
        // looks like it didn't initialize properly
        el->destroy(el);
        return NULL;
    } else {
        // all done, we made an object of any type
        return el;
    }
}