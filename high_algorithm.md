#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * 高精度加法函数
 * @param a 第一个大整数（字符串表示）
 * @param b 第二个大整数（字符串表示）
 * @return 两数之和（字符串表示）
 */
string add(string a, string b) {
    // 确保a的长度不小于b，便于处理
    if (a.length() < b.length()) swap(a, b);
    
    string result;
    int carry = 0;  // 进位值
    
    // 从低位（字符串末尾）开始相加
    for (int i = 0; i < a.length(); i++) {
        // 当前位置的和 = 进位 + a对应位的数字
        int sum = carry + (a[a.length() - 1 - i] - '0');
        
        // 如果b还有对应的位，加上b的对应位
        if (i < b.length()) sum += (b[b.length() - 1 - i] - '0');
        
        // 计算新的进位
        carry = sum / 10;
        
        // 当前位的结果是sum对10取模
        result.push_back(sum % 10 + '0');
    }
    
    // 如果最终还有进位，添加到最高位
    if (carry) result.push_back(carry + '0');
    
    // 翻转结果，因为我们是从低位开始构建的
    reverse(result.begin(), result.end());
    
    return result;
}

/**
 * 比较两个正数的大小
 * @param a 第一个大整数（字符串表示）
 * @param b 第二个大整数（字符串表示）
 * @return a>b返回1，a=b返回0，a<b返回-1
 */
int compare(string a, string b) {
    // 先比较长度，长度不同则长的更大
    if (a.length() != b.length()) return a.length() > b.length() ? 1 : -1;
    
    // 长度相同时，从高位到低位逐位比较
    for (int i = 0; i < a.length(); i++) {
        if (a[i] != b[i]) return a[i] > b[i] ? 1 : -1;
    }
    
    // 所有位都相同，则两数相等
    return 0;
}

/**
 * 高精度减法函数（假设a >= b，都是正数）
 * @param a 被减数（字符串表示）
 * @param b 减数（字符串表示）
 * @return 差值（字符串表示）
 */
string subtract(string a, string b) {
    string result;
    int borrow = 0;  // 借位值
    
    // 从低位（字符串末尾）开始相减
    for (int i = 0; i < a.length(); i++) {
        // 当前位置的差 = a对应位的数字 - 借位
        int diff = (a[a.length() - 1 - i] - '0') - borrow;
        
        // 如果b还有对应的位，减去b的对应位
        if (i < b.length()) diff -= (b[b.length() - 1 - i] - '0');
        
        // 如果差为负，需要从高位借10
        if (diff < 0) {
            diff += 10;
            borrow = 1;  // 设置借位
        } else {
            borrow = 0;  // 不需要借位
        }
        
        // 将当前位的结果添加到结果中
        result.push_back(diff + '0');
    }
    
    // 翻转结果，因为我们是从低位开始构建的
    reverse(result.begin(), result.end());
    
    // 去除前导零
    // find_first_not_of('0')找到第一个非'0'字符的位置
    result.erase(0, result.find_first_not_of('0'));
    
    // 如果结果为空（即a=b），则返回"0"
    if (result.empty()) result = "0";
    
    return result;
}

/**
 * 高精度乘法函数
 * @param a 第一个乘数（字符串表示）
 * @param b 第二个乘数（字符串表示）
 * @return 积（字符串表示）
 */
string multiply(string a, string b) {
    // 处理特殊情况：如果有一个数是0，结果就是0
    if (a == "0" || b == "0") return "0";
    
    // 初始化结果数组，大小为a和b长度之和（最大可能长度）
    vector<int> result(a.length() + b.length(), 0);
    
    // 模拟竖式乘法，从低位到高位逐位相乘
    for (int i = a.length() - 1; i >= 0; i--) {
        for (int j = b.length() - 1; j >= 0; j--) {
            // 计算当前位置的乘积
            int product = (a[i] - '0') * (b[j] - '0');
            
            // 确定结果应该加到哪个位置
            // 两个数第i位和第j位（从右往左数）相乘，结果应该放在第(i+j)位
            int position = a.length() - 1 - i + b.length() - 1 - j;
            
            // 将乘积加到对应位置
            result[position] += product;
        }
    }
    
    // 处理进位
    for (int i = 0; i < result.size() - 1; i++) {
        if (result[i] >= 10) {
            result[i + 1] += result[i] / 10;  // 向高位进位
            result[i] %= 10;  // 当前位保留个位数
        }
    }
    
    // 转换为字符串并去除前导零
    string str_result;
    bool leading_zero = true;  // 是否是前导零
    
    // 从高位到低位构建结果字符串
    for (int i = result.size() - 1; i >= 0; i--) {
        // 跳过前导零
        if (leading_zero && result[i] == 0) continue;
        leading_zero = false;  // 遇到非零数字后，不再是前导零
        
        // 将数字转换为字符添加到结果中
        str_result.push_back(result[i] + '0');
    }
    
    // 如果结果为空（可能全是前导零），则返回"0"
    if (str_result.empty()) str_result = "0";
    
    return str_result;
}

int main() {
    string a, b;
    cout << "请输入两个大整数：" << endl;
    cin >> a >> b;
    
    // 计算并输出加法结果
    cout << "加法结果：" << add(a, b) << endl;
    
    // 减法需要确保被减数不小于减数
    if (compare(a, b) >= 0) {
        // a >= b，直接相减
        cout << "减法结果：" << subtract(a, b) << endl;
    } else {
        // a < b，交换顺序并添加负号
        cout << "减法结果：-" << subtract(b, a) << endl;
    }
    
    // 计算并输出乘法结果
    cout << "乘法结果：" << multiply(a, b) << endl;
    
    return 0;
}
