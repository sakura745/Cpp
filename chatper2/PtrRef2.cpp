#include <iostream>

void fun(int) {
    std::cout << "1\n";
}
void fun(int*) {
    std::cout << "2\n";

}
int main() {
    fun(0);//会匹配到int
    int* p = 0;
    fun(p);//会匹配到int*
    fun(nullptr); 
}

