#include<gmp.h>
#include <stdio.h>

class uint512_base{
        public:
                mpz_t n;
        public:
                uint512_base();
                uint512_base(const char* cs, int base, int size);
                uint512_base(const char* cs, int base);
                ~uint512_base();
};

extern uint512_base uint512_max;

class uint512_t : uint512_base{
        public:
                uint512_t(const char* cs, int base);
                uint512_t();
                ~uint512_t();
                void wrap512();
                void set(const char* cs, int base);
                void mul(uint512_t u2);
                void exor(unsigned long i);
                unsigned long int getLowInt();
                size_t getHexBufSize();
                void toHex(char* buf);
};

