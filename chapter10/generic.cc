#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator> //引入istream_iterator
#include <sstream>
#include <numeric>
#include <iomanip>//引入quote

#include <chrono>
#include <random>
#include <ratio>
#include <execution>//并发算法


int main() {
    std::vector<int> x(100);
    std::sort(std::begin(x), std::end(x));//sort是算法，独立于类
    std::sort(x.begin(), x.end());//begin end是方法，获取迭代器。但是对于容器可以通过方法来获取迭代器。
    // 内建类型没有方法，只能通过算法来获取迭代器

    std::list<int> a;
    a.sort();//sort是方法，在类里面定义。不是算法

    int y[100];//内建类型不支持方法 没有y.sort()
    std::sort(std::begin(y), std::end(y));//也可以运行
    //对于vector 来说 begin end属于迭代器。
    //对于y[100]来说，begin end属于指针，也是迭代器。迭代器是模拟指针的，更广泛的一种指针。


    std::vector<int> v{1, 2, 2, 3, 4, 4, 5};
    //unique需要是有序的。unique是删除连续的元素
    //使用 std::unique 函数去除重复元素
    auto last = std::unique(v.begin(), v.end());
    // 输出去重后
    for (auto it = v.begin(); it != last; ++it) {
        std::cout << *it << " ";//1 2 3 4 5
    }
    std::cout << std::endl;
    // 输出去重后的整体
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";//1 2 3 4 5 4 5 就意味着前几位是排序好，去重之后。剩余的元素不动，留下了 4，5
    }
    std::cout << std::endl;
    std::cout << "-------------------------" << std::endl;

    ///特殊迭代器

    ///back_insert_iterator
    std::vector<int> a1;
    //std::fill_n(a1.begin(), 10, 3);//illegal 会造成缓冲区溢出。因为a1没有预留空间，
    // 而fill_n是对OutputIt first进行递增:*first++ = value;
    //back_insert_iterator 也提供了 递增++ 解引用* 赋值= ，因此在底层也可以使用fill_n，只需要修改一下迭代器
    std::fill_n(std::back_insert_iterator<std::vector<int>>(a1), 10, 3);
    //相当于对*first++ = value; 从OutputIt改成了 back_insert_iterator,把 赋值= 从赋值改成了push_back
    //修改之后的代码过于长，不是很好书写，c++提供了 std::back_inserter 作为替代
///    std::fill_n(std::back_inserter(a1), 10, 3);//legal
    for (auto i : a1) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    ///front_insert_iterator
    std::list<int> a2;
    std::fill_n(std::front_inserter(a2), 10, 3);
    std::cout << "-------------------------" << std::endl;

    ///istream_iterator
    std::istringstream str("1 2 3 4 5 6");//str不能是"123456"，因为输入流包含了空格作为分隔符
    std::istream_iterator<int> b(str);
    std::cout << *b << std::endl;// *b 本质上是 int tmp; str >> tmp;
    //istream_iterator<int>维护一个对象。调用*b之后，如果对象空的之后，使用int tmp; str >> tmp;填充对象
    ++b;//本质是接续调用str >> tmp;刷新istream_iterator<int>维护的缓冲区
    std::cout << *b << std::endl;

    std::istream_iterator<int> b1{};//通过缺省的方式构造，来模拟迭代器的结尾位置。类似于end()。b1是哨兵sentinel类型
    //哨兵的使用可以提高代码的可读性和性能，因为它们允许在不明确指定边界条件的情况下，更容易地识别结束或边界
//    std::istream_iterator<int> b2;//legal
//    std::istream_iterator<int> b3();//illegal c++会将b3解析为函数声明，而不是对象的构造。所以要用{}

    for (; b != b1; ++b) {
        std::cout << *b << ' ';
    }
    std::cout << std::endl;

    int res = std::accumulate(b, b1, 0);//结果是0，上一步循环b已经走到b1的位置了
    std::cout << res << std::endl << "----------------" << std::endl;

    ///ostream_iterator
    std::ostream_iterator<char> oo (std::cout);//{} ()在括号里面有参数的时候，都可以。但是没有参数要注意区分
    //以防c++解析错误
    std::ostream_iterator<int> oi {std::cout, ", "};
    std::fill_n(oi, 5, -1);
    *oo++ = '\n';

    std::ostream_iterator<double> oi2 {std::cout, "; "};
    *oi2++ = 3.14;
    *oi2++ = 2.71;
    *oo++ = '\n';


    std::istringstream stream("1 2 3 4 5");
    std::copy(std::istream_iterator<int>(stream),
            std::istream_iterator<int>(),
            std::ostream_iterator<int>(std::cout, " ")
    );
    std::cout << std::endl << "-------------------------" << std::endl;
    ///反向迭代器
    std::vector<int> c{1, 3, 5, 6, 8, 9};
    std::copy(c.begin(), c.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
    std::copy(c.rbegin(), c.rend(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
    std::cout << std::endl << "-------------------------" << std::endl;

    ///move_iterator
    std::string d = "abc";
    auto e = d;
    std::cout << d << std::endl;
    auto e2 = std::move(d);//move_iterator 类似与move
    std::cout << d << std::endl; //被移动了，没有输出

    std::vector<std::string> vv{"this", "_", "is", "_", "an", "_", "example"};
    auto print_v = [&](auto const rem) {
        std::cout << rem;
        for (const auto& s : vv)
            std::cout << std::quoted(s) << ' ';
        std::cout << '\n';
    };
    print_v("Old contents of the vector: ");

    //可以避免不必要的拷贝，而是将所有权转给accumulate算法。accumulate原本是传值拷贝
    std::string concat = std::accumulate(std::make_move_iterator(vv.begin()),
                                         std::make_move_iterator(vv.end()),
                                         std::string());
    // An alternative that uses std::move_iterator directly could be:
    // using moviter_t = std::move_iterator<std::vector<std::string>::iterator>;
    // std::string concat = std::accumulate(moviter_t(v.begin()),
    //                                      moviter_t(v.end()),
    //                                      std::string());

    // Starting from C++17, which introduced class template argument deduction,
    // the constructor of std::move_iterator can be used directly without
    // template parameters in most cases:
    // std::string concat = std::accumulate(std::move_iterator(v.begin()),
    //                                      std::move_iterator(v.end()),
    //
    print_v("New contents of the vector: ");
    std::cout << "Concatenated as string: " << quoted(concat) << '\n';
    std::cout << std::endl << "-------------------------" << std::endl;

    ///并发算法
    std::random_device rd;
    std::vector<double> vals(10000000);
    for (auto& dd : vals) {
        dd = static_cast<double>(rd());
    }

    for (int i = 0; i < 5; ++i) {
        using namespace std::chrono;
        std::vector<double> sorted(vals);
        const auto startTime = high_resolution_clock::now();
//        std::sort(sorted.begin(), sorted.end());//800ms左右
//        std::sort(std::execution::seq, sorted.begin(), sorted.end());//800ms左右
//        std::sort(std::execution::par, sorted.begin(), sorted.end());//200ms左右
        std::sort(std::execution::par_unseq, sorted.begin(), sorted.end());//250ms左右
//        std::sort(std::execution::unseq, sorted.begin(), sorted.end());//800ms左右
        const auto endTime = high_resolution_clock::now();
        std::cout << "Latency: "
                  << duration_cast<duration<double, std::milli>>(endTime - startTime).count()
                  << " ms" << std::endl;
    }
    //可以某些算法提供policy，具体对于速率的影响要具体测试

}
