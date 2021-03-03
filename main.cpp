#include <iostream>
#include <cstring>
#include "fnv512.hpp"


int main(){
	const char* input = "chongo <Landon Curt Noll> /\\../\\";
	char* output = create_buffer(129+100);
	output[128]=0;

	fnv_context* ctx = fnv512_init(FNV_VARIANT_0);

	fnv512_update(ctx, input, strlen(input));

	fnv512_finalHex(ctx, output);

	printf("output %s",output);

//	fnv0(input, strlen(input), output);
//	printf("output %s",output);

	destroy_buffer(output);
	fnv512_cleanup(ctx);

	return 0;

}
