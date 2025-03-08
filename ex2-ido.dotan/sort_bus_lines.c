#include "sort_bus_lines.h"


void exchange(BusLine *first, BusLine *second)
{
    BusLine temp = *first;
    *first = *second;
    *second = temp;
}

BusLine *partition(BusLine *start, BusLine *end, SortType sort_type)
{

    int pivot_value = (sort_type == DISTANCE) ? end->distance : end->duration;
    BusLine *left = start;
    BusLine *current = start;

    while (current != end)
    {
        int current_value = (sort_type == DISTANCE) ? current->distance :
                current->duration;

        if (current_value <= pivot_value)
        {
            exchange(left, current);
            left++;
        }
        current++;
    }
    exchange(left, end);
    return left;
}

void quick_sort(BusLine *start, BusLine *end, SortType sort_type)
{
    if (start < end)
    {
        BusLine *pivot = partition(start, end, sort_type);
        if (pivot > start) {
            quick_sort(start, pivot - 1, sort_type);
        }
        if (pivot < end) {
            quick_sort(pivot + 1, end, sort_type);
        }
    }
}
void bubble_sort (BusLine *start, BusLine *end)
{
    long length = end - start + 1;
    BusLine *current = start;
    for (long i=0; i < length-1; i++)
    {
        current = start;
        for (long j = 0; j < length-1-i;j++)
        {
            if ((strcmp((current->name),((current+1)->name))) > 0)
            {
                exchange(current, current + 1);
            }
            current++;
        }
    }

}
