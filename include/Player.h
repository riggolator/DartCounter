#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <string>
#include <utility>
#include <wx/wx.h>

struct Round {
  int first = 99999, second = 99999, third = 99999;
};

class Player {
public:
  Round round;
  Player(std::string playerName);
  int current_player_index = 0;
  std::string get_finish();

  std::map<std::string, int> field{
      {"0", 0},   {"1", 0},   {"2", 0},   {"3", 0},   {"4", 0},   {"5", 0},
      {"6", 0},   {"7", 0},   {"8", 0},   {"9", 0},   {"10", 0},  {"11", 0},
      {"12", 0},  {"13", 0},  {"14", 0},  {"15", 0},  {"16", 0},  {"17", 0},
      {"18", 0},  {"19", 0},  {"20", 0},  {"25", 0},  {"D1", 0},  {"D2", 0},
      {"D3", 0},  {"D4", 0},  {"D5", 0},  {"D6", 0},  {"D7", 0},  {"D8", 0},
      {"D9", 0},  {"D10", 0}, {"D11", 0}, {"D12", 0}, {"D13", 0}, {"D14", 0},
      {"D15", 0}, {"D16", 0}, {"D17", 0}, {"D18", 0}, {"D19", 0}, {"D20", 0},
      {"D25", 0}, {"T1", 0},  {"T2", 0},  {"T3", 0},  {"T4", 0},  {"T5", 0},
      {"T6", 0},  {"T7", 0},  {"T8", 0},  {"T9", 0},  {"T10", 0}, {"T11", 0},
      {"T12", 0}, {"T13", 0}, {"T14", 0}, {"T15", 0}, {"T16", 0}, {"T17", 0},
      {"T18", 0}, {"T19", 0}, {"T20", 0}};

  // statistics
  float game_average = 0;
  int hundred_eighty_counter = 0;
  int jackson_counter = 0;
  int round_sum = 0;
  int overthrown = 0;
  int won_leg_counter = 0;
  int lost_leg_counter = 0;
  int played_legs = 0;

  std::string start_date;
  std::string thrown_darts_str;

  std::vector<int> round_sums;
  std::vector<std::pair<std::string, float>> game_averages;
  std::vector<std::string> finish_options;

  std::string get_name() const;
  void update_score(int &score);
  int get_score();
  void add_finish(std::string &finish);
  void reset_round();
  void add_to_round_sums();
  void set_thrown_darts_str(int &counter);

private:
  std::string player_name;
  int player_score;
};

#endif // PLAYER_H
