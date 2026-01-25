#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<dirent.h>
int clear = 0;
int stu_num = 0;
int tea_num = 0;
int temp_ID_num = 0;
int cap = 2;
long login_ID = 0;
FILE *fp = NULL;
struct stu{
    char name[20];
    long ID;
    char password[30];
    int class;
};
struct teacher{
    char name[20];
    char account[20];
    char password[30];
};
struct umbrella{
    int umbrella_num;
}umbrella_arr[20];

struct stu *pointer = NULL;
struct teacher *tea_pointer = NULL;



int command(char arr[20]){
	//定义所有的指令
    char arr1[]="email";
    char arr2[]="help";
    char arr3[]="exit";
    char arr4[]="do leap";
	char arr5[]="search";
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
int command_stu(char arr[20]){
    char arr1[] = {"email"};
    char arr2[] = {"help"};
    if(strcmp(arr,arr1) == 0){
        return 1;
    }else if(strcmp(arr,arr2) == 0){
        return 2;
    }else{
        return 3;
    }
}



int safe_umbrella(char input[]){
    for(int i = 0;input[i]!= '\0';i++){
        int temp = input[i];
        if(temp >= 48 && temp <= 57){
            continue;
        }else{
            return 0;
        }
    }
    return 1;
}



void umbrella(){
    char umbrella[20];
    FILE *fp = NULL;
    fp = fopen("./umbrella.txt","r");
    int umbrella_temp_num = 0;
    while(fscanf(fp,"%d\n",&umbrella_temp_num) == 1){
        int i = 1;
        int j = 0;
        if(umbrella_temp_num == 1){
            umbrella_arr[j].umbrella_num = i;
            i++;
            j++;
        }else{
            umbrella_arr[j].umbrella_num = 0;
            i++;
            j++;
        }
    }
    fclose(fp);
    fp = NULL;
    int control = 1;
    for(int i = 0;i < 20; i++){
        if(umbrella_arr[i].umbrella_num != 0){
        control = 0;
        }
    }
    if(control){
        printf("没有雨伞可以借了\n");
        return;
    }
    printf("现在可以借的雨伞\n");
    for(int i = 0; i < 20;i++){
        if(umbrella_arr[i].umbrella_num != 0){
            printf("%d ",umbrella_arr[i].umbrella_num);
        }
    }
    do{
        printf("请输入您要借的雨伞的编号\n");
        char input[100];
        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")] = '\0';
        if(safe_umbrella(input) == 1){
            int temp = 0;
            for(int i = 0;input[i] != '\0';i++){
                temp = temp*10 + (int)input[i] - 48;
            }
        }

    }
}



int VC(){
    char symbol[7];
    char ans[5];
    int ans_num = 0;
    int symbol_num = 0;
    int i = 0;
    srand((int)time(NULL));
    while(symbol_num < 6){
            int temp_num = rand()%100;
            if(temp_num >= 33 && temp_num <= 46){
               symbol[i] = (char)temp_num;
               i++;
               symbol_num++;
            }
    }
    i = 0;
    while(ans_num < 4){
            int temp_num = rand() % 100;
            if((temp_num>=48 && temp_num<=57) || (temp_num>=65 && temp_num<=90) || (temp_num>=97 && temp_num<=122)){
                if((temp_num>=65 && temp_num<=90) || (temp_num>=97 &&temp_num<=122)){
                    ans[i] = (char)temp_num;
                    i++;
                    ans_num++;
                }
            }
            if(temp_num>=48 && temp_num<=57){
                ans[i] = temp_num;
                i++;
                ans_num++;
            }
    }
    i = 0;
    ans_num = 0;
    symbol_num = 0;
    char output[11];
    while(i < 10){
        int temp_num = rand()%10;
        if(temp_num%2 ==0 && symbol_num < 6){
            output[i] = symbol[symbol_num];
            i++;
            symbol_num++;
        }else if(temp_num%2 != 0 && ans_num < 4){
            output[i] = ans[ans_num];
            i++;
            ans_num++;
        }
    }
    printf("%s\n",output);
    printf("请按顺序输入所有英文字符和数字\n");
    char reply[5];
    fgets(reply,sizeof(reply),stdin);
    reply[strcspn(reply,"\n")] = '\0';
    int result = 1;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    num1 = rand()%10;
    num2 = rand()%100;
    if( rand()%2 == 0){
        num3 = num1 + num2;
        printf("%d + %d = ?\n",num1,num2);
        printf("请输入答案\n");
        scanf("%d",&num4);
        while((clear = getchar()) != '\n');
    }else{
        num3 = num2 - num1;
        printf("%d - %d = ?",num2,num1);
        printf("请输入答案\n");
        scanf("%d",&num4);
        while((clear = getchar()) != '\n');
    }
    if(num4 == num3){
        result = strcmp(reply,ans);
    }
    return result;
}



void Input(){
    pointer = (struct stu*)malloc(sizeof(struct stu)*cap);
    if(pointer == NULL){
        printf("初始化内存失败\n");
    }
    stu_num = 0;
    char name[20];
    long ID = 0;
    char password[30];
    int class = 0;
    fp = fopen("./stu.txt","r");
    if(fp == NULL){
        printf("打开文件失败\n");
    }
    while(fscanf(fp,"%s %d %ld %s",name,&class,&ID,password) == 4){
        if(stu_num >= cap){
            struct stu* new = realloc(pointer,sizeof(struct stu)*cap*2);
            if(new == NULL){
                printf("重新分配内存失败\n");
            }
            cap*=2;
            pointer = new;
        }
         strcpy(pointer[stu_num].name,name); 
         strcpy(pointer[stu_num].password,password);
         pointer[stu_num].ID = ID;
         pointer[stu_num].class = class;
         stu_num++;
         continue;
        }
        fclose(fp);
// for(int i = 0;i <stu_num;i++){
//         printf("%s %ld %s\n",pointer[i].name,pointer[i].ID,pointer[i].password);
//     }
        tea_pointer = (struct teacher*)malloc(sizeof(struct teacher)*20);
        fp = fopen("./teacher.txt","r");
        char account[30];
        int i = 0;
        while(fscanf(fp,"%s %s %s",name,account,password) == 3){
            strcpy(tea_pointer[i].name,name);
            strcpy(tea_pointer[i].password,password);
            strcpy(tea_pointer[i].account,account);
            i++;
            tea_num++;
        }
        fclose(fp);
        fp = NULL;
        // for(int i = 0;i < tea_num;i++){
        //     printf("%s %s %s\n",tea_pointer[i].name,tea_pointer[i].account,tea_pointer[i].password);
        // }
}



void sign_up(){
    char password[30];
    char temp[30];
    printf("请输入你的名字\n");
    char stu_name[100];
    fgets(stu_name,sizeof(stu_name),stdin);
    stu_name[strcspn(stu_name,"\n")] = '\0';
    //创建相应的学生的文件
    
    printf("请输入你的班级\n");
    int class;
    scanf("%d",&class);
    while((clear = getchar()) != '\n');
do{
    printf("请设置密码\n");
    fgets(password,sizeof(password),stdin);
    password[strcspn(password,"\n")] = '\0';
    printf("请再次输入密码\n");
    fgets(temp,sizeof(temp),stdin);
    temp[strcspn(temp,"\n")] = '\0';
    strcmp(password,temp);
    if(strcmp(password,temp) != 0){
        printf("两次密码输入不一样\n");
    }
}while(strcmp(password,temp) != 0);
    long newID = 2025001001 + stu_num;
    printf("自动生成学号：%ld\n",newID);
    char temp_ID[20];
    sprintf(temp_ID,"%ld",newID);
    mkdir(temp_ID,0777);
    fp = fopen("./stu.txt","a");
    if(fp == NULL){
        printf("文件打开失败\n");
    }
    fprintf(fp,"%s %d %ld %s\n",stu_name,class,newID,password);
    fclose(fp);
    strcpy(pointer[stu_num].name,stu_name); 
    strcpy(pointer[stu_num].password,password);
    pointer[stu_num].ID = newID;
    pointer[stu_num].class = class;
    stu_num++;
    fp = NULL;
}



int login(){
    int d = 1;
    Input();
    char input[10];
    while(d){
    printf("学生输入:student 老师输入:teacher\n");
    scanf("%s",input);
    while((clear = getchar()) != '\n');
    if (strcmp(input,"student") == 0){
     d = 0;
    char password[30];
    printf("请输入你的学号\n");
    long ID = 0;
    scanf("%ld",&ID);
    login_ID = ID;
    while((clear = getchar()) != '\n');
    printf("请输入密码\n");
    fgets(password,sizeof(password),stdin);
    int c = 0;
    while(c !=3 ){
        int test_num = VC();
        if(test_num == 0 ){
            break;
        }else{
              c++;}
    }
    int a = 1;
    int b = 0;
    if(c != 3){
    password[strcspn(password,"\n")] = '\0';
    for(int i = 0;i < stu_num;i++){
        //printf("%ld",ID);
        //printf("%ld",pointer[i].ID);
        //控制打印内容
        if(ID == pointer[i].ID){
            a = 0;
            b = 1;
            if(strcmp(password,pointer[i].password) == 0){
                printf("登录成功\n");
                return 1;
                b = 0;
            }
        }
    }
    if(a){
            printf("没有此帐号，请先注册\n");
    }
    if(b){
            printf("密码错误\n");
    }
}else{
    printf("验证码输入错误过多，退出系统\n");
    exit(1);
}
}else if(strcmp(input,"teacher") ==0 ){
    d = 0;
    printf("请输入你的姓名\n");
    char name[20];
    scanf("%s",name);
    while((clear = getchar()) != '\n');
    printf("请输入你的帐号\n");
    char account[30];
    fgets(account,sizeof(account),stdin);
    account[strcspn(account,"\n")] = '\0';
    printf("请输入你的密码\n");
    char password[20];
    fgets(password,sizeof(password),stdin);
    password[strcspn(password,"\n")] = '\0';
    int c = 0;
    while(c !=3 ){
        int test_num = VC();
        if(test_num == 0 ){
            break;
        }else{
              c++;}
    }
    int a = 1;
    int b = 0;
    if(c != 3){
    for(int i = 0;i < tea_num;i++){
        //控制打印内容
        if(strcmp(account,tea_pointer[i].account) == 0){
            a = 0;
            b = 1;
            if(strcmp(password,tea_pointer[i].password) == 0){
                printf("登录成功\n");
                return 2;
                b = 0;
            }
        }
    }
    if(a){
            printf("没有此帐号，请联系学校注册\n");
    }
    if(b){
            printf("密码错误\n");
    }
}else{
    printf("验证码输入错误过多，退出系统\n");
    exit(1);
}
}else{
    printf("请输入正确的指令\n");
}
    }
}
int search_command(char input[30]){
    if(strcmp(input,"class") == 0){
        return 1;
    }else if(strcmp(input,"name") == 0){
        return 2;
    }else if(strcmp(input,"ID") == 0){
        return 3;
    }else if(strcmp(input,"exit") == 0){
        return 0;
    }else {
        return 4;
    }
    
}


void search(){
    printf("class:查询班级学生 name:查询该学生详情信息 ID:查询该学生详情信息\n");
    printf("输入 exit 退出此程序\n");
    char input[20];
    scanf("%s",input);
    while((clear = getchar()) != '\n');
    int control = 0;
    control = search_command(input);
    while(control != 0){
        switch(control){
            case 1:
            printf("请输入班级\n");
            int class = 0;
            scanf("%d",&class);
            while((clear = getchar()) != '\n');
            int a = 1;
            printf("%-18s %-15s %-15s %s\n", "姓名", "学号", "密码", "班级");
            for(int i = 0;i < stu_num; i++){
                if(class == pointer[i].class){
                    printf("%-15s %-12ld %-15s %d\n",pointer[i].name,pointer[i].ID,pointer[i].password,pointer[i].class);
                    a = 0;
                }
            }
            if(a){
                printf("没有这个班级\n");
                }
            printf("class:查询班级学生 name:查询该学生详情信息 ID:查询该学生详情信息\n");
            printf("输入 exit 退出此程序\n");
            char input[30];
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            control = search_command(input);
            break;
            case 2:
            printf("请输入姓名\n");
            char name[20];
            scanf("%s",name);
            while((clear = getchar()) != '\n');
            int b = 1;
            for(int i = 0; i < stu_num; i++){
            if(strcmp(pointer[i].name,name) == 0){
                printf("%-18s %-15s %-15s %s\n", "姓名", "学号", "密码", "班级");
                printf("%-15s %-12ld %-15s %d\n",pointer[i].name,pointer[i].ID,pointer[i].password,pointer[i].class);
                b = 0;
            }
            }
            if(b){
                printf("没有这个学生\n");
            }
            printf("class:查询班级学生 name:查询该学生详情信息 ID:查询该学生详情信息\n");
            printf("输入 exit 退出此程序\n");
            input[30];
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            control = search_command(input);
            break;
            case 3:
            printf("请输入学生ID\n");
            long ID = 0;
            int c = 1;
            scanf("%ld",&ID);
            printf("%-18s %-15s %-15s %s\n", "姓名", "学号", "密码", "班级");
            for(int i = 0; i< stu_num;i++){
                if(ID == pointer[i].ID){
                    printf("%-15s %-12ld %-15s %d\n",pointer[i].name,pointer[i].ID,pointer[i].password,pointer[i].class);
                    c = 0;
                }
            }
            if(c){
                printf("没有此学生\n");
            }
            printf("class:查询班级学生 name:查询该学生详情信息 ID:查询该学生详情信息\n");
            printf("输入 exit 退出此程序\n");
            input[30];
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            control = search_command(input);
            break;
            case 4:
            printf("没有此指令\n");
            printf("class:查询班级学生 name:查询该学生详情信息 ID:查询该学生详情信息\n");
            printf("输入 exit 退出此程序\n");
            input[30];
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            control = search_command(input);
            break;
            case 0:
            control = 0;
            break;
        }
    }
}



void email(){
    printf("请选择您要发送信息的方式\n");
    printf("class:按班级发送 ID:按学号发送\n");
    printf("输入 exit 退出程序\n");
    char input[20];
    int control = 1;
    scanf("%s",input);
    while((clear = getchar()) != '\n');
    control = search_command(input);
    while(control != 0){
        switch(control){
            case 1:
            printf("请输入班级\n");
            int class = 0;
            temp_ID_num = 0;
            int a = 1;
            scanf("%d",&class);
            while((clear = getchar()) != '\n');
            char *temp_ID[20];
            for(int i =0;i < stu_num;i++){
                if(class == pointer[i].class){
                    temp_ID[temp_ID_num] = (char *)malloc(20*sizeof(char));
                    sprintf(temp_ID[temp_ID_num],"%ld",pointer[i].ID);
                    temp_ID_num++;
                    a = 0;
                }
            }
            if(a){
                printf("没有此班级\n");
                break;
            }
            printf("请输入邮件的标题\n");
            char title[40];
            fgets(title,sizeof(title),stdin);
            title[strcspn(title,"\n")] = '\0';
            char information[200];
            printf("请输入内容\n");
            fgets(information,sizeof(information),stdin);
            information[strcspn(information,"\n")] = '\0';
            for(int i = 0;i < temp_ID_num;i++){
            FILE *fp;
            fp = NULL;
            char temp[50] = "./";
            strcat(temp,temp_ID[i]);
            strcat(temp,"/");
            strcat(temp,title);
            fp = fopen(temp,"wb");
            if(fp == NULL){
            printf("打开文件失败\n");
            exit(1);
            }
            fwrite(information,1,strlen(information),fp);
            fclose(fp);
            }
            for(int i = 0;i < temp_ID_num;i++){
                free(temp_ID[i]);
            }
            printf("请选择您要发送信息的方式\n");
            printf("class:按班级发送 ID:按学号发送\n");
            printf("输入 exit 退出程序\n");
            char input[20];
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            control = search_command(input);
            break;
        case 3:
            printf("请输入学生的学号\n");
            long ID = 0;
            scanf("%ld",&ID);
            while((clear = getchar()) != '\n');
            int b = 1;
            char temp_ID_[30];
            for(int i = 0;i < stu_num; i++){
                if(ID == pointer[i].ID){
                    b = 0;
                    sprintf(temp_ID_,"%ld",pointer[i].ID);
                }
            }
            if(b){
                printf("没有此学生\n");
                break;
            }
            printf("请输入邮件的标题\n");
            title[40];
            fgets(title,sizeof(title),stdin);
            title[strcspn(title,"\n")] = '\0';
            information[200];
            printf("请输入内容\n");
            fgets(information,sizeof(information),stdin);
            information[strcspn(information,"\n")] = '\0';
            FILE *fp = NULL;
            char temp[] = "./";
            strcat(temp,temp_ID_);
            strcat(temp,"/");
            strcat(temp,title);
            fp = fopen(temp,"wb");
            if(fp == NULL){
            printf("打开文件失败\n");
            exit(1);
            }
            fwrite(information,1,strlen(information),fp);
            fclose(fp);
            printf("请选择您要发送信息的方式\n");
            printf("class:按班级发送 ID:按学号发送\n");
            printf("输入 exit 退出程序\n");
            input[20];
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            control = search_command(input);
            break;
        }
    }
}



void receive_email(){
    char temp_login_ID[30];
    sprintf(temp_login_ID,"%ld",login_ID);
    char temp[50] = "./";
    strcat(temp,temp_login_ID);
    DIR *dir = NULL;
    int entry_num = 0;
    dir = opendir(temp);
    if(!dir){
        printf("没有邮件\n");
        return;
    }
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        if (entry->d_type == DT_REG) { 
        printf("邮件: %s\n", entry->d_name);
        entry_num++;
        }
    }
    rewinddir(dir);
    printf("请输入你要打开邮件的名字\n");
    char title[30];
    fgets(title,sizeof(title),stdin);
    title[strcspn(title,"\n")] = '\0';
    int a = 1;
    while((entry = readdir(dir)) != NULL){
            if(entry->d_type != DT_REG){
                continue;
            }
            if(strcmp(title,entry->d_name) == 0){
                a = 0;
                break;
            }
        }
        if(a){
        printf("没有此文件\n");
        return;
    }
            FILE *fp = NULL;
            strcat(temp,"/");
            strcat(temp,entry->d_name);
            char information[200];
            fp = fopen(temp,"r");
            fgets(information,sizeof(information),fp);
            printf("%s\n",information);
            printf("是否删除此文件\n");
            printf("输入yes or no\n");
            char input[20];
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            int b = 1;
            while(b){
            if(strcmp(input,"yes") == 0){
                remove(temp);
                printf("删除成功\n");
                b = 0;
            }else if(strcmp(input,"no") == 0){
                b = 0;
                break;
            }else{
                printf("指令错误\n");
            }
        }
}
int main(){
    Input();
    char input[20];
    int test_num = 0;
    int choose_sys = 0;
    while(test_num == 0){
    printf("欢迎来到学生管理系统\n");
    printf("您是否拥有帐号，yes登陆，no进入注册\n");
    fgets(input,sizeof(input),stdin);
    input[strcspn(input,"\n")] = '\0';
    if(strcmp(input,"yes") == 0){
        choose_sys = login();
        test_num = 1;
    }else if(strcmp(input,"no") == 0){
        sign_up();
        test_num = 0;
    }else{
        printf("指令错误，请输入yes或者no");
    }
}
    if(choose_sys == 2){
        int command_num = 0;
        printf("输入 help 查询所有指令\n");
        scanf("%s",input);
        while((clear = getchar()) != '\n');
        command_num = command(input);
        while(command_num != 0){
        switch(command_num){
            case 2:
            search();
            printf("输入 help 查询所有指令\n");
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            command_num = command(input);
            break;
            case 6:
            email();
            printf("输入 help 查询所有指令\n");
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            command_num = command(input);
            break;
            case 5:
            printf("search : 查询学生详细信息\n");
            printf("email : 发送邮件给学生\n");
            printf("exit : 推出程序\n");
            printf("输入 help 查询所有指令\n");
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            command_num = command(input);
            break;
            case 10:
            printf("请输入正确的指令\n");
            printf("输入 help 查询所有指令\n");
            scanf("%s",input);
            while((clear = getchar()) != '\n');
            command_num = command(input);
            break;
            case 0:
            free(pointer);
            free(tea_pointer);
            return 0;
            break;
        }
    }
    }else if(choose_sys == 1){
        int command_num = 0;
        printf("输入 help 查询所有指令\n");
        scanf("%s",input);
        while((clear = getchar()) != '\n');
        command_num = command_stu(input);
        while(command_num != 0){
            switch(command_num){
                case 1:
                receive_email();
                printf("输入 help 查询所有指令\n");
                scanf("%s",input);
                while((clear = getchar()) != '\n');
                command_num = command_stu(input);
                break;
                case 2:
                printf("email : 查询老师发的邮件\n");
                printf("输入 help 查询所有指令\n");
                scanf("%s",input);
                while((clear = getchar()) != '\n');
                command_num = command_stu(input);
                break;
                case 3:
                printf("请输入正确的指令\n");
                printf("输入 help 查询所有指令\n");
                scanf("%s",input);
                while((clear = getchar()) != '\n');
                command_num = command_stu(input);
                break;
            }
        }
    }     
    free(pointer);
    free(tea_pointer);
    return 0;
}