#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int num;
    struct node *next;
} Node;

typedef struct linked_list {
    int length;
    Node *head;
} NumList;

Node *newNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->next = NULL;
    return p;
}

void initList(NumList *n) {
    n->head = NULL;
}

void appendHeadList(NumList *s, Node *p) {
    if(s->head == NULL) {
        s->head = p;
    } else {
        p->next = s->head;
        s->head = p;
    }
}

/*
insert node เข้าใน list ที่เรียงลำดับ(Sorted)
-ให้เขียนฟังก์ชัน InsertBetween( ) เพิ่มสมาชิกใหม่เข้าไปแทรก
ระหว่าง node ที่มีค่าตัวเลขที่น้อยและตัวเลขที่มาก ของ linked list
*/

void InsertBetween(NumList *s, Node *p) {
    Node *curr = s->head, *prev = NULL;

    while(curr && p->num > curr->num) { // run each node for check
        prev = curr;
        curr = curr->next;
    }

    if(!prev) {
        p->next = s->head; // insert first node
        s->head = p;
    } else {
        prev->next = p;
        p->next = curr;
    }
}

void printNumList(NumList L) {
    Node *pCurr = L.head;

    while(pCurr != NULL) {
        printf("Num: %d\n", pCurr->num);
        pCurr = pCurr->next;
    }
}

int main() {
    NumList NL;
    Node *N;
    initList(&NL);
    for(int i = 5; i >= 0; i-=2) {
        N = newNode();
        N->num = i;
        appendHeadList(&NL, N);
    }

    Node *test = newNode();
    test->num = 2;
    InsertBetween(&NL, test);

    printNumList(NL);
    return 0;
}