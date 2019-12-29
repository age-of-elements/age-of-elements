inherit "/lib/room";

void create_room() {
    set_lumens(1);

    set_brief("Crossroads of Darkhill");

    set_description(
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
	"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
	"ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
	"aliquip ex ea commodo consequat. Duis aute irure dolor in "
	"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
	"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
	"culpa qui officia deserunt mollit anim id est laborum."
      );

    set_exits( ([
	"north": "/realms/darkhill/room/0_1_0"
	, "south": "/realms/darkhill/room/0_-1_0"
	, "east": "/realms/darkhill/room/1_0_0"
	, "west": "/realms/darkhill/room/-1_0_0"
      ]) );

    set_items( ([
	"button": "A blue button."
	, "book": "A small book."
      ]) );

    set_commands( ([
	"push": "push_cmd"
	, "read": "read_cmd"
      ]) );
}

void reset_room() {
}

void init_room() {
}

int push_cmd(string arg) {
    if (!arg || strstr(arg, "button") == -1) {
	return notify_fail("Push what?\n"), 0;
    }

    write("You push the %^BLUE%^blue%^RESET%^ button.\n");

    return 1;
}

int read_cmd(string arg) {
    if (!arg || strstr(arg, "book") == -1) {
	return notify_fail("Read what?\n"), 0;
    }

    write("You open the book, read a page, then close the book.\n");

    return 1;
}
