/*
** /basic/player/telopt.c
**
** Author: Tamarindo
**
**   Date: August 2019
**
** Purpose: This module performs some of the core handling of telnet
**	negotiation driven from a driver hook in the master  object.
**	These messages are passed to the telopt_negotiate function.
**
**      This file process:
**
**	* Mud Server Status Protocol (MSSP)
**	* Generic Mud Communications Protocol (GMCP)
**
** References:
**
**	https://tintin.sourceforge.io/protocols/mssp/
**	http://mudflinging.tumblr.com/post/37634529575/gmcp-negotiation-in-ldmud
**	https://www.gammon.com.au/gmcp
**	http://www.aardwolf.com/wiki/index.php/Clients/GMCP
**	http://nexus.ironrealms.com/GMCP
**
** See Also:
**
**	/include/mssp.h
**	/include/gmcp.h
**      /obj/login/mssp.c
**      /obj/login/gmcp.c
*/

#ifndef MSSP_H
#include <mssp.h>
#endif // MSSP_H

#ifndef GMCP_H
#include <gmcp.h>
#endif // GMCP_H

#ifndef OBJ_LOGIN_MSSP_C
#include "/obj/login/mssp.c"
#endif // OBJ_LOGIN_MSSP_C

#ifndef OBJ_LOGIN_GMCP_C
#include "/obj/login/gmcp.c"
#endif // OBJ_LOGIN_GMCP_C

#define OBJ_LOGIN_TELOPT_C

public void
telopt_negotiate(int action, int option, int *optdata) {
    string type;
    int n;

    switch (option)
    {
    case TELOPT_MSSP:

	if (action == DO) {
	    binary_message(({IAC, SB, TELOPT_MSSP}));
	    binary_message(to_bytes(mssp_message(), "UTF-8"));
	    binary_message(({IAC, SE}));
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
