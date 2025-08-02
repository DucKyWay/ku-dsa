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

// void solve(int n, int x) {
//     Node *head = createCircle(n);
//     Node *prev = NULL;
//     Node *curr = head;

//     while(n > 0) {
//         for(int i = 0; i < x - 1; i++) {
//             prev = curr;
//             curr = curr->next;
//         }
//         printf("%d", curr->data);
//         if(n != 1) printf(" ");

//         prev->next = curr->next;

//         if(curr == head) head = curr->next;

//         Node *temp = curr;
//         curr = curr->next;
//         free(temp);

//         n--;
//     }
//     printf("\n");
// }

void solve(int n, int x) {
    Node* head = createCircle(n);
    Node* prev = NULL;
    Node* curr = head;

    while(n > 0) {
        for(int i = 1; i < x; i++) {
            prev = curr;
            curr = curr->next;
        }

        printf("%d", curr->data);
        if(n != 1) printf(" ");

        // ลบ curr
        if(curr == prev) {
            free(curr);
            break;
        }

        prev->next = curr->next;

        if(curr == head) {
            head = curr->next;
        }

        Node* temp = curr;
        curr = curr->next;
        free(temp);
        n--;
    }

    printf("\n");
}

int main() {
    int n, x;
    scanf("%d", &n);
    scanf("%d", &x);
    solve(n, x);

    return 0;
}