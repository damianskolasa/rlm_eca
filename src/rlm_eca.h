/*
 * rlm_eca.h
 *
 *  Created on: 11-07-2011
 *      Author: damiank
 */

#ifndef RLM_ECA_H_
#define RLM_ECA_H_

#include <freeradius-devel/ident.h>
RCSID("$Id$")

#include <freeradius-devel/radiusd.h>
#include <freeradius-devel/modules.h>

#include <pthread.h>

#define WITH_LIBTOMCRYPT

#ifdef WITH_LIBTOMCRYPT
#define LTC_ECC
#include <tomcrypt.h>
#endif

#define INITIAL_STATE_STR "0"
#define CHALLENGE_RESP_STATE "1"

typedef struct {
	char *accept_msg;//Message that will be displayed to user on successfull auth/autor
	char *challenge_msg;//Message that will be displayed to user on challenge
	char *reject_msg;//Message that will be displayed to user on rejecection
	char *users_filename;//name of file that will be used to hold user certs
	char *srv_pubkey_filename;
	char *srv_prvkey_filename;
} rlm_eca_t;

typedef struct {
	char username[32];
	char nas_name[32];
	char nas_ip[4];
	int user_rand;
	int srv_rand;
	char state;
	ecc_key usr_key;
} eca_auth_ctx;

struct eca_auth_list_struct {
	eca_auth_ctx *node = NULL;
	struct eca_auth_list_struct *next = NULL;
} eca_auth_list;


static int ninstance = 0;

static int eca_instantiate(CONF_SECTION *conf, void **instance);
static int eca_detach(void *instance);
static int eca_authorize(void *instance, REQUEST *request);

int generate_random();
int sign_message();
int verify_message();

module_t rlm_eca = { RLM_MODULE_INIT, "eca", RLM_TYPE_THREAD_SAFE, /* type */
eca_instantiate, /* instantiation */
eca_detach, /* detach */
{ NULL, /* authentication */
eca_authorize, /* authorization */
NULL, /* preaccounting */
NULL, /* accounting */
NULL, /* checksimul */
NULL, /* pre-proxy */
NULL, /* post-proxy */
NULL /* post-auth */
}, };

static const CONF_PARSER module_config[] = {
		{ "srv_pubkey_filename",
		PW_TYPE_STRING_PTR, offsetof(rlm_eca_t, srv_pubkey_filename), NULL,
		"yes" },
		{ "srv_prvkey_filename", PW_TYPE_STRING_PTR, offsetof(rlm_eca_t,srv_prvkey_filename
		), NULL, "yes" },
		{ "accept_msg", PW_TYPE_STRING_PTR, offsetof(rlm_eca_t, accept_msg),
				NULL, "Welcome!" },
				{ "challenge_msg", PW_TYPE_STRING_PTR,
				offsetof(rlm_eca_t, challenge_msg), NULL, "Please wait..." },
				{
				"reject_msg", PW_TYPE_STRING_PTR, offsetof(rlm_eca_t,
						reject_msg), NULL, "Error!" },
						{ "users_filename",
				PW_TYPE_STRING_PTR, offsetof(rlm_eca_t, users_filename), NULL,
				"/usr/local/etc/freeradius/eca_users.cfg" },

		{ NULL, -1, 0, NULL, NULL } /* end the list */
};

#endif /* RLM_ECA_H_ */
