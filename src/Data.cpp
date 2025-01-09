#include "../include/Data.h"
#include "../include/Player.h"
#include "../include/WriteJson.h"
#include <filesystem>
#include <iostream>
#include <json.hpp>
#include <string>
#include <utility>
#include <vector>
#include <wx/listbox.h>
#include <wx/wx.h>

#define path_name "data/"

void Data::players_exists(std::vector<Player> &players) {
  for (auto p : players) {
    check_exist(p.get_name());
  }
}

bool Data::check_exist(std::string player_name) {

  if (!std::filesystem::exists(path_name)) {
    std::cout << "Directory data/ does not exist " << path_name << std::endl;
    std::filesystem::create_directory(path_name);
    if (std::filesystem::exists(path_name)) {
      std::cout << "Directory data/ is created now " << path_name << std::endl;
    } else {
      std::cout << "could not create data/ " << path_name << std::endl;
    }
  }
  std::filesystem::path path = path_name + player_name;
  if (std::filesystem::exists(path)) {
    std::cout << "Directory exists " << path << std::endl;
    return true;
  }
  std::cout << "Directory NOT exists, create " << path << std::endl;
  return false;
}

void Data::create_player_file(std::string player_name) {
  std::filesystem::create_directory(path_name + player_name);
  WriteJson::createPlayerJson(player_name);
}

void Data::data_handler(Player &p, int &current_multiplier, int &value,
                        int &throw_counter) {
  int hit = value * current_multiplier;
  if (throw_counter == 0) {
    p.round_sum += p.round.first;
    // std::cout << "Hit: " << p.round.first << " | round_sum : " << p.round_sum
    //          << std::endl;
  }
  if (throw_counter == 1) {
    p.round_sum += p.round.second;
    // std::cout << "Hit: " << p.round.second << " | round_sum : " <<
    // p.round_sum
    //         << std::endl;
  }
  if (throw_counter == 2) {
    p.round_sum += p.round.third;
    // std::cout << "Hit: " << p.round.first << " | round_sum : " << p.round_sum
    //         << std::endl;
  }
  p.add_to_round_sums();
  std::cout << "Wurf: " << throw_counter << " | round_sum : " << p.round_sum
            << std::endl;
  if (!p.round_sums.empty()) {
    p.game_average =
        std::accumulate(p.round_sums.begin(), p.round_sums.end(), 0.0) /
        p.round_sums.size();
  } else {
    p.game_average = 0;
  }
  p.reset_round();

  if (current_multiplier == 1) {
    std::string key = std::to_string(value);
    p.field[key]++;
  } else if (current_multiplier == 2) {
    std::string key = "D" + std::to_string(value);
    p.field[key]++;
  }
  if (current_multiplier == 3) {
    std::string key = "T" + std::to_string(value);
    p.field[key]++;
  }
  if (value == 50) {
    std::string key = "D25";
    p.field[key]++;
  }
  if (throw_counter == 2) {
    set_game_averages_exec(p);
  }
}
void Data::leg_started(std::vector<Player> &players) {
  for (Player p : players) {
    p.played_legs++;
  }
}

void Data::set_game_averages_exec(Player &p) {

  p.game_averages.emplace_back(WriteJson::getCurrentDateTime(), p.game_average);
  // p.game_averages.push_back(
  //   {WriteJson::getCurrentDateTime(), p.game_average});
  std::cout << p.get_name() << ":\n " << p.game_average << "\n"
            << p.game_averages.back().second << " | "
            << p.game_averages.back().first << "\n"
            << std::endl;
}
void Data::set_game_averages(std::vector<Player> &players) {
  for (Player &p : players) {
    set_game_averages_exec(p);
  }
  // std::cout << "PRINTING PLAYER AVERAGES\n" << std::endl;
  // for (Player p : players) {
  // for (auto &[key, value] : p.game_averages) {
  // std::cout << p.get_name() << ": " << key << " | " << value << std::endl;
  //}
  //}
}
void Data::combination_checker(Player &p) {
  if (p.round.first == 60 and p.round.second == 60 and p.round.third == 60) {
    p.hundred_eighty_counter++;
  }

  if (p.round.first + p.round.second + p.round.third != 26) {
    return;
  }

  // Check if numbers are exactly 20, 5, and 1 in any order
  std::array<int, 3> numbers = {p.round.first, p.round.second, p.round.third};
  std::sort(numbers.begin(), numbers.end()); // Sort the array
  if (numbers == std::array<int, 3>{1, 5, 20}) {
    p.jackson_counter++;
  }
}

void Data::print_player(Player &p) {
  std::cout << p.get_name() << std::endl;
  std::cout << p.start_date << std::endl;
  std::cout << "averages:\n" << std::endl;
  for (auto const &e : p.game_averages) {
    std::cout << e.first << " | " << e.second << std::endl;
  }

  std::cout << "180s: " << p.hundred_eighty_counter << std::endl;
  std::cout << "jackson: " << p.jackson_counter << std::endl;
  std::cout << "overthrown: " << p.overthrown << std::endl;
  std::cout << "won legs: " << p.won_leg_counter << std::endl;
  std::cout << "played legs: " << p.played_legs << std::endl;
  std::cout << "fields:\n" << std::endl;
  for (auto const &e : p.field) {
    std::cout << e.first << ": " << e.second << std::endl;
  }
}
void Data::leg_handler(std::vector<Player> &players,
                       int &current_player_index) {
  if (players.size() < 2) {
    for (Player p : players) {
      p.played_legs++;
      return;
    }
  }
  for (int i = 0; i < players.size(); i++) {
    if (i == current_player_index) {
      players.at(i).won_leg_counter++;
    } else {
      players.at(i).lost_leg_counter++;
    }
    players.at(i).played_legs++;
  }
}