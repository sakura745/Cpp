#include <iostream>
#include <vector>

int main() {
    //建造一个buffer用来进行找取最大值
    constexpr size_t buffer_count = 10001;
    std::vector<size_t> buffer(buffer_count);
    for (size_t i = 0; i < buffer_count; ++i) {
        buffer[i] = i;
    }

/*  for (size_t i = 0; i < buffer_count; ++i) {
 *      max_value = (max_value > buffer[i]) ? max_value : buffer[i];
 *  }
 *  迭代表达式占用性能过多，循环体执行的内容过少
 *
 *  for (size_t i = 0; i < buffer_count; i += 8) {
 *      max_value = (max_value > buffer[i]) ? max_value : buffer[i];
 *      max_value = (max_value > buffer[i + 1]) ? max_value : buffer[i + 1];
 *      max_value = (max_value > buffer[i + 2]) ? max_value : buffer[i + 2];
 *      max_value = (max_value > buffer[i + 3]) ? max_value : buffer[i + 3];
 *      max_value = (max_value > buffer[i + 4]) ? max_value : buffer[i + 4];
 *      max_value = (max_value > buffer[i + 5]) ? max_value : buffer[i + 5];
 *      max_value = (max_value > buffer[i + 6]) ? max_value : buffer[i + 6];
 *      max_value = (max_value > buffer[i + 7]) ? max_value : buffer[i + 7];
 *  }
 *  花费更多性能在循环体上，迭代降低了8倍。有个明显缺点是迭代次数是8的倍数，
 *  不是8的倍数在最后一次迭代时会存在内存访问越界问题。
 *
 *  for (size_t i = 0; i + 8 < buffer_count; i += 8) {
 *      max_value = (max_value > buffer[i]) ? max_value : buffer[i];
 *      max_value = (max_value > buffer[i + 1]) ? max_value : buffer[i + 1];
 *      max_value = (max_value > buffer[i + 2]) ? max_value : buffer[i + 2];
 *      max_value = (max_value > buffer[i + 3]) ? max_value : buffer[i + 3];
 *      max_value = (max_value > buffer[i + 4]) ? max_value : buffer[i + 4];
 *      max_value = (max_value > buffer[i + 5]) ? max_value : buffer[i + 5];
 *      max_value = (max_value > buffer[i + 6]) ? max_value : buffer[i + 6];
 *      max_value = (max_value > buffer[i + 7]) ? max_value : buffer[i + 7];
 *  }
 *  for (size_t i = buffer_count / 8 * 8; i  < buffer_count; ++i) {
 *      max_value = (max_value > buffer[i]) ? max_value : buffer[i];
 *  }
 *  先处理能被整除的部分，再处理剩余不满足八个的部分，相同逻辑写了两次
 *
 * 用指针优化
 * auto ptr = buffer.begin();
 * for (size_t i = 0; i + 8 < buffer_count; i += 8) {//处理 前8的倍数个元素 1-8 9-16 ...
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *    }
 *    避免迭代次数过多问题
 *    switch (buffer_count % 8) {//处理 后余8的最后几个 8000-最后
 *        case 7: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 6: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 5: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 4: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 3: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 2: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 1: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *    }
 *
 *    先处理不能被整除剩下的，也就是余数
 *    switch (buffer_count % 8) {//处理 前几个余数 如果是19个 处理1-3
 *        case 0一定要放到最上面。如果mod为0，表示至少有8个要被处理（假设数组不为空）
 *        case 0: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 7: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 6: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 5: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 4: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 3: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 2: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
 *        case 1: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *    }
 *    buffer_count - 1中的 -1 表示 switch 先处理了前余数个。因为是整数除法，会去掉不满足8个。1就是余数
 *    (19 - 1) / 8 = 2, 还剩下2次8条迭代要处理。
 *    for (size_t i = 0; i < (buffer_count - 1) / 8; ++i) {//处理4-11 12-19
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *        max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
 *    }
 *    有个特性 ：switch 中循环体和 for 循环体很像
 */

    //本质上先执行 switch 再执行 for，和上面的逻辑上一样。
    //若 buffer_count % 8 = 2，则跳转到case 2执行。从case 2到1执行完之后，for的循环体结束，再进入下一次迭代（进入for循环
    size_t max_value = buffer[0];
    auto ptr = buffer.begin();
    size_t i = 0;
    switch (buffer_count % 8)
        // i < (buffer_count - 1 + 8) / 8 为什么要加8是因为switch先使用了一次循环体结构，++i
        // i < (buffer_count - 1 + 8) / 8 改为 i - 1 < (buffer_count - 1) / 8更明朗
        for (/*switch会跳过一个变量的定义，会出现error，因此提到99行的位置*/; i < (buffer_count - 1 + 8) / 8; ++i) {
            [[fallthrough]];
            case 0: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 7: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 6: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 5: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 4: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 3: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 2: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 1: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        }

    std::cout << max_value << std::endl;
}
