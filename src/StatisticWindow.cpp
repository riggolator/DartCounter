// #include "../include/StatisticWindow.h"
// #include "../include/Player.h"
// #include "../include/ReadJson.h"
// #include <wx/wx.h>
//// #include <wx/chart.h>
// #include "../../matplotlib-cpp/matplotlibcpp.h"
// #include <map>
// #include <vector>

// StatisticWindow::StatisticWindow(std::vector<Player> &players)
//: wxFrame(nullptr, wxID_ANY, "Statistics", wxDefaultPosition,
// wxSize(800, 600)) {

// wxPanel *panel = new wxPanel(this, wxID_ANY);
// wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

//// Titel hinzufügen
// wxStaticText *title =
// new wxStaticText(panel, wxID_ANY, "Player Statistics", wxDefaultPosition,
// wxDefaultSize, wxALIGN_CENTER);
// wxFont titleFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
// wxFONTWEIGHT_BOLD);
// title->SetFont(titleFont);
// mainSizer->Add(title, 0, wxALL | wxALIGN_CENTER, 10);

//// SIGSEV ERRO sPOSSIBLE:
// Player player = players.at(0);

//// Gewinnquote berechnen
// float winRate =
//(player.played_legs > 0)
//? (static_cast<float>(player.won_leg_counter) / player.played_legs) *
// 100
//: 0;
// wxString winRateText = wxString::Format("Win Rate: %.2f%%", winRate);
// wxStaticText *winRateLabel = new wxStaticText(panel, wxID_ANY, winRateText);
// mainSizer->Add(winRateLabel, 0, wxALL | wxALIGN_CENTER, 10);

//// Average-Entwicklung als Liniendiagramm
// wxBoxSizer *chartSizer = new wxBoxSizer(wxHORIZONTAL);
// wxPanel *chartPanel =
// new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
// chartSizer->Add(chartPanel, 1, wxALL | wxEXPAND, 5);

//// Heatmap für Dartboard-Treffer
// wxPanel *heatmapPanel =
// new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(300, 300));
// chartSizer->Add(heatmapPanel, 1, wxALL | wxEXPAND, 5);

// mainSizer->Add(chartSizer, 1, wxALL | wxEXPAND, 10);

//// Schließen-Button
// wxButton *closeButton = new wxButton(panel, wxID_ANY, "Close",
// wxDefaultPosition, wxSize(100, 30));
// mainSizer->Add(closeButton, 0, wxALL | wxALIGN_CENTER, 10);
// closeButton->Bind(wxEVT_BUTTON, &StatisticWindow::OnClose, this);

// panel->SetSizer(mainSizer);
//}

// void StatisticWindow::OnClose(wxCommandEvent &event) { Close(true); }

#include "../include/StatisticWindow.h"
#include "../include/Player.h"
#include "../include/ReadJson.h"
#include "../third_party/matplotlib-cpp/matplotlibcpp.h"
#include <map>
#include <vector>
#include <wx/wx.h>
namespace plt = matplotlibcpp;

StatisticWindow::StatisticWindow(std::vector<Player> const &players)
    : wxFrame(nullptr, wxID_ANY, "Statistics", wxDefaultPosition,
              wxSize(800, 600)),
      players(players) {

  wxPanel *panel = new wxPanel(this, wxID_ANY);
  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *title =
      new wxStaticText(panel, wxID_ANY, "Player Statistics", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTER);
  wxFont titleFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
  title->SetFont(titleFont);
  mainSizer->Add(title, 0, wxALL | wxALIGN_CENTER, 10);

  playerDropdown = new wxChoice(panel, wxID_ANY);
  for (const auto &player : players) {
    playerDropdown->Append(player.get_name());
  }
  playerDropdown->Bind(wxEVT_CHOICE, &StatisticWindow::OnPlayerSelection, this);
  mainSizer->Add(playerDropdown, 0, wxALL | wxALIGN_CENTER, 10);

  winRateLabel = new wxStaticText(panel, wxID_ANY, "Win Rate: ");
  mainSizer->Add(winRateLabel, 0, wxALL | wxALIGN_CENTER, 10);

  chartPanel =
      new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
  heatmapPanel =
      new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(300, 300));

  wxBoxSizer *chartSizer = new wxBoxSizer(wxHORIZONTAL);
  chartSizer->Add(chartPanel, 1, wxALL | wxEXPAND, 5);
  chartSizer->Add(heatmapPanel, 1, wxALL | wxEXPAND, 5);

  mainSizer->Add(chartSizer, 1, wxALL | wxEXPAND, 10);

  wxButton *closeButton = new wxButton(panel, wxID_ANY, "Close",
                                       wxDefaultPosition, wxSize(100, 30));
  mainSizer->Add(closeButton, 0, wxALL | wxALIGN_CENTER, 10);
  closeButton->Bind(wxEVT_BUTTON, &StatisticWindow::OnClose, this);

  panel->SetSizer(mainSizer);
  if (!players.empty()) {
    UpdateStatistics(0);
  }
}

void StatisticWindow::OnClose(wxCommandEvent &event) { Close(true); }

void StatisticWindow::OnPlayerSelection(wxCommandEvent &event) {
  int selectedIndex = playerDropdown->GetSelection();
  if (selectedIndex != wxNOT_FOUND) {
    UpdateStatistics(selectedIndex);
  }
}

void StatisticWindow::UpdateStatistics(int playerIndex) {
  Player &player = players.at(playerIndex);
  float winRate =
      (player.played_legs > 0)
          ? (static_cast<float>(player.won_leg_counter) / player.played_legs) *
                100
          : 0;
  std::cout << "win rate: " << winRate << std::endl;
  winRateLabel->SetLabel(wxString::Format("Win Rate: %.2f%%", winRate));

  DrawAverageChart(player);
  DrawHeatmap(player);
}

void StatisticWindow::DrawAverageChart(const Player &player) {
  plt::figure();
  std::vector<std::string> timestamps;
  std::vector<double> averages;
  for (const auto &[timestamp, avg] : player.game_averages) {
    timestamps.push_back(timestamp);
    averages.push_back(avg);
  }
  plt::plot(timestamps, averages);
  plt::title("Average Score Over Time");
  plt::show();
}

void StatisticWindow::DrawHeatmap(const Player &player) {
  // plt::figure();
  // std::vector<int> x, y, intensity;
  // int counter = 0;
  // for (const auto &[field, count] : player.field_hits) {
  // x.push_back(counter);
  // y.push_back(0);
  // intensity.push_back(count);
  // counter++;
  //}
  // plt::scatter(x, y, 100, intensity);
  // plt::title("Dartboard Heatmap");
  // plt::show();
}
