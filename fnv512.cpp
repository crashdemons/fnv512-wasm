// fnv512, a python library for 512-bit versions of the fnv-0/fnv-1/fnv-1a hashes
// Copyright (C) 2021 tweqx
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "fnv512.hpp"


const uint512_t fnv_prime("00000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000157",16);


int version(){
	return 20210224;
}


char* create_buffer(size_t size){
	return (char*) malloc(size);
}
void destroy_buffer(void* buffer){
	free(buffer);
}

char nibble2hex(unsigned char nibble) {
  if (nibble < 10)
    return '0' + nibble;
  else
    return 'a' + nibble - 10;
}



fnv_context* fnv512_init(int variant){
	fnv_context* ctx = (fnv_context*) create_buffer(sizeof(fnv_context));
	ctx->digest_bits = 512;
	ctx->digest_bytes = 64;

	if(variant<FNV_VARIANT_MIN || variant>FNV_VARIANT_MAX) variant = FNV_VARIANT_DEFAULT;
	ctx->variant = variant;

	switch(variant){
		case FNV_VARIANT_0:
			ctx->hash.set("0",10);
			break;
		case FNV_VARIANT_1:
		case FNV_VARIANT_1A:
		default:
  			ctx->hash.set("b86db0b1171f4416dca1e50f309990acac87d059c90000000000000000000d21e948f68a34c192f62ea79bc942dbe7ce182036415f56e34bac982aac4afe9fd9",16);
			break;
	}

	return ctx;
}

void fnv512_cleanup(fnv_context* ctx){
	destroy_buffer(ctx);
}

void fnv512_update(fnv_context* ctx, const char* data, size_t len){
  if(ctx->variant==FNV_VARIANT_1A){
	  for (size_t i = 0; i < len; i++) {
  	  // xor with a byte of data
	ctx->hash.exor(data[i]);

    	// multiplication by 2^344 + 2^8 + 0x57
	ctx->hash.mul(fnv_prime);
  	}
  }else{
  	for (size_t i = 0; i < len; i++) {
    	// multiplication by 2^344 + 2^8 + 0x57
	ctx->hash.mul(fnv_prime);

    	// xor with a byte of data
	ctx->hash.exor(data[i]);
  	}
  }
}


//author: Niels Keurentjes
//https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array
int char2int(char input)
{
  if(input >= '0' && input <= '9')
    return input - '0';
  if(input >= 'A' && input <= 'F')
    return input - 'A' + 10;
  if(input >= 'a' && input <= 'f')
    return input - 'a' + 10;
  throw std::invalid_argument("Invalid input string");
}
void hex2bin(const char* src, char* target, int maxBytes)
{
  int i=0;
  while(*src && src[1] && i<maxBytes)
  {
    *(target++) = char2int(*src)*16 + char2int(src[1]);
    src += 2;
    i++;
  }
}

void fnv512_final(fnv_context* ctx, char* digest){
   size_t hexSize = ctx->hash.getHexBufSize();
   char* hexdigest = create_buffer(hexSize);

   fnv512_finalHex(ctx, hexdigest);
   hex2bin(hexdigest, digest, ctx->digest_bytes);

   destroy_buffer(hexdigest);

}
void fnv512_finalHex(fnv_context* ctx, char* hexdigest){
   ctx->hash.toHex(hexdigest);
   /*uint512_t hash = ctx->hash;//copy hash since we modify it - you could instead use directly since this *is* "final" but...
   unsigned int hex_digest_len = ctx->digest_bytes * 2;
   unsigned int hex_digest_max = hex_digest_len - 1;
   for (unsigned int i = 0; i < hex_digest_len; i++) {
    hexdigest[hex_digest_max - i] = nibble2hex(bitwise_cast<unsigned char>(hash) & 0xf);
    hash >>= 4;
  }*/
}

