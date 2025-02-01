cmake_minimum_required(VERSION 3.10)

# Projektname
project(DartCounter)

# Festlegen des Standards für C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# wxWidgets suchen
find_package(wxWidgets REQUIRED COMPONENTS core base)
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})
include_directories(${Python3_NumPy_INCLUDE_DIRS})
include_directories(third_party)  # Falls du matplotlibcpp.h in third_party/ hast


# Include-Verzeichnisse
include_directories(include)

# Quellcode-Dateien
file(GLOB SOURCES "src/*.cpp")
set(SOURCES ${SOURCES} main.cpp)  # main.cpp explizit hinzufügen

# wxWidgets-Bibliotheken einbinden
include(${wxWidgets_USE_FILE})

# Erstellen der ausführbaren Datei
add_executable(DartCounter ${SOURCES})

#target_link_libraries(DartCounter ${wxWidgets_LIBRARIES})
target_link_libraries(DartCounter ${wxWidgets_LIBRARIES} ${Python3_LIBRARIES})


