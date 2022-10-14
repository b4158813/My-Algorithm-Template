#include <cstdlib>
using namespace std;
int main(){

    // 先写一个data.py用于数据生成
    system("g++ std.cpp -std=c++20 -O2 -o std.exe");
    system("g++ my.cpp -std=c++20 -O2 -o my.exe");
    while(1){

        system("python data.py > in.txt");
        system("std.exe < in.txt > std_out.txt");
        system("my.exe < in.txt > my_out.txt");
        
        if(system("fc std_out.txt my_out.txt")){
            system("echo input is:");
            system("type in.txt");
            exit(1);
        }
    }
    return 0;
    
}