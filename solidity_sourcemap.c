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
