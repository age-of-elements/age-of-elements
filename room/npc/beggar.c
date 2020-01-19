inherit "/obj/monster";

void create_monster() {
    set_name("beggar");
    set_short("Beggar");
    set_long("A poor, filthly looking beggar.");
    set_level(3);
    set_al(200);
    set_race("human");
    set_hp(30);
    load_chat(1, ({ "Beggar says: Please, give money to a poor beggar!\n"
	, "Beggar says: Why can't I find any money?\n"
	, "Beggar says: Two coins please!\n"
      }) );
    load_a_chat(20, ({ "Beggar says: Why do you do this to me?\n",
	"Beggar says: Ouch! Please have mercy on a poor beggar!\n"
      }) );
    set_match(this_object()
	, ({ "give_beggar" // action
	  })
	, ({ "gives" // type
	  })
	, ({ 0 // match
	  })
      );
}

void give_beggar(string str)
{
    string who;
    int money;

    if (sscanf(str, "%s gives you %d gold coins.", who, money) != 2) {
	return;
    }

    say("Beggar says: Thank you.\n");

//    if (query_money() >= 12
//	&& object_name(environment(this_object())) == "room/yard.c") {
	command("east");
	command("buy beer");
	command("drink beer");
	command("west");
//    }
}
