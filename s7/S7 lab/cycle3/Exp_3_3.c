#include<stdio.h>
#include<string.h>
char input[10];
char grammar[10][10];
int n,top = -1, ip = 0;
char stack[10];

void push(char c)
{
	top+=1;
	stack[top]=c;
}
void pop(int l)
{
	
	top-=l;
}
void printstack() {
	int j;
	for(j=0;j<=top;j++)
		printf("%c",stack[j]);
}
void printstring()
{
	int j;
	for(j=ip;j<strlen(input);j++)
		printf("%c",input[j]);
}


void reduce() {
	int f=1;
	while(f) {
		f=0;
		for(int k = 0; k < n; k++) {
			char lhs = grammar[k][0];
			char *rhs = grammar[k]+3;
			int len = strlen(rhs);
			if(top+1 >= len) {
				int match= 1,t = top-len+1;
				for (int m=0;m<len;m++) {
					if (stack[t+m] != rhs[m]) {
						match = 0;
						break;
					}
				}
				if (match) {
					pop(len);
					push(lhs);
					printf("\tReduce %c->%s\n\t\t",lhs,rhs);
					f=1;
					break;
				}
			}
		}
		
	}
}


int main() {
	int i;
	printf("Enter no of production");
	scanf("%d",&n);
	printf("\nEnter the productions");
	for(i=0;i<n;i++)
		scanf("%s",grammar[i]);
	printf("Enter the input string");
	scanf("%s",input);
	printf("\nStack\tInput\tAction\n");
	while(ip < strlen(input)) {
		push(input[ip]);
		ip++;
		printstack();
		printf("\t");
		printstring();
		printf("\tShift");
		reduce();
		printf("\n");
	}
	if(top==0 && stack[top]==grammar[0][0] && ip==strlen(input)) {
		printf("\nAccepted");
	}
	else
		printf("\nRejected");
}