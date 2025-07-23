// เขียนโปรแกรมภาษา C หรือ C++ เพื่อ คำนวนพี้น ที่ของสี่เหลี่ยมรูปหนึ่ง
// โดยรับข้อมูลความกว้างและความยาวจากผู้ใช้
// โดยแบ่ง ออกเป็น 3 ฟังก์ชัน (มีการรับส่งพารามิเตอร์ ห้ามใช้ตัวแปร global)
// - การรับข้อมูล (สำหรับรับข้อมูลความกว้าง, ความยาว)
// - การหาพี้นที่
// - การแสดงผลลัพธ์พี้นที่
// (Note: แก้ไขจากโปรแกรมในหน้า 34 ใน lecture6 ให้มี 3 ฟังก์ชัน)
// ส่งเป็นโปรแกรมภาษา C หรือ C++

// Suphawinee Chatasawapreeda
// ===================================================
#include <iostream>
using namespace std;

void inputSize(float *width, float *length) {
    cout << "Enter width : ";
    cin >> *width;
    cout << "Enter length : ";
    cin >> *length;
}

void calRecArea(float w, float l, float *pArea) {

    *pArea = w * l;
}

void displayArea(float area) {
    cout << "Rectangle area is " << area << endl;
}

int main() {

    float width, length, area;
    inputSize(&width, &length);
    calRecArea(width, length, &area);
    displayArea(area);
    return 0;
}