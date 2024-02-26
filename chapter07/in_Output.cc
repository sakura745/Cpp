#include <iostream>
#include <iomanip> //操纵符setw setfill的引入
#include <string>

int main() {
//    int x;
//    //std::cin >> x;
//
//    //这种组合会出错。因为非格式化读入，没有解析操作，格式化输出
//    //sizeof是4个字符，如果只输入1[Enter],将没有输出，再输入2 [Enter]，满足四个字符才会有输出。虽然输出结果错误
//    std::cin.read(reinterpret_cast<char*>(&x), sizeof(x));
//    std::cout << x << std::endl;

    //x1与y1输出不同，内存存储的数据相同，通过<<的重载，输出类型不同，导致最终结果不同。
    char x1 = '0';
    std::cout << x1 << std::endl;
    int y1 = static_cast<int>(x1);
    std::cout << y1 << std::endl;
    std::cout << "---------------" << std::endl;

    char x2 = '0';
    std::cout.setf(std::ios_base::showpos);//setf:flag showpos:position
    std::cout << x2 << std::endl;
    int y2 = static_cast<int>(x2);
    std::cout << y2 << std::endl;
    std::cout << "---------------" << std::endl;

    char x3 = '0';
    std::cout.setf(std::ios_base::showpos);
    std::cout.width(10);//整个输出占10个字符
    std::cout << x3 << std::endl;
    std::cout << "---------------" << std::endl;

    char x4 = '0';
    std::cout.setf(std::ios_base::showpos);
    std::cout.width(10);//读过一次就会重置
    std::cout.fill('.');//空白填充为'.'，缺省为[Space]
    std::cout << x4 << std::endl;
    std::cout.width(10);//fill就没有读过一次就重置
    std::cout << y2 << std::endl;
    std::cout << "---------------" << std::endl;

    //操纵符修改  setw就是width也会被重置，std::endl也是操纵符
    std::cout << std::showpos << std::setw(10) << std::setfill('.') << x4 << '\n'
              << std::setw(10) << y2 << '\n';
    std::cout << "---------------" << std::endl;

    //输入"00010"，会输出10；输入"    10"，会输出10；输入"+10"，也会输出10；
    int a;
    std::cin >> a;
    std::cout << a << std::endl;
    //但是int改为char就不行了
    std::cout << "---------------" << std::endl;

    //c++的字符串
    std::string b;
    std::cin >> b;
    std::cout << b << std::endl;
    std::cout << "---------------" << std::endl;

    //c语言的字符串，有越界风险，会导致报错崩溃。注字符串结束要有'\0'
    char c[5];
    std::cin >> c;
    std::cout << c << std::endl;
    std::cout << "---------------" << std::endl;

    char d[5];
    std::cin >> std::setw(5) >> d;//不会出现越界而导致系统崩溃
    std::cout << d << std::endl;
    std::cout << "---------------" << std::endl;
}