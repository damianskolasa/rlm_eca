/*
 ============================================================================
 Name        : rlm_eca.c
 Author      : Damian Kolasa
 Version     : 1.0
 Copyright   : My
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rlm_eca.h"

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


int handle_initial_state(rlm_eca_t *rlm_eca, REQUEST *request);
int handle_challenge_resp_state(rlm_eca_t *rlm_eca, REQUEST *request);

static int eca_instantiate(CONF_SECTION *conf, void **instance) {
	rlm_eca_t *rlm_eca;

	rlm_eca = rad_malloc(sizeof(*rlm_eca));
	(void) memset(rlm_eca, 0, sizeof(*rlm_eca));

	if (cf_section_parse(conf, rlm_eca, module_config) < 0) {
		free(rlm_eca);
		return -1;
	}

	if (!ninstance) {
		//RDEBUG("Creating instance...");
		//TODO Init auth req list

		ninstance++;
	} else {
		//RDEBUG("Prevented creating instance %d", ninstance);
		ninstance++;
	}

	*instance = rlm_eca;
	return 0;
}

static int eca_detach(void *instance) {
	//RDEBUG("Freeing instance %d", ninstance);
	free(instance);
	ninstance--;
	//TODO or only --ninstance == 0 ?
	return 0;
}

static int eca_authorize(void *instance, REQUEST *request) {
	VALUE_PAIR *auth_type = NULL,
			*user_name = NULL,
			*user_passw = NULL,
			*state = NULL, *user_rand = NULL, *user_hash = NULL;
	char *username = NULL;

	auth_type = pairfind(request->packet->vps, PW_AUTHTYPE);
	if (auth_type == NULL) {
		RDEBUG2("WARNING: Auth-Type not set.");
		return RLM_MODULE_FAIL;
	}
	if (!strcasecmp(auth_type->data.strvalue, "ECA")) {
		RDEBUG2("WARNING: Auth-Type is not ECA");
		return RLM_MODULE_FAIL;
	}

	user_name = pairfind(request->packet->vps, PW_USER_NAME);
	if (user_name == NULL) {
		RDEBUG2("WARNING: No username");
		return RLM_MODULE_FAIL;
	}
	username = user_name->data.strvalue;

	state = pairfind(request->packet->vps, PW_STATE);
	if (state == NULL) {
		RDEBUG2("WARNING: No state");
		return RLM_MODULE_FAIL;
	}

	//PW_DIGEST_HA1
	//PW_DIGEST_NONCE
	//PW_USER_NAME
	//PW_NAS_IP_ADDRESS
	//PW_STATE
	// PW_NAS_IDENTIFIER

	if (strcasecmp(INITIAL_STATE_STR, state->data.strvalue)) {
		/*user_rand = pairfind(request->packet->vps, PW_USER_NAME);
			if (user_name == NULL) {
				RDEBUG2("WARNING: No username");
				return RLM_MODULE_FAIL;
			}
			username = user_name->data.strvalue;*/
	} else if (strcasecmp(CHALLENGE_RESP_STATE, state->data.strvalue)) {

	} else {
		RDEBUG2("WARNING: Unknown state");
		return RLM_MODULE_FAIL;
	}

	pthread_mutex_lock(&mutex1);

	pthread_mutex_unlock(&mutex1);

}

int main(void) {
	do_ecc();

	return EXIT_SUCCESS;
}

