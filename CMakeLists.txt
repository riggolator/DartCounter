cmake_minimum_required(VERSION 3.10)

# Projektname
project(DartCounter)

# Festlegen des Standards für C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# wxWidgets suchen
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include-Verzeichnisse
include_directories(include)

# Quellcode-Dateien
file(GLOB SOURCES "src/*.cpp")
set(SOURCES ${SOURCES} main.cpp)  # main.cpp explizit hinzufügen

# wxWidgets-Bibliotheken einbinden
include(${wxWidgets_USE_FILE})

# Erstellen der ausführbaren Datei
add_executable(DartCounter ${SOURCES})

target_link_libraries(DartCounter ${wxWidgets_LIBRARIES})

