/*
 * Accounting module
 *
 * $Id: acc_mod.c,v 1.27.2.1.4.1 2004/07/18 22:56:23 sobomax Exp $
 *
 * Copyright (C) 2001-2003 Fhg Fokus
 *
 * This file is part of ser, a free SIP server.
 *
 * ser is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * For a license to use the ser software under conditions
 * other than those described here, or to purchase support for this
 * software, please contact iptel.org by e-mail at the following addresses:
 *    info@iptel.org
 *
 * ser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 * -------
 * 2003-03-06: aligned to change in callback names (jiri)
 * 2003-03-06: fixed improper sql connection, now from 
 * 	           child_init (jiri)
 * 2003-03-11: New module interface (janakj)
 * 2003-03-16: flags export parameter added (janakj)
 * 2003-04-04  grand acc cleanup (jiri)
 * 2003-04-06: Opens database connection in child_init only (janakj)
 * 2003-04-24  parameter validation (0 t->uas.request) added (jiri)
 * 2003-11-04  multidomain support for mysql introduced (jiri)
 */


#include <stdio.h>

#include "../../sr_module.h"
#include "../../dprint.h"
#include "../../mem/mem.h"
#include "../tm/t_hooks.h"
#include "../tm/tm_load.h"
#include "../tm/h_table.h"
#include "../../parser/msg_parser.h"
#include "../../parser/parse_from.h"

#include "acc_mod.h"
#include "acc.h"
#include "../tm/tm_load.h"

#ifdef RAD_ACC
#include <radiusclient.h>
#include "dict.h"
#endif

MODULE_VERSION

struct tm_binds tmb;

static int mod_init( void );
static void destroy(void);
static int child_init(int rank);

#ifdef SQL_ACC
db_con_t* db_handle;   /* Database connection handle */
#endif

/* ----- Parameter variables ----------- */


/* what would you like to report on */
/* should early media replies (183) be logged ? default==no */
int early_media = 0;
/* should failed replies (>=3xx) be logged ? default==no */
int failed_transactions = 0;
/* would you like us to report CANCELs from upstream too? */
int report_cancels = 0;
/* report e2e ACKs too */
int report_ack = 1;

/* syslog flags, that need to be set for a transaction to 
 * be reported; 0=any, 1..MAX_FLAG otherwise */
int log_flag = 0;
int log_missed_flag = 0;
/* noisiness level logging facilities are used */
int log_level=L_NOTICE;
char *log_fmt=DEFAULT_LOG_FMT;
#ifdef RAD_ACC
static char *radius_config = "/usr/local/etc/radiusclient/radiusclient.conf";
int radius_flag = 0;
int radius_missed_flag = 0;
static int service_type = -1;
void *rh;
struct attr attrs[A_MAX];
struct val vals[V_MAX];
#endif


#ifdef SQL_ACC
char *db_url=DEFAULT_DB_URL; /* Database url */

/* sql flags, that need to be set for a transaction to 
 * be reported; 0=any, 1..MAX_FLAG otherwise; by default
 * set to the same values as syslog -> reporting for both
 * takes place
 */
int db_flag = 0;
int db_missed_flag = 0;
int db_localtime = 0;

char *db_table_acc="acc"; /* name of database table> */


/* names of columns in tables acc/missed calls*/
char* acc_sip_from_col      = "sip_from";
char* acc_sip_to_col        = "sip_to";
char* acc_sip_status_col    = "sip_status";
char* acc_sip_method_col    = "sip_method";
char* acc_i_uri_col         = "i_uri";
char* acc_o_uri_col         = "o_uri";
char* acc_totag_col			= "totag";
char* acc_fromtag_col		= "fromtag";
char* acc_domain_col		= "domain";
char* acc_from_uri			= "from_uri";
char* acc_to_uri			= "to_uri";
char* acc_sip_callid_col    = "sip_callid";
char* acc_user_col          = "username";
char* acc_time_col          = "time";

/* name of missed calls table, default=="missed_calls" */
char *db_table_mc="missed_calls";
#endif

static int w_acc_log_request(struct sip_msg *rq, char *comment, char *foo);
#ifdef SQL_ACC
static int w_acc_db_request(struct sip_msg *rq, char *comment, char *foo);
#endif
#ifdef RAD_ACC
static int w_acc_rad_request(struct sip_msg *rq, char *comment, char *foo);
#endif

static cmd_export_t cmds[] = {
	{"acc_log_request", w_acc_log_request, 1, 0, REQUEST_ROUTE},
#ifdef SQL_ACC
	{"acc_db_request", w_acc_db_request, 2, 0, REQUEST_ROUTE},
#endif
#ifdef RAD_ACC
	{"acc_rad_request", w_acc_rad_request, 1, 0, REQUEST_ROUTE},
#endif
	{0, 0, 0, 0, 0}
};

static param_export_t params[] = {
	{"early_media",			INT_PARAM, &early_media          },
	{"failed_transactions",	INT_PARAM, &failed_transactions  },
	{"report_ack",			INT_PARAM, &report_ack           },
	{"report_cancels",		INT_PARAM, &report_cancels 		},
	/* syslog specific */
	{"log_flag",			INT_PARAM, &log_flag         	},
	{"log_missed_flag",		INT_PARAM, &log_missed_flag		},
	{"log_level",			INT_PARAM, &log_level            },
	{"log_fmt",				STR_PARAM, &log_fmt				},
#ifdef RAD_ACC
	{"radius_config",		STR_PARAM, &radius_config		},
	{"radius_flag",				INT_PARAM, &radius_flag			},
	{"radius_missed_flag",		INT_PARAM, &radius_missed_flag		},
	{"service_type", 		INT_PARAM, &service_type },
#endif
	/* db-specific */
#ifdef SQL_ACC
	{"db_flag",				INT_PARAM, &db_flag			},
	{"db_missed_flag",		INT_PARAM, &db_missed_flag		},
	{"db_table_acc",          STR_PARAM, &db_table_acc         }, 
	{"db_table_missed_calls", STR_PARAM, &db_table_mc },
	{"db_url",                STR_PARAM, &db_url               },
	{"acc_sip_from_column",   STR_PARAM, &acc_sip_from_col  },
	{"acc_sip_to_column",     STR_PARAM, &acc_sip_status_col},
	{"acc_sip_status_column", STR_PARAM, &acc_sip_status_col},
	{"acc_sip_method_column", STR_PARAM, &acc_sip_method_col},
	{"acc_i_uri_column",      STR_PARAM, &acc_i_uri_col     },
	{"acc_o_uri_column",      STR_PARAM, &acc_o_uri_col     },
	{"acc_sip_callid_column", STR_PARAM, &acc_sip_callid_col},
	{"acc_user_column",       STR_PARAM, &acc_user_col      },
	{"acc_time_column",       STR_PARAM, &acc_time_col      },
	{"acc_from_uri_column",		STR_PARAM, &acc_from_uri },
	{"acc_to_uri_column",		STR_PARAM, &acc_to_uri },
	{"acc_totag_column",		STR_PARAM, &acc_totag_col },
	{"acc_fromtag_column", 		STR_PARAM, &acc_fromtag_col },
	{"acc_domain_column", 		STR_PARAM, &acc_domain_col },
#endif
	{0,0,0}
};


struct module_exports exports= {
	"acc",
	cmds,       /* exported functions */
	params,     /* exported params */
	mod_init,   /* initialization module */
	0,	    /* response function */
	destroy,    /* destroy function */
	0,	    /* oncancel function */
	child_init  /* per-child init function */
};


/* ------------- Callback handlers --------------- */

static void acc_onreply( struct cell* t,  struct sip_msg *msg,
	int code, void *param );
static void acc_onack( struct cell* t,  struct sip_msg *msg,
	int code, void *param );
static void acc_onreq( struct cell* t, struct sip_msg *msg,
	int code, void *param ) ;
static void on_missed(struct cell *t, struct sip_msg *reply,
	int code, void *param );
static void acc_onreply_in(struct cell *t, struct sip_msg *reply,
	int code, void *param);

/* --------------- function definitions -------------*/

static int verify_fmt(char *fmt) {

	if (!fmt) {
		LOG(L_ERR, "ERROR: verify_fmt: formatting string zero\n");
		return -1;
	}
	if (!(*fmt)) {
		LOG(L_ERR, "ERROR: verify_fmt: formatting string empty\n");
		return -1;
	}
	if (strlen(fmt)>ALL_LOG_FMT_LEN) {
		LOG(L_ERR, "ERROR: verify_fmt: formatting string too long\n");
		return -1;
	}

	while(*fmt) {
		if (!strchr(ALL_LOG_FMT,*fmt)) {
			LOG(L_ERR, "ERROR: verify_fmt: char in log_fmt invalid: %c\n", 
				*fmt);
			return -1;
		}
		fmt++;
	}
	return 1;
}

static int mod_init( void )
{

	load_tm_f	load_tm;

	fprintf( stderr, "acc - initializing\n");

	/* import the TM auto-loading function */
	if ( !(load_tm=(load_tm_f)find_export("load_tm", NO_SCRIPT, 0))) {
		LOG(L_ERR, "ERROR: acc: mod_init: can't import load_tm\n");
		return -1;
	}
	/* let the auto-loading function load all TM stuff */
	if (load_tm( &tmb )==-1) return -1;

	if (verify_fmt(log_fmt)==-1) return -1;

	/* register callbacks */

	/*  report on completed transactions */
	if (tmb.register_tmcb( TMCB_RESPONSE_OUT, acc_onreply, 0 /* empty param */ ) <= 0)
		return -1;
	/* account e2e acks if configured to do so */
	if (tmb.register_tmcb( TMCB_E2EACK_IN, acc_onack, 0 /* empty param */ ) <=0 )
		return -1;
	/* disable silent c-timer for registered calls */
	if (tmb.register_tmcb( TMCB_REQUEST_IN, acc_onreq, 0 /* empty param */ ) <=0 )
		return -1;
	/* report on missed calls */
	if (tmb.register_tmcb( TMCB_ON_FAILURE, on_missed, 0 /* empty param */ ) <=0 )
		return -1;
	/* get incoming replies ready for processing */
	if (tmb.register_tmcb( TMCB_RESPONSE_IN, acc_onreply_in, 0 /* empty param */)<=0)
		return -1;

#ifdef SQL_ACC
	if (bind_dbmod()) {
		LOG(L_ERR, "ERROR: acc: init_child bind_db failed..."
				"did you load a database module?\n");
		return -1;
	}
#endif

#ifdef RAD_ACC
	memset(attrs, 0, sizeof(attrs));
	memset(attrs, 0, sizeof(vals));
	attrs[A_CALLING_STATION_ID].n		= "Calling-Station-Id";
	attrs[A_CALLED_STATION_ID].n		= "Called-Station-Id";
	attrs[A_SIP_TRANSLATED_REQUEST_URI].n	= "Sip-Translated-Request-URI";
	attrs[A_ACCT_SESSION_ID].n		= "Acct-Session-Id";
	attrs[A_SIP_TO_TAG].n			= "Sip-To-Tag";
	attrs[A_SIP_FROM_TAG].n			= "Sip-From-Tag";
	attrs[A_SIP_CSEQ].n			= "Sip-CSeq";
	attrs[A_ACCT_STATUS_TYPE].n		= "Acct-Status-Type";
	attrs[A_SERVICE_TYPE].n			= "Service-Type";
	attrs[A_SIP_RESPONSE_CODE].n		= "Sip-Response-Code";
	attrs[A_SIP_METHOD].n			= "Sip-Method";
	attrs[A_USER_NAME].n			= "User-Name";
	vals[V_STATUS_START].n			= "Start";
	vals[V_STATUS_STOP].n			= "Stop";
	vals[V_STATUS_FAILED].n			= "Failed";
	vals[V_SIP_SESSION].n			= "Sip-Session";

	/* open log */
	rc_openlog("ser");
	/* read config */
	if ((rh = rc_read_config(radius_config)) == NULL) {
		LOG(L_ERR, "ERROR: acc: error opening radius config file: %s\n", 
			radius_config );
		return -1;
	}
	/* read dictionary */
	if (rc_read_dictionary(rh, rc_conf_str(rh, "dictionary"))!=0) {
		LOG(L_ERR, "ERROR: acc: error reading radius dictionary\n");
		return -1;
	}

	INIT_AV(rh, attrs, vals, "acc", -1, -1);

	if (service_type != -1)
		vals[V_SIP_SESSION].v = service_type;
#endif

	return 0;
}

static int child_init(int rank)
{
#ifdef SQL_ACC
	db_handle = db_init(db_url);
	if (!db_handle) {
        LOG(L_ERR, "acc:init_child(): Unable to connect database\n");
		return -1;
	}
#endif
	return 0;
}

static void destroy(void)
{
#ifdef SQL_ACC
    if (db_handle) db_close(db_handle);
#endif
}


static inline void acc_preparse_req(struct sip_msg *rq)
{
	/* try to parse from for From-tag for accounted transactions; 
	 * don't be worried about parsing outcome -- if it failed, 
	 * we will report N/A
	 */
	parse_headers(rq, HDR_CALLID| HDR_FROM| HDR_TO, 0 );
	parse_from_header(rq);
	parse_orig_ruri(rq);
}

/* prepare message and transaction context for later accounting */
static void acc_onreq( struct cell* t, struct sip_msg *msg,
	int code, void *param )
{
	if (is_acc_on(msg) || is_mc_on(msg)) {
		acc_preparse_req(msg);
		/* also, if that is INVITE, disallow silent t-drop */
		if (msg->REQ_METHOD==METHOD_INVITE) {
			DBG("DEBUG: noisy_timer set for accounting\n");
			t->noisy_ctimer=1;
		}
	}
}

/* is this reply of interest for accounting ? */
static int should_acc_reply(struct cell *t, int code)
{
	struct sip_msg *r;

	r=t->uas.request;

	/* validation */
	if (r==0) {
		LOG(L_ERR, "ERROR: acc: should_acc_reply: 0 request\n");
		return 0;
	}

	/* negative transactions reported otherwise only if explicitely 
	 * demanded */
	if (!failed_transactions && code >=300) return 0;
	if (!is_acc_on(r))
		return 0;
	if (skip_cancel(r))
		return 0;
	if (code < 200 && ! (early_media && code==183))
		return 0;

	return 1; /* seed is through, we will account this reply */
}

/* parse incoming replies before cloning */
static void acc_onreply_in(struct cell *t, struct sip_msg *reply,
	int code, void *param)
{
	/* validation */
	if (t->uas.request==0) {
		LOG(L_ERR, "ERROR: acc: should_acc_reply: 0 request\n");
		return;
	}

	/* don't parse replies in which we are not interested */
	/* missed calls enabled ? */
	if (((t->is_invite && code>=300 && is_mc_on(t->uas.request))
					|| should_acc_reply(t,code)) 
				&& (reply && reply!=FAKED_REPLY)) {
		parse_headers(reply, HDR_TO, 0 );
	}
}

/* initiate a report if we previously enabled MC accounting for this t */
static void on_missed(struct cell *t, struct sip_msg *reply,
	int code, void *param )
{
	int reset_lmf; 
#ifdef SQL_ACC
	int reset_dmf;
#endif
#ifdef RAD_ACC
	int reset_rmf;
#endif

	/* validation */
	if (t->uas.request==0) {
		DBG("DBG: acc: on_missed: no uas.request, local t; skipping\n");
		return;
	}

	if (t->is_invite && code>=300) {
		if (is_log_mc_on(t->uas.request)) {
			acc_log_missed( t, reply, code);
			reset_lmf=1;
		} else reset_lmf=0;
#ifdef SQL_ACC
		if (is_db_mc_on(t->uas.request)) {
			acc_db_missed( t, reply, code);
			reset_dmf=1;
		} else reset_dmf=0;
#endif
#ifdef RAD_ACC
		if (is_rad_mc_on(t->uas.request)) {
			acc_rad_missed(t, reply, code );
			reset_rmf=1;
		} else reset_rmf=0;
#endif
		/* we report on missed calls when the first
		 * forwarding attempt fails; we do not wish to
		 * report on every attempt; so we clear the flags; 
		 * we do it after all reporting is over to be sure
		 * that all reporting functios got a fair chance
		 */
		if (reset_lmf) resetflag(t->uas.request, log_missed_flag);
#ifdef SQL_ACC
		if (reset_dmf) resetflag(t->uas.request, db_missed_flag);
#endif
#ifdef RAD_ACC
		if (reset_rmf) resetflag(t->uas.request, radius_missed_flag);
#endif
	}
}


/* initiate a report if we previously enabled accounting for this t */
static void acc_onreply( struct cell* t, struct sip_msg *reply,
	int code, void *param )
{
	/* validation */
	if (t->uas.request==0) {
		DBG("DBG: acc: onreply: no uas.request, local t; skipping\n");
		return;
	}

	/* acc_onreply is bound to TMCB_REPLY which may be called
	   from _reply, like when FR hits; we should not miss this
	   event for missed calls either
	*/
	on_missed(t, reply, code, param );

	if (!should_acc_reply(t, code)) return;
	if (is_log_acc_on(t->uas.request))
		acc_log_reply(t, reply, code);
#ifdef SQL_ACC
	if (is_db_acc_on(t->uas.request))
		acc_db_reply(t, reply, code);
#endif
#ifdef RAD_ACC
	if (is_rad_acc_on(t->uas.request))
		acc_rad_reply(t, reply, code);
#endif
}




static void acc_onack( struct cell* t , struct sip_msg *ack,
	int code, void *param )
{
	/* only for those guys who insist on seeing ACKs as well */
	if (!report_ack) return;
	/* if acc enabled for flagged transaction, check if flag matches */
	if (is_log_acc_on(t->uas.request)) {
		acc_preparse_req(ack);
		acc_log_ack(t, ack);
	}
#ifdef SQL_ACC
	if (is_db_acc_on(t->uas.request)) {
		acc_preparse_req(ack);
		acc_db_ack(t, ack);
	}
#endif
#ifdef RAD_ACC
	if (is_rad_acc_on(t->uas.request)) {
		acc_preparse_req(ack);
		acc_rad_ack(t,ack);
	}
#endif
	
}

/* these wrappers parse all what may be needed; they don't care about
 * the result -- accounting functions just display "unavailable" if there
 * is nothing meaningful
 */
static int w_acc_log_request(struct sip_msg *rq, char *comment, char *foo)
{
	str txt; str phrase;

	txt.s=ACC_REQUEST;
	txt.len=ACC_REQUEST_LEN;
	phrase.s=comment;
	phrase.len=strlen(comment);	/* fix_param would be faster! */
	acc_preparse_req(rq);
	return acc_log_request(rq, rq->to, &txt, &phrase);
}
#ifdef SQL_ACC
static int w_acc_db_request(struct sip_msg *rq, char *comment, char *table)
{
	str phrase;

	phrase.s=comment;
	phrase.len=strlen(comment);	/* fix_param would be faster! */
	acc_preparse_req(rq);
	return acc_db_request(rq, rq->to,&phrase,table, SQL_MC_FMT );
}
#endif
#ifdef RAD_ACC
static int w_acc_rad_request(struct sip_msg *rq, char *comment, 
				char *foo)
{
	str phrase;

	phrase.s=comment;
	phrase.len=strlen(comment);	/* fix_param would be faster! */
	acc_preparse_req(rq);
	return acc_rad_request(rq, rq->to,&phrase);
}
#endif
