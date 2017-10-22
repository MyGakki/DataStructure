#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int coef;
	int expo;
	struct Node *next;
}slink;

slink *createPoly(int n) {
	slink *head, *p, *tail;
	tail = head = (slink *)malloc(sizeof(slink));
	for (int i = 1; i <= n; i++) {
		p = (slink *)malloc(sizeof(slink));
		scanf("%d", &p->coef);
		scanf("%d", &p->expo);
		tail->next = p;
		tail = p;
	}
	tail->next = NULL;
	return head;
}

slink *plusPoly(slink *polyA, slink *polyB) {
	slink *a, *b, *result, *c;
	result = polyA;
	a = polyA->next;
	b = polyB->next;
	while (a != NULL && b != NULL) {
		if (a->expo > b->expo) {
			result->next = b;
			result = b;
			b = b->next;
		} else if (a->expo < b->expo) {
			result->next = a;
			result = a;
			 a = a->next;
		} else if (a->coef + b->coef != 0) {
			a->coef = a->coef + b->coef;
			result->next = a;
			result = a;
			a = a->next;
			c = b;
			b = b->next;
			delete c;
		} else {
			c = a;
			a = a->next;
			delete c;
			c = b;
			b = b->next;
			delete c;
		}
	}
	if (a != NULL) {
		result->next = a;
	} else {
		result->next = b;
	}
	//		delete polyB;
	return polyA;
}

void displayList(slink *head) {
	slink *a = head->next;
	while (a != NULL) {
		printf("(%d,%d)  ", a->coef, a->expo);
		a = a->next;
	}
	printf("\n");
}


int main() {
	slink *polyA, *polyB, *result;
	int lenA, lenB;
	printf("输入第一个多项式的长度");
	scanf("%d", &lenA);
	polyA = createPoly(lenA);
	displayList(polyA);
	printf("输入第二个多项式的长度");
	scanf("%d", &lenB);
	polyB = createPoly(lenB);
	displayList(polyB);
	result = plusPoly(polyA, polyB);
	displayList(result);
	system("pause");
	return 0;
}