/*
** /obj/login/interface.c
**
**  Author: Tamarindo
**
**    Date: December 2019
**
** Purpose: This file handles communication.
**
*/
#ifndef OBJ_LOGIN_INTERFACE_C
#define OBJ_LOGIN_INTERFACE_C

#include <daemons.h>

#ifndef OBJ_LOGIN_MXP_C
#include "/obj/login/mxp.c"
#endif // OBJ_LOGIN_MXP_C

private string terminal;
private nosave mapping terminal_info;

public string get_terminal();
public void set_terminal(string arg);

public string
get_terminal() {
    return terminal;
}

public void
set_terminal(string arg) {
    switch (arg) {

    case "ansi":
        terminal = "ansi";
	break;

    case "xterm-grey":
	terminal = "xterm-grey";
        break;

    case "xterm-256color":
	terminal = "xterm-256color";
        break;

    case "unknown":
	terminal = "unknown";
        break;

    default:
        log_file("TERMINALS", "Unknown terminal type: " + arg + "\n");
        break;
    }

    if (!terminal_info || terminal != arg) {
        terminal_info = TERMINAL_D->query_terminal_info(terminal);
    }
}

/*
**   Function: catch_msg
**
**    Purpose: Used to implement communication protocols between livings.
**
** Parameters: mixed *|struct|mapping|object msg, the non-string message
**             from say(), tell_room() or tell_object() for all living
**             objects that can hear it.
**
**             object ob, the object that has sent the message
**
**    Returns: void
*/
void catch_msg(mixed msg, object obj) {
   //write("catch_msg()\n");
}

/*
**   Function: catch_tell
**
**    Purpose: Filters and processes text before it is written to the
**             living. This enables communications between NPCs and from
**             a user to an NPC. Messages sent to an interactive object
**             are also received by the catch_tell() lfun. If the receiver
**             (or ones of its shadows) didn't have this lfun it would be
**             sent to the socket directly. Messages sent by an interactive
**             object to itself inside the catch_tell() are written to the
**             socket immediately.
**
** Parameters: string msg, the string message from say(), tell_object(),
**             tell_room() or write() for all living objects that could hear
**             it.
**
**    Returns: void
*/
void catch_tell(string msg) {
    write(terminal_colour(process_mxp(msg, does_mxp), terminal_info));
}
#endif // OBJ_LOGIN_INTERFACE_C
