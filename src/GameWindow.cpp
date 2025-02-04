#include "../include/GameWindow.h"
#include "../include/FinishOption.h"
#include "../include/Player.h"
#include "Data.h"
#include "WriteJson.h"
#include <string>
#include <wx/listbox.h>
#include <wx/wx.h>

GameWindow::GameWindow(const std::vector<Player> &added_players,
                       const int &start_score)
    : wxFrame(nullptr, wxID_ANY, "Dart Counter - Game", wxDefaultPosition,
              wxSize(800, 600)),
      players(added_players), initial_score(start_score) {
  if (players.empty()) {

    wxMessageBox("No player added, terminate Dart Counter", "Error",
                 wxOK | wxICON_INFORMATION);
    Close(true);
  }

  if (!players.empty()) {
    for (Player &p : players) {
      p.update_score(initial_score);
    }
  }

  wxPanel *panel = new wxPanel(this, wxID_ANY);
  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);

  // Spielername und Score Sizer
  wxGridSizer *playerGrid = new wxGridSizer(players.size(), 5, 5, 5);

  // Spieler und Scores anzeigen
  for (size_t i = 0; i < players.size(); ++i) {
    // Spielername
    wxStaticText *playerText =
        new wxStaticText(panel, wxID_ANY, players.at(i).get_name(),
                         wxDefaultPosition, wxDefaultSize);
    playerText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                               wxFONTWEIGHT_NORMAL));
    if (i == current_player_index) {
      playerText->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                 wxFONTWEIGHT_BOLD));
      playerText->SetForegroundColour(*wxRED);
    }

    wxStaticText *thrown_darts_text =
        new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    thrown_darts_text->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT,
                                      wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    thrown_darts_texts.push_back(
        thrown_darts_text); // Speichere für spätere Updates

    wxStaticText *AverageText = new wxStaticText(
        panel, wxID_ANY, std::to_string(players.at(i).game_average),
        wxDefaultPosition, wxDefaultSize);
    AverageText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                wxFONTWEIGHT_NORMAL));
    playerTexts.push_back(playerText);   // Speichere für spätere Updates
    AverageTexts.push_back(AverageText); // Speichere für spätere Updates

    // Spieler Score
    wxStaticText *scoreText = new wxStaticText(
        panel, wxID_ANY, std::to_string(players.at(i).get_score()),
        wxDefaultPosition, wxDefaultSize);
    scoreText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                              wxFONTWEIGHT_NORMAL));
    if (i == current_player_index) {
      scoreText->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                wxFONTWEIGHT_BOLD));
    }
    scoreTexts.push_back(scoreText); // Speichere für spätere Updates
    wxStaticText *FinishText = new wxStaticText(
        panel, wxID_ANY,
        FinishOption::get_finish(players.at(current_player_index).get_score()),
        wxDefaultPosition, wxDefaultSize);
    FinishText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                               wxFONTWEIGHT_NORMAL));
    FinishTexts.push_back(FinishText); // Speichere für spätere Updates

    playerGrid->Add(playerText, 0, wxALL, 5);
    playerGrid->Add(thrown_darts_text, 0, wxALL, 5);
    playerGrid->Add(AverageText, 0, wxALL, 5);
    playerGrid->Add(scoreText, 0, wxALL, 5);
    playerGrid->Add(FinishText, 0, wxALL, 5);
  }

  mainSizer->Add(playerGrid, 1, wxALL | wxEXPAND, 10);

  panel->SetSizer(mainSizer);

  // Unten: Eingabebereich
  wxGridSizer *numberPadSizer =
      new wxGridSizer(6, 0, 5, 5); // 6 Zeilen, 4 Spalten

  // Double- und Triple-Buttons
  wxButton *doubleButton = new wxButton(panel, wxID_ANY, "Double",
                                        wxDefaultPosition, wxSize(80, 50));
  wxButton *tripleButton = new wxButton(panel, wxID_ANY, "Triple",
                                        wxDefaultPosition, wxSize(80, 50));
  numberPadSizer->Add(doubleButton, 0, wxALL | wxEXPAND, 5);
  numberPadSizer->Add(tripleButton, 0, wxALL | wxEXPAND, 5);

  // Zahlen von 0 bis 20, 25, 50
  for (int i = 0; i <= 20; ++i) {
    wxButton *numberButton = new wxButton(panel, wxID_ANY, std::to_string(i),
                                          wxDefaultPosition, wxSize(50, 50));
    numberPadSizer->Add(numberButton, 0, wxALL | wxEXPAND, 5);
    Bind(wxEVT_BUTTON, &GameWindow::OnNumberClick, this, numberButton->GetId());
  }

  wxButton *button25 =
      new wxButton(panel, wxID_ANY, "25", wxDefaultPosition, wxSize(50, 50));
  button25->Bind(wxEVT_BUTTON, &GameWindow::OnNumberClick, this);
  wxButton *button50 =
      new wxButton(panel, wxID_ANY, "50", wxDefaultPosition, wxSize(50, 50));
  button50->Bind(wxEVT_BUTTON, &GameWindow::OnNumberClick, this);
  numberPadSizer->Add(button25, 0, wxALL | wxEXPAND, 5);
  numberPadSizer->Add(button50, 0, wxALL | wxEXPAND, 5);

  // Füge das Nummernfeld dem Haupt-Sizer hinzu
  mainSizer->Add(numberPadSizer, 1, wxALL | wxEXPAND, 10);

  panel->SetSizer(mainSizer);

  // Event-Bindings für Double- und Triple-Buttons
  doubleButton->Bind(wxEVT_BUTTON, &GameWindow::OnDoubleClick, this);
  tripleButton->Bind(wxEVT_BUTTON, &GameWindow::OnTripleClick, this);
}

void GameWindow::UpdatePlayerHighlight() {
  for (size_t i = 0; i < players.size(); ++i) {
    if (i == current_player_index) {
      playerTexts[i]->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT,
                                     wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
      playerTexts[i]->SetForegroundColour(*wxRED);
      scoreTexts[i]->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT,
                                    wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    } else {
      playerTexts[i]->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT,
                                     wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
      playerTexts[i]->SetForegroundColour(*wxBLACK);
      scoreTexts[i]->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT,
                                    wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    }
  }
}

void GameWindow::NextPlayer() {

  std::cout << "im in next player: "
            << players.at(current_player_index).thrown_darts_str << std::endl;

  update_thrown_darts_text();
  throw_counter = 0; // Zurücksetzen der Würfe

  current_player_index =
      (current_player_index + 1) % players.size(); // Nächster Spieler
  players.at(current_player_index).thrown_darts_str = "";
  update_thrown_darts_text();
  UpdatePlayerHighlight();
}

void GameWindow::update_thrown_darts_str() {
  players.at(current_player_index).set_thrown_darts_str(throw_counter);
  update_thrown_darts_text();
}

void GameWindow::update_thrown_darts_text() {
  thrown_darts_texts.at(current_player_index)
      ->SetLabel(players.at(current_player_index).thrown_darts_str);
}

void GameWindow::OnNumberClick(wxCommandEvent &event) {
  // Behandle die Nummernklicks
  int player_score = players.at(current_player_index).get_score();

  wxButton *button = dynamic_cast<wxButton *>(event.GetEventObject());

  int value = std::stoi(button->GetLabel().ToStdString());
  int multiplier = current_multiplier; // Standard: 1, Double: 2, Triple: 3
  int hit = value * multiplier;
  if (value == 50) {
    hit = 50;
    multiplier = 2;
  }
  if (value == 25) {
    hit = 25;
    multiplier = 1;
  }

  if (throw_counter == 0) {
    players.at(current_player_index).round.first = hit;
  } else if (throw_counter == 1) {
    players.at(current_player_index).round.second = hit;
  } else if (throw_counter == 2) {
    players.at(current_player_index).round.third = hit;
  }
  Data::combination_checker(players.at(current_player_index));
  Data::data_handler(players.at(current_player_index), current_multiplier,
                     value, throw_counter);
  AverageTexts.at(current_player_index)
      ->SetLabel(std::to_string(players.at(current_player_index).game_average));

  // Anweisung für double finish
  if (multiplier == 2 and hit == player_score) {
    player_score -= hit;
    players.at(current_player_index).update_score(player_score);
    Data::leg_handler(players, current_player_index);
    // players.at(current_player_index).won_leg_counter++;
    scoreTexts.at(current_player_index)
        ->SetLabel(
            std::to_string(players.at(current_player_index).get_score()));
    wxMessageBox(players.at(current_player_index).get_name() +
                     " has won the game!",
                 "Congratulations", wxOK | wxICON_INFORMATION);
    Data::set_game_averages(players);
    WriteJson::UpdatePlayerJson(players);

    // Schließe das Fenster
    Close(true);
  }
  // verhindere negativen score
  if (player_score - hit <= 1) {
    hit = 0;
    players.at(current_player_index).overthrown++;
    players.at(current_player_index).update_score(player_score);
    //    players.at(current_player_index).thrown_darts_str = "";
    //    update_thrown_darts_str();

    NextPlayer();
    player_score = players.at(current_player_index).get_score();
  }
  // verhindere playerScore = 1
  if (player_score == 2 and multiplier != 2) {
    hit = 0;
  }
  // verhindere finish ohne double
  if (multiplier != 2 and hit == player_score) {
    hit = 0;
  }
  player_score -= hit;
  players.at(current_player_index).update_score(player_score);
  current_multiplier = 1; // Zurücksetzen auf Standard
  players.at(current_player_index).set_thrown_darts_str(throw_counter);
  update_thrown_darts_str();
  // thrown_darts_texts.at(current_player_index)
  //   ->SetLabel(players.at(current_player_index).thrown_darts_str);

  throw_counter++;
  Data::set_game_averages(players);
  WriteJson::UpdatePlayerJson(players);
  if (throw_counter == 3) {
    scoreTexts.at(current_player_index)
        ->SetLabel(
            std::to_string(players.at(current_player_index).get_score()));
    FinishTexts.at(current_player_index)
        ->SetLabel(FinishOption::get_finish(
            players.at(current_player_index).get_score()));
    NextPlayer();
    Data::set_game_averages(players);
    WriteJson::UpdatePlayerJson(players);
  }
  scoreTexts.at(current_player_index)
      ->SetLabel(std::to_string(players.at(current_player_index).get_score()));
  FinishTexts.at(current_player_index)
      ->SetLabel(FinishOption::get_finish(
          players.at(current_player_index).get_score()));
}

void GameWindow::OnDoubleClick(wxCommandEvent &event) {
  current_multiplier = 2;
}

void GameWindow::OnTripleClick(wxCommandEvent &event) {
  current_multiplier = 3;
}
