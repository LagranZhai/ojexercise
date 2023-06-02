#include<iostream>
#include<chrono>
#include<algorithm>
#include<random>
//using std::cin;
//using std::cout;
using namespace std;
using namespace chrono;
int a[(int)1e7];
void get_array(){
    for(int i=0;i<(1e7);i++)a[i]=i;
}
int main(){
    ios::sync_with_stdio(false);
    get_array();
    auto tstart=system_clock::now();
    sort(a,a+int(1e7));
    auto tend=system_clock::now();
    auto duration=duration_cast<microseconds>(tend-tstart);
    cout<<double(duration.count())<<endl;
    get_array();
    tstart=system_clock::now();
    random_device rd;
    mt19937 g(rd());
    tstart=system_clock::now();
    shuffle(a,a+int(1e7),g);
    //random_shuffle(a,a+(int)1e6);
    //sort(a,a+int(1e7));
    tend=system_clock::now();
    duration=duration_cast<milliseconds>(tend-tstart);
    cout<<double(duration.count())<<endl;
    return 0;
}
