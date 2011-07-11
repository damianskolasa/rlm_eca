/*
 * rlm_eca.h
 *
 *  Created on: 11-07-2011
 *      Author: damiank
 */

#ifndef RLM_ECA_H_
#define RLM_ECA_H_

typedef struct {




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

	{ "use_mppe",    PW_TYPE_BOOLEAN,
	  offsetof(rlm_mschap_t,use_mppe), NULL, "yes" },
	{ "require_encryption",    PW_TYPE_BOOLEAN,
	  offsetof(rlm_mschap_t,require_encryption), NULL, "no" },
	{ "require_strong",    PW_TYPE_BOOLEAN,
	  offsetof(rlm_mschap_t,require_strong), NULL, "no" },
	{ "with_ntdomain_hack",     PW_TYPE_BOOLEAN,
	  offsetof(rlm_mschap_t,with_ntdomain_hack), NULL, "no" },
	{ "passwd",   PW_TYPE_STRING_PTR,
	  offsetof(rlm_mschap_t, passwd_file), NULL,  NULL },
	{ "ntlm_auth",   PW_TYPE_STRING_PTR,
	  offsetof(rlm_mschap_t, ntlm_auth), NULL,  NULL },
	{ "allow_retry",   PW_TYPE_BOOLEAN,
	  offsetof(rlm_mschap_t, allow_retry), NULL,  "yes" },
	{ "retry_msg",   PW_TYPE_STRING_PTR,
	  offsetof(rlm_mschap_t, retry_msg), NULL,  NULL },
	{ NULL, -1, 0, NULL, NULL }		/* end the list */
};




#endif /* RLM_ECA_H_ */
