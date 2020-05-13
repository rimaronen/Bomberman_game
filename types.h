#pragma once
// enum types of levels in load window
enum level_t {level_1_lv, level_2_lv, level_3_lv, level_4_lv, level_5_lv, level_6_lv, no_level_lv };
// enum tyeps of the buttons in the menu 
enum choice_t {start_btn, load_btn, exit_btn, no_btn};
// enum types of blocked items 
enum blocked_t {barrier_blk, player_blk, explosion_blk, no_blk};
// enum types of movments on the board
enum move_t {up_mov, right_mov, down_mov, left_mov, no_mov};
// enum types of the guards in the game
enum guard_type_t {simple_guard_gt, clever_guard_gt};