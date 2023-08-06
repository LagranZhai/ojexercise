#include<iostream>
#include<chrono>
#include<algorithm>
using std::cin;
using std::cout;
using namespace std;
int a[(int)1e6];
void get_array(){
    for(int i=0;i<(1e6);i++)a[i]=i;
}
int main(){
    std::ios::sync_with_stdio(false);
    get_array();
    auto tstart=system_clock::now();
    sort(a,a+int(1e6));
    auto tend=system_clock::now();
    auto duration=duration_cast<microseconds>(tstart-tend);
    cout<<double(duration.count())<<endl;
    get_array();
    tstart=system_clock::now();
    random_shuffle(a,a+(int)1e6);
    sort(a,a+int(1e6));
    tend=system_clock::now();
    duration=duration_cast<microseconds>(tstart-tend);
    cout<<double(duration.count())<<endl;
    return 0;
}
