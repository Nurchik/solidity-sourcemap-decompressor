//
// Created by  nuradil on 24/3/22.
//

#ifndef SOLIDITY_SOURCEMAP_H
#define SOLIDITY_SOURCEMAP_H

struct Accumulator {
    long offset;
    long size;
    long fileId;
    char jumpType[2];
};

struct Accumulator decompress_source_map(int idx, char* source_map);

#endif //SOLIDITY_SOURCEMAP_H
