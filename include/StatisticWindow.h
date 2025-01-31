#ifndef STATISTIC_WINDOW_H
#define STATISTIC_WINDOW_H

#include "../include/Player.h"
#include <string>
#include <vector>
#include <wx/listbox.h>
#include <wx/wx.h>

class StatisticWindow : public wxFrame {
public:
  StatisticWindow(std::vector<Player> &);
  void OnClose(wxCommandEvent &event);

private:
};

#endif // STATISTIC_WINDOW_H
