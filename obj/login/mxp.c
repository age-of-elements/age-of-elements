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
private string process_mxp(string message);

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

    write(process_mxp(MXPTAG("!-- Set up MXP elements --")));
    write(process_mxp(MXPTAG("!ELEMENT RNum FLAG=\"RoomNum\" ATT=\"id\" EMPTY")));
    write(process_mxp(MXPTAG("!ELEMENT RName FLAG=\"RoomName\"")));
    write(process_mxp(MXPTAG("!ELEMENT RDesc FLAG=\"RoomDesc\"")));
    write(process_mxp(MXPTAG("!ELEMENT RExits FLAG=\"RoomExit\"")));
    write(process_mxp(MXPTAG("!ELEMENT Prompt FLAG=\"Prompt\"")));
    write(process_mxp(MXPTAG("!ELEMENT Ex '<send>'")));
}

/*
**   Function: process_mxp
**
**    Purpose: Process MXP.
**
** Parameters: string message, the message to transform
**
**    Returns: string
*/
private string
process_mxp(string message) {
    int line = 0;
    int length = 0;
    int i = 0;
    int inTag = 0;
    int inEntity = 0;

    string *original_lines = explode(message, "\n");
    string *processed_lines = allocate(sizeof(original_lines));

    for (line = 0; line < sizeof(original_lines); line++) {
	processed_lines[line] = does_mxp ? MXPMODE(1) : "";

        length = sizeof(original_lines[line]);

        for (i = 0; i < length; i++) {
            if (inTag) { /* in a tag, eg. <send> */
                if (original_lines[line][i..i] == MXP_END) {
                    inTag = 0;

                    if (does_mxp) {
                        processed_lines[line] += ">";
                    }
                } else if (does_mxp) { /* copy tag only when MXP does_mxp */
                    processed_lines[line] += original_lines[line][i..i];
                }
            } else if (inEntity) { /* in a tag, eg. <send> */
                if (does_mxp) { /* copy tag only when MXP does_mxp */
                    processed_lines[line] += original_lines[line][i..i];
                }

                if (original_lines[line][i..i] == ";") {
                    inEntity = 0;
                }
            } else {
                if (original_lines[line][i..i] == MXP_BEG) {
                    inTag = 1;

                    if (does_mxp) {
                        processed_lines[line] += "<";
                    }
                } else if (original_lines[line][i..i] == MXP_END) { /* should not get this case */
                    processed_lines[line] += ">";
                } else if (original_lines[line][i..i] == MXP_AMP) {
                    inEntity = 1;

                    if (does_mxp) {
                        processed_lines[line] += "<";
                    }
                } else if (does_mxp) {
                    if (original_lines[line][i..i] == "<") {
                        processed_lines[line] += "&lt;";
                    } else if (original_lines[line][i..i] == ">") {
                        processed_lines[line] += "&gt;";
                    } else if (original_lines[line][i..i] == "&") {
                        processed_lines[line] += "&amp;";
                    } else if (original_lines[line][i..i] == "\"") {
                        processed_lines[line] += "&quot;";
                    } else {
                        processed_lines[line] += original_lines[line][i..i];
                    }
                } else { /* not MXP - just copy character */
                    processed_lines[line] += original_lines[line][i..i];
                }
            }
        }
    }

    return implode(processed_lines, "\n");
}
#endif // OBJ_LOGIN_MXP_C
