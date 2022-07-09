#include <iostream>

void print_buf(std::string prefix, int buf[], int n) {
    std::cout << prefix << "[";
    for (int i=0; i<n; i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << buf[i];
    }
    std::cout << "]" << std::endl;
}

void sort_quick(int buf[], int l, int r) {
    if (l >= r) {
        return;
    }
    int i = l;
    int j = r;
    int x = buf[i];
    while (i < j) {
        while(i < j && x <= buf[j]) j--;
        if (i < j)
            buf[i] = buf[j]; //这里表示x和buf[j]交换

        while(i < j && x >= buf[i]) i++;
        if (i < j) {
            buf[j] = buf[i]; //这里代表x和buf[i]交换
        }

    }
    buf[i] = x; //这里已经将>x的元素移动到右边， <x的元素移动到左边了
    sort_quick(buf, l, i-1);
    sort_quick(buf, i+1, r);

}

int main() {
    const int n = 10;
    int buf[][n] = {
        {8,7,9,10,5,3,4,6,2,1},
        {10,9,8,7,6,5,4,3,2,1},
        {4,3,2,1,10,9,8,7,6,5},
        {4,10,9,6,5,3,2,8,7,1},
        {4,10,9,6,5,3,2,8,7,2},
        {0,10,9,6,5,3,2,8,7,1},
        {999,7,9,10,5,3,4,6,2,1},
    };
    int buflen = sizeof(buf)/sizeof(buf[0]); //获取数组长度
    std::cout << "buflen:" << buflen << std::endl;

    for (int i=0; i<buflen; i++) {
        int *subbuf = buf[i];
        int len = n;

        //排序前打印
        std::cout << i+1 << ".-----" << std::endl;
        print_buf("    ", subbuf, len);

        //排序
        sort_quick(subbuf, 0, len-1);

        //排序前打印
        print_buf("    ", subbuf, len);
    }
    return 0;
}
