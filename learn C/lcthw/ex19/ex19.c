#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h"


void map_des(void *self){
    struct Map *map = self;
    if(map->location)   free(map->location);
    if(map->start)  free(map->start);
    if(map) free(map);
}


void room_des(void *self){
    struct Map *map = self;
    for(int i = 0; i < 4;i++){
        if(map->room[i])    free(map->room[i]);
    }
}


void monster_des(void *self){
    struct Map *map = self;
    for(int i = 0; i < 4; i++){
        if(map->room[i]->bad_guy)   free(map->room[i]->bad_guy);
    }
}

void die(char *message,struct Map *map){

    monster_des(map);
    room_des(map);
    map_des(map);

    if(errno){
        perror(message);
    }
    else{
        printf("%s\n",message);
    }

    exif(1);
}


int Monster_attack(void *self, int damage)
{
    Monster *monster = self;

    printf("You attack %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if(monster->hit_points > 0) {
        printf("It is still alive.\n");
        return 0;
    } else {
        printf("It is dead!\n");
        return 1;
    }
}

int Monster_init(void *self)
{
    Monster *monster = self;
    monster->hit_points = 10;
    return 1;
}

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};


void *Room_move(void *self, Direction direction)
{
    Room *room = self;
    Room *next = NULL;

    if(direction == NORTH && room->north) {
        printf("You go north, into:\n");
        next = room->north;
    } else if(direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
    } else if(direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
    } else if(direction == WEST && room->west) {
        printf("You go west, into:\n");
        next = room->west;
    } else {
        printf("You can't go that direction.");
        next = NULL;
    }

    if(next) {
        next->_(describe)(next);
    }

    return next;
}


int Room_attack(void *self, int damage)
{
    Room *room = self;
    Monster *monster = room->bad_guy;

    if(monster) {
        monster->_(attack)(monster, damage);
        return 1;
    } else {
        printf("You flail in the air at nothing. Idiot.\n");
        return 0;
    }
}


Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};


void *Map_move(void *self, Direction direction)
{
    Map *map = self;
    Room *location = map->location;
    Room *next = NULL;

    next = location->_(move)(location, direction);

    if(next) {
        map->location = next;
    }

    return next;
}

int Map_attack(void *self, int damage)
{
    Map* map = self;
    Room *location = map->location;

    return location->_(attack)(location, damage);
}


int Map_init(void *self)
{
    Map *map = self;

    // make some rooms for a small map
    //先创建房间
    Room *hall = NEW(Room, "The great Hall");
    if(!hall)   die("hall创建失败",map);
    map->room[0] = hall;
    Room *throne = NEW(Room, "The throne room");
    if(!throne) die("throne创建失败",map);
    map->room[1] = throne;
    Room *arena = NEW(Room, "The arena, with the minotaur");
    if(!arena)  die("arena创建失败",map);
    map->room[2] = arena;
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");
    if(!kitchen)    die("kitchen创建失败",map);
    map->room[3] = kitchen;

    // put the bad guy in the arena
    //创建怪物
    arena->bad_guy = NEW(Monster, "The evil minotaur");
    if(!arena->bad_guy) die("monster创建失败",map);
    // setup the map rooms
    //再将房间连接
    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;
    kitchen->west = throne;

    // start the map and the character off in the hall
    //设立开始房间
    map->start = hall;
    map->location = hall;

    return 1;
}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int process_input(Map *game)
{
    printf("\n> ");

    char ch = getchar();
    getchar();
    // eat ENTER
    //避免缓冲区出现问题

    int damage = rand() % 4;

    switch(ch) {
        case -1:
            //退出游戏
            printf("Giving up? You suck.\n");
            return 0;
            break;

        case 'n':
            //移动
            game->_(move)(game, NORTH);
            break;

        case 's':
            game->_(move)(game, SOUTH);
            break;

        case 'e':
            game->_(move)(game, EAST);
            break;

        case 'w':
            game->_(move)(game, WEST);
            break;

        case 'a':
            //攻击
            game->_(attack)(game, damage);
            break;
        case 'l':
            printf("You can go:\n");
            if(game->location->north) printf("NORTH\n");
            if(game->location->south) printf("SOUTH\n");
            if(game->location->east) printf("EAST\n");
            if(game->location->west) printf("WEST\n");
            break;

        default:
            //保证程序不会出现问题
            printf("What?: %d\n", ch);
    }
    //继续循环
    return 1;
}

int main(int argc, char *argv[])
{
    // simple way to setup the randomness
    srand(time(NULL));

    // make our map to work with
    
    Map *game = NEW(Map, "The Hall of the Minotaur.");
    if(!game)   die("地图创建失败",game);
    //这里成功创建了地图对象，内部调用了Map_init函数

    printf("You enter the ");
    game->location->_(describe)(game->location);

    //创建游戏之后运行
    while(process_input(game)) {}

    return 0;
}