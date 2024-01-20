#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "systemc.h"

template<unsigned int S = 32> 
sc_uint<S> divu25(sc_uint<S> n)
{
    sc_uint<S + 3> x = n, y;
    y = x + 1;
    x = (y << 2) + x + (y >> 3);
    if constexpr(S > 7) {
        x = x - (x >> 10);
    }
    if constexpr(S > 19) {
        x = (x >> 20) + x;
    }
    x = (x >> 7);
    return x;
}

template<unsigned int S = 32> 
int check(void)
{
    cout << "Checking bitwidth " << S << endl;

    const unsigned int m = ((uint64_t)1 << S) - 1;
    sc_uint<S> i = m;
    do {
        i++;
        sc_uint<S> v = divu25<S>(i);

        if (v != i/25) {
            cout << "Error (" << i << ") : expects " << i/25 << " != has " << v << endl;
            return 1;
        }
        if (i % 3000000 == 0) {
            printf(".");
            fflush(stdout);
        }
    } while (i < m);
    return 0;
}

int sc_main(int argc, char *argv[])
{
    int v = 0;
    v += check<1>();
    v += check<2>();
    v += check<3>();
    v += check<4>();
    v += check<5>();
    v += check<6>();
    v += check<7>();
    v += check<8>();
    v += check<9>();
    v += check<10>();
    v += check<11>();
    v += check<12>();
    v += check<13>();
    v += check<14>();
    v += check<15>();
    v += check<16>();
    v += check<17>();
    v += check<18>();
    v += check<19>();
    v += check<20>();
    v += check<21>();
    v += check<22>();
    v += check<23>();
    v += check<24>();
    v += check<25>();
    v += check<26>();
    v += check<27>();
    v += check<28>();
    v += check<29>();
    v += check<30>();
    v += check<31>();
    v += check<32>();
    return v;
}
