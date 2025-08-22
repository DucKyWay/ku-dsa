// สุภาวิณี ฉัตรอัศวปรีดา 6710405541

#include <stdio.h>

void tower_of_hanoi(int n, char from_rod, char aux_rod, char to_rod, int *count) {
    if(n == 0) return;
    tower_of_hanoi(n - 1, from_rod, to_rod, aux_rod, count);
    printf("move: %d from %c to %c\n", n, from_rod, to_rod);
    (*count)++;
    tower_of_hanoi(n - 1, aux_rod, from_rod, to_rod, count);
}

int main() {
    int count = 0, n;
    scanf("%d", &n);
    tower_of_hanoi(n, 'A', 'B', 'C', &count);
    printf("%d\n", count);
    return 0;
}