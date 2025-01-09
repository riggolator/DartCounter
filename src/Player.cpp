#include "../include/Player.h"
#include <wx/listbox.h>
#include <wx/wx.h>

Player::Player(const std::string added_playerName)
    : player_name(added_playerName){};

void Player::update_score(int &score) { player_score = score; }
int Player::get_score() { return player_score; }
std::string Player::get_name() { return player_name; }

void Player::add_finish(std::string &finish) {
  finish_options.push_back(finish);
}

void Player::reset_round() {
  if (round.first != 99999 and round.second != 99999 and round.third != 99999) {
    round.first = 99999;
    round.second = 99999;
    round.third = 99999;
    round_sum = 0;
  }
}
void Player::add_to_round_sums() {
  if (round.first != 99999 and round.second != 99999 and round.third != 99999) {
    round_sums.push_back(round_sum);
  }
}
