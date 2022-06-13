#include <iostream>
#include <vector>

int main() {
    constexpr size_t buffer_count = 10001;
    std::vector<size_t> buffer(buffer_count);
    for (size_t i = 0; i < buffer_count; ++i) {
        buffer[i] = i;
    }

    size_t max_value = buffer[0];
    auto ptr = buffer.begin();

    /*第一步
    for (size_t i = 0; i + 8 < buffer_count; i += 8) {//处理 前8的倍数个元素 1-8 9-16 ...
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
    }
    switch (buffer_count % 8) {//处理 后余8的最后几个 8000-最后
        case 7 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 6 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 5 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 4 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 3 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 2 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 1 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
    }
    */

    /*第一步优化
    switch (buffer_count % 8) {//处理 前几个余数 如果是22个 处理1-6
        case 0 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 7 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 6 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 5 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 4 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 3 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 2 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
        case 1 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
    }
    for (size_t i = 0; i < (buffer_count - 1) / 8 //-1是为了处理后（-1是因为后）8n个
     ; ++i) {//处理7-14 15-22
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
    }
    */

    //最终
    size_t i = 0;
    switch (buffer_count % 8)
        for (/*switch会跳过一个变量的定义，会出现error，因此提到61行的位置*/; i < (buffer_count - 1 + 8) / 8; ++i) {
            [[fallthrough]];
            case 0 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 7 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 6 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 5 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 4 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 3 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 2 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 1 : max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        }

    std::cout << max_value << std::endl;
}
