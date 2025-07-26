/*
ให้เขียนคำสั่งสร้างประเภทข้อมูลขึ้นเอง ในภาษาซี
โดยมีโครงสร้างข้อมูลสำหรับ node 2 ทิศทาง  
โดย data เป็น integer
    LLINK->DATA->RLINK
• เขียนฟังก์ชัน newNode() สร้างโหนดใหม่
• ใน main() ให้เขียนตัวแปร first เป็นโหนดแรก มีค่า data = 3  
  ให้เขียนตัวแปร second เป็นโหนดถัดมา มีค่า data = 5
และให้เชื่อมต่อ first กับ second แบบ Ordinary Doubly Linked List
*/

#include <iostream>

using namespace std;

typedef struct node {
    int data;
    struct node *llink;
    struct node *rlink;
} Node;

Node* newNode(int value) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = value;
    p->llink = nullptr;
    p->rlink = nullptr;
    return p;
}

int main() {
    Node *first = newNode(3);
    Node *second = newNode(5);

    first->rlink = second;
    second->llink = first;
    
    cout << "First node data: " << first->data << endl;
    cout << "Second node data: " << second->data << endl;
    cout << "First->rlink->data: " << first->rlink->data << endl;
    cout << "Second->llink->data: " << second->llink->data << endl;

    return 0;
}