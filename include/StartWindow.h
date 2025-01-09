#ifndef START_WINDOW_H
#define START_WINDOW_H

#include "../include/Player.h"
#include <string>
#include <vector>
#include <wx/listbox.h>
#include <wx/wx.h>

class StartWindow : public wxFrame {
public:
  StartWindow();
  void add_player(std::string player_name);
  std::vector<Player> get_players();

private:
  std::vector<Player> players;
  wxListBox *playerListBox;
  wxTextCtrl *playerNameInput;

  void OnAddPlayer(wxCommandEvent &event);
  void OnNewPlayer(wxCommandEvent &event);
  void OnStartGame_301(wxCommandEvent &event);
  void OnStartGame_501(wxCommandEvent &event);
  void OnStartGame_701(wxCommandEvent &event);
  void OnViewStatistics(wxCommandEvent &event);
  void OnShowDialog(std::string player_name);
};

#endif // START_WINDOW_H
