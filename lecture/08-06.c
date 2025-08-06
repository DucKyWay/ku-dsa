/* สุภาวิณี ฉัตรอัศวปรีดา 6710405541 รายวิชา 01418231 Data Structure and Algorithms (Sec 1) Semester 1/2568*/

/*
ฟังก์ชัน an = an-1 + 3; a1 = 2
Sequence a = {2, 5, 8,...}
เขียนโปรแกรมภาษาซี สำหรับเรียกและประมวลผลฟังก์ชัน recursion ของฟังก์ชันเวียนบังเกิด a(n) = a(n-1)+3  
และเขียนแผนภาพการเรียกฟังก์ชัน a(5)
*/

#include <stdio.h>

int a(int n) { // recursion
    if (n == 1) {
        return 2; // base case
    } else {
        return a(n - 1) + 3;
    }
}

int main() {
    int result = a(5);
    printf("a(%d) = %d\n", n, result);
    return 0;
}

/* แผนภาพ a(5)
a(5)
|
|-- a(4)
│   |-- a(3)
│   │   |-- a(2)
│   │   │   |-- a(1) = 2
│   │   │   --- +3 = 5
│   │   --- +3 = 8
│   --- +3 = 11
--- +3 = 14
*/
