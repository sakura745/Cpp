#include <iostream>
#include <stack>//引入stack
#include <vector>
#include <queue>//引入queue priority_queue

int main() {
    std::stack<int> p;
    std::stack<int, std::vector<int>/*容器从缺省deque变为vector*/> p1;
    p1.push(3);
    p1.push(2);
    p1.pop();
    p1.top();

}