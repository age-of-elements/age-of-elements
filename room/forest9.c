#include <global.h>

inherit LIB_ROOM;

void
create_room()
{
    set_lumens(1);

    set_brief("Deep forest");

    set_description(
	"You are in the deep forest."
      );

    set_exits( ([
	"north": "/room/forest8"
	, "east": "/room/forest10"
	, "west": "/room/forest11"
      ]) );
}
