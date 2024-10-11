#include <stdio.h>

typedef struct Node {
	int data;
}Node;
typedef struct SLL {
	Node head;
	Node* nextNode;
}SLL;
int main()
{
	SLL sll;
	Node n; n.data = 1;
	sll.head = n;

	printf("%d", sll.head.data);

	Node n2; n2.data = 2;
	sll.nextNode = &n2;

	printf("%d", sll.nextNode->data);

	return 0;
}