#include <stdio.h>
#include <map>
using namespace std;
typedef map< int, int > MyMap;
#define MAXN 1000
#define MAXSQRTK 10000
#define P 1000000007

void get_factor( int k, MyMap& f ) {
    for( int i = 1; i * i <= k; ++i ) { 
        if( k % i == 0 ) {
            f[i] = f[k/i] = 0; 
        }       
    }   
}

int main() {

    int t, i, n, k, y;
    MyMap  factor;
    MyMap::reverse_iterator it; 

    for( scanf( "%d", &t ); t--; ) { 
        scanf( "%d%d", &n, &k );
        factor.clear();
        get_factor( k, factor );
        factor[1] = 1;

        for( i = 0; i < n; ++i ) { 
            scanf( "%d", &y ); 
            if( k % y != 0 ) continue; 
            for( it = factor.rbegin(); it != factor.rend(); ++it ) {
                if( it->first >= y && it->first % y == 0 ) {
                    it->second = ( it->second + factor[it->first/y] ) % P;
                }               
            }           
        }       
        printf( "%d\n", factor[k] );
    }   

    return 0;
}