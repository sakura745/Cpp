#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>

std::vector<long> randomArray(const auto& maxSize, const auto& maxValue) {
    std::srand(time(nullptr));
    std::vector<long> arr(maxSize);
    for(auto & i : arr){
        i =  std::rand() % maxValue + 1;
    }
    return arr;
}
int main() {
    long maxSize = 99999999;
    long maxValue = 999999999;

    long maxV = 0;
    long maxV2 = 0;
    long maxV3 = 0;

    std::vector test = randomArray(maxSize, maxValue);

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    for (auto& i : test) {
        maxV = maxV > i ? maxV : i;
    }
    std::cout << maxV << std::endl;
    std::chrono::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time1 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "For-Range spent times is " << time1.count() << "s" << std::endl << std::endl;

    long index = 0;
    auto ptr = test.begin();
    switch (maxSize % 8)
        for (;index < (maxSize + 7) / 8; ++index) {
            case 0: maxV2 = maxV2 > *ptr ? maxV2 : *ptr; ++ptr;
            case 7: maxV2 = maxV2 > *ptr ? maxV2 : *ptr; ++ptr;
            case 6: maxV2 = maxV2 > *ptr ? maxV2 : *ptr; ++ptr;
            case 5: maxV2 = maxV2 > *ptr ? maxV2 : *ptr; ++ptr;
            case 4: maxV2 = maxV2 > *ptr ? maxV2 : *ptr; ++ptr;
            case 3: maxV2 = maxV2 > *ptr ? maxV2 : *ptr; ++ptr;
            case 2: maxV2 = maxV2 > *ptr ? maxV2 : *ptr; ++ptr;
            case 1: maxV2 = maxV2 > *ptr ? maxV2 : *ptr; ++ptr;
        }
    std::cout << maxV2 << std::endl;
    std::chrono::time_point t3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time2 = std::chrono::duration_cast<std::chrono::duration<double>>(t3 - t2);
    std::cout << "DuffsDevice spent times is " << time2.count() << "s" << std::endl << std::endl;

    for (size_t i = 0; i < test.size(); ++i) {
        maxV3 = maxV3 > test[i] ? maxV3 : test[i];
    }
    std::cout << maxV3 << std::endl;
    std::chrono::time_point t4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time3 = std::chrono::duration_cast<std::chrono::duration<double>>(t4 - t3);
    std::cout << "Normal loop spent times is " << time3.count() << "s" << std::endl;
}

