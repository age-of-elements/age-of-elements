/*
** /obj/login/mssp.c
**
**  Author: Tamarindo
**
**    Date: August 2019
**
** Purpose: This file prepares the Mud Server Status Protocol (MSSP)
**	message.
**
** References:
**
**	https://tintin.sourceforge.io/protocols/mssp/
**	https://grapevine.haus/mssp
**
** See Also:
**
**	/include/mssp.h
**	/obj/login/telopt.c
*/

#ifndef OBJ_LOGIN_MSSP_C
#define OBJ_LOGIN_MSSP_C

#ifndef MSSP_H
#include <mssp.h>
#endif // MSSP_H

static int does_mssp = 0;

private void set_mssp(int arg);
public nomask int does_mssp();
private string mssp_message();

/*
**    Function: set_mssp
**
**     Purpose: Set whether the client supports MSSP.
**
**  Parameters: int arg, 0 for false, 1 for true.
**
**     Returns: void
*/
private void
set_mssp(int arg) {
    does_mssp = arg;
}

/*
** Function: does_mssp
**
**  Purpose: Query whether the client supports MSSP.
**
**  Returns: int, 0 for false, 1 for true.
*/
public nomask int
does_mssp() {
    return does_mssp;
}

private string
mssp_message() {
    string mssp_message = "";

    mapping mssp = ([
      MSSP_VAR_NAME: MSSP_VAL_NAME          // Required
      , MSSP_VAR_PLAYERS: MSSP_VAL_PLAYERS  // Required
      , MSSP_VAR_UPTIME: MSSP_VAL_UPTIME    // Required
#ifdef MSSP_VAR_HOSTNAME
      , MSSP_VAR_HOSTNAME: MSSP_VAL_HOSTNAME
#endif
#ifdef MSSP_VAR_PORT
      , MSSP_VAR_PORT: MSSP_VAL_PORT
#endif
#ifdef MSSP_VAR_CODEBASE
      , MSSP_VAR_CODEBASE: MSSP_VAL_CODEBASE
#endif
#ifdef MSSP_VAR_CONTACT
      , MSSP_VAR_CONTACT: MSSP_VAL_CONTACT
#endif
#ifdef MSSP_VAR_CREATED
      , MSSP_VAR_CREATED: MSSP_VAL_CREATED
#endif
#ifdef MSSP_VAR_DISCORD
      , MSSP_VAR_DISCORD: MSSP_VAL_DISCORD
#endif
#ifdef MSSP_VAR_ICON
      , MSSP_VAR_ICON: MSSP_VAL_ICON
#endif
#ifdef MSSP_VAR_IP
      , MSSP_VAR_IP: MSSP_VAL_IP
#endif
#ifdef MSSP_VAR_LANGUAGE
      , MSSP_VAR_LANGUAGE: MSSP_VAL_LANGUAGE
#endif
#ifdef MSSP_VAR_LOCATION
      , MSSP_VAR_LOCATION: MSSP_VAL_LOCATION
#endif
#ifdef MSSP_VAR_MINIMUM_AGE
      , MSSP_VAR_MINIMUM_AGE: MSSP_VAL_MINIMUM_AGE
#endif
#ifdef MSSP_VAR_WEBSITE
      , MSSP_VAR_WEBSITE: MSSP_VAL_WEBSITE
#endif
#ifdef MSSP_VAR_FAMILY
      , MSSP_VAR_FAMILY: MSSP_VAL_FAMILY
#endif
#ifdef MSSP_VAR_GENRE
      , MSSP_VAR_GENRE: MSSP_VAL_GENRE
#endif
#ifdef MSSP_VAR_GAMEPLAY
      , MSSP_VAR_GAMEPLAY: MSSP_VAL_GAMEPLAY
#endif
#ifdef MSSP_VAR_GAMESYSTEM
      , MSSP_VAR_GAMESYSTEM: MSSP_VAL_GAMESYSTEM
#endif
#ifdef MSSP_VAR_INTERMUD
      , MSSP_VAR_INTERMUD: MSSP_VAL_INTERMUD
#endif
#ifdef MSSP_VAR_STATUS
      , MSSP_VAR_STATUS: MSSP_VAL_STATUS
#endif
#ifdef MSSP_VAR_SUBGENRE
      , MSSP_VAR_SUBGENRE: MSSP_VAL_SUBGENRE
#endif
#ifdef MSSP_VAR_AREAS
      , MSSP_VAR_AREAS: MSSP_VAL_AREAS
#endif
#ifdef MSSP_VAR_HELPFILES
      , MSSP_VAR_HELPFILES: MSSP_VAL_HELPFILES
#endif
#ifdef MSSP_VAR_MOBILES
      , MSSP_VAR_MOBILES: MSSP_VAL_MOBILES
#endif
#ifdef MSSP_VAR_OBJECTS
      , MSSP_VAR_OBJECTS: MSSP_VAL_OBJECTS
#endif
#ifdef MSSP_VAR_ROOMS
      , MSSP_VAR_ROOMS: MSSP_VAL_ROOMS
#endif
#ifdef MSSP_VAR_CLASSES
      , MSSP_VAR_CLASSES: MSSP_VAL_CLASSES
#endif
#ifdef MSSP_VAR_LEVELS
      , MSSP_VAR_LEVELS: MSSP_VAL_LEVELS
#endif
#ifdef MSSP_VAR_RACES
      , MSSP_VAR_RACES: MSSP_VAL_RACES
#endif
#ifdef MSSP_VAR_SKILLS
      , MSSP_VAR_SKILLS: MSSP_VAL_SKILLS
#endif
#ifdef MSSP_VAR_ANSI
      , MSSP_VAR_ANSI: MSSP_VAL_ANSI
#endif
#ifdef MSSP_VAR_GMCP
      , MSSP_VAR_GMCP: MSSP_VAL_GMCP
#endif
#ifdef MSSP_VAR_MSDP
      , MSSP_VAR_MSDP: MSSP_VAL_MSDP
#endif
#ifdef MSSP_VAR_MCCP
      , MSSP_VAR_MCCP: MSSP_VAL_MCCP
#endif
#ifdef MSSP_VAR_MCP
      , MSSP_VAR_MCP: MSSP_VAL_MCP
#endif
#ifdef MSSP_VAR_MSP
      , MSSP_VAR_MSP: MSSP_VAL_MSP
#endif
#ifdef MSSP_VAR_MXP
      , MSSP_VAR_MXP: MSSP_VAL_MXP
#endif
#ifdef MSSP_VAR_PUEBLO
      , MSSP_VAR_PUEBLO: MSSP_VAL_PUEBLO
#endif
#ifdef MSSP_VAR_UTF_8
      , MSSP_VAR_UTF_8: MSSP_VAL_UTF_8
#endif
#ifdef MSSP_VAR_VT100
      , MSSP_VAR_VT100: MSSP_VAL_VT100
#endif
#ifdef MSSP_VAR_XTERM_256_COLORS
      , MSSP_VAR_XTERM_256_COLORS: MSSP_VAL_XTERM_256_COLORS
#endif
#ifdef MSSP_VAR_SSL
      , MSSP_VAR_SSL: MSSP_VAL_SSL
#endif
#ifdef MSSP_VAR_PAY_TO_PLAY
      , MSSP_VAR_PAY_TO_PLAY: MSSP_VAL_PAY_TO_PLAY
#endif
#ifdef MSSP_VAR_PAY_FOR_PERKS
      , MSSP_VAR_PAY_FOR_PERKS: MSSP_VAL_PAY_FOR_PERKS
#endif
#ifdef MSSP_VAR_HIRING_BUILDERS
      , MSSP_VAR_HIRING_BUILDERS: MSSP_VAL_HIRING_BUILDERS
#endif
#ifdef MSSP_VAR_HIRING_CODERS
      , MSSP_VAR_HIRING_CODERS: MSSP_VAL_HIRING_CODERS
#endif
    ]);

    // IAC SB MSSP MSSP_VAR "PLAYERS" MSSP_VAL "52" MSSP_VAR "UPTIME" MSSP_VAL "1234567890" IAC SE

    foreach (string var, string val : mssp) {
	mssp_message += sprintf("%c%s%c%s", MSSP_VAR, var, MSSP_VAL, val);
    }

    return mssp_message;
}
#endif // OBJ_LOGIN_MSSP_C
