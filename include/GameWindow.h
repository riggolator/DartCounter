// #ifndef GAMEWINDOW_H
// #define GAMEWINDOW_H

//// #include <vector>

// #include <string>
// #include <vector>
// #include <wx/listbox.h>
// #include <wx/wx.h>

// class GameWindow : public wxFrame {
// public:
// GameWindow(int modi, std::vector<std::string> players);
// std::vector<std::string> get_players();

// private:
// int modi;
// wxListBox *playerListBox;
// wxTextCtrl *playerNameInput;
// std::vector<std::string> players;

// void OnAddPlayer(wxCommandEvent &event);
// void OnStartGame(wxCommandEvent &event);
// void OnViewStatistics(wxCommandEvent &event);
//};

// class DartGame {
// public:
// std::vector<std::string> players;
//};

// #endif // GAMEWINDOW_H
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "../include/Player.h"
#include <string>
#include <vector>
#include <wx/wx.h>

class GameWindow : public wxFrame {
public:
  GameWindow(const std::vector<Player> &players, const int &start_score);
  int player_id = 0;
  int throw_counter = 0;
  int current_player_index = 0;
  int initial_score;

private:
  // std::vector<std::string> player_names;
  std::vector<Player> players;
  int current_multiplier = 1; // Standardwert: Einfacher Wurf
  wxStaticText *scoreText;
  wxStaticText *player_name_text;
  wxStaticText *thrown_darts_text;
  wxStaticText *AverageText;
  wxStaticText *FinishText;
  std::vector<wxStaticText *> playerTexts;
  std::vector<wxStaticText *> thrown_darts_texts;
  std::vector<wxStaticText *> AverageTexts;
  std::vector<wxStaticText *> scoreTexts;
  std::vector<wxStaticText *> FinishTexts;

  void OnNumberClick(wxCommandEvent &event);
  void OnDoubleClick(wxCommandEvent &event);
  void OnTripleClick(wxCommandEvent &event);
  void NextPlayer();
  void UpdatePlayerHighlight();
  void update_thrown_darts_str();
  void update_thrown_darts_text();
};

#endif // GAMEWINDOW_H
