#include <iostream>
#include <string>

void fun(int x) {
//void fun(const int x) {error:show redefinition
}
void fun(double x) {}

void fun(std::string x) {}//过滤掉了，无法将实参转为形参

int main() {
    fun(3);
}