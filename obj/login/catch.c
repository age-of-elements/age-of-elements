/*
** /obj/login/catch.c
**
**  Author: Tamarindo
**
**    Date: December 2019
**
** Purpose: This file handles communication between livings.
**
*/

#ifndef OBJ_LOGIN_CATCH_C
#define OBJ_LOGIN_CATCH_C

#ifndef OBJ_LOGIN_MXP_C
#include "/obj/login/mxp.c"
#endif // OBJ_LOGIN_MXP_C

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
    write(process_mxp(msg));
}
#endif // OBJ_LOGIN_CATCH_C

