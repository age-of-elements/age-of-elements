#define F_ROOM_RESET_USED        1
#define F_ROOM_INIT_USED         2

private nosave int flags;
private nosave int lumens;
private nosave mixed brief;
private nosave mixed description;
private nosave mapping exits;
private nosave mapping items;
private nosave mapping commands;

int
get_lumens()
{
    return lumens;
}

void
set_lumens(int arg)
{
    lumens = arg;
}

string
get_brief()
{
    if (closurep(brief)) {
	return funcall(brief);
    }

    return brief;
}

void
set_brief(mixed arg)
{
    if (!stringp(arg) || !closurep(arg)) {
	return;
    }

    brief = arg;
}

string
get_description()
{
    if (closurep(description)) {
	return funcall(description);
    }

    return description;
}

void
set_description(mixed arg)
{
    if (!stringp(arg) || !closurep(arg)) {
	return;
    }

    description = arg;
}

mapping
get_exits()
{
    return exits;
}

void
set_exits(mapping arg)
{
    if (!arg) {
	exits = 0;

	return;
    }

    if (!mappingp(arg) || !sizeof(m_indices(arg))) {
	return;
    }

    exits = deep_copy(arg);
}

mixed
get_exit(string arg)
{
    if (!arg || !exits || !sizeof(exits)) {
	return 0;
    }

    return exits[arg];
}

void
add_exit(string dir, mixed room)
{
    if (!stringp(dir) || (!stringp(room) && !closurep(room))) {
	return;
    }

    if (!exits) {
	exits = ([ dir: room ]);
    } else {
	exits[dir] = room;
    }
}

void
remove_exit(string arg)
{
    if (exits && mappingp(exits)) {
	exits = m_delete(exits, arg);
    }

    if (!sizeof(exits)) {
	exits = 0;
    }
}

mapping
get_items()
{
    mapping ret = copy(items);

    if (ret && mappingp(ret) && sizeof(ret)) {
	string synonym;

	foreach (string key, string val : ret) {
	    if (sscanf(val, "=%s", synonym) == 1 && member(ret, synonym)) {
		ret[key] = ret[synonym];
	    }
	}
    }

    return ret;
}

void
set_items(mapping arg)
{
    if (!arg) {
	items = 0;

	return;
    }

    if (!mappingp(arg) || !sizeof(m_indices(arg))) {
	return;
    }

    items = deep_copy(arg);

    foreach (mixed item : m_indices(arg)) {
	if (pointerp(item) && sizeof(item)) {
	    string synonym;

	    foreach (mixed element : item) {
		if (stringp(element)) {
		    if (!synonym) {
			synonym = element;
			items[element] = arg[item];
		    } else {
			items[element] = sprintf("=%s", synonym);
		    }
		}
	    }

	    m_delete(items, item);
	}
    }
}

mixed
get_item(string arg)
{
    string synonym;

    if (!arg || !items || !sizeof(items)) {
	return 0;
    }

    if (stringp(items[arg])
	&& sscanf(items[arg], "=%s", synonym) == 1
	&& member(items, synonym)) {
	return items[synonym];
    }

    return items[arg];
}

void
add_item(mixed item, mixed desc)
{
    if (!stringp(desc) || !closurep(desc)) {
	return;
    }

    if (!items) {
	items = ([ item: desc ]);
    } else {
	items[item] = desc;
    }

    if (pointerp(item) && sizeof(item)) {
	string synonym;

	foreach (mixed element : item) {
	    if (stringp(element)) {
		if (!synonym) {
		    synonym = element;
		    items[element] = item[element];
		} else {
		    items[element] = sprintf("=%s", synonym);
		}
	    }
	}

	m_delete(items, item);
    }
}

void
remove_item(string arg)
{
    if (items && mappingp(items)) {
	m_delete(items, arg);
    }

    string synonym = sprintf("=%s", arg);

    foreach (string key, mixed val : items) {
	if (stringp(val) && val == synonym) {
	    m_delete(items, key);
	}
    }

    if (!sizeof(items)) {
	items = 0;
    }
}

mapping
query_commands()
{
    return commands;
}

void
set_commands(mapping arg)
{
    if (!arg) {
	commands = 0;
    }

    if (!mappingp(arg) || !sizeof(m_indices(arg))) {
	return;
    }

    commands = deep_copy(arg);
}

mixed
get_command(string arg)
{
    if (!arg || !commands || !sizeof(commands)) {
	return 0;
    }

    return commands[arg];
}

void
add_command(string cmd, mixed func)
{
    if (!stringp(cmd) || (!stringp(func) && !closurep(func))) {
	return;
    }

    if (!mappingp(commands)) {
	commands = ([ cmd: func ]);
    } else {
	commands[cmd] = func;
    }
}

void
remove_command(string arg)
{
    if (commands && mappingp(commands)) {
	commands = m_delete(commands, arg);
    }

    if (!sizeof(commands)) {
	commands = 0;
    }
}

varargs int
move(string dir, string room)
{
    if (!this_player())
    {
	return 0;
    }

    if (!dir) {
	dir = query_verb();
    }

    if (!room && (!exits || !(room = exits[dir]))) {
	return 0;
    }

    this_player()->move_player(dir, room);
    return 1;
}

int
id(string arg)
{
    if (items && arg && items[arg]) {
	return 1;
    }

    return 0;
}

void
create()
{
    if (function_exists("reset_room", this_object())) {
	flags |= F_ROOM_RESET_USED;
    }

    this_object()->create_room();

    if (function_exists("init_room", this_object())) {
	flags |= F_ROOM_INIT_USED;
    }
}

void
reset()
{
    if (flags & F_ROOM_RESET_USED) {
	this_object()->reset_room();
    }

    // reset_room() may call destruct()
    if (!this_object()) {
       return;
    }
}

void
init()
{
    add_action("command_driver", "", 1);

    if (flags & F_ROOM_INIT_USED) {
	this_object()->init_room();
    }

    if (!this_player()) {
	return;
    }


}

void
heart_beat()
{
}

int
search_cmd(string str)
{
    tell_object(this_player()
	, "You search around, but did not find any interesting discoveries.");

    return 1;
}

int
listen_cmd(string str)
{
    tell_object(this_player()
	, "You listen intently, but did not hear any interesting sounds.");

    return 1;
}

int
smell_cmd(string str)
{
    tell_object(this_player()
	, "You sniff vigorously, but did not detect any interesting scents.");

    return 1;
}

int
command_driver(string arg)
{
    string verb;
    mixed func;
    int ret;

    verb = query_verb();

    if (commands && widthof(commands) && (func = commands[verb])) {
	// Convert to a closure if not already done so.
	if (stringp(func)) {
	    func = symbol_function(func, this_object());
	    commands[verb] = func;
	}

	ret = funcall(func, arg, this_player());

	if (ret) {
	    return ret;
	}
    }

    if (exits && (func = exits[verb])) {
	if (closurep(func)) {
	    func = funcall(func, arg, this_player());

	    if (!stringp(func) && !objectp(func)) {
		return func;
	    }
	}

	ret = move(verb, func);

	if (ret) {
	    return ret;
	}
    }

    if (verb == "search") {
	return search_cmd(arg);
    }

    if (verb == "listen" || verb == "hear") {
	return listen_cmd(arg);
    }

    if (verb == "smell") {
	return smell_cmd(arg);
    }

    if (this_player()->is_npc()) {
	func = symbol_function("command_driver", this_player());
	ret = funcall(func, arg, this_player());

	if (ret) {
	    return ret;
	}
    }

    return 0;
}
