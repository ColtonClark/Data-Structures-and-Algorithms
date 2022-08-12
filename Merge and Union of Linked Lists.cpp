// Name: Colton Clark
// Student ID: 004352008
// Email: clark326@cougars.csusm.edu

#include <iostream>
using namespace std;

struct Node {
	int ELEM;
	Node* next;
};

void push(Node** Start, int x);

bool isPresent(Node* head, int value);

void print(Node* node);

void push(Node** Start, int x)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	Node* last = (*Start);

	new_node->ELEM = x;
	new_node->next = NULL;
	if (*Start == NULL)
	{
		*Start = new_node;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

void print(Node* node)
{
	while (node != NULL)
	{
		cout << node->ELEM << ' ';
		node = node->next;
	}
}

bool isPresent(Node* head, int value)
{
	Node* t = head;
	while (t != NULL)
	{
		if (t->ELEM == value)
			return 1;
		t = t->next;
	}
}

void unionLL(Node* LA, Node* LB)
{
	Node* t1 = LA;
	Node* t2 = LB;
	Node* LU = NULL;
	while (t1 != NULL)
	{
		push(&LU, t1->ELEM);
		t1 = t1->next;
	}
	while (t2 != NULL)
	{
		if (!isPresent(LU, t2->ELEM))
			push(&LU, t2->ELEM);
		t2 = t2->next;
	}
	cout << "\nA and B union result is:\n";
	print(LU);
}

void mergeLL(Node* LA, Node* LB)
{
	Node* t1 = LA;
	Node* t2 = LB;
	Node* LM = NULL;

	while (t1 != NULL && t2 != NULL)
	{
		if (t1->ELEM < t2->ELEM)
		{
			push(&LM, t1->ELEM);
			t1 = t1->next;

		}
		else
		{
			push(&LM, t2->ELEM);
			t2 = t2->next;
		}

	}
	while (t1 != NULL) {
		push(&LM, t1->ELEM);
		t1 = t2->next;
	}

	while (t2 != NULL) {
		push(&LM, t2->ELEM);
		t2 = t2->next;
	}

	cout << "\nA and B merged result is:\n";
	print(LM);
}

int main()
{
	Node* LA = NULL;
	Node* LB = NULL;
	push(&LA, 3);
	push(&LA, 5);
	push(&LA, 8);
	push(&LA, 11);
	push(&LB, 2);
	push(&LB, 6);
	push(&LB, 8);
	push(&LB, 9);
	push(&LB, 22);
	push(&LB, 24);
	cout << "\nList A is:\n";
	print(LA);
	cout << "\n\nList B is:\n";
	print(LB);
	cout << endl;
	unionLL(LA, LB);
	cout << endl;
	mergeLL(LA, LB);
	cout << endl;
}