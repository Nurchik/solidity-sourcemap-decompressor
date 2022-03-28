from cffi import FFI

ffibuilder = FFI()

ffibuilder.cdef("""
    struct res_node {
        long offset, size, fileId;
        char jumpType;
    };
    struct res_node * decompress(char* sourcemap, long *counter);
""")

ffibuilder.set_source("sourcemap_decompressor", """
    #include "solidity_sourcemap.h"
""", sources=["solidity_sourcemap.c"])

if __name__ == "__main__":
    ffibuilder.compile()
