inherit "/lib/room";

void create_room() {
    set_lumens(1);

    set_brief("Deep forest");

    set_description(
	"You are in the deep forest."
      );

    set_exits( ([
	"west": "/room/forest9"
	, "east": "/room/forest7"
      ]) );
}
