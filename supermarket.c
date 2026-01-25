#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int count2 = 9;
struct goods{
    char name[20];
    float price;
    int num;
};
int match(char goods[],struct goods* goodarr,int count2,int goodnum){
    int result = 1;
    for(int i = 0;i < count2;i++){
        if(strcmp(goods,goodarr[i].name) == 0){
            goodarr[i].num+=goodnum;
            result = 0;
            return 1;
            break;
        }
    }
    if(result){
        printf("没有此商品\n");
    }
}
void matchname(char goods[],struct goods* goodarr,int count2){
    for (int i = 0;i < count2;i++){
    if(strcmp(goods,goodarr[i].name) == 0){
            printf("%s的价格是%.1f\n",goodarr[i].name,goodarr[i].price);
    }
}
}
void print(int count2,struct goods* goodarr){
    printf("商品名  价格  数量\n");
    for(int i = 0;i < count2; i++ ){
        if(goodarr[i].num != 0){
            printf("%s   %.1f   %d\n",goodarr[i].name,goodarr[i].price,goodarr[i].num);
        }
    }
    float goodsum = 0;
    float temp = 0;
    for(int i = 0;i < count2; i++){
        temp = goodarr[i].num*goodarr[i].price;
        goodsum +=temp;
    }
    printf("您需要支付商品的总价是 %.1f\n",goodsum);
}
void supermarket(){
    int goods_num = 10;
    int cap = 9;
    //int count2 = 9;//通过这个进行计数
    //分配初始内存,使用的是malloc函数
    //要用到指向结构体的一个指针
    struct goods* goodarr = (struct goods*)malloc(sizeof(struct goods)*cap);
    //好习惯 检查内存分配是否成功
    if (goodarr == NULL){
        //
    }
    //定义一部分商品
    //goods的结构体数组
    struct goods temp[] = {
        {"bread",2.0,0},
        {"milk",3.0,0},
        {"instant noodles",5.0,0},
        {"mineral water",1.0,0},
        {"ham",1.5,0},
        {"liuliu candy",5.0,0},
        {"mint candy",10.0,0},
        {"dried tofu",1.0,0},
        {"spicy strips",0.5,0},
        {"tissue",1.0,0},
    };
    //将上面的添加到结构体指针中
    for(int i = 0; i < 9;i++){
        goodarr[i] = temp[i];
    }
    char input[10];
    scanf("%s",input);
    int clear;
        while((clear = getchar()) != '\n' && clear!= EOF);
    if (strcmp(input,"manager") == 0){
        //结构体数组的增长
    if (count2 == cap){
        struct goods *new = realloc(goodarr,2*sizeof(struct goods)*cap);
        //好习惯 检查内存是否成功分配
        if (new == NULL){
            //
        }
        //写入新的商品名称和价格
        printf("请输入新商品的名字\n");
        char new_good[20];
        fgets(new_good,sizeof(new_good),stdin);
        new_good[strcspn(new_good,"\n")] = '\0';
        while((clear = getchar()) != '\n' && clear!= EOF);
        float new_price = 0.0;
        printf("请输入新商品的价格\n");
        scanf("%f",&new_price);
        while((clear = getchar()) != '\n' && clear!= EOF);
        count2++;
        //还指针和空间变量
        cap = cap * 2;
        goodarr = new;
        strcmp(goodarr[count2].name,new_good);
        goodarr[count2].price = new_price;
        goodarr[count2].num = 0;
    }
    }else if (strcmp(input,"consumer") == 0){
        char goods[20];
        int goodnum = 0;
        int result = 0;
    while(1){
        goodnum = 0;
        printf("请输入您要购买的商品\n");
        printf("输入exit进入结算\n");
        char goods[20];
        fgets(goods,sizeof(goods),stdin);
        goods[strcspn(goods,"\n")] = '\0';
        matchname(goods,goodarr,count2);
        if(strcmp(goods,"exit") == 0){
            break;
        }
        result = match(goods,goodarr,count2,goodnum);
        if(result == 1){
        printf("请输入您要购买商品的数量\n");
        scanf("%d",&goodnum);
        while((clear = getchar()) != '\n' && clear!= EOF);
        match(goods,goodarr,count2,goodnum);
        }
        }
    }else{
        printf("别乱输入！\n");
    }
    print(count2,goodarr);
}
int main(){
    supermarket();
    return 0;
}