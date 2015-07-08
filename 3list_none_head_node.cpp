//��ͷ��㵥����ĸ������

#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;

struct LinkList {
	int value;
	LinkList *next;
};

//�������뽨������������ͷ������
LinkList *BuildList() {
	LinkList *head = NULL;
	int data;
	int i = 0;
	while (scanf("%d", &data) != EOF) {
		//scanf("%d", &data);++i;
		LinkList *new_node = (LinkList *)malloc(sizeof(LinkList));
		if (NULL == new_node) {
			fprintf(stderr, "malloc failed");
			return head;
		}
		new_node->value = data;
		if (head == NULL) {
			new_node->next = NULL;
			head = new_node;
		}
		else {
			new_node->next = head;
			head = new_node;
		}
	}
	return head;
}

//������ͷ������ڵ�
LinkList *InsertToHead(int value, LinkList *head) {
	LinkList *new_node = (LinkList *)malloc(sizeof(LinkList));
	if (new_node == NULL) {
		fprintf(stderr, "malloc failed");
		return head;
	}
	new_node->value = value;
	new_node->next = NULL;
	if (head == NULL) {
		head = new_node;
	}
	else {
		new_node->next = head;
		head = new_node;
	}
	return head;
}

//����β������ڵ�
LinkList *InsertToTail(int value, LinkList *head) {
	LinkList *new_node = (LinkList *)malloc(sizeof(LinkList));
	if (new_node == NULL) {
		fprintf(stderr, "malloc failed");
		return head;
	}
	new_node->value = value;
	new_node->next = NULL;

	if (head == NULL)
		head = new_node;
	else {
		LinkList *pnode = head;
		while (pnode->next != NULL)
			pnode = pnode->next;
		pnode->next = new_node;
	}
	return head;
}

//ɾ��ĳ�ڵ�
LinkList *DeletebyValue(int value, LinkList* head) {
	if (head == NULL)
		return head;
	LinkList *pToDelete = NULL;
	if (head->value == value) {
		pToDelete = head;
		head = head->next;
	}
	else {
		LinkList *p = head;
		while (p->next != NULL && p->next->value != value)
			p = p->next;
		if (p->next != NULL) {
			pToDelete = p->next;
			p->next = pToDelete->next;
		}
	}
	if (pToDelete != NULL) {
		free(pToDelete);
		pToDelete = NULL;
	}
	return head;
}

unsigned int Length(LinkList *head) {
	unsigned int length = 0;
	LinkList *p = head;
	while (p) {
		++length;
		p = p->next;
	}
	return length;
}

//��ӡ������
void PrintList(LinkList *head) {
	LinkList *p = head;
	while (p) {
		printf("%d ", p->value);
		p = p->next;
	}
	printf("\n");
}

//�����ӡ�������ǵݹ�
void RPrintList(LinkList* head) {
	if (NULL == head)
		return;
	stack<int> list_stack;
	while (head) {
		list_stack.push(head->value);
		head = head->next;
	}
	while (!list_stack.empty()) {
		printf("%d ", list_stack.top());
		list_stack.pop();
	}
	printf("\n");
}
//�����ӡ�������ݹ�
void RPrintListRecursively(LinkList* head) {
	if (NULL == head)
		return;
	else {
		RPrintListRecursively(head->next);
		printf("%d ", head->value);
	}
}
//ð����������
LinkList* Sort(LinkList *head) {
	if (NULL == head)
		return head;
	int length = Length(head);
	int unorder_size = length;
	int flag = 1;
	while (flag) {
		flag = 0;
		LinkList *p = head;
		for (int i = 0; p->next && i < unorder_size; ++i) {
			if (p->value > p->next->value) {
				int temp = p->value;
				p->value = p->next->value;
				p->next->value = temp;
				flag = 1;
			}
			p = p->next;
		} 
		--unorder_size;
	}
	return head;
}

//��ת������
LinkList* ReverseList(LinkList *head) {
	//��ʵ����if�жϵ�����ڵ����С�����������
	//���Ǳ���ģ���Ϊ֮��ĳ������������ж�
	if (NULL == head || NULL == head->next){
		return head;
	}
	LinkList *reverse_head = NULL;  //��ת�������ͷָ��
	LinkList *pcurrent = head;      //pcurrent��������
	while (pcurrent) {
		LinkList* temp = pcurrent;
		pcurrent = pcurrent->next;
		temp->next = reverse_head;
		reverse_head = temp;
	}
	return reverse_head;
}

//�ҳ���������k���ڵ㣨k > 0)
LinkList * GetRKthNode(LinkList *head, int k) {
	if (k < 1 || NULL == head)
		return NULL;
	LinkList *first = head;
	LinkList *second = head;

	//����ڵ����С��k����NULL
	for (int i = 1; i < k; ++i) {
		if (second->next)
			second = second->next;
		else
			return NULL;
	}

	//����ָ��ͬʱ�ƶ���ֱ�����secondָ���ߵ����һ���ڵ㣬
	//��ʱ����firstָ��ָ��ľ��ǵ�����k���ڵ�
	while (second->next != NULL) { 
		first = first->next;
		second = second->next;
	}
	return first;
}

//���ص�������м�ڵ㣬������ڵ����Ϊż��ʱ
//�ú������������n/2 + 1���ڵ�
LinkList *GetMiddleNode (LinkList* head) {
	//����Ϊ�ջ��߽���һ���ڵ�
	if (NULL == head || NULL == head->next)
		return head;

	LinkList *first = head;
	LinkList *second = head;
	while (second->next) {
		first = first->next;
		second = second->next;
		if (second->next) {  //���ڵ����Ϊż��ʱ����Ƚ�����
			second = second->next;
		}
	}
	return first;
}

//�ϲ���������ĵ������ǵݹ�
//����ԭ����ȵ�Ԫ�ض�����
LinkList* MergeList(LinkList* heada, LinkList *headb) {
	if (NULL == heada)
		return headb;
	if (NULL == headb)
		return heada;

	LinkList *head_merge = NULL;

	//�Ƚϵ�һ���ڵ��С��ȡС����Ϊ�ϲ����һ���ڵ�
	if (heada->value <= headb->value) {
		head_merge = heada;
		//ע�������������˳���ܻ�������heada��ָ���
		heada = heada->next;
	}
	else {
		head_merge = headb;
		//ע�������������˳���ܻ�������headb��ָ���
		headb = headb->next;
		//head_merge->next = NULL;
	}
	head_merge->next = NULL;

	LinkList *pmerge = head_merge;
	while(heada != NULL && headb != NULL) {
		if (heada->value <= headb->value) {
			pmerge->next = heada;
			heada = heada->next;
			pmerge = pmerge->next;
			
		}
		else {
			pmerge->next = headb;
			headb = headb->next;
			pmerge = pmerge->next;
		}
		pmerge->next = NULL;
	}
	if (heada)
		pmerge->next = heada;
	else if (headb)
		pmerge->next = headb;

	return head_merge;
}

//�ϲ���������ĵ������ݹ�
//����ԭ����ȵ�Ԫ�ض�����
LinkList* MergeListRecursively(LinkList *heada, LinkList *headb) {
	if (NULL == heada)
		return headb;
	if (NULL == headb)
		return heada;
	
	LinkList *head_merge = NULL;
	if (heada->value <= headb->value) {
		head_merge = heada;
		head_merge->next = MergeListRecursively(heada->next, headb);
	}
	else {
		head_merge = headb;
		head_merge->next = MergeListRecursively(heada, headb->next);
	}
	return head_merge;
}

//�ж��������Ƿ��л�
bool HasCircle(LinkList *head) {
	if (NULL == head)
		return false;
	LinkList *first = head;
	LinkList *second = head;
	while (first && second->next) {
		second = second->next->next;
		first = first->next;
		if (first == second)
			return true;
	}
	return false;
}

//�ж����������Ƿ��ཻ
bool IsCross(LinkList* heada, LinkList *headb) {
	if (NULL == heada || NULL == headb)
		return false;
	LinkList* taila = heada;
	LinkList* tailb = headb;
	while (taila->next)
		taila = taila->next;
	while (tailb->next)
		tailb = tailb->next;
	return taila == tailb;
}

//�ҳ����������ཻ�ĵ�һ���ڵ�
LinkList* GetFirstCrossNode(LinkList* heada, LinkList* headb) {
	if (NULL == heada || NULL == headb)
		return NULL;

	int lengtha = 1;
	LinkList* taila = heada;
	while (taila->next) {
		++lengtha;
		taila = taila->next;
	}

	int lengthb = 1;
	LinkList* tailb = headb;
	while (tailb->next) {
		++lengthb;
		tailb = tailb->next;
	}

	//��������û���ཻ
	if (taila != tailb)
		return NULL;

	LinkList* plong = heada; //ָ�򳤶ȴ������
	LinkList* pshort = headb;//ָ�򳤶�С������
	int diff;
	if (lengthb > lengtha) {
		diff = lengthb - lengtha;
		plong = headb;
		pshort = heada;
	}

	//����������ǰ�ߣ�ʹ�������������
	for (int i = 0; i < diff; ++i)
		plong = plong->next;

	while (plong && pshort && plong != pshort) {
		plong = plong->next;
		pshort = pshort->next;
	}
	return plong;
}

//��֪������ڻ������������ĵ�һ���ڵ�
LinkList* GetFirstCircleNode(LinkList* head) {
	if (NULL == head)
		return NULL;

	//�ж����������Ƿ��л���û�����ؿ�
	LinkList *first = head;
	LinkList *second = head;
	while (first && second->next) {
		first = first->next;
		second = second->next->next;
		if (first == second)
			break;
	}
	if (NULL == first || NULL == second->next)
		return NULL;

	//������ʱ���е�����ڵ���Ϊ�����β�ڵ㣬
	//�ͽ�ԭ�����Ϊ�����ཻ�ĵ�������һ��������㼴Ϊ����
	LinkList* assumed_tail = first;
	LinkList* head1 = head;
	LinkList* head2 = assumed_tail->next;

	LinkList *pa = head1;
	int length1 = 1;
	while (pa != assumed_tail) {
		pa = pa->next;
		++length1;
	}

	LinkList* pb = head2;
	int length2 = 1;
	while (pb != assumed_tail) {
		pb = pb->next;
		++length2;
	}
	pa = head1;
	pb = head2;
	if (length1 > length2) {
		int diff = length1 - length2;
		while (diff--)
			pa = pa->next;
	}
	else {
		int diff = length2 - length1;
		while (diff--)
			pb = pb->next;
	}
	while (pa != pb) {
		pa = pa->next;
		pb = pb->next;
	}
	return pa;
}

//ɾ��ĳ��ָ��ָ��Ľ�㣬ʱ�临�Ӷ�O(1)
void DeleteTheNode(LinkList *head, LinkList *to_delete) {
	if (NULL == to_delete || NULL == head)
		return;

	//Ҫɾ���������һ�����
	if (NULL == to_delete->next) {
		if (head == to_delete) { //Ҫɾ������������е�һ�����
			head = NULL;
			free(to_delete);
			to_delete = NULL;  //��ֹ����ָ��
		}
		else {             //�����ж����㣬Ҫɾ��β���
			LinkList* p = head;
			while (p->next != to_delete)
				p = p->next;
			p->next = NULL;
			free(to_delete);
			to_delete = NULL;    //��ֹ����ָ��
		}
	} 
	else { //Ҫɾ���Ĳ���β���
		LinkList *pnext = to_delete->next;
		to_delete->value = pnext->value;
		to_delete->next = pnext->next;
		free(pnext);
		pnext = NULL;
	}
}

int main() {

	/*LinkList *head = BuildList();
	head = InsertToHead(9, head);
	head = InsertToTail(100, head);
	head = DeletebyValue(2, head);
	printf("length: %d\n", Length(head));
	PrintList(head);
	head = Sort(head);
	printf("list1: ");PrintList(head);*/

	/*head = ReverseList(head);
	PrintList(head);*/

	/*LinkList* kth = GetRKthNode(head, 1);
	if (kth)
	printf("1th��%d\n", kth->value);*/

	/*LinkList *mid = GetMiddleNode(head);
	if (mid)
		printf("mid : %d\n", mid->value);*/

	/*RPrintListRecursively(head);
	printf("\n");
	RPrintList(head);*/

	//LinkList *head = BuildList();
	//LinkList *headb = BuildList();
	//printf("list2: ");PrintList(headb);
	//LinkList *head_merge = MergeList(head, headb);
	////LinkList *head_merge = MergeListRecursively(head, headb);
	//printf("list merge: ");PrintList(head_merge);

	/*
	//LinkList* head = (LinkList*)malloc(sizeof(LinkList));
	//head->next = head;
	LinkList *head = BuildList();
	LinkList *temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = head;
	if (HasCircle(head)) {
		printf("yes\n");
	}
	else
		printf("no\n");*/
	
	/*LinkList *head = BuildList();
	LinkList *temp = head;
	while (temp->next)
		temp = temp->next;
	LinkList* headb = BuildList();
	temp->next = headb->next->next;
	LinkList* p = GetFirstCrossNode(head, headb);
	if (p)
		printf("%d\n", p->value);*/
}