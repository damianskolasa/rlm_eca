/*
 * eca_openssl.c
 *
 *  Created on: 25-08-2011
 *      Author: damiank
 */

#ifdef WITH_OPENSSL
#include <openssl/ecdsa.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <openssl/bn.h>
#include <openssl/bio.h>
#include <openssl/pem.h>



void do_ecc(void) {
	int ret;
	ECDSA_SIG *sig = NULL;
	EC_KEY *ec_key = EC_KEY_new();
	EC_GROUP *group = NULL;

	EC_KEY *cli_prv = NULL, *cli_pub = NULL, *srv_prv = NULL, *srv_pub = NULL;
	BIO *in_cli_prv= NULL, *in_cli_pub = NULL, *in_srv_prv = NULL, *in_srv_pub = NULL;

	in_cli_prv = BIO_new(BIO_s_file());
	BIO_read_filename(in_cli_prv, "/HOME/damiank/inz/cli_prv.pem");
	cli_prv = PEM_read_bio_ECPrivateKey(in_cli_prv, NULL, NULL, NULL);
	if (cli_prv == NULL) {
		printf("Blad11 ");
		return EXIT_FAILURE;
	}

	in_cli_pub = BIO_new(BIO_s_file());
	BIO_read_filename(in_cli_pub, "/HOME/damiank/inz/cli_pub.pem");
	cli_pub = PEM_read_bio_EC_PUBKEY(in_cli_pub, NULL, NULL, NULL);
	if (cli_pub == NULL) {
		printf("Blad12 ");
		return EXIT_FAILURE;
	}

	in_srv_prv = BIO_new(BIO_s_file());
	BIO_read_filename(in_srv_prv, "/HOME/damiank/inz/srv_prv.pem");
	srv_prv = PEM_read_bio_ECPrivateKey(in_srv_prv, NULL, NULL, NULL);
	if (srv_prv == NULL) {
		printf("Blad13 ");
		return EXIT_FAILURE;
	}

	in_srv_pub = BIO_new(BIO_s_file());
	BIO_read_filename(in_srv_pub, "/HOME/damiank/inz/srv_pub.pem");
	srv_pub = PEM_read_bio_EC_PUBKEY(in_srv_pub, NULL, NULL, NULL);
	if (srv_pub == NULL) {
		printf("Blad14 ");
		return EXIT_FAILURE;
	}

	if (ec_key == NULL) {
		printf("Blad1 ");
		return EXIT_FAILURE;
	}
	group = EC_GROUP_new_by_curve_name(NID_sect283k1);

	BIGNUM *cli_prv_num = EC_KEY_get0_private_key(cli_prv);

	printf("Private key: %s\n", BN_bn2hex(cli_prv_num));

	if (EC_KEY_set_group(ec_key, group) == 0) {
		/*goto end;

		 ec_key->group = EC_GROUP_new_by_curve_name(NID_sect283k1);
		 if (ec_key->group == NULL) {*/
		printf("Blad2 ");
		return EXIT_FAILURE;
	}

	if (!EC_KEY_generate_key(ec_key)) {
		printf("Blad3 ");
		return EXIT_FAILURE;
	}

	SHA256_CTX *sha256_ctx;
	sha256_ctx = OPENSSL_malloc(sizeof(SHA256_CTX));
	char sha256_sig[SHA256_DIGEST_LENGTH];
	if (sha256_ctx == NULL) {
		printf("Blad4 ");
		return EXIT_FAILURE;
	}

	if (!SHA256_Init(sha256_ctx)) {
		printf("Blad5 ");
		return EXIT_FAILURE;
	}

	if (!SHA256_Update(sha256_ctx, "Testowy string11",
					strlen("Testowy string11"))) {
		printf("Blad6 ");
		return EXIT_FAILURE;
	}

	if (!SHA256_Final(sha256_sig, sha256_ctx)) {
		printf("Blad7 ");
		return EXIT_FAILURE;
	}

	printf("SHA256: ");
	int i;
	for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		printf("%x", sha256_sig[i]);
	}
	printf("\n");

	sig = ECDSA_do_sign(sha256_sig, SHA256_DIGEST_LENGTH, cli_prv);
	if (sig == NULL) {
		printf("Blad8 ");
		return EXIT_FAILURE;
	}

	printf("Cli prv s: %s\n", BN_bn2hex(sig->s));
	printf("Cli prv r: %s\n", BN_bn2hex(sig->r));

	//ec_key->priv_key;

	ret = ECDSA_do_verify(sha256_sig, SHA256_DIGEST_LENGTH, sig, cli_pub);

	if (ret == -1) {
		printf("Blad9 ");
		return EXIT_FAILURE;
	} else if (ret == 0) {
		printf("Client -> Server ZLE !!\n");
	} else /* ret == 1 */
	{
		printf("Client -> Server DOBRZE\n");
	}
	ECDSA_SIG_free(sig);

	printf("SHA256: ");
	for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		printf("%x", sha256_sig[i]);
	}
	printf("\n");

	sig = ECDSA_do_sign(sha256_sig, SHA256_DIGEST_LENGTH, srv_prv);
	if (sig == NULL) {
		printf("Blad8 ");
		return EXIT_FAILURE;
	}

	printf("Srv prv s: %s\n", BN_bn2hex(sig->s));
	printf("Srv prv r: %s\n", BN_bn2hex(sig->r));

	ret = ECDSA_do_verify(sha256_sig, SHA256_DIGEST_LENGTH, sig, srv_pub);

	if (ret == -1) {
		printf("Blad9 ");
		return EXIT_FAILURE;
	} else if (ret == 0) {
		printf("Server -> Client ZLE !!\n");
	} else /* ret == 1 */
	{
		printf("Server -> Client DOBRZE\n");
	}

	OPENSSL_free(sha256_ctx);
	EC_KEY_free(ec_key);
	EC_KEY_free(cli_prv);
	EC_KEY_free(cli_pub);
	EC_KEY_free(srv_prv);
	EC_KEY_free(srv_pub);
	ECDSA_SIG_free(sig);
	BIO_free(in_cli_prv);
	BIO_free(in_cli_pub);
	BIO_free(in_srv_prv);
	BIO_free(in_srv_pub);
}



#endif
