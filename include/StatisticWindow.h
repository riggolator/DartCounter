#ifndef STATISTIC_WINDOW_H
#define STATISTIC_WINDOW_H

#include "../include/Player.h"
#include <map>
#include <string>
#include <vector>
#include <wx/listbox.h>
#include <wx/wx.h>

class StatisticWindow : public wxFrame {
public:
  StatisticWindow(std::vector<Player> const &);
  void OnClose(wxCommandEvent &event);
  void OnPlayerSelection(wxCommandEvent &event);

private:
  std::vector<Player> players;
  wxChoice *playerDropdown;
  wxStaticText *winRateLabel;
  wxPanel *chartPanel;
  wxPanel *heatmapPanel;
  void UpdateStatistics(int playerIndex);
  void DrawAverageChart(const Player &player);
  void DrawHeatmap(const Player &player);
};

#endif // STATISTIC_WINDOW_H

// #ifndef STATISTIC_WINDOW_H
// #define STATISTIC_WINDOW_H

// #include "../include/Player.h"
// #include <string>
// #include <vector>
// #include <wx/listbox.h>
// #include <wx/wx.h>

// class StatisticWindow : public wxFrame {
// public:
// std::vector<Player> players;
// StatisticWindow(std::vector<Player> &);
// void OnClose(wxCommandEvent &event);

// private:
// };

// #endif // STATISTIC_WINDOW_H
