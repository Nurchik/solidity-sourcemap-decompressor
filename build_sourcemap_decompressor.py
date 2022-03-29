from cffi import FFI

ffibuilder = FFI()

ffibuilder.cdef("""
    long ** decompress_opt(char* sourcemap, long *counter);
""")

ffibuilder.set_source("sourcemap_decompressor", """
    #include "solidity_sourcemap.h"
""", sources=["solidity_sourcemap.c"])

if __name__ == "__main__":
    ffibuilder.compile()
