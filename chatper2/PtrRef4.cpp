#include <iostream>

void fun(int* param) {
    *param = *param + 1;
}
int main() {
    int* p1 = nullptr;
    fun(p1);//will be error
}

