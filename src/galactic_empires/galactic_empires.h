#pragma once
#include "Location.h"
#include "Fleet.h"
#include "player.h"
#include "world.h"
#include <vector>
#ifdef _WIN32
#include <String>
#else
#include <string>
#endif

#define MAX_PLAYER_COUNT	16
#define MAP_DIMENSIONS_X	20
#define MAP_DIMENSIONS_Y	20

#define DEFAULT_OWNER		0xffff

class Galactic_Empires {

public:
    Galactic_Empires();
    ~Galactic_Empires();

    uint16_t    add_player(std::string player_name);
    void        print_map();
    void        print_stats();
    void        perform_game_tick();
    void        perform_player(uint16_t id);
    void        get_command(uint16_t id);
    void        is_galactic_empire();

    bool        exit_game;
    std::vector<Fleet>		all_fleets;
    std::vector<World>		all_worlds;

private:
    std::string				players[MAX_PLAYER_COUNT];
    uint16_t				num_loaded_players;
    uint64_t				year;

    std::vector<struct player_action>	action_queue;
    uint64_t fleet_stationed(uint64_t world);
};
