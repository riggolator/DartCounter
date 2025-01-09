#ifndef WRITEJSON_H
#define WRITEJSON_H

#include "../include/Player.h"
#include <wx/wx.h>

namespace WriteJson {
void createPlayerJson(const std::string &playerName);
void UpdatePlayerJson(std::vector<Player> &players);
void UpdatePlayerJsonExec(Player &p);
std::string getCurrentDateTime();
} // namespace WriteJson

#endif // WRITEJSON_H
