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


constexpr uint512_t fnv_prime = 0x00000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000157_cppui512;

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
			ctx->hash = 0;
			break;
		case FNV_VARIANT_1:
		case FNV_VARIANT_1A:
		default:
  			ctx->hash = 0xb86db0b1171f4416dca1e50f309990acac87d059c90000000000000000000d21e948f68a34c192f62ea79bc942dbe7ce182036415f56e34bac982aac4afe9fd9_cppui512;
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
    	ctx->hash ^= data[i];

    	// multiplication by 2^344 + 2^8 + 0x57
    	ctx->hash *= fnv_prime;
  	}
  }else{
  	for (size_t i = 0; i < len; i++) {
    	// multiplication by 2^344 + 2^8 + 0x57
    	ctx->hash *= fnv_prime;

    	// xor with a byte of data
    	ctx->hash ^= data[i];
  	}
  }
}

void fnv512_final(fnv_context* ctx, char* hexdigest){
   uint512_t hash = ctx->hash;//copy hash since we modify it - you could instead use directly since this *is* "final" but...
   unsigned int hex_digest_len = ctx->digest_bytes * 2;
   unsigned int hex_digest_max = hex_digest_len - 1;
   for (unsigned int i = 0; i < hex_digest_len; i++) {
    hexdigest[hex_digest_max - i] = nibble2hex(bitwise_cast<unsigned char>(hash) & 0xf);
    hash >>= 4;
  }
}


const char*
fnv0(const char* data, size_t len, char* hexdigest) {//hexdigest should be 64*2 chars long

  // implementation : https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-0_hash_(deprecated)
  uint512_t hash = 0;

  for (size_t i = 0; i < len; i++) {
    // multiplication by 2^344 + 2^8 + 0x57
    hash *= fnv_prime;

    // xor with a byte of data
    hash ^= data[i];
  }

  for (unsigned int i = 0; i < 128; i++) {
    hexdigest[127 - i] = nibble2hex(bitwise_cast<unsigned char>(hash) & 0xf);
    hash >>= 4;
  }

  return hexdigest;//128
}
const char*
fnv1(const char* data, size_t len, char* hexdigest) {

  // implementation : https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1_hash
  uint512_t hash = 0xb86db0b1171f4416dca1e50f309990acac87d059c90000000000000000000d21e948f68a34c192f62ea79bc942dbe7ce182036415f56e34bac982aac4afe9fd9_cppui512;

  for (size_t i = 0; i < len; i++) {
    // multiplication by 2^344 + 2^8 + 0x57
    hash *= fnv_prime;

    // xor with a byte of data
    hash ^= data[i];
  }

  for (unsigned int i = 0; i < 128; i++) {
    hexdigest[127 - i] = nibble2hex(bitwise_cast<unsigned char>(hash) & 0xf);
    hash >>= 4;
  }
  return hexdigest;//128
}
const char*
fnv1a(const char* data, size_t len, char* hexdigest) {

  // implementation : https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
  uint512_t hash = 0xb86db0b1171f4416dca1e50f309990acac87d059c90000000000000000000d21e948f68a34c192f62ea79bc942dbe7ce182036415f56e34bac982aac4afe9fd9_cppui512;

  for (size_t i = 0; i < len; i++) {
    // xor with a byte of data
    hash ^= data[i];

    // multiplication by 2^344 + 2^8 + 0x57
    hash *= fnv_prime;
  }

  for (unsigned int i = 0; i < 128; i++) {
    hexdigest[127 - i] = nibble2hex(bitwise_cast<unsigned char>(hash) & 0xf);
    hash >>= 4;
  }
  return hexdigest;//128
}

/*
static PyMethodDef fnv512_methods[] = {
     {"fnv0", fnv0, METH_VARARGS, "hash function fnv-0"},
     {"fnv1", fnv1, METH_VARARGS, "hash function fnv-1"},
     {"fnv1a", fnv1a, METH_VARARGS, "hash function fnv-1a"},
     {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fnv512_module =
{
    PyModuleDef_HEAD_INIT,
    "fnv512",
    NULL,
    -1,
    fnv512_methods
};

PyMODINIT_FUNC
PyInit_fnv512(void) {
     return PyModule_Create(&fnv512_module);
}
*/
