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

#define OBJ_LOGIN_MSP_C

static int does_msp = 0;

private void set_msp(int arg);
public nomask int does_msp();
public varargs void msp_output(string sound_or_music, mapping data);
public varargs void msp_test(int test);

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

/*
**    Function: msp_output
**
**     Purpose: Send an MSP message to the client.
**
**  Parameters: string sound_or_music, MSP_SOUND or MSP_MUSIC (required)
**              mapping data, contains keys with value(s):
**              MSP_ID: MSP_FILENAME (required)
**              MSP_ID: MSP_VOLUME (optional, defaults to "50", min "1" to max "100")
**              MSP_ID: MSP_LENGTH (optional, defaults to "1".  "-1" repeats)
**              MSP_ID: MSP_PRIORITY with MSP_SOUND only (optional, defaults to "50", min "1" to max "100")
**              MSP_ID: MSP_CONTINUE with MSP_MUSIC only (optional, defaults to "1" to continue, "0" to restart wav)
**              MSP_ID: MSP_TYPE (optional)
**              MSP_ID: MSP_URL (optional, typically a URL or local file path)
**
**     Returns: void
*/
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
		}
	    }

	    trigger += ")\r\n";

            binary_message(({IAC, SB, TELOPT_MSP}));
            binary_message(to_bytes(trigger, "UTF-8"));
            binary_message(({IAC, SE}));
        }
    }
}

/*
**    Function: msp_test
**
**     Purpose: Test MSP from the ZMud specification found at
**              https://www.zuggsoft.com/zmud/msp.htm.
**
**  Parameters: int arg, number of the test.
**
**     Returns: void
*/
public varargs void msp_test(int test) {
    switch (test) {
	case 0:
	    // !!SOUND(Off U=https://www.ageofelements.org/sounds)
	    // This is how we tell our client where to download these files from.
	    msp_output(MSP_SOUND, ([
		MSP_FILENAME: "Off"
		, MSP_URL: "https:/\/www.ageofelements.org/sounds"
	      ]));
	    break;
	case 1:
	    // !!MUSIC(wind.wav V=25 L=-1 T="weather")
	    // The music of wind continuously plays.
	    msp_output(MSP_MUSIC, ([
		MSP_FILENAME: "wind.wav"
		, MSP_VOLUME: MSP_VOLUME_LOW
		, MSP_LENGTH: MSP_LENGTH_REPEAT
		, MSP_TYPE: "weather"
	      ]));
	    break;
	case 2:
	    // !!SOUND(lightning V=25 L=1 T=weather)
	    // A lightning strike at low volume must be far off.
	    msp_output(MSP_SOUND, ([
		MSP_FILENAME: "lightning"
		, MSP_VOLUME: MSP_VOLUME_LOW
		, MSP_LENGTH: MSP_LENGTH_DEFAULT
		, MSP_TYPE: "weather"
	      ]));
	    break;
	case 3:
	    // !!SOUND(tornado V=50 L=1 T=weather)
	    // A tornado is spinning somewhere in the distance.
	    msp_output(MSP_SOUND, ([
		MSP_FILENAME: "tornado"
		, MSP_VOLUME: MSP_VOLUME_DEFAULT
		, MSP_LENGTH: MSP_LENGTH_DEFAULT
		, MSP_TYPE: "weather"
	      ]));
	    break;
	case 4:
	    // !!SOUND(lightning V=75 L=2 T=weather)
	    // Two back-to-back lightning strikes at high volume!
	    msp_output(MSP_SOUND, ([
		MSP_FILENAME: "lightning"
		, MSP_VOLUME: MSP_VOLUME_HIGH
		, MSP_LENGTH: "2"
		, MSP_TYPE: "weather"
	      ]));
	    break;
	case 5:
	    // !!SOUND(tornado V=75 L=1 T=weather)
	    // High volume tornado!
	    msp_output(MSP_SOUND, ([
		MSP_FILENAME: "tornado"
		, MSP_VOLUME: MSP_VOLUME_HIGH
		, MSP_LENGTH: MSP_LENGTH_DEFAULT
		, MSP_TYPE: "weather"
	      ]));
	    break;
	case 6:
	    // !!SOUND(lightning V=100 L=1 T=weather)
	    // Very loud lightning!
	    msp_output(MSP_SOUND, ([
		MSP_FILENAME: "lightning"
		, MSP_VOLUME: MSP_VOLUME_LOUD
		, MSP_LENGTH: MSP_LENGTH_DEFAULT
		, MSP_TYPE: "weather"
	      ]));
	    break;
	case 7:
	    // !!MUSIC(Off)
	    // This stops the repeating wind sound
	    msp_output(MSP_MUSIC, ([
		MSP_FILENAME: "Off"
	      ]));
	    break;
    }
}
