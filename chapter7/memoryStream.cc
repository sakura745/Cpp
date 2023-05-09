#include <iostream>
#include <sstream>
#include <iomanip>

int main() {

//    std::ostringstream obj1;
//    obj1 << std::setw(10) << std::setfill('.') << 10;
//    std::string res = obj1.str();
//    std::cout << res << std::endl;
//    std::cout << "---------------" << std::endl;


    std::ostringstream obj1;
    obj1 << 10;
    std::string res = obj1.str();
    std::istringstream obj2(res);//输入流，初始化要给一个内存。输入到内存中，内存要给
    int x;
    obj2 >> x;
    std::cout << x << std::endl;
    std::cout << "---------------" << std::endl;

    std::ostringstream buf("test", std::ios_base::ate);
    buf << '1';
    std::cout << buf.str() << '\n';
    std::cout << "---------------" << std::endl;

    std::ostringstream buf2("test");
    buf2 << '1';//输入的初始模式为第一个，'1'会将`t`代替
    std::cout << buf2.str() << '\n';//str()是c++风格字符串
    std::cout << "---------------" << std::endl;

    std::ostringstream buf3("test");
    buf3 << '1';

    std::string res3 = buf3.str();
    auto c_res3 = res3.c_str();//c_str()是c风格字符串
    std::cout << c_res3 << std::endl;

    //c++reference: std::basic_string<CharT,Traits,Allocator> str() const; 右值
    auto c_res32 = buf3.str().c_str();
    std::cout << c_res32 << std::endl;//程序行为是未定义的，是因为buf3.str()是右值，执行完，将会被释放掉。c_res32指向了未定义的内存地址

    std::cout << buf3.str().c_str() << std::endl;//是可以的
    std::cout << "---------------" << std::endl;


    std::string a;
    a += "Hello";//内存不断开辟 释放
    a += " World";
    a += " Hello";
    a += " World";
    std::cout << a << std::endl;

    std::ostringstream obj3;
    obj3 << "Hello";//性能变好，因为流会维护一个较大缓冲区
    obj3 << " World";
    obj3 << " Hello";
    obj3 << " World";
    std::cout << obj3.str() << std::endl;
    std::cout << "---------------" << std::endl;

}