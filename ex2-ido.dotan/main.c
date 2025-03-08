#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
#include <ctype.h>
#define MAX_INPUT 60
#define MAX_VAR_LEN 20
#define DURATION_ARG "by_duration"
#define DISTANCE_ARG "by_distance"
#define NAME_ARG "by_name"
#define TEST_ARG "test"
#define BASE 10
#define INVALID_DISTANCE (-1)
#define MIN_DISTANCE 0
#define MAX_DISTANCE 1000
#define MIN_DURATION 10
#define MAX_DURATION 100



/**
 * This function gets a string and returns an integer if is successfully
 * casts it into a positive integer and 0 otherwise
 */
int is_valid_integer(char str[])
{
    long val = strtol(str, NULL, BASE);
    if (val > 0)
    {
        return val;
    }

    return 0;
}
/**
 * This function gets a string and returns an integer if is successfully
 * casts it into a positive integer or 0 and -1 otherwise
 */
int is_valid_distance(char str[])
{
    if (!strcmp(str,"0"))
    {
        return 0;
    }
    float val1 = strtof(str,NULL);
    long val2 = strtol(str, NULL, BASE);

    if (val2 > 0 && (val1 - val2 ==0))
    {
        return val2;
    }

    return INVALID_DISTANCE;
}
/**
 * This function checks if the argument received from the user is valid and
 * returns a number representing the argument or invalid if the input is
 * invalid
 */
int check_arg(char *argv[])
{
    if (!strcmp(argv[1],DURATION_ARG))
    {
        return DURATION;
    }
    if (!strcmp(argv[1],DISTANCE_ARG))
    {
        return DISTANCE;
    }
    if (!strcmp(argv[1],NAME_ARG))
    {
        return NAME;
    }
    if (!strcmp(argv[1],TEST_ARG))
    {
        return TEST;
    }
    return INVALID;
}
/**
 * This function gets input from the user for the number lines and returns
 * the number of lines if the input is valid and 0 otherwise
 */
int get_num_lines()
{
    char buffer[MAX_INPUT];
    if (!fgets(buffer,MAX_INPUT,stdin))
    {
        return 0;
    }
    int num_lines = is_valid_integer(buffer);
    while (!num_lines)
    {
        printf("Error: number of lines must be an int greater than 0.\n");
        printf("Enter number of lines. Then enter\n");
        if (!fgets(buffer,MAX_INPUT,stdin))
        {
            return 0;
        }
        num_lines = is_valid_integer(buffer);
    }
    return num_lines;
}
/**
 * This function gets a string and returns an true if its a valid line name
 * and false otherwise
 */
bool is_valid_name(const char *name) {
    while (*name)
    {
        if (!islower(*name) && !isdigit(*name))
        {
            return false;
        }
        name++;
    }
    return true;
}
/**
 * This function is used to check if the line input from the user is valid
 * and returns 0 upon success and 1 otherwise
 */
 int is_line_valid(char *buffer)
 {

     char name[MAX_VAR_LEN],distance_str[MAX_VAR_LEN],
     duration_str[MAX_VAR_LEN];
     if (sscanf(buffer,"%[^,],%[^,],%s",name,distance_str,duration_str)
     != 3)
     {
         return EXIT_FAILURE;
     }
     if (!is_valid_name(name))
     {
         printf("Error: bus name should contain only digits and small "
                "chars\n");
         return EXIT_FAILURE;
     }
     int distance = is_valid_distance(distance_str);
     int duration = is_valid_integer(duration_str);
     if (MIN_DURATION > duration || MAX_DURATION < duration)
     {
         printf("Error: duration should be an integer between 10 and 1000 "
                "(includes) \n");
         return EXIT_FAILURE;
     }
     if (MIN_DISTANCE > distance || MAX_DISTANCE < distance)
     {
         printf("Error: distance should be an integer between 0 and 1000\n");
         return EXIT_FAILURE;
     }
     return EXIT_SUCCESS;
 }

/**
 * This function gets the lines info from the user and enters them the lines
 * list and returns 0 for success and 1 otherwise
 */
int get_lines(BusLine *bus_lines, int num_lines)
{
    int counter = 0;
    while (counter < num_lines)
    {
        char buffer[MAX_INPUT];
        printf("Enter line info. Then enter\n");
        if (!fgets(buffer,MAX_INPUT,stdin))
        {
            return EXIT_FAILURE;
        }
        if (!is_line_valid(buffer))
        {
            char name[MAX_VAR_LEN],distance_str[MAX_VAR_LEN],
                    duration_str[MAX_VAR_LEN];
            if (sscanf(buffer,"%[^,],%[^,],%s",name,distance_str,duration_str)
            != 3)
            {
                return EXIT_FAILURE;
            }
            int distance = (int) strtol(distance_str,NULL,BASE);
            int duration = (int) strtol(duration_str,NULL,BASE);
            BusLine new_bus_line;
            strcpy(new_bus_line.name,name);
            new_bus_line.distance = distance;
            new_bus_line.duration = duration;
            bus_lines[counter] = new_bus_line;
            counter++;
        }

    }
    return EXIT_SUCCESS;
}
/**
 * This function gets a list of bus lines and length of the list and prints
 * the bus lines in the list
 */
void print_list(BusLine *line_list,int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%s,%d,%d\n",line_list[i].name,line_list[i].distance,
               line_list[i].duration);
    }
}
/**
 * This function gets the original bus line list and a new bus line list and
 * prints if it successfully sorts the bus lines by the parameters defined
 */
void test(BusLine *line_list,BusLine *sorted_line_list,int num_lines)
{
    quick_sort(sorted_line_list,sorted_line_list+(num_lines-1),
                          DISTANCE);
    if (is_sorted_by_distance(sorted_line_list,sorted_line_list+(num_lines-1)))
    {printf("TEST 1 PASSED:  The array is sorted by distance\n");
    } else
    {
        printf("TEST 1 FAILED:  The array is not sorted by distance\n");
    }
    if (is_equal(sorted_line_list,sorted_line_list+(num_lines-1),
                 line_list,line_list+(num_lines-1)))
    {printf("TEST 2 PASSED: The array has the same items after sorting\n");
    }else
    {printf("TEST 2 FAILED: The array does not have the same items after "
            "sorting\n");
    }
    quick_sort(sorted_line_list,sorted_line_list+(num_lines-1),
                          DURATION);
    if (is_sorted_by_duration(sorted_line_list,sorted_line_list+(num_lines-1)))
    {printf("TEST 3 PASSED: The array is sorted by duration\n");
    } else
    {printf("TEST 3 FAILED: The array is not sorted by duration\n");
    }
    if (is_equal(sorted_line_list,sorted_line_list+(num_lines-1),
                 line_list,line_list+(num_lines-1)))
    {printf("TEST 4 PASSED: The array has the same items after sorting\n");
    }else
    {printf("TEST 4 FAILED: The array does not have the same items after "
            "sorting\n");
    }
    bubble_sort(sorted_line_list,sorted_line_list+(num_lines-1));
    if (is_sorted_by_name(sorted_line_list,sorted_line_list+(num_lines-1)))
    {printf("TEST 5 PASSED: The array is sorted by name\n");
    } else
    {printf("TEST 5 FAILED: The array is not sorted by name\n");
    }
    if (is_equal(sorted_line_list,sorted_line_list+(num_lines-1),
                 line_list,line_list+(num_lines-1)))
    {printf("TEST 6 PASSED: The array has the same items after sorting\n");
    }else
    {printf("TEST 6 FAILED: The array does not have the same items after "
            "sorting\n");
    }
}
/**
 * This function is the main function of the program
 */
int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: enter only 1 argument of sort type, by_name, "
               "by_duration, by_name or test.\n");
        return EXIT_FAILURE;
    }
    int sort = check_arg(argv);
    if (sort == INVALID)
    {
        printf("Usage: enter only 1 argument of sort type, by_name, "
               "by_duration, by_name or test.\n");
        return EXIT_FAILURE;}
    printf("Enter number of lines. Then enter\n");
    int num_lines = get_num_lines();
    if(!num_lines)
    {
        return EXIT_FAILURE;}
    BusLine *line_list = malloc(num_lines * sizeof(BusLine));
    if (!line_list)
    {
        return EXIT_FAILURE;}
    if (get_lines(line_list,num_lines))
    {
        free(line_list);
        return EXIT_FAILURE;}
    BusLine *sorted_line_list = malloc(num_lines *sizeof(BusLine));
    if (!sorted_line_list)
    {
        free(line_list);
        return EXIT_FAILURE;}
    memcpy(sorted_line_list,line_list,num_lines*sizeof(BusLine));
    if (sort == DISTANCE || sort == DURATION)
    {
        quick_sort(sorted_line_list,sorted_line_list+(num_lines-1),sort);
        print_list(sorted_line_list,num_lines);
        free(line_list);
        free(sorted_line_list);
        return EXIT_SUCCESS;}
    if (sort == NAME)
    {
        bubble_sort(sorted_line_list,sorted_line_list+(num_lines-1));
        print_list(sorted_line_list,num_lines);
        free(line_list);
        free(sorted_line_list);
        return EXIT_SUCCESS;}
    test(line_list, sorted_line_list, num_lines);
    free(line_list);
    free(sorted_line_list);
    return EXIT_SUCCESS;
}

