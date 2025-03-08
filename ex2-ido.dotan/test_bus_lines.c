#include "test_bus_lines.h"
#include "stdbool.h"
#include "string.h"

int is_sorted_by_distance (const BusLine *start, const BusLine *end)
{
    if (start == end)
    {
        return true;
    }
   const BusLine *current = start;
    while (current != end-1)
    {
        if(current->distance > (current+1)->distance)
        {
            return false;
        }
        current++;
    }
    return true;
}
int is_sorted_by_duration (const BusLine *start, const BusLine *end)
{
    if (start == end)
    {
        return true;
    }
    const BusLine *current = start;
    while (current != end-1)
    {
        if(current->duration > (current+1)->duration)
        {
            return false;
        }
        current++;
    }
    return true;
}
int is_sorted_by_name (const BusLine *start, const BusLine *end)
{
    if (start == end)
    {
        return true;
    }
    const BusLine *current = start;
    while (current != end-1)
    {
        if (strcmp(current->name, (current+1)->name) > 0) {
            return false;
        }
        current++;
    }
    return true;
}
int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original)
{
    const BusLine *current_sorted = start_sorted;
    const BusLine *current_original = start_original;
    while (current_sorted != end_sorted && current_original != end_original)
    {
        const BusLine *name_p = start_sorted;
        bool is_name = false;
        while (name_p != (end_sorted+1))
        {
            if (!strcmp(current_original->name,name_p->name))
            {
                is_name = true;
                break;
            }
            name_p++;
        }
        if (!is_name)
        {
            return false;
        }
        current_sorted++;
        current_original++;
    }
    if (current_sorted == end_sorted && current_original == end_original)
    {
        return true;
    }
    return false;
}

