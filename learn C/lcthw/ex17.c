#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//#define MAX_DATA 512
//#define MAX_ROWS 100
int MAX_DATA;
int MAX_ROWS;
//这是最基础的数据的结构体
struct Address {
    int id;
    //set的值变为1,说明已经创建数据,0表示没有初始化
    int set;
    char *name;
    char *email;
};

//结构体数组
struct Database {
    struct Address *rows;
    int SMAX_DATA;
    int SMAX_ROWS;
};

//另一个结构体，用来方便访问内容，只需要函数传递一个指针就可以。
//突然意识到不只这个作用，还有释放内存。
//而且函数返回值只能有一个，FILE和结构体的数据这能选择一个，但必须同时传递两个数据，所以用结构体数组来解决
struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn) {
    if (conn) {
        if (conn->db) {
            if (conn->db->rows) {
                for (int i = 0; i < MAX_ROWS; i++) {
                    free(conn->db->rows[i].name);
                    free(conn->db->rows[i].email);
                }
                free(conn->db->rows);
            }
            free(conn->db);
        }
        if (conn->file) fclose(conn->file);
        free(conn);
    }
}

//这个函数就是为了在程序无法正常继续向下执行的时候进行退出，但目前没有释放内存，不完善
void die(const char *message,struct Connection *conn)
{
    if(conn)    Database_close(conn);
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

//打印数据
void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

//从文件中加载数据
void Database_load(struct Connection *conn)
{
    fread(&MAX_DATA,sizeof(int),1,conn->file);
    fread(&MAX_ROWS,sizeof(int),1,conn->file);
    conn->db->SMAX_DATA = MAX_DATA;
    conn->db->SMAX_ROWS = MAX_ROWS;

    conn->db->rows = malloc(sizeof(struct Address) * MAX_ROWS);
    if(!conn->db->rows)     die("load rows failed",conn);
    for(int i = 0; i < MAX_ROWS;i++){
        struct Address *cur = &conn->db->rows[i];
        //判断是否成功加载数据
        if(!cur)    die("read file failed",conn);

        fread(&cur->id,sizeof(int),1,conn->file);
        fread(&cur->set,sizeof(int),1,conn->file);
        cur->name = malloc(sizeof(char)*MAX_DATA);
        fread(cur->name,sizeof(char)*MAX_DATA,1,conn->file);
        cur->email = malloc(sizeof(char)*MAX_DATA);
        fread(cur->email,sizeof(char)*MAX_DATA,1,conn->file);
        if(!cur->name || !cur->email)   die("name or email load failed",conn);
    }
}

//这个函数的作用就是打开文件，只不过要保证安全访问文件
struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error",conn);

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error",conn);

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    //文件指针安全判断
    if(!conn->file) die("Failed to open the file",conn);

    return conn;
}



void Database_write(struct Connection *conn)
{
    //重置指针
    rewind(conn->file);

    fwrite(&conn->db->SMAX_DATA, sizeof(int), 1, conn->file);
    fwrite(&conn->db->SMAX_ROWS,sizeof(int),1,conn->file);


    for(int i = 0; i < MAX_ROWS; i++){
        struct Address *cur = &conn->db->rows[i];
        if(!cur)    die("write file failed",conn);
        fwrite(&cur->id,sizeof(int),1,conn->file);
        fwrite(&cur->set,sizeof(int),1,conn->file);
        fwrite(cur->name,sizeof(char)*MAX_DATA,1,conn->file);
        fwrite(cur->email,sizeof(char)*MAX_DATA,1,conn->file);
    }


    int rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.",conn);
}

void Database_create(struct Connection *conn,int cMAX_DATA,int cMAX_ROWS)
{
    int i = 0;
    MAX_DATA = cMAX_DATA;
    MAX_ROWS = cMAX_ROWS;
    conn->db->SMAX_ROWS = cMAX_ROWS;
    conn->db->SMAX_DATA = cMAX_DATA;
    conn->db->rows = malloc(sizeof(struct Address) * MAX_ROWS);
    if (!conn->db->rows) die("row memory failed", conn);

    for (i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &conn->db->rows[i];
        cur->id = i;
        cur->set = 0;
        cur->name = malloc(sizeof(char)*MAX_DATA);
        cur->email = malloc(sizeof(char)*MAX_DATA);
        if (!cur->name || !cur->email) die("memory name or email failed", conn);
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    //方便后面操作，conn->db->rows[id]太长了
    struct Address *addr = &conn->db->rows[id];
    //判断是否已经创建email
    if(addr->set) die("Already set, delete it first",conn);
    //改为1,说明已经注册了
    addr->set = 1;
    //了解这里的bug,name可能大于MAX_DATA
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    if(res[MAX_DATA - 1] != '\0')   die("name too long",conn);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed",conn);

    res = strncpy(addr->email, email, MAX_DATA);
    if(res[MAX_DATA - 1] != '\0')   die("email too long",conn);
    if(!res) die("Email copy failed",conn);
}

//访问某个特定ID的数据
void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set",conn);
    }
}

void Database_delete(struct Connection *conn, int id) {
    struct Address *addr = &conn->db->rows[id];
    addr->set = 0;
    memset(addr->name, 0, MAX_DATA);
    memset(addr->email, 0, MAX_DATA);
}

void Database_find_name(struct Connection *conn,char *name){
    int a = 1;
    for(int i = 0; i < MAX_ROWS; i++){
        struct Address *addr = &conn->db->rows[i];
        if(strcmp(name,addr->name) == 0){
            Address_print(addr);
            a = 0;
        }
    }
    if(a)   printf("no matching name\n");
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        //通过set来判断数据是否存在
        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{   
    /*params是参数的意思。这里没什么，判断传递参数的数量，最少是3个，
    后面的[]里的内容是不同action会传递更多数量的参数*/
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]",NULL);

    //文件名字
    char *filename = argv[1];
    //程序需要做出的行为
    char action = argv[2][0];
    //打开文件
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    //防止越界访问
    //atoi是将字符串类型的数字转化为整数类型，方便后续比较
    if(argc > 3) id = atoi(argv[3]);
    //if(id >= MAX_ROWS) die("There's not that many records.",conn);

    switch(action) {
        case 'c':
            //创建一个基础文件，说白了就是初始化一个没有任何email的文件
            if(argc != 5)   die("需要MAX_DATA和MAX_ROWS",conn);
            Database_create(conn,atoi(argv[3]),atoi(argv[4]));
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get",conn);

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set",conn);

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete",conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        case 'f':
            Database_find_name(conn,argv[3]);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list",conn);
    }

    Database_close(conn);

    return 0;
}