#include <cstdio>
#include <iostream>

/**
 * 贝格尔编排法:
 *     设长度为n的序列，如果n为奇数则取n+1 否则取n为实际长度为len
 *     将序列对折成"U"型的形状
 *     [固定数]在每一轮交替放置到第一个元素和最后一个元素
 *     其他元素每一轮逆时针轮转 len/2-1 个索引数
 *
 * 例如: 长度6的编排
 * Round: 1  Round: 2  Round: 3  Round: 4  Round: 5
 * 1 <=> 6   6 <=> 4   2 <=> 6   6 <=> 5   3 <=> 6
 * 2 <=> 5   5 <=> 3   3 <=> 1   1 <=> 4   4 <=> 2
 * 3 <=> 4   1 <=> 2   4 <=> 5   2 <=> 3   5 <=> 1
 */

void beagle_arrangement(int n) {
    printf("----beagle_arrangement(%d)\n", n);
    int len = (n % 2 == 1) ? n+1 : n; //偶数化的队伍数
    int halfNum = len/2; //长度的一半
    int moveNum = halfNum-1; //每次移动索引数
    int lastElemIdx = len-1;
    //初始化队伍索引数组

    for (int r=0; r<len-1; r++) {
        printf("Round: %2d \t", r+1);
    }
    printf("\n");
    for (int j=0; j<halfNum; j++) {
        for (int r=0; r<len-1; r++) {
            //贝格尔编排法-轮转

            //当前轮次每个元素总共移动索引位
            //NOTE 因为是计算那个索引的元素会移动到当前索引所以需要用lastElemIdx-moveNum
            int roundMoveNum = r*(lastElemIdx-moveNum);
            int p = (j + roundMoveNum)%lastElemIdx;
            int q = (lastElemIdx-j + roundMoveNum)%lastElemIdx;
            if (j==0) {
                q = (lastElemIdx == n) ? -1 : lastElemIdx; //最后一个元素需要特殊处理
                if (r%2==1) {
                    std::swap(p, q); //每个轮次交替交换[固定数的位置]
                }
            }
            printf("%-2d <=> %-2d\t", p+1, q+1);
        }
        printf("\n");
    }
}

int main() {
    beagle_arrangement(10);
    beagle_arrangement(5);
    return 0;
}
