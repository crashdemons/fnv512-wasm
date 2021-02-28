#include "uint512_t.hpp"

                uint512_base::uint512_base(){
			printf("ctor0 uint512_base %p\r\n",this);
                        mpz_init2(n,512);
                }
                uint512_base::uint512_base(const char* cs, int base, int size){
			printf("ctor3 uint512_base %p\r\n",this);
                        mpz_init2(n,size);
                        mpz_set_str(n,cs,base);
                }
                uint512_base::uint512_base(const char* cs, int base){
			printf("ctor2 uint512_base %p\r\n",this);
                        mpz_init2(n,512);
                        mpz_set_str(n,cs,base);
                }

                uint512_base::~uint512_base(){
			printf("dctor uint512_base %p\r\n",this);
                        mpz_clear(n);
                }

uint512_base uint512_max("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",16);

                uint512_t::uint512_t(const char* cs, int base) : uint512_base(cs,base){
			printf("ctor2 uint512_t %p = %s\r\n",this, cs);

		}
                uint512_t::uint512_t() : uint512_base() {
			printf("ctor0 uint512_t %p\r\n",this);
		}
                void uint512_t::wrap512(){
                        if(mpz_cmp(n,uint512_max.n) > 0){
			//	printf("%s\r\n",mpz_get_str(NULL, 16, n));
			//	printf("  > \r\n");
			//	printf("%s\r\n",mpz_get_str(NULL, 16, uint512_max.n));

                                mpz_sub(n,n,uint512_max.n);
                        }
                }
                void uint512_t::set(const char* cs, int base){
			printf("set uint512_t %p = %s\r\n",this,cs);
                        mpz_set_str(n,cs,base);
                }
                void uint512_t::mul(uint512_t u2){
                        mpz_mul(n, n, u2.n);
                        wrap512();
                }
                void uint512_t::exor(unsigned long i){
                        mpz_t n2;
                        mpz_init_set_ui(n2,i);
                        mpz_xor(n, n, n2);
                        mpz_clear(n2);
                        wrap512();
                }
                unsigned long int uint512_t::getLowInt(){
                        return mpz_get_ui(n);
                }

                size_t uint512_t::getHexBufSize(){
                        return mpz_sizeinbase(n, 16)+2;
                }
                void uint512_t::toHex(char* buf){
                        mpz_get_str(buf, 16, n);
                }

