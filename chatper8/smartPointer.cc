#include <iostream>
#include <new>
#include <memory>//引入share_ptr unique_ptr

int* fun() {
    int* res = new int(100);
    return res;
}

std::shared_ptr<int> fun1() {
    std::shared_ptr<int> res(new int(100));
    return res;
}

void fun2(int*) {

}

void fun3(int *ptr) {
    std::cout << "fun3 is called~" << std::endl;
    delete ptr;
}

std::unique_ptr<int> fun4() {

//    std::unique_ptr<int> res(new int(100));
    auto res = std::make_unique<int>(3);
    return res;
}

void fun5(int* ptr) {
    std::cout << "fun5 is called~" << std::endl;
    delete ptr;
}

struct Str{
   std::shared_ptr<Str> m_nei;
    ~Str() {
        std::cout << "~Str() is called~\n";
    }
};
struct Str1{
    std::weak_ptr<Str1> m_nei;
    ~Str1() {
        std::cout << "~Str1() is called~\n";
    }
};
int main() {
    int* y4 = fun();//内存所有权不清晰，不知道是fun调用delete还是main调用

    //shared_ptr

    //类型不同
    int* x1(new int (3));
    std::shared_ptr<int> x(new int (100));//类型为 shared_ptr<int>，不用担心内存泄漏，当x生命周期结束，调用析构函数自动销毁
    //包含引用计数默认为1，表示有多少个在引用该内存

    std::cout << *x << std::endl;
    std::cout << x.use_count() << std::endl;//引用计数

    std::shared_ptr<int> y = x;//共享一个引用计数对象，引用计数为2
    //假设系统在该行结束，系统会先对y进行销毁，引用计数：2->1，再对x销毁，计数1->0。
    //当计数为0，析构函数会对该内存进行销毁。
    //C++规则：先构造的后销毁，后构造的先销毁。
    std::cout << x.use_count() << std::endl;
    std::cout << y.use_count() << std::endl;
    {
        std::shared_ptr<int> y1 = x;
        std::cout << y1.use_count() << std::endl;
    }
    std::cout << x.use_count() << std::endl;

    auto yy1 = fun1();//不会出现问题

    std::cout << *(yy1.get()) << std::endl;// y.get()返回一个int* 指针，再解引用是对int* 指针解引用
    std::cout << *yy1 << std::endl;//是对智能指针解引用

    //fun2(y);//illegal
    fun2(yy1.get());//为了和正常指针相互调用而引入的get

    yy1.reset(new int(50));//先对yy1原有的进行引用计数减1，如果为0，则释放内存，重新接受50这块内存，计数变为1
    yy1.reset((int*) nullptr);//不关联任何资源，等价于std::shared_ptr<int> x;

    std::shared_ptr<int> x2(new int(100), fun3);
    //计数减一，为零。调用销毁函数：会执行fun3对应的代码，并销毁int(100)的内存。自定义销毁函数。fun3函数指针

    //shared_ptr有两个地址，一个存储100，一个存储引用技术，都是在heap上。这两个地址可能差的很远，用缓存进行读写，可能造成性能损失
    std::shared_ptr<int> ptr(new int(100));
    std::shared_ptr<int> ptr2 = std::make_shared<int>(99);//改成 auto ptr2 = std::make_shared<int>(99);也可以
    //make_shared分配一块内存写入99，同时分配给引用计数的内存。放的尽量近。对shared_ptr的优化

    std::shared_ptr<int[]> ptr3(new int[5]);//c17
    auto ptr4 = std::make_shared<int[]>(5);//c20

    std::shared_ptr<int> a(new int(100));
    std::shared_ptr<int> b(a);//a的两个信息（内存信息和引用计数）都给b
//    std::shared_ptr<int> c(a.get());//导致double free错误，只有内存信息给了c

    int* p = new int(40);
    //p2先销毁，释放一次p。p1再销毁，又释放p。double free
    std::shared_ptr<int> p1(p);
//    std::shared_ptr<int> p2(p);//double free
    std::cout << "--------------------" << std::endl;


    //unique_ptr
    std::unique_ptr<int> xx(new int(100));//xx独占
    std::cout << xx.get() << std::endl;
//    std::unique_ptr<int> yy = xx;//illegal
    std::unique_ptr<int> yy = std::move(xx);
    std::cout << xx.get() << std::endl;
    std::cout << yy.get() << std::endl;

    //这不是拷贝，函数内部是移动的方式到临时对象，临时对象初始化zz
    //把资源所有权从res给到zz
    std::unique_ptr<int> zz = fun4();
    std::unique_ptr<int, decltype(&fun5)> ww(new int(100), fun5);//指定回收内存
    std::cout << "--------------------" << std::endl;

    //weak_ptr

    //循环引用，指针指向内存不能被释放.Str中为shared_ptr
    std::shared_ptr<Str> xxx(new Str{});
    std::shared_ptr<Str> yyy(new Str{});
    xxx->m_nei = yyy;
    yyy->m_nei = xxx;

    //将Str中改为weak_ptr
    //引入weak_ptr。weak与shared共享一块内存，但不会影响shared的引用计数
    std::shared_ptr<Str1> xxxx(new Str1{});
    std::shared_ptr<Str1> yyyy(new Str1{});
    xxxx->m_nei = yyyy;
    yyyy->m_nei = xxxx;

    //引用计数的引入是为了释放内存不出现问题，但是weak会对引用计数的做法产生影响
    //如何同时使用weak且不影响计数
    //lock() :把weak作为shared，来判断shared的有效性，来决定是否继续使用指针
    if (auto ppp = xxxx->m_nei.lock(); ppp) {
        std::cout << "Can access pointer\n";
    } else {
        std::cout << "Can not access pointer\n";
    }


    std::cout << "--------------------" << std::endl;
}