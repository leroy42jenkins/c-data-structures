#include "hash_helpers.h"


uint8_t hash_xor8(const char *s) {
	const uint8_t f = 0xff;
	uint8_t h = 0;

	for (size_t i = 0; s[i] != '\0'; ++i) {
		h = (h + s[i]) & f;
	}

	return ((h ^ f) + 1) & f;
}

uint32_t hash_adler32(const char *s) {
	const uint32_t mod = 65521;
	uint32_t a = 1;
	uint32_t b = 0;

	for (size_t i = 0; s[i] != '\0'; ++i) {
		a = (a + s[i]) % mod;
		b = (a + b) % mod;
	}

	return (b << 16) | a;
}

uint32_t hash_crc32(const char *s) {
	const uint32_t f = 0xffffffff;
	uint32_t h = f;

	for (size_t i = 0; s[i] != '\0'; ++i) {
		uint8_t b = s[i];
		h = h ^ b;

		for (uint8_t j = 8; j > 0; --j) {
			h = (h >> 1) ^ (0xED88320 & (-1 * (h & 1)));
		}
	}

	return h ^ f;
}

uint64_t hash_djb2(const char *s) {
	uint64_t h = 5381;

	for (size_t i = 0; s[i] != '\0'; ++i) {
		h = s[i] + (h << 5) + h;
	}

	return h;
}

uint64_t hash_sdbm(const char *s) {
	uint64_t h = 0;

	for (size_t i = 0; s[i] != '\0'; ++i) {
		h = s[i] + (h << 6) + (h << 16) - h;
	}

	return h;
}

