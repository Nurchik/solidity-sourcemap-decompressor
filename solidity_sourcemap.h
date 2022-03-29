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

struct node {
    char *s, *l, *f, *j, *m;
};

typedef struct node node_t;

struct cnode {
    const char *s, *l, *f, *j;
};

typedef struct cnode cnode_t;

node_t node_at(char *str, int ix);

cnode_t cnode_at(const char *str, int ix);

struct res_node {
    long offset, size, fileId;
    char jumpType;
};

typedef struct res_node rnode;

struct res_node * decompress(char* sourcemap, long* counter);

struct result_array {
    rnode * array;
    long length;
};

long ** decompress_opt(char* sourcemap, long *counter);
char ltjt(const long* jt);
#endif //SOLIDITY_SOURCEMAP_H
