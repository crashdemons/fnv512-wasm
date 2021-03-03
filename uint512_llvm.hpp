#pragma once
#include <cstdint>

/*

[                  64 bytes                                    ]        (1x uint512_t)
[              32              ][              32              ]        (2x uint256_t)
[     16       ][     16       ][     16       ][     16       ]        (4x uint128_t)
[   8  ][   8  ][   8  ][   8  ][   8  ][   8  ][   8  ][   8  ]        (8x uint64_t)
8888888888888888888888888888888888888888888888888888888888888888        (64 uint8_t / char)
1234567890123456789012345678901234567890123456789012345678901234 64

*/


typedef unsigned _ExtInt(512) uint512_t;

#define _PROMOTE512(a) ((uint512_t)a)
#define _LSHIFT512(a,s) _PROMOTE512(_PROMOTE512(a)<<s)
#define _RSHIFT512(a,s) _PROMOTE512(_PROMOTE512(a)>>s)
#define _UINT64_TO_512(a,b,c,d, e,f,g,h) ( \
_LSHIFT512(a,384) | \
_LSHIFT512(b,320) | \
_LSHIFT512(c,256) | \
_LSHIFT512(d,192) | \
_LSHIFT512(e,128) | \
_LSHIFT512(f, 64) | \
_LSHIFT512(g,  0) )

static constexpr uint512_t uint512(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h){
	return _UINT64_TO_512(a,b,c,d,e,f,g,h);
}

static constexpr uint512_t uint512(uint64_t n){
	return _PROMOTE512(n);
}
