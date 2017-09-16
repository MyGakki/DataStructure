#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

struct SQList{
	int *elem;
	int listsize;
	int len;
}; 

void InitList(SQList *L){
	L->elem = (int *)malloc(MAXSIZE * sizeof(int));
	if(!L->elem)
		exit;
	L->len = 0;
	L->listsize = MAXSIZE;
} 

void ListInsert(SQList *L,int i,int e){
	if(i < 1||i > L->len + 1)
		exit;
	if(L->len >= L->listsize) {
		int *newbase = (int *)realloc(L->elem,(L->listsize + 10) * sizeof(int));
		if(!newbase)
			exit;
		L->elem = newbase;
		L->listsize += 10;
	}
	int *q = &(L->elem[i - 1]);
	for(int *p = &(L->elem[L->len - 1]);p >= q;--p)
		*(p + 1) = *p;
	*q = e;
	++L->len;
}

void ListDelete(SQList *L,int i) {
	if(i < 1||i > L->len)
		exit;
	int *p = &(L->elem[i - 1]);
	int *q = &(L->elem[L->len - 1]);
	for(++p;q >= p;++p)
		*(p - 1) = *p;
	L->len--;
} 

void DisplayList(SQList *L){
	for(int i = 0;i < L->len;i++) {
		printf("%d ",L->elem[i]);
	}
	printf("  len:%d\n",L->len);
}

int main(){
	SQList sqlist;
	InitList(&sqlist);
	int length;
	scanf("%d",&length);
	for(int i = 0;i < length;i++) {
		scanf("%d",&sqlist.elem[i]);
		sqlist.len++;
	}
	DisplayList(&sqlist);
	ListInsert(&sqlist,5,12);
	DisplayList(&sqlist);
	ListDelete(&sqlist,5);
	DisplayList(&sqlist);
	return 0;
	 
} 
