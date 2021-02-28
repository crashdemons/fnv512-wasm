#!/bin/bash
rm -rf fnv512-wasm-dist
mkdir fnv512-wasm-dist

#W_FLAGS="-O3 -flto -DNDEBUG"
W_FLAGS="-g -v"
echo $W_FLAGS
emcc $W_FLAGS -s MODULARIZE=1 -s 'EXPORT_NAME="createFnv512Module"' -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' -I/home/crash/opt/include -L/home/crash/opt/lib -lgmp uint512_t.cpp fnv512.cpp -o fnv512-wasm-dist/fnv512-wasm.js


cat fnv512-wasm-dist/fnv512-wasm.js js-wrapper/wrapper.js > fnv512-wasm-dist/fnv512-wrapped.js
