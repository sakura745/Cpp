#include <iostream>
#include <fstream>

int main() {

    //iostate -- char假设char是实例
    //原理展示，都是位设置，类似与ios_base::in ...
    //badbit  -- 0000 0001
    //failbit -- 0000 0010
    //eofbit  -- 0000 0100
    //位掩码类型
    //iostate m_state : 0000 0011 类似读写执行权限，goodbit为 0000 0000

    //构造没有关联
//    std::ofstream outFile;
//    outFile << 10;//outFile会产生badbit错误--不可恢复的错误

//    int x;
//    std::cin >> x;
//    //但终端不输入整型，输入"Hello"，cin会产生failbit -- 可以恢复的流错误

//    std::ofstream outFile;
//    outFile.close();//outFile已经是关闭状态，再设置close，也会产生failbit

//    int x;
//    std::cin >> x;
//    //在linux系统中，终端输入`Ctrl + d`会直接结束该终端输入。因为它的意思是输入"达到了终端输入的结尾"
//    //eofbit 与输入序列有关

//    int x;
//    std::cin >> x;
//    std::cout << std::cin.good()
//              << std::cin.fail()
//              << std::cin.bad()
//              << std::cin.eof()
//              << static_cast<bool>(std::cin) << std::endl;
//    //对终端直接输入`Ctrl + d` 会显示01010  显示eof被设置
//    //输入10 输出10001
//    //输出的01010和10001中，fail 和 eof都相同（01010都是1，10001都是0）


//    char x;
//    std::cin >> x;
//    std::cout << std::cin.fail() << " " << std::cin.eof() << std::endl;
//    std::cin >> x;
//    std::cout << std::cin.fail() << " " << std::cin.eof() << std::endl;
//    //前面输出有字符，想要主动eof，需要摁两次`ctrl + d`
//    //终端输入a 两次主动eof
//    // 结果为
//    // a0 0
//    // 1 1 fail eof同时设置

//    int x;
//    std::cin >> x;
//    std::cout << " " << std::cin.fail() << " " << std::cin.eof() << std::endl;
//    //输入10 两次主动eof、
//    //结果为10 0 1 fail eof不会被同时设置
//    //读char和int处理方法不一样，char就一个字节，int不一定多少个字节

//    int x;
//    if (std::cin >> x) {//if中的内容被隐式转化为bool类型，static_cast<bool>(std::cin)的值
//    }

    std::ifstream file("../example.txt");
    int x;

    // 尝试读取文件中的数据
    file >> x;

    if (file.fail()) {
        std::cout << "Failed to read data from the file." << std::endl;
        // 复位流的状态
        file.clear(); // 将流的状态复位为正常
        // 或者使用 setstate() 设置特定状态
        file.setstate(std::ios_base::goodbit); // 设置流的状态为正常
    }
    // 继续使用流进行操作
    file >> x; // 现在可以继续使用流
    std::cout << x << std::endl;
}
