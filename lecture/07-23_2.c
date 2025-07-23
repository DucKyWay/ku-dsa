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
} NumList;

Node *newNode() {
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->next = NULL;
    return p;
}

void initList(NumList *n) {
    n->head = NULL;
}

int appendHeadList(NumList *s, Node *p) {
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

void main() {
    NumList NL;
    Node *N;
    initList(&NL);
    for(int i = 0; i < 3; ++i) {
        N = newNode;
        N->num = i;
        appendHeadList(&NL, N);
    }

    printNumList(NL);
    return 0;
}