#ifndef HASH_HELPERS_H
#define HASH_HELPERS_H


#include <stdlib.h>
#include <stdint.h>


uint8_t hash_xor8(const char *);

uint32_t hash_adler32(const char *);

uint32_t hash_crc32(const char *);

uint64_t hash_djb2(const char *);

uint64_t hash_sdbm(const char *);


#endif
