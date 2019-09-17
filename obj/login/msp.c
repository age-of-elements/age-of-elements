/*
** /obj/login/msp.c
**
**  Author: Tamarindo
**
**    Date: September 2019
**
** Purpose: This file prepares the Mud Sound Protocol (MSP) message.
**
** References:
**
**      https://www.zuggsoft.com/zmud/msp.htm
**
** See Also:
**
**      /include/msp.h
**      /obj/login/telopt.c
*/

#ifndef __TELNET_H
#include <sys/telnet.h>
#endif // __TELNET_H

#ifndef MSP_H
#include <msp.h>
#endif // MSP_H

static int does_msp = 0;

private void set_msp(int arg);
public nomask int does_msp();
public varargs void msp_output(string sound_or_music, mapping data);

/*
**    Function: set_msp
**
**     Purpose: Set whether the client supports MSP.
**
**  Parameters: int arg, 0 for false, 1 for true.
**
**     Returns: void
*/
private void
set_msp(int arg) {
    does_msp = arg;
}

/*
** Function: does_msp
**
**  Purpose: Query whether the client supports MSP.
**
**  Returns: int, 0 for false, 1 for true.
*/
public nomask int
does_msp() {
    return does_msp;
}

public varargs void
msp_output(string sound_or_music, mapping data) {
    string trigger;

    if (interactive() && does_msp) {
        if (data && mappingp(data) && member(data, MSP_FILENAME) != 0
          && member(({MSP_SOUND, MSP_MUSIC}), sound_or_music) != -1) {
            trigger = sprintf("\n!!%s(%s", sound_or_music, data[MSP_FILENAME]);

            foreach (string parameter : ({MSP_VOLUME, MSP_LENGTH, MSP_PRIORITY, MSP_CONTINUE, MSP_TYPE, MSP_URL})) {
                if (member(data, parameter) != 0) {
                    trigger += sprintf(" %s=%s", parameter, data[parameter]);
                } else if (parameter == MSP_PRIORITY && sound_or_music == MSP_SOUND) {
                    trigger += sprintf(" %s=%s", parameter, MSP_PRIORITY_DEFAULT);
                } else if (parameter == MSP_CONTINUE && sound_or_music == MSP_MUSIC) {
                    trigger += sprintf(" %s=%s", parameter, MSP_CONTINUE_DEFAULT);
                } else {
                    switch (parameter) {
                        case MSP_VOLUME:
                            trigger += sprintf(" %s=%s", parameter, MSP_VOLUME_DEFAULT);
                            break;
                        case MSP_LENGTH:
                            trigger += sprintf(" %s=%s", parameter, MSP_LENGTH_DEFAULT);
                            break;
                        default:
                            // Note: No action taken for empty MSP_URL data per the specification
                            break;
                    }
                }
            }

            trigger += ")\r\n";

            binary_message(({IAC, SB, TELOPT_MSP}));
            binary_message(to_bytes(trigger, "UTF-8"));
            binary_message(({IAC, SE}));
        }
    }
}
