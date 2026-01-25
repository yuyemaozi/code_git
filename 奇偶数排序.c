#include<stdio.h>
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void paixu(int num[],int count) {
	for (int t = 0; t < count + 1; t++) {
		for (int i = 0; i < count - t - 1; i++) {
			if (num[i] > num[i + 1]) {
				swap(&num[i], &num[i + 1]);
			}
		}
	}
}
void odd_even(int num[]) {
	int oddnum[100];
	int evennum[100];
	int odd = 0;
	int even = 0;
	int t = 0;
	int m = 0;
	int n = 0;
	for (int i = 0; i < 10; i++) {
		if (num[i] % 2 == 0) {
				oddnum[t] = num[i];
				t++;
				odd++;
		}
		else {
			evennum[m] = num[i];
			m++;
			even++;
		}
    
	}
	do{
	    paixu(oddnum,odd);
		paixu(evennum,even);
    for(int i = 0;i<even;i++){
        printf("%d ",evennum[i]);
    }
	for(int i = 0;i<odd;i++){
        printf("%d ",oddnum[i]);
    }
	printf("\n输入0结束程序");
		scanf("%d",&n);
		if( n!=0 && n%2==0 ){
			oddnum[odd] = n;
			odd++;
		}else if( n!= 0 && n%2 != 0 ){
			evennum[even] = n;
			even++;
		}
}while(n!=0);
}
int main() {
	int num[10];
	int count = 0;
	for (int i = 0; i < 10; i++) {
		scanf("%d", &num[i]);
		count++;
	}
		odd_even(num);
		return 0;
}