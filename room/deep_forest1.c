inherit "/lib/room";

void create_room() {
    set_lumens(1);

    set_brief("Deep forest");

    set_description(
	"In the deep forest. The wood lights up to the east."
      );

    add_exit("east", "/room/plane12");
}
