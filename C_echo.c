#include <stdio.h>
#include<string.h>
int main() {
    char input[100];
    fgets(input,sizeof(input),stdin);
    input[strcspn(input,"\n")] = '\0';
    int temp = 0;
    for(int i = 0;input[i] != '\0';i++){
    temp = temp*10 + (int)input[i] - 48;
    }
    printf("%d",temp);
    return 0;
}