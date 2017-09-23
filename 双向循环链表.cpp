#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct node {
	ElemType data;
	struct node *prior;
	struct node *next;
}dlink;


dlink *credclink(int n);
int getLen(dlink *head);
int getElem(dlink *head, int i, ElemType *e);
int deleteElem(dlink *head, int i);
int insertElem(dlink *head, int i, ElemType e);
void printDlink(dlink *head);

void main() {
	dlink *head = credclink(5);
	int len = getLen(head);
	printf("%d\n",len);
	int *elem = (ElemType *)malloc(sizeof(ElemType));
	getElem(head, len, elem);
	printf("%d\n", *elem);
	deleteElem(head, 3);
	insertElem(head, 3, 13);
	printDlink(head);
}


dlink *credclink(int n) {
	dlink *head, *p, *s;
	p = head = (dlink *)malloc(sizeof(dlink));
	for (int i = 1; i <= n; i++) {
		s = (dlink *)malloc(sizeof(dlink));
		scanf("%d", &s->data);
		s->prior = p;
		p->next = s;
		p = s;
	}
	p->next = head;
	head->prior = p;
	return head;
}

int getLen(dlink *head) {
	int i = 0;
	dlink *p = head->next;
	for (; p != head; i++) {
		p = p->next;
	}
	return i;
}

int getElem(dlink *head, int i, ElemType *e) {
	int j = 1;
	dlink *p;
	if (i < 1) return 0;
	p = head->next;
	while (p != head && j < i) {
		p = p->next;
		j++;
	}
	if (p == head) return 0;
	*e = p->data;
	return 1;
}

int deleteElem(dlink *head,int i) {
	dlink *p, *q;
	int j = 0;
	if (i < 1) return 0;
	p = head;
	while (p->next != head && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p->next == head) return 0;
	q = p->next;
	p->next = q->next;
	p->next->prior = p;
	free(q);
	return 1;
}

int insertElem(dlink *head, int i, ElemType e) {
	dlink *p, *q;
	int j = 0;
	if (i < 1) return 0;
	p = head;
	while (p->next != head && j < i - 1) {
		p = p->next;
		j++;
	}
	if ((p->next != head) || (p->next == head && j == i - 1)) {
		q = (dlink *)malloc(sizeof(dlink));
		q->data = e;
		q->next = p->next;
		q->prior = p;
		p->next = q;
		q->next->prior = q;
		return 1;
	}
	else return 0;
}

void printDlink(dlink *head) {
	dlink *p = head->next;
	while (p != head) {
		printf("%4d", p->data);
		p = p->next;
	}
	printf("\n");
}