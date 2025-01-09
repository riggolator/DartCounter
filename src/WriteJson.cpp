#include "../include/WriteJson.h"
#include "../include/Player.h"
#include <ctime>
#include <fstream>
#include <json.hpp>
#include <string>
#include <vector>
#include <wx/listbox.h>
#include <wx/wx.h>

#define path "data/"

std::string WriteJson::getCurrentDateTime() {
  auto now = std::time(nullptr);
  std::ostringstream stream;
  stream << std::put_time(std::localtime(&now), "%d/%m/%Y %H:%M:%S");
  return stream.str();
}

// Funktion, um die JSON-Datei zu erstellen
void WriteJson::createPlayerJson(const std::string &playerName) {
  std::string currentDate = getCurrentDateTime();

  // JSON-Daten erstellen
  nlohmann::json playerData;
  playerData["player_name"] = playerName;
  playerData["start_date"] = currentDate;
  playerData["game_averages"] = {{currentDate, 0}};
  playerData["hundred_eighty_counter"] = 0;
  playerData["jackson_counter"] = 0;
  playerData["overthrown"] = 0;
  playerData["won_leg_counter"] = 0;
  playerData["played_legs"] = 0;

  // `field` erstellen
  for (int i = 0; i <= 20; ++i) {
    playerData["field"][std::to_string(i)] = 0;
  }
  playerData["field"]["25"] = 0;

  // `Dfield` erstellen
  for (int i = 1; i <= 20; ++i) {
    playerData["Dfield"]["D" + std::to_string(i)] = 0;
  }
  playerData["Dfield"]["D25"] = 0;

  // `Tfield` erstellen
  for (int i = 1; i <= 20; ++i) {
    playerData["Tfield"]["T" + std::to_string(i)] = 0;
  }

  // JSON-Datei speichern
  std::string fileName = path + playerName + "/" + playerName + ".json";
  std::ofstream outFile(fileName);
  if (outFile.is_open()) {
    outFile << playerData.dump(4); // Schön formatierte JSON-Ausgabe
    outFile.close();
    std::cout << "JSON file created: " << fileName << std::endl;
  } else {
    std::cerr << "Failed to create file: " << fileName << std::endl;
  }
}

void WriteJson::UpdatePlayerJson(std::vector<Player> &players) {
  for (Player &p : players) {
    WriteJson::UpdatePlayerJsonExec(p);
  }
}

void WriteJson::UpdatePlayerJsonExec(Player &p) {
  std::string currentDate = getCurrentDateTime();

  // JSON-Daten erstellen
  nlohmann::json playerData;
  playerData["player_name"] = p.get_name();
  playerData["start_date"] = p.start_date;
  // playerData["game_averages"] = p.game_averages;
  playerData["hundred_eighty_counter"] = p.hundred_eighty_counter;
  playerData["jackson_counter"] = p.jackson_counter;
  playerData["overthrown"] = p.overthrown;
  playerData["won_leg_counter"] = p.won_leg_counter;
  playerData["played_legs"] = p.played_legs;
  std::cout << "WRITING JSON AVERAGE NOW: " << std::endl;
  for (auto const &average : p.game_averages) {
    std::cout << average.first << " | " << average.second << std::endl;
    playerData["game_averages"][average.first] = average.second;
  }

  // `field` erstellen
  for (int i = 0; i <= 20; ++i) {
    playerData["field"][std::to_string(i)] = p.field.at(std::to_string(i));
  }
  playerData["field"]["25"] = p.field.at("25");

  // `Dfield` erstellen
  for (int i = 1; i <= 20; ++i) {
    playerData["Dfield"]["D" + std::to_string(i)] =
        p.field.at("D" + std::to_string((i)));
  }
  playerData["Dfield"]["D25"] = p.field.at("D25");

  // `Tfield` erstellen
  for (int i = 1; i <= 20; ++i) {
    playerData["Tfield"]["T" + std::to_string(i)] =
        p.field.at("T" + std::to_string(i));
  }

  // JSON-Datei speichern
  std::string fileName = path + p.get_name() + "/" + p.get_name() + ".json";
  std::ofstream outFile(fileName);
  if (outFile.is_open()) {
    outFile << playerData.dump(4); // Schön formatierte JSON-Ausgabe
    outFile.close();
    std::cout << "JSON file updated: " << fileName << std::endl;
  } else {
    std::cerr << "Failed to update file: " << fileName << std::endl;
  }
}
