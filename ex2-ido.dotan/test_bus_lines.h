#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H and
// #endif //EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**
 * This function checks if the lines are sorted by distances in an ascending
 * order
 */
int is_sorted_by_distance (const BusLine *start, const BusLine *end);

/**
 * This function checks if the lines are sorted by duration in an ascending
 * order
 */
int is_sorted_by_duration (const BusLine *start, const BusLine *end);

/**
 * This function checks if the lines are sorted by name in an ascending
 * order(by the settings of strcmp)
 */
int is_sorted_by_name (const BusLine *start, const BusLine *end);

/**
 * This function checks if the original list and the sorted list are in the
 * same length and as well the all the names in the original list appear in
 * the sorted list
 */
int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H and
// #endif //EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
