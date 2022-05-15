/*
https://www.luogu.com.cn/problem/P3369
__gnu_pbds内自带的平衡树 (rb_tree && splay)
注意：这是一个set，如果需要插入重复元素，请使用哈希表维护一个时间戳，并采用pair(x,时间戳)
支持操作：
- 插入一个数
- 删除一个数
- 求x的排名
- 求排名为x的数
- 求x的前驱（小于x的最大的数）
- 求x的后继（大于x的最小的数）
*/

#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
using ll = int64_t;
using pii = pair<int,int>;

void solve(){
    
    int n;
    cin>>n;
    unordered_map<int,int> ma;
    tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> tr;
    int op,x;
    while(n--){
        cin>>op>>x;
        if(op==1){
            tr.insert(pair(x,ma[x]++));
        }else if(op==2){
            tr.erase(pair(x,--ma[x]));
        }else if(op==3){
            cout << tr.order_of_key(pair(x,0)) + 1 << '\n';
        }else if(op==4){
            cout << (*tr.find_by_order(x-1)).first << '\n';
        }else if(op==5){
            cout << (*--tr.lower_bound(pair(x, 0))).first << '\n';
        }else if(op==6){
            cout << (*tr.upper_bound(pair(x, ma[x]-1))).first << '\n';
        }
    }
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