
/*cheetsheet.c
*	Made by Timor Koulikov
*	if you find any error in the code, or the explanations at the code  are poorly written please let me know. any suggestion are welcomed too.
*	email:timormat321@gmail.com
* */
#include <stdio.h>
#include <stdbool.h>

/*
*	
*	
*	structure of NodeList 
*	

IntNode* head=0x1000 -
		      |
		      |		
*		      |		________________		_______________			 ______________
*			\--->	|address:0x1000|     /-------->	|address:0x2000|     /-------->	|address:0x3000|
*				|value:1       |     |		|value:2       |     |		|value:3       |
*				|next:0x2000   |-----/		|next:0x3000   |-----/		|next:0x0000   |
*				|______________|		|______________|		|______________|			


		

*/

typedef struct IntNode
{
	
	int value;
	//each Node must contain pointer to next Node
	struct IntNode* next;
}IntNode;

//creating a new Node dynamiclly.
IntNode* createNode(int x)
{
	//alloctaing memory for new node
	IntNode* newInt = (IntNode*)malloc(sizeof(IntNode));
	//initializing Node variables
	newInt->value = x;
	
	//newNode next Node is Null by default
	newInt->next = NULL;

	return newInt;
}

//free all the memmry allocated in our createNode function.
//in our IntNode we allocated once so we need only to free IntNode* in.
//if for example we allocated memory for other vairables we would need to free them to. e.g GenericNode->name=(char*)malloc(sizeof(char)*MAXLEN) :: this would require free(GenericNode->name) 
//
void freeNode(IntNode* in)
{
	free(in);
}

//like the freeNode() we print the whole List
void freeListRecursive(IntNode** head)
{
	//if head is NULL
	if (!*head)
		return;

	IntNode* next = (*head)->next;
	freeListRecursive(&next);
	free(*head);
	//after we free *head, *head is not NULL. so we need to assign NULL to *head.
	//beacuse we pass double-pointer we assure that the pointer that passed is also NULL.
	*head = NULL;
}

void freeList(IntNode** head)
{
	IntNode* tmp = *head;
	IntNode* curr = *head;
	if (!*head)
		return;
	while (curr)
	{
		tmp = tmp->next;
		free(curr);
		curr = tmp;
	}
	*head = NULL;
}


//printing the value Node
//intput:pointer to the Node.
void printNode(IntNode* i)
{
	printf("value=%d\n", i->value);
}
//printing recursively the whole list.
//input:pointer to the head of the list
void printList(IntNode* head)
{
	if (!head)
		return;
	printNode(head);
	printList(head->next);
}

/*
insert functions
insert function always pass the head as double pointer. e.g IntNode** head.
*/


//insertAtEnd: insert new Node at end ot the list. kinda explanatory :/
//input:double-pointer to head of the list,pointer to new Node

//the functions starts at the head and moves until it find the last Node.
void insertEnd(IntNode** head, IntNode* newInt)
{

	//if list is empty
	if (*head == NULL)
	{
		*head = newInt;
		return;
	}
	//if *head is the last node
	if ((*head)->next == NULL)
	{
		//adding to the last Node the new Node
		(*head)->next = newInt;
		return;
	}
	//iterating through the list by calling the next Node
	IntNode* tmp = (*head)->next;
	insertEnd(&tmp, newInt);
}

//insertStart: adding new int to the start of the list. since we are changing the head of the list we MUST send doulbe-pointer. if we wont do this the passed pointer will point to the previus head.
void insertStart(IntNode** head, IntNode* newInt)
{
	//head is empty make NewInt as the head of the list
	if (*head == NULL)
	{
		*head = newInt;
		return;
	}
	newInt->next = *head;
	*head = newInt;
}

//insertAt:adding new Node after exsisting Node.
//input:double-pointer to head, newNode
//output:1 if sucsses. 0 if fail(

//to insert new Node in middle of the list we need to 'grab' the list from 2 sides.*p is the Node before newInt.*p->next is the Node afterNew Int.
//Before: (head)->..... (p)->(p->next)->......        After: head->......... (p)->newInt->(p->next)->.............
bool insertAt(IntNode** head, IntNode* p, IntNode* newInt)
{
	//if list empty we return 0
	if (*head == NULL)
	{
		return 0;
	}
	//if *head and p are the same Node we insert newInt after p.
	//we 'grabed' p and p->next.
	if (*head == p)
	{
		
		newInt->next = p->next;
		p->next = newInt;
		return 1;
	}
	IntNode* tmp = (*head)->next;
	insertAt(&tmp,p,newInt);
}


//delete function
//delete function always pass the head as double pointer. e.g IntNode** head.
//in this cheat sheet i wrote only one delete function. but i encourage you to wrote more function. such as deleteEnd ,deleteStart ,e.t.c..

void deleteNodeRecursive(IntNode** head, IntNode* d)
{
	if (!*head)
		return;

	if (*head == d)
	{
		(*head) = (*head)->next;
		return;
	}

	IntNode* tmp = (*head)->next;
	if (!tmp) return;
	if (d == tmp)
	{
		(*head)->next = tmp->next;
		freeNode(d);

	}
	else
	{
		deleteNodeRecursive(&tmp, d);
	}
}

void deleteNode(IntNode** head, IntNode* d)
{
	IntNode* p = *head;
	IntNode* dNode = NULL;
	if (*head)
	{
		if (*head == d)
		{
			*head = (*head)->next;
			free(p);
		}
		else
		{
			while (p->next &&
				p->next==d)
			{
				p = p->next;
			}
			if (p->next)
			{
				dNode = p->next;
				p->next = dNode->next;
				free(dNode);
			}
		}
	}
}

//reverseList. if list order was 1->2->3. after reverse the list order will be 3->2->1                	the fucntion is recursive,bcz why not :)
//intput:pointer to head
//output:pointer to new head
//!!!DISCLAIMER!!! very usless function. probably you will never use it !!!DISCLAIMER!!!
IntNode* reverseList(IntNode* head)
{
	//if list empty
	if (head == NULL)
		return;
	//if list has only one node
	if (head->next == NULL)
		return head;
	
	IntNode* rest = reverseList(head->next);

	head->next->next = head;
	head->next = NULL;
	return rest;
	
	
}



/*TODO:
	int lengthList(IntNode* head)
		will be added after H.W
	IntNode* CopyList(IntNode* head)
		will be added after H.W

	add nonRecursive functions .
*/

int main(void)
{
	IntNode* head = createNode(3);
	insertEnd(&head, createNode(4));
	insertEnd(&head, createNode(5));
	insertAt(&head, head->next, createNode(6));
	deleteNode(&head, head->next->next);
	freeList(&head);
	printList(head);
	printf("\n");
	printList(reverseList(head));
	//Write your code here...
}


