#include <iostream>
#include <sstream>
#include <string>

int main() {
    //tellp 返回当前可以写入的位置
    std::ostringstream s;
    std::cout << s.tellp() << '\n';
    s << 'h';
    std::cout << s.tellp() << '\n';
    s << "ello, world ";
    std::cout << s.tellp() << '\n';
    s << 3.14 << '\n';
    std::cout << s.tellp() << '\n' << s.str();
    std::cout << "---------------" << std::endl;

    std::string str = "Hello, world";
    std::istringstream in(str);
    std::string word;
    in >> word;
    std::cout << "After reading the word \"" << word
              << "\" tellg() returns " << in.tellg() << '\n';
    //输出word时，只输入到 Hello,  后面world没有被打出来，是因为标准输入流在处理字符串时，会读取信息直到遇到分隔符。
    //[space]就是一个典型的分隔符。
    std::cout << "---------------" << std::endl;


    std::string str2 = "Hello, world";
    std::istringstream in2(str2);
    std::string word1, word2;

    in2 >> word1;
    in2.seekg(0); // 回溯
    in2 >> word2;

    std::cout << "word1 = " << word1 << '\n'
              << "word2 = " << word2 << '\n';
    std::cout << "---------------" << std::endl;

    std::ostringstream os("hello, world");
    os.seekp(7);//绝对位置
    os << 'W';
    os.seekp(0, std::ios_base::end);//相对位置
    os << '!';
    os.seekp(0);
    os << 'H';
    std::cout << os.str() << '\n';

}