#ifndef DATA_H
#define DATA_H

#include "../include/Player.h"
#include <string>
#include <vector>
#include <wx/wx.h>

namespace Data {

void players_exists(std::vector<Player> &players);
bool check_exist(std::string player_name);
void create_player_file(std::string player_name);
void data_handler(Player &p, int &current_multiplier, int &value,
                  int &throw_counter);
void leg_handler(std::vector<Player> &players, int &current_player_index);
void leg_started(std::vector<Player> &players);
void set_game_averages(std::vector<Player> &players);
void combination_checker(Player &p);
void print_player(Player &p);
void set_game_averages_exec(Player &p);
} // namespace Data

#endif // DATA_H
