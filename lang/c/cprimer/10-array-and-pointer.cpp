#include <stdio.h>

void practice1() {
    int ref[] = {8, 4, 0, 2};
    int *ptr;
    int index;

    for (index  = 0, ptr=ref; index < 4; index++, ptr++) {
        printf("%d %d \n", ref[index], *ptr);
    }
}

void practice4() {
    int *ptr;
    int torf[2][2] = {12, 14, 16};
    ptr = torf[0];
    printf("*ptr: %d, *(ptr+2): %d\n", *ptr, *(ptr + 2)); //12 16

    int fort[2][2] = {{12}, {14, 16}};
    ptr = fort[0];
    printf("*ptr: %d, *(ptr+2): %d\n", *ptr, *(ptr + 2)); //12 14
}

void practice5() {
    int (*ptr) [2];
    int torf[2][2] = {12, 14, 16};
    ptr = torf;
    printf("**ptr: %d, **(ptr+1): %d\n", **ptr, **(ptr+1)); //12 16

    int fort[2][2] = {{12}, {14, 16}};
    ptr = fort;
    printf("**ptr: %d, **(ptr+1): %d\n", **ptr, **(ptr+1)); //12 14
}

void practice6() {
    int grid[30][100];
    int *ptr11 = &grid[22][56];
    printf("ptr11: %p\n", ptr11);
    int *ptr12 = grid[22] + 56;
    printf("ptr12: %p\n", ptr12);
    int *ptr13 = *(grid + 22) + 56;
    printf("ptr13: %p\n", ptr13);

    int *ptr21 = &grid[22][0];
    printf("ptr21: %p\n", ptr21);
    int *ptr22 = grid[22];
    printf("ptr22: %p\n", ptr22);
    int *ptr23 = *(grid+22);
    printf("ptr23: %p\n", ptr23);

    int *ptr31 = &grid[0][0];
    printf("ptr31: %p\n", ptr31);
    int *ptr32 = grid[0];
    printf("ptr32: %p\n", ptr32);
    int *ptr33 = *grid;
    printf("ptr33: %p\n", ptr33);
}

void practice7() {
    int digits[10];
    float rates[6];
    int mat[3][5];
    char *psa[20];
    char (*pstr)[20];

    char strs[20];
    for (int i=0; i<20; i++) {
        strs[i] = i+65;
        psa[i] = &strs[i];
    }
    pstr = &strs;
    printf("strs:");
    for (int i=0; i<20; i++) {
        printf(" %c", strs[i]);
    }
    printf("\n");

    printf("psa:");
    for (int i=0; i<20; i++) {
        printf(" %c", *psa[i]);
    }
    printf("\n");

    printf("pstr:");
    for (int i=0; i<20; i++) {
        printf(" %c", (*pstr)[i]);
    }
    printf("\n");
}

void practice8() {
    int digits[] = {1, 2, 4, 8, 16, 32};
    int val = digits[2];
    printf("val: %d\n", val);

    int digits2[100] = {0};
    digits2[99] = -1;
    printf("digits2:");
    for (int i=0; i<100; i++) {
        printf(" %d", digits2[i]);
    }
    printf("\n");
}

void practice10() {
    float rootbeer[10], things[10][5], *pf, value = 2.2;
    int i = 3;
    rootbeer[2] = value; //T
    //scanf("%f", &rootbeer); //F
    //rootbeer = value; //F
    //printf("%f", rootbeer); //F
    things[4][4] = rootbeer[3]; //T
    //things[5] = rootbeer; //F
    //pf = value; //F
    pf = rootbeer; //T
}

int main(void) {
    printf("practice1 =====================\n");
    practice1();
    printf("practice4 =====================\n");
    practice4();
    printf("practice5 =====================\n");
    practice5();
    printf("practice6 =====================\n");
    practice6();
    printf("practice7 =====================\n");
    practice7();
    printf("practice8 =====================\n");
    practice8();
    printf("practice10 ====================\n");
    practice10();
    return 0;
}
