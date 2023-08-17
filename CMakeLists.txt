cmake_minimum_required(VERSION 3.27)

find_package(wxWidgets REQUIRED COMPONENTS net core base)

include(${wxWidgets_USE_FILE})

include(FetchContent)
FetchContent_Declare(sqlite3 URL "https://www.sqlite.org/snapshot/sqlite-snapshot-202205041843.tar.gz")
FetchContent_MakeAvailable(sqlite3)
if (NOT sqlite3_POPULATED)
  FetchContent_Populate(sqlite3)
endif()

add_executable(TirDocApp main.cpp db_manager_sqlite.cpp 
client_manager.cpp weapon_manager.cpp bullet_manager.cpp wx_error_observer.cpp clients_frame.cpp weapon_frame.cpp bullet_frame.cpp "${sqlite3_SOURCE_DIR}/sqlite3.c")

set_target_properties(TirDocApp PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(TirDocApp PUBLIC "${sqlite3_SOURCE_DIR}")

target_link_libraries(TirDocApp ${wxWidgets_LIBRARIES})
