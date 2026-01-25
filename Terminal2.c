#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int count1 = 10;
int count2 = 10;
int goods_num = 10;
int cap = 10;
int clear;
int oddnumcap = 5;
int evennumcap = 5;
struct goods{
    char name[20];
    float price;
    int num;
};
struct goods* goodarr;
int match(char goods[],struct goods* goodarr,int count2,int goodnum){
    int result = 1;
    for(int i = 0;i < count2;i++){
        if(strcmp(goods,goodarr[i].name) == 0){
            goodarr[i].num+=goodnum;
            result = 0;
            return result;
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
	for (int i = 0; i < count2;i++){
		if(goodarr[i].num != 0){
			goodarr[i].num = 0;
		}
	}
}
int command(char arr[100]){
	//定义所有的指令
    char arr1[]="list";
    char arr2[]="help";
    char arr3[]="do exit";
    char arr4[]="do leap";
	char arr5[]="do multtable";
	char arr6[]="do searchnum";
	char arr7[]="do oddeven";
	char arr8[]="do manager";
	char arr9[]="do consumer";
	//对指令进行匹配
    if(strcmp(arr,arr4) == 0){
        return 1;
    }else if(strcmp(arr,arr5) == 0){
		return 2;
	}else if(strcmp(arr,arr6) == 0){
		return 3;
	}else if(strcmp(arr,arr3) == 0){
		return 0;
	}else if(strcmp(arr,arr2) == 0){
		return 5;
	}else if(strcmp(arr,arr7) == 0){
		return 4;
	}else if(strcmp(arr,arr1) == 0){
		return 6;
	}else if(strcmp(arr,arr8) == 0){
		return 7;
	}else if(strcmp(arr,arr9) == 0){
		return 8;
	}
	else {
		return 10;
	}
}
struct goods* sumpermaket(){
        //分配初始内存,使用的是malloc函数
        //要用到指向结构体的一个指针
        goodarr = (struct goods*)malloc(sizeof(struct goods)*cap);
        //好习惯 检查内存分配是否成功
        if (goodarr == NULL){
			char temp[] = {"exit"};
            command(temp);
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
    for(int i = 0; i < 10;i++){
        goodarr[i] = temp[i];
    }
	return goodarr;
}
void supermaketconsumer(){
	// struct goods* goodarr = sumpermaket();
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
        if(!result){
        printf("请输入您要购买商品的数量\n");
        scanf("%d",&goodnum);
        while((clear = getchar()) != '\n' && clear!= EOF);
        match(goods,goodarr,count2,goodnum);
        }
        }
		print(count2,goodarr);
}

int supermaketmanager(){
	if (count2 >= cap){
		int tempnum = 2*cap;
        struct goods *new = (struct goods*)realloc(goodarr,sizeof(struct goods)*tempnum);
        //好习惯 检查内存是否成功分配
        if (new == NULL){
			char temp[] = {"exit"};
            command(temp);
        }
		//还指针和空间变量
        cap = tempnum;
        goodarr = new;
	}
        //写入新的商品名称和价格
        printf("请输入新商品的名字\n");
        char new_good[20];
        fgets(new_good,sizeof(new_good),stdin);
        new_good[strcspn(new_good,"\n")] = '\0';
        //while((clear = getchar()) != '\n' && clear!= EOF);
        float new_price = 0.0;
        printf("请输入新商品的价格\n");
        scanf("%f",&new_price);
        while((clear = getchar()) != '\n' && clear!= EOF);
        count2++;
        //还指针和空间变量
        // cap = tempnum;
        // goodarr = new;
        strcpy(goodarr[count2 - 1].name,new_good);
        goodarr[count2 - 1].price = new_price;
        goodarr[count2 - 1].num = 0;
		//free(goodarr);
    }
//简单的两个数的交换
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
//冒泡排序
void paixu(int num[],int count) {
	for (int t = 0; t < count + 1; t++) {
		for (int i = 0; i < count - t - 1; i++) {
			//注意不能越界，所以要减去1
			if (num[i] > num[i + 1]) {
				swap(&num[i], &num[i + 1]);
			}
		}
	}
}
//闰年的判断
void panduan(int year) {
	int num1 = year % 100;
	if (num1 == 0) {
		num1 = year % 400;
		if (num1 == 0) {
			printf("%d是闰年\n", year);
		}
		else {
			printf("%d不是闰年\n", year);
		}
	}
	else {
		num1 = year % 4;
		if (num1 == 0) {
			printf("%d是闰年\n", year);
		}
		else {
			printf("%d不是闰年\n", year);

		}
	}
}
 void chengfabiao(int jiujiu) {
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= i; j++) {
				//制表符的作用
				printf("%d*%d=%d\t", j, i, i * j);
			}
			printf("\n");
		}
 }
 void search(int num[], int target) {
	 int m = 0;
	 printf("num = ");
	 for (int m = 0; m < 12; m++) {
		 printf("%d ", num[m]);
	 }
	 for (int i = 0; i < 11; i++) {
		 for (int t = 1; t + m < 12; t++) {
			//用t来处理重复取到一组数的问题
			 if (num[t + m] + num[i] == target) {
				 printf("\ntarget = %d\n", target);
				 printf("index : [%d %d]\n", t + m, i);
				 printf("%d + %d = %d\n", num[t + m], num[i], target);
				 break;
			 }
		 }
		 m++;
	 }
 }
 void odd_even(int numarr[]) {
	int *oddarr = NULL;
	int *evenarr = NULL;
	oddarr = (int*)malloc(5*sizeof(int));
	evenarr = (int*)malloc(5*sizeof(int));
	int oddnum[5];
	int evennum[5];
	free(oddarr);
	free(evenarr);
	int odd = 0;
	int even = 0;
	int t = 0;
	int m = 0;
	int n = 0;
	for (int i = 0; i < count1; i++) {
		if (numarr[i] % 2 == 0) {
				oddarr[t] = numarr[i];
				t++;
				odd++;
		}
		else {
			evenarr[m] = numarr[i];
			m++;
			even++;
		}
    
	}
	//用odd 和 even 还有 t 来将一个数组分成两个数组
	do{
	    paixu(oddarr,odd);
		paixu(evenarr,even);
    for(int i = 0;i<even;i++){
        printf("%d ",evenarr[i]);
    }
	for(int i = 0;i<odd;i++){
        printf("%d ",oddarr[i]);
    }
	if(oddnum >= oddnumcap){
		int *newoddarr = (int*)realloc(oddarr,sizeof(oddnum)*2);
		oddnumcap*=2; 
		oddarr = newoddarr;
	}
	if(evennum >= evennumcap){
		int *newevenarr = (int*)realloc(evenarr,sizeof(evennum)*2);
		evennumcap*=2;
		evenarr = newevenarr;
	}
	
	printf("\n输入0结束程序");
		scanf("%d",&n);
		while ((clear = getchar()) != '\n' && clear != EOF);
		if( n!=0 && n%2==0 ){
			oddarr[odd] = n;
			odd++;
		}else if( n!= 0 && n%2 != 0 ){
			evenarr[even] = n;
			even++;
		}
}while(n!=0);

}

int main(){
	//部分变量的初始化
	// int count2 = 9;
    // int goods_num = 10;
    // int cap = 9;
	goodarr = sumpermaket();
	int numshuzu[] = { 1,2,3,4,5,6,12,15,11,7,8,13 };
	int target = 0;
	int num = 0;
	int num_arr[10];
	int count = 0;
	int c;
	printf("(zjq53) > ");
	char arr[100];
    fgets(arr,sizeof(arr),stdin);
    arr[strcspn(arr,"\n")] = '\0';
    num = command(arr);
	while (num != 0) {
		switch (num) {
		case 1:
			printf("请输入你要判断的年份");
			int year = 0;
			scanf("%d", &year);
            while ((c = getchar()) != '\n' && c != EOF);
			//清楚缓存区
			printf("程序正在执行。。。\n");
			printf("程序执行结束\n");
			panduan(year);
			printf("(zjq53) > ");
			fgets(arr,sizeof(arr),stdin);
            arr[strcspn(arr,"\n")] = '\0';
            num = command(arr);
			break;
		case 2:
			printf("程序正在执行。。。\n");
			printf("程序执行结束\n");
			int jiujiu = 0;
			chengfabiao(jiujiu);
			printf("(zjq53) > ");
			fgets(arr,sizeof(arr),stdin);
            arr[strcspn(arr,"\n")] = '\0';
            num = command(arr);
			break;
		case 3:
			scanf("%d", &target);
			while ((c = getchar()) != '\n' && c != EOF);
			search(numshuzu, target);
			printf("(zjq53) > ");
			fgets(arr,sizeof(arr),stdin);
            arr[strcspn(arr,"\n")] = '\0';
            num = command(arr);
			break;
		case 4:
		    printf("请输入10个数字，以回车分开");
			for (int i = 0; i < 10; i++) {
		    scanf("%d", &num_arr[i]);
			while ((c = getchar()) != '\n' && c != EOF);
		    count++;
	        }   
		        odd_even(num_arr);
		        printf("(zjq53) > ");
				fgets(arr,sizeof(arr),stdin);
				arr[strcspn(arr,"\n")] = '\0';
				num = command(arr);
		    break;
		case 5:
		       printf("help:\n");
			   printf("You can use this command to understand how to use the terminal\n");
			   printf("The terminal can receive some simple commands\n");
			   printf("You can use list to show all commands that you can use\n");
               printf("If you want to quit the terminal,type in exit on your screen\n");
			   printf("(zjq53) > ");
			   fgets(arr,sizeof(arr),stdin);
               arr[strcspn(arr,"\n")] = '\0';
               num = command(arr);
			break;
		case 6:
		      printf("list:\n");
			  printf("List all commands that you can do on this terminal\n");
			  printf("help:\n");
			  printf("You can use it to seek help\n");
			  printf("exit:\n");
			  printf("You can use it to quit the terminal\n");
			  printf("do leap:\n");
			  printf("You can use this command to determind whether a certain year is a leap year\n");
			  printf("do multtable:\n");
			  printf("You can use this command to generate a multiplication table\n");
			  printf("do searchnum:\n");
			  printf("You can use this command to find which two numbers in the array that i provided add up to the number you gave\n");
			  printf("do oddeven:\n");
			  printf("You can use this command to sort the 10 numbers you input by separating them into odd and even numbers\n");
			  printf("(zjq53) > ");
			   fgets(arr,sizeof(arr),stdin);
               arr[strcspn(arr,"\n")] = '\0';
               num = command(arr);
		    break;
		case 7:
		       supermaketmanager();
			   //free(goodarr);
		       printf("(zjq53) > ");
		       fgets(arr,sizeof(arr),stdin);
               arr[strcspn(arr,"\n")] = '\0';
               num = command(arr);
		       break;
		case 8:
		// goodarr = sumpermaket();
		supermaketconsumer();
		//free(goodarr);
		printf("(zjq53) > ");
		fgets(arr,sizeof(arr),stdin);
               arr[strcspn(arr,"\n")] = '\0';
               num = command(arr);
			   break;
		case 0:
			return 0;
			break;
		case 10:
			printf("程序错误\n");
			printf("(zjq53) > ");
			fgets(arr,sizeof(arr),stdin);
			arr[strcspn(arr,"\n")] = '\0';
			num = command(arr);
			break;
		 }
	}
	free(goodarr);
	return 0;
}