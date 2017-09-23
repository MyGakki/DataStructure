#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct node {
	ElemType data;
	struct node *next;
}slink;

slink *CreateSlink_H(int n) {
	slink *head,*s;
	head = (slink *)malloc(sizeof(slink));
	head->next = NULL;
	for(int i = 0;i < n;i++) {
		s = (slink *)malloc(sizeof(slink)); 
		scanf("%d",&s->data);
		s->next = head->next;
		head->next = s; 
	}
	return head;
}

slink *CreateSlink_T(int n) {
	slink *tail,*s,*head;
	head = tail = (slink *)malloc(sizeof(slink));
	for(int i = 0;i < n;i++) {
		s = (slink *)malloc(sizeof(slink));
		scanf("%d",&s->data);
		tail->next = s;
		tail = s;
	}
	tail->next = NULL;
	return head;
}

int DisplayList(slink *head) {
	int i = 0;
	slink *s = head;
	for(;(s = s->next) != NULL;i++){
		printf("%d ",s->data);
	}
	printf("\n");
	return i;
}

int getlen(slink *head) {
	slink *s = head;
	int i = 0;
	for(;(s = s->next) != NULL;i++){
	}
	return i;
} 

int getelem(slink *head,int n,ElemType *e) {
	slink *s = head;
	if(n < 1) return 0;
	for(int i = 1;(s = s->next)!= NULL&&i < n;i++){
	}
	if(s == NULL)
		return 0;
	*e = s->data;
	return 1;
}

main() {
	int len;
	scanf("%d",&len);
	//slink *link_H = CreateSlink_H(len);
	//DisplayList(link_H);
	slink *link_T = CreateSlink_T(len);
	DisplayList(link_T);
	int *e = (ElemType *)malloc(sizeof(ElemType));
	getelem(link_T,3,e);
	printf("%d\n",*e);
}
