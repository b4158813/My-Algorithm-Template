/*
https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/I?f0a28=1
双指针+双栈+01可行性背包 复杂度O(n*s)
双栈可以用于维护双指针过程中的区间性质
- 右指针右移时：向栈1加入元素并维护栈底到栈顶的性质（取出时，元素顺序为从右到左）
- 左指针右移时：
    - 若栈2空，则将栈1元素全部依次加入栈2同时维护性质，此时取出栈2顶即左指针元素
    - 若栈2非空，直接取出栈2顶即左指针元素（取出时，元素顺序为从左到右）

形象来说，这是两个底对底的栈： (栈2) ------底|  |底------ (栈1)

此操作可以用于维护 区间gcd 等性质

仅用一个队列维护不行的原因：队首元素未包含整个区间的性质内容
*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;

class stk{
public:
    vector<bitset<1001>> val;
    vector<int> vec;

    stk(){
        bitset<1001> tp;
        tp[0] = 1;
        val.emplace_back(tp);
    }

    void push(const int &x){
        vec.emplace_back(x);
        auto b = val.back();
        val.emplace_back(b | (b<<x));
    }

    int top(){
        return vec.back();
    }

    void pop(){
        vec.pop_back();
        val.pop_back();
    }

    bool empty(){
        return vec.empty();
    }
};

stk s1 = stk();
stk s2 = stk();

void add(const int &x){
    s1.push(x);
}

void del(){
    if(s2.empty())
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
    s2.pop();
}

bool ok(int x){
    auto a1 = s1.val.back();
    auto a2 = s2.val.back();
    for(int i=0;i<=x;++i){
        if(a2[i] && a1[x-i])
            return true;
    }
    return false;
}



void solve(){
    
    int n,s;
    cin>>n>>s;
    vector<int> a(n);
    for(int i=0;i<n;++i) cin>>a[i];
    int ans = 2e5;
    for(int i=0,j=0;i<n;++i){
        add(a[i]);
        while(j<=i && ok(s)){
            ans = min(ans, i-j+1);
            del();
            j++;
        }
    }
    cout << (ans==200000 ? -1 : ans) << '\n';
    
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int _ = 1;
    // cin>>_;
    while(_--){
        
        solve();
        
    }
    
    return 0;
}