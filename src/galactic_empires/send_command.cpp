#include <galactic_empires.h>

GE_Error_Codes Galactic_Empires::send_command(uint16_t player_id,
                                              uint64_t source_id,
                                              uint64_t target_id,
                                              uint64_t size_num)
{
    /* Validate source world */
    if(source_id >= all_worlds.size()){
        return GE_INVALID_WORLD;
    }

    if(all_worlds[source_id].get_owner() != player_id){
        return GE_INVALID_OWNER;
    }

    /* Validate Target world */
    if(target_id >= all_worlds.size()){
        return GE_INVALID_WORLD;
    }

    /* Validate fleet size */
    if( size_num > all_fleets[fleet_stationed(source_id)].get_size()){
        return GE_INVALID_FLEET_SIZE;
    }

    if(size_num == 0){
        return GE_INVALID_FLEET_SIZE;
    }

    /* Commit the fleet */
    all_fleets[fleet_stationed(source_id)].subtract_ships(size_num);

    /* Make a new fleet */
    Fleet new_fleet(
        all_worlds[source_id].get_position(),
        size_num,
        all_worlds[source_id].get_owner()
    );

    new_fleet.travel_to(all_worlds[target_id].get_position());

    all_fleets.push_back(new_fleet);

    return GE_SUCCESS;
}