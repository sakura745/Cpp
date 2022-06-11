#include <iostream>

int main() {
    for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 5; ++k) {    //only this loop is affected by break
            if (k == 2) break;           //跳出单层for循环
            std::cout << j << k << ' ';  //
        }
    }

    std::cout << '\n';

    for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 5; ++k) {    //only this loop is affected by break
            if (k == 2) goto label;      //跳出多层for循环
            std::cout << j << k << ' ';  //
        }
    }
label:
    ;

    std::cout << '\n';

    for (int i = 0; i < 10; i++) {
        if (i != 5) continue;
        std::cout << i << " ";       //this statement is skipped each time i!=5
    }

    std::cout << '\n';

    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 5; k++) {   //only this loop is affected by continue
            if (k == 3) continue;
            std::cout << j << k << " "; //this statement is skipped each time k==3
        }
    }
}
