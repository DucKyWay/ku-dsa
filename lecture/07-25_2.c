/*
ส่งโปรแกรมภาษา C โดยดูตัวอย่างจากหน้า 23 ใน lecture 5
โดยสมมติการ insert node เข้าใน list ที่เรียงลำดับ(Sorted)
-ให้เขียนฟังก์ชัน InsertBetween( ) เพิ่มสมาชิกใหม่เข้าไปแทรกระหว่าง node ที่มีค่าตัวเลขที่น้อยและตัวเลขที่มาก ของ linked list.
*/

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
    for(int i = 0; i < 3; ++i) {
        N = newNode(i);
        N->num = i;
        appendHeadList(&NL, N);
    }

    printNumList(NL);
    return 0;
}