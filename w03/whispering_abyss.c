#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* createCircle(int n) {
    Node *head = NULL, *tail = NULL;

    for(int i = 1; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = i;
        newNode->next = NULL;

        if(head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    tail->next = head; // circle
    return head;
}

int main() {
    int n, x;
    if (scanf("%d %d", &n, &x) != 2) return 0;

    Node *head = createCircle(n);

    // prev เริ่มที่ tail
    Node *prev = head;
    while (prev->next != head) {
        prev = prev->next;
    }
    Node *curr = head;

    while (n > 0) {
        // mod โคตรเร็วหวะ
        int step = x % n;
        if (step == 0) step = n;

        // step-1
        for (int i = 1; i < step; i++) {
            prev = curr;
            curr = curr->next;
        }

        printf("%d", curr->data);
        if (n > 1) printf(" ");

        // ลบ curr
        prev->next = curr->next;
        if (curr == head) {
            head = curr->next;
        }
        Node *tmp = curr;
        curr = curr->next;
        free(tmp);
        n--;
    }

    printf("\n");
    return 0;
}