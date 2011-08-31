/*
 * eca_ltc.c
 *
 *  Created on: 25-08-2011
 *      Author: damiank
 */


#ifdef WITH_LIBTOMCRYPT
#include "rlm_eca.h"

int generate_random(){

}

void do_ecc(void) {
	hash_state md;
	char *msg = "Testowy string11";
	unsigned char digest[32];
	int err;

	sha256_init(&md);
	sha256_process(&md, msg, strlen(msg));
	sha256_done(&md, digest);

	ecc_key mykey;
	if (register_prng(&sprng_desc) == -1) {
		printf("Error registering sprng!\n");
		return;
	}

	if ((err = ecc_make_key(NULL, find_prng("sprng"), 32, &mykey)) != CRYPT_OK) {
		printf("Error making key: %s\n", error_to_string(err));
		return;
	}

	unsigned char key[1024];
	unsigned long size;
	memset(key, 0, sizeof(key));
	ecc_export(key, &size, PK_PRIVATE, &mykey);
	printf("Priv key: %s\n", key);
	memset(key, 0, sizeof(key));
	ecc_export(key, &size, PK_PUBLIC, &mykey);
	printf("Public key: %s\n", key);

}

#endif
