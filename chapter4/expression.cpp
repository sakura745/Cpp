#include <iostream>

void fun(int p1, int p2) {
    std::cout << p1 << ' ' << p2 << '\n';
}
int main() {
    int x = 0;
    fun(x = x + 1, x = x + 1);
    /*
     * g++:
     * x = x + 1 -> arg1
     * x = x + 1 -> arg2
     * p1 = arg1
     * p2 = arg2
     *
     * clang++:
     * x = x + 1 -> arg1
     * p1 = arg1
     * x = x + 1 -> arg2
     * p2 = arg2
     */

    int y = 0;
    y = y + 1;
    y = y + 1;
    fun(y, y);
}