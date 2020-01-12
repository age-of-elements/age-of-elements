/*
** /obj/login/mxp.c
**
**  Author: Tamarindo
**
**    Date: September 2019
**
** Purpose: This file handles the Mud eXtension Protocol (MXP)
**      message.
**
** References:
**
**      https://www.gammon.com.au/mushclient/addingservermxp.htm
**
** See Also:
**
**      /include/mxp.h
**      /obj/login/telopt.c
*/

#ifndef OBJ_LOGIN_MXP_C
#define OBJ_LOGIN_MXP_C

#ifndef TELNET_H__
#include <sys/telnet.h>
#endif // TELNET_H__

#ifndef MXP_H
#include <mxp.h>
#endif // MXP_H

static int does_mxp = 0;

private void set_mxp(int arg);
public nomask int does_mxp();
private void init_mxp();

/*
**    Function: set_mxp
**
**     Purpose: Set whether the client supports MXP.
**
**  Parameters: int arg, 0 for false, 1 for true.
**
**     Returns: void
*/
private void
set_mxp(int arg) {
    does_mxp = arg;
}

/*
** Function: does_mxp
**
**  Purpose: Query whether the client supports MXP.
**
**  Returns: int, 0 for false, 1 for true.
*/
public nomask int
does_mxp() {
    return does_mxp;
}

/*
** Function: init_mxp
**
**  Purpose: Set up MXP Elements.
**
**  Returns: void
*/
private void
init_mxp() {
    // Tell the client that from now on we are sending MXP sequences
    binary_message(({IAC, SB, TELOPT_MXP, IAC, SE}));

    // Switch to "permanent secure" mode, MXP tags now enabled
    write(process_mxp(MXPMODE(6)));

    write(process_mxp(MXPTAG("!-- Set up MXP elements --"), does_mxp));
    write(process_mxp(MXPTAG("!ELEMENT RNum FLAG=\"RoomNum\" ATT=\"id\" EMPTY"), does_mxp));
    write(process_mxp(MXPTAG("!ELEMENT RName FLAG=\"RoomName\""), does_mxp));
    write(process_mxp(MXPTAG("!ELEMENT RDesc FLAG=\"RoomDesc\""), does_mxp));
    write(process_mxp(MXPTAG("!ELEMENT RExits FLAG=\"RoomExit\""), does_mxp));
    write(process_mxp(MXPTAG("!ELEMENT Prompt FLAG=\"Prompt\""), does_mxp));
    write(process_mxp(MXPTAG("!ELEMENT Ex \"<send>\""), does_mxp));
}
#endif // OBJ_LOGIN_MXP_C
