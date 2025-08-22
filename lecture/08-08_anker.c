// สุภาวิณี ฉัตรอัศวปรีดา 6710405541

/*
* ทำ assignment หน้า 16 lecture 10
* เขียนโปรแกรมภาษา C และ แผนภาพเรียก ack(1,1)
* เขียนผลลัพธ์ของ ack(1,1)
*/

#include <stdio.h>

int ack(int m, int n) {

    if(m > 0 && n > 0) {
        return ack(m - 1, ack(m, n - 1));
    } else if(m > 0 && n == 0) {
        return ack(m - 1, 1); 
    } else if(m == 0) {
        return n + 1;
    } else return -1;
}

int main() {
    
    printf("%d\n", ack(2, 1));    
    printf("%d", ack(1, 1));    
    return 0;
}