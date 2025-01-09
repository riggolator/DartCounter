#include "../include/StartWindow.h"
#include "../include/Data.h"
#include "../include/GameWindow.h"
#include "../include/Player.h"
#include "../include/ReadJson.h"
#include <string>

void StartWindow::add_player(std::string player_name) {
  Player p(player_name);
  players.push_back(p);
}
std::vector<Player> StartWindow::get_players() { return players; }

StartWindow::StartWindow()
    : wxFrame(nullptr, wxID_ANY, "Dart Counter", wxDefaultPosition,
              wxSize(600, 400)) {
  wxPanel *panel = new wxPanel(this, wxID_ANY);
  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
  // Titel hinzufügen
  wxStaticText *title =
      new wxStaticText(panel, wxID_ANY, "Dart Counter", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTER);
  wxFont titleFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
  title->SetFont(titleFont);
  mainSizer->Add(title, 0, wxALL | wxALIGN_CENTER, 10);

  // Horizontale Aufteilung des Fensters
  wxBoxSizer *horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
  // Linke Seite: Eingabefeld und Liste
  wxBoxSizer *leftSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *inputSizer = new wxBoxSizer(wxHORIZONTAL);
  playerNameInput = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,
                                   wxDefaultPosition, wxSize(200, 30));
  wxButton *addButton =
      new wxButton(panel, wxID_ANY, "Add", wxDefaultPosition, wxSize(100, 30));
  inputSizer->Add(playerNameInput, 1, wxALL | wxEXPAND, 5);
  inputSizer->Add(addButton, 0, wxALL, 5);
  leftSizer->Add(inputSizer, 0, wxALL | wxEXPAND, 5);

  wxButton *NewPlayerButton = new wxButton(panel, wxID_ANY, "New Player",
                                           wxDefaultPosition, wxSize(100, 30));
  inputSizer->Add(NewPlayerButton, 0, wxALL, 5);

  playerListBox =
      new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
  leftSizer->Add(playerListBox, 1, wxALL | wxEXPAND, 5);
  horizontalSizer->Add(leftSizer, 1, wxALL | wxEXPAND, 5);

  // Rechte Seite: Start- und Statistics-Buttons
  wxBoxSizer *rightSizer = new wxBoxSizer(wxVERTICAL);

  wxButton *start_button_301 = new wxButton(panel, wxID_ANY, "Start 301",
                                            wxDefaultPosition, wxSize(150, 50));
  wxButton *start_button_501 = new wxButton(panel, wxID_ANY, "Start 501",
                                            wxDefaultPosition, wxSize(150, 50));
  wxButton *start_button_701 = new wxButton(panel, wxID_ANY, "Start 701",
                                            wxDefaultPosition, wxSize(150, 50));
  wxButton *statsButton = new wxButton(panel, wxID_ANY, "Statistics",
                                       wxDefaultPosition, wxSize(150, 50));
  rightSizer->Add(start_button_301, 1, wxALL | wxALIGN_CENTER, 10);
  rightSizer->Add(start_button_501, 1, wxALL | wxALIGN_CENTER, 10);
  rightSizer->Add(start_button_701, 1, wxALL | wxALIGN_CENTER, 10);
  rightSizer->Add(statsButton, 1, wxALL | wxALIGN_CENTER, 10);

  horizontalSizer->Add(rightSizer, 0, wxALL | wxEXPAND, 5);

  mainSizer->Add(horizontalSizer, 1, wxALL | wxEXPAND, 10);

  panel->SetSizer(mainSizer);

  // Event-Bindings
  addButton->Bind(wxEVT_BUTTON, &StartWindow::OnAddPlayer, this);
  NewPlayerButton->Bind(wxEVT_BUTTON, &StartWindow::OnNewPlayer, this);
  start_button_301->Bind(wxEVT_BUTTON, &StartWindow::OnStartGame_301, this);
  start_button_501->Bind(wxEVT_BUTTON, &StartWindow::OnStartGame_501, this);
  start_button_701->Bind(wxEVT_BUTTON, &StartWindow::OnStartGame_701, this);
  statsButton->Bind(wxEVT_BUTTON, &StartWindow::OnViewStatistics, this);
}

void StartWindow::OnAddPlayer(wxCommandEvent &event) {
  wxString player_name = playerNameInput->GetValue();
  if (!player_name.IsEmpty()) {
    if (Data::check_exist(player_name.ToStdString())) {
      Player p(player_name.ToStdString());
      ReadJson::read_json(p);
      Data::print_player(p);
      players.push_back(p);
      playerListBox->Append(player_name);
      playerNameInput->Clear();
    } else {
      StartWindow::OnShowDialog(player_name.ToStdString());
    }
  }
}

void StartWindow::OnNewPlayer(wxCommandEvent &event) {
  wxString player_name = playerNameInput->GetValue();
  if (!player_name.IsEmpty()) {
    if (Data::check_exist(player_name.ToStdString())) {

      wxMessageBox("Account already exists, choose another Name.", "Error",
                   wxOK | wxICON_WARNING);

      playerNameInput->Clear();
    } else {

      Data::create_player_file(player_name.ToStdString());
      if (Data::check_exist(player_name.ToStdString())) {
        Player p(player_name.ToStdString());
        players.push_back(p);
        playerListBox->Append(player_name);
      } else {
        wxMessageBox("Creating " + player_name + " failed!", "Error",
                     wxOK | wxICON_WARNING);
      }
      playerNameInput->Clear();
    }
  }
}

void StartWindow::OnShowDialog(std::string player_name) {
  wxMessageDialog dialog(this, "Player does not exist. Create Player?",
                         "Player Check", wxYES_NO | wxICON_QUESTION);

  if (dialog.ShowModal() == wxID_YES) {
    Data::create_player_file(player_name);
    if (Data::check_exist(player_name)) {
      Player p(player_name);
      players.push_back(p);
      playerListBox->Append(player_name);
    } else {
      wxMessageBox("Creating " + player_name + " failed!", "Error",
                   wxOK | wxICON_WARNING);
    }
    playerNameInput->Clear();

  } else {
    wxMessageBox("Player will not be created.", "Info", wxOK | wxICON_WARNING);
    playerNameInput->Clear();
  }
}

void StartWindow::OnStartGame_301(wxCommandEvent &event) {
  if (players.empty()) {
    wxMessageBox("Please add at least one player to start the game.", "Warning",
                 wxOK | wxICON_WARNING);
    return;
  }
  GameWindow *game_window_301 = new GameWindow(get_players(), 301);
  game_window_301->Show(true);
}
void StartWindow::OnStartGame_501(wxCommandEvent &event) {
  if (players.empty()) {
    wxMessageBox("Please add at least one player to start the game.", "Warning",
                 wxOK | wxICON_WARNING);
    return;
  }
  GameWindow *game_window_501 = new GameWindow(get_players(), 501);
  game_window_501->Show(true);
}
void StartWindow::OnStartGame_701(wxCommandEvent &event) {
  if (players.empty()) {
    wxMessageBox("Please add at least one player to start the game.", "Warning",
                 wxOK | wxICON_WARNING);
    return;
  }
  GameWindow *game_window_701 = new GameWindow(get_players(), 701);
  game_window_701->Show(true);

  // wxMessageBox("Starting game with " + std::to_string(players.size()) +
  //" players.",
  //"Info", wxOK | wxICON_INFORMATION);
}

void StartWindow::OnViewStatistics(wxCommandEvent &event) {
  wxMessageBox("Statistics feature is not implemented yet.", "Info",
               wxOK | wxICON_INFORMATION);
}
