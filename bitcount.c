#include "bitcount.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

unsigned int bit_clz_general(uint64_t v) {
	// From http://www.codeproject.com/Tips/784635/UInt-Bit-Operations
    uint64_t i;
    unsigned int c;

    i = ~v;
    c = ((i ^ (i + 1)) & i) >> 63;

    i = (v >> 32) + 0xffffffff;
    i = ((i & 0x100000000) ^ 0x100000000) >> 27;
    c += i;  v <<= i;

    i = (v >> 48) + 0xffff;
    i = ((i & 0x10000) ^ 0x10000) >> 12;
    c += i;  v <<= i;

    i = (v >> 56) + 0xff;
    i = ((i & 0x100) ^ 0x100) >> 5;
    c += i;  v <<= i;

    i = (v >> 60) + 0xf;
    i = ((i & 0x10) ^ 0x10) >> 2;
    c += i;  v <<= i;

    i = (v >> 62) + 3;
    i = ((i & 4) ^ 4) >> 1;
    c += i;  v <<= i;

    c += (v >> 63) ^ 1;

    return c;
}

unsigned int bit_ctz_general(uint64_t v) {
	// From http://www.codeproject.com/Tips/784635/UInt-Bit-Operations
    uint64_t i = ~v;
    unsigned int c = ((i ^ (i + 1)) & i) >> 63;

    i = (v & 0xffffffff) + 0xffffffff;
    i = ((i & 0x100000000) ^ 0x100000000) >> 27;
    c += i;  v >>= i;

    i = (v & 0xffff) + 0xffff;
    i = ((i & 0x10000) ^ 0x10000) >> 12;
    c += i;  v >>= i;

    i = (v & 0xff) + 0xff;
    i = ((i & 0x100) ^ 0x100) >> 5;
    c += i;  v >>= i;

    i = (v & 0xf) + 0xf;
    i = ((i & 0x10) ^ 0x10) >> 2;
    c += i;  v >>= i;

    i = (v & 3) + 3;
    i = ((i & 4) ^ 4) >> 1;
    c += i;  v >>= i;

    c += ((v & 1) ^ 1);

    return c;
}

unsigned int bit_popcount_general(uint64_t v) {
	// see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
    v -= ((v >> 1) & 0x5555555555555555);
    v = (v & 0x3333333333333333) + ((v >> 2) & 0x3333333333333333);
    return ((v + (v >> 4) & 0xF0F0F0F0F0F0F0F) * 0x101010101010101) >> 56;
}

#ifdef __cplusplus
}
#endif
