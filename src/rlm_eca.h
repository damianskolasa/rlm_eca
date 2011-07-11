/*
 * rlm_eca.h
 *
 *  Created on: 11-07-2011
 *      Author: damiank
 */

#ifndef RLM_ECA_H_
#define RLM_ECA_H_

typedef struct {

	char *srv_pubkey_filename;
	char *ecc_domain_name;
	char *users_filename;

} rlm_eca_t;

static int eca_instantiate(CONF_SECTION *conf, void **instance);
static int eca_detach(void *instance);

static int eca_authorize(void *instance, REQUEST *request);

module_t rlm_eca = {
      RLM_MODULE_INIT,
      "eca",
      RLM_TYPE_THREAD_SAFE,           /* type */
      eca_instantiate,                /* instantiation */
      eca_detach,                    /* detach */
      {
              NULL,                   /* authentication */
              eca_authorize,          /* authorization */
              NULL,                   /* preaccounting */
              NULL,                   /* accounting */
              NULL,                   /* checksimul */
              NULL,                   /* pre-proxy */
              NULL,                   /* post-proxy */
              NULL                    /* post-auth */
      },
};

static const CONF_PARSER module_config[] = {
	{ "srv_pubkey_filename",    PW_TYPE_STRING_PTR,
	  offsetof(rlm_eca_t,srv_pubkey_filename), NULL, "yes" },
	{ "ecc_domain_name",    PW_TYPE_STRING_PTR,
	  offsetof(rlm_eca_t,ecc_domain_name), NULL, "yes" },
	{ "users_filename",    PW_TYPE_STRING_PTR,
	  offsetof(rlm_eca_t,users_filename), NULL, "yes" },
	{ NULL, -1, 0, NULL, NULL }		/* end the list */
};




#endif /* RLM_ECA_H_ */
