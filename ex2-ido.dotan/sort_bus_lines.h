#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and
// #endif //EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21

/**
 * The struct used for representing bus lines.
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

typedef enum SortType
{
    DISTANCE,
    DURATION,
    NAME,
    TEST,
    INVALID
} SortType;
/** Function to swap two BusLine elements
*/
void exchange(BusLine *first, BusLine *second);
/**
 * This function is used order an array using bubble sort method
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * This function is used to order an array using quicksort method
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * A helper function to quicksort that puts the pivot in the right place
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
// write only between #define EX2_REPO_SORTBUSLINES_H and
// #endif //EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
