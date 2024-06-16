#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <memory>

int main() {
    int* ptr = new int(3);
    int* ptr1 = new int[3];
    std::cout << sizeof(ptr) << std::endl;
    std::cout << sizeof(ptr1) << std::endl;

    std::vector<int> x;
    std::cout << sizeof(x) << std::endl;//获取x指针的大小+其他辅助内存。sizeof是编译期，vector赋值是运行期
    std::cout << "--------------------" << std::endl;

    std::allocator<int> al;//分配器
    int* ptr2 = al.allocate(3);//分配了内存，并没有构造对象
    //在分配的内存上，可以使用placement new 构造对象
    new (ptr) int(12);
    new (ptr + 1) int(13);
    new (ptr + 2) int(14);
    //在释放通过分配器分配的内存时，有：对于int型，无需手动调用析构函数销毁对象。但是对于其他类型，记得要手动调用析构函数销毁对象
    al.deallocate(ptr2, 3);//这个3和分配的3必须相等
    std::cout << "--------------------" << std::endl;

    //malloc free只会分配和回收内存，不对构造和析构对象.c++中类的提出才明确构造和析构。按字节分配

    int *p1 = (int*)malloc(4 * sizeof(int));  // allocates enough for an array of 4 int
    int *p2 = (int*)malloc(sizeof(int[4])); // same, naming the type directly
    int *p3 = (int*)malloc(4*sizeof *p3);   // same, without repeating the type name

    if (p1) {
        for (int n = 0; n < 4; ++n) // populate the array
            p1[n] = n * n;
        for (int n = 0; n < 4; ++n) // print it back out
            printf("p1[%d] == %d\n", n, p1[n]);
    }

    free(p1);
    free(p2);
    free(p3);
    std::cout << "--------------------" << std::endl;


}