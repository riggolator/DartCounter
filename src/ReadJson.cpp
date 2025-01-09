#include "../include/ReadJson.h"
#include "Player.h"
#include <ctime>
#include <fstream>
#include <json.hpp>
#include <string>
#include <wx/listbox.h>
#include <wx/wx.h>

#define path "data/"

void ReadJson::read_json(Player &player) {
  std::string filePath = path + player.get_name() + "/" + player.get_name() +
                         ".json"; // Pfad zur JSON-Datei
  nlohmann::json jsonData;

  try {
    // JSON-Datei einlesen
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
      throw std::ios_base::failure("Fehler beim Öffnen der Datei");
    }

    inputFile >> jsonData; // JSON-Inhalt in das json-Objekt laden
    inputFile.close();

    if (jsonData.contains(
            "player_name")) { // Prüfen, ob der Schlüssel existiert
      // std::string name = jsonData["player_name"];
      if (jsonData.at("player_name") != player.get_name()) {
        std::cout << "WRONG JSON FILE !!!" << std::endl;
        return;
      }
    }
    if (jsonData.contains("start_date")) { // Prüfen, ob der Schlüssel existiert
      player.start_date = jsonData.at("start_date");
    } else {
      player.start_date = "999999999";
    }
    if (jsonData.contains(
            "hundred_eighty_counter")) { // Prüfen, ob der Schlüssel existiert
      player.hundred_eighty_counter = jsonData.at("hundred_eighty_counter");
    } else {
      player.hundred_eighty_counter = 999999999;
    }
    if (jsonData.contains(
            "jackson_counter")) { // Prüfen, ob der Schlüssel existiert
      player.jackson_counter = jsonData.at("jackson_counter");
    } else {
      player.jackson_counter = 999999999;
    }
    if (jsonData.contains("overthrown")) { // Prüfen, ob der Schlüssel existiert
      player.overthrown = jsonData.at("overthrown");
    } else {
      player.overthrown = 999999999;
    }
    if (jsonData.contains(
            "won_leg_counter")) { // Prüfen, ob der Schlüssel existiert
      player.won_leg_counter = jsonData.at("won_leg_counter");
    } else {
      player.won_leg_counter = 999999999;
    }
    if (jsonData.contains(
            "played_legs")) { // Prüfen, ob der Schlüssel existiert
      player.played_legs = jsonData.at("played_legs");
    } else {
      player.played_legs = 999999999;
    }
    if (jsonData.contains("game_averages")) {
      for (const auto &[key, value] : jsonData["game_averages"].items()) {
        player.game_averages.emplace_back(key, value);
      }
    }
    if (jsonData.contains("field")) {
      for (const auto &[key, value] : jsonData["field"].items()) {

        player.field.at(key) = value;
      }
    }
    if (jsonData.contains("Dfield")) {
      for (const auto &[key, value] : jsonData["Dfield"].items()) {

        player.field.at(key) = value;
      }
    }
    if (jsonData.contains("Tfield")) {
      for (const auto &[key, value] : jsonData["Tfield"].items()) {

        player.field.at(key) = value;
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Fehler: " << e.what() << std::endl;
  }
}
