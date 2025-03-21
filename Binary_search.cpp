#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//返回第一个大于等于target的数
int lowerbound(vector<int> &nums, int target)
{
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r)
    {
        int mid = (r - l) / 2 + l;
        if (nums[mid] >= target)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        } //此时l=r+1;//左边全部小于target，右边全部大于等于target
    }
    return l; // nums[l]就是>=target的第一个数
}
