inherit "/lib/room";

void create_room() {
    set_lumens(1);

    set_brief("East road");

    set_description(
	"East road runs north-south."
      );

    set_exits( ([
	"north": "/room/eastroad3"
	, "south": "/room/eastroad1"
      ]) );
}
