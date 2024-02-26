#include <iostream>

int main() {
   //before C17
   int x = -1;
   if (x > 2) {
       std::cout << "x > 2\n";
   } else if (x > 0)
       std::cout << "x > 0\n";
   else
       std::cout << "x <= 0\n";

   int grade = 59;
   if (grade > 60) {
       if (grade > 80)
           std::cout << "Excellent\n";
//       else
//           std::cout << "Good\n";
   } else
       std::cout << "Bad!\n";

   //from C17 编译器选择分支，删除不满足条件的分支。优化
   constexpr int grade2 = 80;
   if constexpr (grade2 < 60) {
       std::cout << "Fail\n";
   } else {
       std::cout << "Pass\n";
       if constexpr (grade2 == 100) {
           std::cout << "Excellent\n";
       } else {
           std::cout << "Not bad\n";
       }
   }


   int a = 3;
   {
       int b = 3 * a;//希望b是不可见的，在c++17之前加上域{}
       if (b > 100) {

       } else {

       }
       // ...没有用到b
   }

   //from C17
   if (int b = 3 * a; b > 100) {

   } else {

   }

   //before c17
   int y;
   std::cin >> y;
   switch (y) {
       case 2 + 1://case 3:
           std::cout << "Hello\n";
   }

   //from c17
   int z;
   switch (std::cin >> z; z) {
       default:
           std::cout << "China\n";
           break;
       case 2 + 1://case 3:
            std::cout << "Hello\n";
            break;
       case 4:
            std::cout << "World\n";
            break;
       case 5://5和6共享逻辑
       case 6:
           std::cout << "Beijing\n";
           break;
       case 7:
           std::cout << "Harbin\n";
           [[fallthrough]];//c++17：表示[[fallthrough]]属性，除去部分编译器的warning.是为了告知编译器，需要这种特性。
       case 8:
           std::cout << "Heilongjiang\n";
           break;
   }
}
