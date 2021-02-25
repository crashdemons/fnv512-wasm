# fnv512

fnv512 is an implementation for the FNV-0/FNV-1/FNV-1A 512 bits hashing algorithms
 which has been rebuilt for WebAssembly (WASM).

All credit goes to tweqx for this library

## Requirements
 - emcc (Emscripten)
 - updated C++11 libraries/includes
 - curl (for downloading Boost in chronotext-boost)
 - EMSCRIPTEN_PATH environmental variable set to your EMSDK directory

## Installation

To install
 - create a directory for the project
 - clone the 1.62 branch of `chronotext-boost` (https://github.com/arielm/chronotext-boost/tree/1.62) into "chronotext-boost" directory inside the project directory (NOTE: if you do not switch to the 1.62 branch, you will receive errors about bitwise_cast later!)
 - clone this respository into `fnv512-wasm` directory in the project directory (chronotext-boost should be accessible by ../chronotext-boost when the current directory is fnv512-wasm)
 - change directory to `chronotext-boost` and follow the Setup and Build (only emscripten is needed) instructions on their repository. https://github.com/arielm/chronotext-boost/blob/1.62/README.md  This will build the Boost C++ library for webassembly.
 - change directory to `fnv512-wasm` (../fnv512-wasm)
 - run `./make-wasm.sh`



## Usage

coming soon

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)
