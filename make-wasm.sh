rm -rf fnv512-wasm-dist
mkdir fnv512-wasm-dist
emcc -O3 -s MODULARIZE=1 -s 'EXPORT_NAME="createfnv512Module"' -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' -I../chronotext-boost/dist/emscripten/include/ fnv512.cpp -o fnv512-wasm-dist/fnv512-wasm.js

cat fnv512-wasm-dist/fnv512-wasm.js fnv512-js-wrapper/fnv512-wrapper.js > fnv512-wasm-dist/fnv512-wrapped.js
