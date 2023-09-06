#include <fstream>
#include <iostream>
#include <string>

int main() {
    ///ofstream 和 ifstream关联到同一个文件时，只有一个有效。处于打开状态的无法再次打开

//    std::ofstream outFile("my_file");//把 my_file 这个文件与outFile关联起来了, my_file的位置是根据可执行程序同一个路
//    径下的
//    outFile << "Hello\n";

//    std::ifstream inFile("my_file");//把 my_file 这个文件与inFile关联起来了
//    std::cout << inFile.is_open() << '\n';//检测文件是否打开，返回值为bool
    //打开文件意味着你的程序可以从文件中读取数据，如果文件不存在、权限不足或其他原因导致文件无法打开
//    std::string x;
//    inFile >> x;
//    std::cout << x << '\n';
//    std::cout << "---------------" << std::endl;


    //这种关闭打开方式不常见
//    std::ofstream outFile;//缺省方式构造
//    std::cout << outFile.is_open() << '\n';//输出0，outFile没有关联任何文件，没有打开
//    outFile.open("my_file");//另一种关联方式
//    std::cout << outFile.is_open() << '\n';//输出1
//    outFile.close();
//    std::cout << outFile.is_open() << '\n';//输出0


    //多数用这种
//    {//使用域的形式，域结束可以自动关闭文件
//        std::ofstream outFile("my_file");
//        outFile << "Hello\n";
//    }

//        std::ofstream outFile("my_file", std::ios_base::out);//第二个参数给了缺省值
//        //参数可以组合： "std::ios_base::in | std::ios_base::ate"
//        //为什么用 "|" 来使用呢
//        //C++在构造时，原理是用 0010 表示 std::ios_base::in
//        //                      0001 表示 std::ios_base::ate
//        //0010 0001只是用来表示原理，而不是真实使用

    //清除原有内容，写入文件（对程序来说是输出，对文件来说是写入）
    std::ofstream outFile("my_file", std::ios_base::out | std::ios_base::trunc);
    outFile << "World\n";

}

