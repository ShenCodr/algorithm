#include <iostream>
#include <string>
using namespace std;

class Trie {
public:
    // 字典树节点的结构体
    struct Node {
        Node* son[26]{};  // 子指针数组，大小26，对应小写英文字母 a~z，默认都初始化为 nullptr
        bool end = false; // 标记是否有单词在此节点结束
    };

    Node* root = new Node{}; // 根节点，永远不为空，所有操作从这里开始

    // 私有方法：在 Trie 中查找一个字符串
    // 返回值含义：
    //   0 -> 完全不存在该前缀
    //   1 -> 存在该前缀，但不是完整单词
    //   2 -> 完全匹配一个已插入的单词
    int find(const string& word) {
        Node* curr = root; // 从根节点开始遍历
        for (char ch : word) {
            int idx = ch - 'a';            // 将字符转换为 0~25 的索引
            if (curr->son[idx] == nullptr) {
                // 如果对应子节点为空，则整个前缀/单词都不存在
                return 0;
            }
            curr = curr->son[idx];         // 否则沿指针继续向下
        }
        // 遍历完毕后，如果 curr->end 为 true，则表示完整单词匹配，否则只是前缀匹配
        return curr->end ? 2 : 1;         // 2 表示单词匹配，1 表示只匹配前缀
    }

    // 构造函数
    Trie() {
        // 根节点已经在成员初始化时 new 过了，不需要额外操作
    }

    // 在 Trie 中插入一个单词
    void insert(const string& word) {
        Node* curr = root; // 从根开始
        for (char ch : word) {
            int idx = ch - 'a';                   // 转换为索引
            if (curr->son[idx] == nullptr) {
                // 如果路径不存在，就新建一个节点
                curr->son[idx] = new Node();
            }
            curr = curr->son[idx];                // 移动到下一个节点
        }
        curr->end = true;                         // 单词结束，打上标记 
    }

    // 精确查找一个单词是否已插入
    bool search(const string& word) {
        return find(word) == 2; // 只有返回2才是真正匹配完整单词
    }

    // 检查是否存在以给定前缀开头的单词
    bool startsWith(const string& prefix) {
        int res = find(prefix);
        return res == 1 || res == 2; // 前缀匹配或完整单词都算
    }
};
