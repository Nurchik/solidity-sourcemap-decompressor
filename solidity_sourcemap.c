//
// Created by  nuradil on 24/3/22.
//

#include "solidity_sourcemap.h"
#include "string.h"
#include "stdlib.h"

struct Accumulator decompress_source_map(int idx, char* source_map) {
    struct Accumulator accumulator = {-1, -1, -1, "-"};
    char *rest, *token;
    int count = 0;
    int token_count = 0;
    char delimiter_sml = ':';
    char *sml;
    char *sml_rest;

    while ((token = strtok_r(source_map, ";", &rest)) && (count < idx)){
        source_map = NULL;
        token_count = 0;
        while ((sml = strtok_r(token, &delimiter_sml, &sml_rest))) {
            token = NULL;
            if (strlen(sml) == 0){
                continue;
            }

            if (token_count == 0) {
                accumulator.offset = strtol(sml, NULL, 10);
            }
            else if (token_count == 1) {
                accumulator.size = strtol(sml, NULL, 10);
            }
            else if (token_count == 2) {
                accumulator.fileId = strtol(sml, NULL, 10);
            }
            else if (token_count == 3) {
                strcpy(accumulator.jumpType, sml);
            }
            else {
                break;
            }
            token_count++;
        }
        count++;
    }
    return accumulator;
}

struct result_array allocate_array(char *str) {
    char *node;
    long count = 0;
    for (; (node=strchr(str, ';')) != NULL; (++count, str=node + 1));
    rnode *arr = (rnode *) calloc(count + 1, sizeof(rnode));
    struct result_array res = {arr, count + 1};
    return res;
}

node_t node_at(char *str, int ix) {
    node_t res = {0};
    char *tok_node = NULL;
    char *tok_part = NULL;
    int nc = 0;
    char **dst[5] = {&res.s, &res.l, &res.f, &res.j, &res.m};

    while ( (tok_node = strsep(&str, ";")) != NULL && nc < ix ) {
        char ***p_dst = dst;
        for (; (tok_part = strsep(&tok_node, ":")) != NULL; ++p_dst) {
            **p_dst = (*tok_part ? tok_part : **p_dst);
        }
    }

    return res;
}

//cnode_t cnode_at(const char *str, int ix) {
//    cnode_t res = {0};
//    char *tok_node, *tok_part;
//    int nc = -1;
//    const char **dst[5] = {&res.s, &res.l, &res.f, &res.j, &res.m};
//
//    for (; (tok_node = strchr(str, ';')) != NULL && nc < ix; ++nc) {
//        const char ***p_dst = dst;
//        for (tok_part = strchr(str, ':');
//             tok_part != NULL && tok_part < tok_node;
//             tok_part = strchr(str, ':'), ++p_dst) {
//            if (tok_part - str)
//                **p_dst = str;
//            str = tok_part + 1;
//        }
//
//        if (tok_node - str)
//            **p_dst = str;
//
//        str = tok_node + 1;
//        while (*str == ';' && nc < ix) {++str; ++nc;};
//    }
//
//    int *dst_s[5] = {&res.s_, &res.l_, &res.f_, &res.j_, &res.m_};
//    for (int i = 0; i < 5; ++i) {
//        if (*dst[i] == NULL) {
//            *dst_s[i] = 0;
//            continue;
//        }
//        int l = 0;
//        for (; (*dst[i])[l] != ';' && (*dst[i])[l] != ':'; ++l) ;
//        *dst_s[i] = l;
//    }
//    return res;
//}

struct res_node * decompress(char* sourcemap, long *counter){
    struct result_array res = allocate_array(sourcemap);
    rnode *arr = res.array;
    *counter = res.length;
    char *node;
    char *component;
    long idx = 0;
    rnode acc = {-1, -1, -1, '-'};
    long *acc_map[4] = {&acc.offset, &acc.size, &acc.fileId, NULL};
    for (; (node=strchr(sourcemap, ';')) != NULL; (idx += 1)) {
        if (node == sourcemap) {
            *(arr + idx) = acc;
            sourcemap=node + 1;
            continue;
        }
        long **p_acc_map = acc_map;
        for (; (component = strchr(sourcemap, ':')) != NULL && component < node && *p_acc_map != NULL; p_acc_map++) {
            if (component == sourcemap) {
                sourcemap = component + 1;
                continue;
            }
            **p_acc_map = strtol(sourcemap, NULL, 10);
            sourcemap = component + 1;
        }
        if (*p_acc_map != NULL) {
            **p_acc_map = strtol(sourcemap, NULL, 10);
        }
        else if (*sourcemap != ';' && *sourcemap != ':') {
            acc.jumpType = *sourcemap;
        }
        *(arr + idx) = acc;
        sourcemap=node + 1;
    }
    if (*sourcemap != '\0') {
        long **p_acc_map = acc_map;
        for (; (component = strchr(sourcemap, ':')) != NULL && *p_acc_map != NULL; p_acc_map++) {
            if (component == sourcemap) {
                sourcemap = component + 1;
                continue;
            }
            **p_acc_map = strtol(sourcemap, NULL, 10);
            sourcemap = component + 1;
        }
        if (*p_acc_map != NULL) {
            **p_acc_map = strtol(sourcemap, NULL, 10);
        } else if (*sourcemap != ';' && *sourcemap != ':') {
            acc.jumpType = *sourcemap;
        }
    }
    *(arr + idx) = acc;

    return res.array;
}