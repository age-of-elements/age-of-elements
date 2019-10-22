/*
** /basic/player/telopt.c
**
** Author: Tamarindo
**
**   Date: August 2019
**
** Purpose: This module performs some of the core handling of telnet
**	negotiation driven from a driver hook in the master object.
**	These messages are passed to the telopt_negotiate function.
**
**      This file process:
**
**	* Mud Sound Protocol (MSP)
**	* Mud Server Status Protocol (MSSP)
**	* Mud eXtention Protocol (MXP)
**	* Generic Mud Communications Protocol (GMCP)
**
** References:
**
**	Telnet Negotiation in LDMud:
**
**	http://mudflinging.tumblr.com/post/37634529575/gmcp-negotiation-in-ldmud
**
**	MSP:
**
**	https://www.zuggsoft.com/zmud/msp.htm
**
**	MSSP:
**
**	https://tintin.sourceforge.io/protocols/mssp/
**
**	MXP:
**
**	https://www.gammon.com.au/mushclient/addingservermxp.htm
**
**	GMCP:
**
**	https://www.gammon.com.au/gmcp
**	http://www.aardwolf.com/wiki/index.php/Clients/GMCP
**	http://nexus.ironrealms.com/GMCP
**
** See Also:
**
**	/include/msp.h
**	/include/mssp.h
**	/include/mxp.h
**	/include/gmcp.h
**      /obj/login/msp.c
**      /obj/login/mssp.c
**      /obj/login/mxp.c
**      /obj/login/gmcp.c
*/

#ifndef TELNET_H__
#include <sys/telnet.h>
#endif // TELNET_H__

#ifndef MSP_H
#include <msp.h>
#endif // MSP_H

#ifndef MSSP_H
#include <mssp.h>
#endif // MSSP_H

#ifndef MXP_H
#include <mxp.h>
#endif // MXP_H

#ifndef GMCP_H
#include <gmcp.h>
#endif // GMCP_H

#ifndef OBJ_LOGIN_MSP_C
#include "/obj/login/msp.c"
#endif // OBJ_LOGIN_MSP_C

#ifndef OBJ_LOGIN_MSSP_C
#include "/obj/login/mssp.c"
#endif // OBJ_LOGIN_MSSP_C

#ifndef OBJ_LOGIN_MXP_C
#include "/obj/login/mxp.c"
#endif // OBJ_LOGIN_MXP_C

#ifndef OBJ_LOGIN_GMCP_C
#include "/obj/login/gmcp.c"
#endif // OBJ_LOGIN_GMCP_C

#define OBJ_LOGIN_TELOPT_C

public void
telopt_negotiate(int action, int option, int *optdata) {
    switch (option)
    {
    case TELOPT_MSP:
	if (action == DO) {
	    set_msp(1);
	    // Send the default URL
	    msp_output(MSP_SOUND, ([MSP_FILENAME: MSP_FILENAME_OFF, MSP_URL: MSP_URL_DEFAULT]));
	    msp_test(1);
	    call_out(#'msp_test, 10, 2);
	    call_out(#'msp_test, 20, 3);
	    call_out(#'msp_test, 30, 4);
	    call_out(#'msp_test, 40, 5);
	    call_out(#'msp_test, 50, 6);
	    call_out(#'msp_test, 60, 7);
	} else if (action == DONT) {
	    set_msp(0);
	}
	break;

    case TELOPT_MSSP:
	if (action == DO) {
	    set_mssp(1);

	    binary_message(({IAC, SB, TELOPT_MSSP}));
	    binary_message(to_bytes(mssp_message(), "UTF-8"));
	    binary_message(({IAC, SE}));
	} else if (action == DONT) {
	    set_mssp(0);
	}
	break;

    case TELOPT_MXP:
	if (action == DO) {
	    set_mxp(1);
	    init_mxp();
	} else if (action == DONT) {
	    set_mxp(0);
	}
	break;

    case TELOPT_GMCP:
	if (action == SB) {
	    gmcp_input(optdata);
	}
	break;

    default:
	if (action == WILL) {
	    binary_message(to_bytes(sprintf("%c%c%c", IAC, DONT, option), "UTF-8"), 3);
	} else if (action == DO) {
	    binary_message(to_bytes(sprintf("%c%c%c", IAC, WONT, option), "UTF-8"), 3);
	}
    }
}
