#include <iostream>
#include <string>

void fun(int x) {
//void fun(const int x) {error:show redefinition

}
void fun(double x) {

}

void fun(std::string x) {

}

int main() {
    fun(3);
}