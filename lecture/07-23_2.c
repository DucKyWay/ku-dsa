/*
ส่งโปรแกรมภาษา C โดยดูตัวอย่างจากหน้า 23 ใน lecture 5
-แก้ไข Struct linked list ให้มีส่วนชี้ไปที่ head(ตัวแรก) และ last (ตัวสุดท้าย)
-แก้ไข เพิ่มคำสั่งแก้ไข  ค่า length ใน linked list
-เขียนฟังก์ชัน InsertLast( ) เพิ่มสมาชิกใหม่เข้าไปทางส่วนท้าย ของ linked list.
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
    Node *last;
} NumList;

Node *newNode(int value) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->num = value;
    p->next = NULL;
    return p;
}

void initList(NumList *n) {
    n->head = NULL;
    n->last = NULL;
    n->length = 0;
}

void appendHeadList(NumList *s, Node *p) {
    if(s->head == NULL) {
        s->head = p;
        s->last = p;
    } else {
        p->next = s->head;
        s->head = p;
    }
    s->length++;
}

void InsertLast(NumList *s, Node *p) {
    if(s->head == NULL) {
        s->head = p;
        s->last = p;
    } else {
        s->last->next = p;
        s->last = p;
    }
    s->length++;
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

    for(int i = 10; i < 12; ++i) {
        N = newNode(i);
        InsertLast(&NL, N);
    }

    printNumList(NL);
    return 0;
}