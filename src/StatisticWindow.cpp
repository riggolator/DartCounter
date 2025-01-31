#include "../include/StatisticWindow.h"
#include "../include/Player.h"
#include "../include/ReadJson.h"
#include <wx/wx.h>
// #include <wx/chart.h>
// #include "../../matplotlib-cpp/matplotlibcpp.h"
#include <map>
#include <vector>

StatisticWindow::StatisticWindow(std::vector<Player> &players)
    : wxFrame(nullptr, wxID_ANY, "Statistics", wxDefaultPosition,
              wxSize(800, 600)) {

  wxPanel *panel = new wxPanel(this, wxID_ANY);
  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

  // Titel hinzufügen
  wxStaticText *title =
      new wxStaticText(panel, wxID_ANY, "Player Statistics", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTER);
  wxFont titleFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
  title->SetFont(titleFont);
  mainSizer->Add(title, 0, wxALL | wxALIGN_CENTER, 10);

  // SIGSEV ERRO POSSIBLE:
  Player player = players.at(0);

  // Gewinnquote berechnen
  float winRate =
      (player.played_legs > 0)
          ? (static_cast<float>(player.won_leg_counter) / player.played_legs) *
                100
          : 0;
  wxString winRateText = wxString::Format("Win Rate: %.2f%%", winRate);
  wxStaticText *winRateLabel = new wxStaticText(panel, wxID_ANY, winRateText);
  mainSizer->Add(winRateLabel, 0, wxALL | wxALIGN_CENTER, 10);

  // Average-Entwicklung als Liniendiagramm
  wxBoxSizer *chartSizer = new wxBoxSizer(wxHORIZONTAL);
  wxPanel *chartPanel =
      new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
  chartSizer->Add(chartPanel, 1, wxALL | wxEXPAND, 5);

  // Heatmap für Dartboard-Treffer
  wxPanel *heatmapPanel =
      new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(300, 300));
  chartSizer->Add(heatmapPanel, 1, wxALL | wxEXPAND, 5);

  mainSizer->Add(chartSizer, 1, wxALL | wxEXPAND, 10);

  // Schließen-Button
  wxButton *closeButton = new wxButton(panel, wxID_ANY, "Close",
                                       wxDefaultPosition, wxSize(100, 30));
  mainSizer->Add(closeButton, 0, wxALL | wxALIGN_CENTER, 10);
  closeButton->Bind(wxEVT_BUTTON, &StatisticWindow::OnClose, this);

  panel->SetSizer(mainSizer);
}

void StatisticWindow::OnClose(wxCommandEvent &event) { Close(true); }
