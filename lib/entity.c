private string name;
private string * aliases;
private mixed brief;
private mixed description;
private nosave int lumens;

string
get_name()
{
    return name;
}

void
set_name(string arg)
{
    name = arg;
}

string *
get_aliases()
{
    return pointerp(aliases) ? copy(aliases) : 0;
}

void
set_aliases(string * arg)
{
    if (!arg) {
	aliases = 0;
	return;
    }

    if (pointerp(arg)) {
	aliases = copy(arg);
    }
}

void
add_alias(string arg)
{
    if (!arg) {
	return;
    }

    if (!pointerp(aliases)) {
	aliases = ({ arg });
	return;
    }

    if (member(aliases, arg) < 0) {
	aliases += ({ arg });
    }
}

void
remove_alias(string arg)
{
    if (arg && aliases && pointerp(aliases)) {
	aliases -= ({ arg });
    }
}

int
has_alias(string arg)
{
    if (!arg || !pointerp(aliases)) {
	return 0;
    }

    return member(aliases, arg) >= 0 ? 1 : 0;
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

int
id(string arg)
{
    if (!arg || !name) {
	return 0;
    }

    if (arg == name) {
	return 1;
    }

    return has_alias(arg);
}

void
create()
{
}

void
reset()
{
}

void
init()
{
}
