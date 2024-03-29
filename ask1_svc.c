/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "ask1.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
ask1_prog1_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		XY_array inner_product_1_arg;
		X_array averagex_1_arg;
		Y_array averagey_1_arg;
		r_times_X_Y product_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case inner_product:
		_xdr_argument = (xdrproc_t) xdr_XY_array;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) inner_product_1_svc;
		break;

	case averageX:
		_xdr_argument = (xdrproc_t) xdr_X_array;
		_xdr_result = (xdrproc_t) xdr_float;
		local = (char *(*)(char *, struct svc_req *)) averagex_1_svc;
		break;

	case averageY:
		_xdr_argument = (xdrproc_t) xdr_Y_array;
		_xdr_result = (xdrproc_t) xdr_float;
		local = (char *(*)(char *, struct svc_req *)) averagey_1_svc;
		break;

	case product:
		_xdr_argument = (xdrproc_t) xdr_r_times_X_Y;
		_xdr_result = (xdrproc_t) xdr_rXY;
		local = (char *(*)(char *, struct svc_req *)) product_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (ASK1_PROG1, ASK1_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, ASK1_PROG1, ASK1_VERS, ask1_prog1_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (ASK1_PROG1, ASK1_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, ASK1_PROG1, ASK1_VERS, ask1_prog1_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (ASK1_PROG1, ASK1_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
