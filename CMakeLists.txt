cmake_minimum_required(VERSION 3.28)
project(naval_warfare)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(naval_warfare main.cpp
        ships/ship.cpp
        ships/ship.h
        gamefield/gamefield.cpp
        gamefield/gamefield.h
        ships/ship_manager.cpp
        ships/ship_manager.h
        ships/shippart.cpp
        ships/shippart.h
        gamefield/cell.cpp
        gamefield/cell.h
        abilities/ability.h
        abilities/double_damage.cpp
        abilities/double_damage.h
        abilities/scanner.cpp
        abilities/scanner.h
        abilities/bombard.cpp
        abilities/bombard.h
        abilities/ability_manager.cpp
        abilities/ability_manager.h
        exceptions/invalid_ability_usage.cpp
        exceptions/invalid_ability_usage.h
        exceptions/ship_placement_error.cpp
        exceptions/ship_placement_error.h
        exceptions/attack_out_of_bound.cpp
        exceptions/attack_out_of_bound.h
        exceptions/command_input_error.cpp
        exceptions/command_input_error.h
        game/game.cpp
        game/game.h
        game/game_state.cpp
        game/game_state.h
        game/user_input.cpp
        game/user_input.h
        exceptions/load_error.cpp
        exceptions/load_error.h
        game/game_controller.h
        game/game_drawer.cpp
        game/game_drawer.h
        exceptions/out_of_bound.cpp
        exceptions/out_of_bound.h
        game/game_interface.h
        game/simple_game_drawer.h
)