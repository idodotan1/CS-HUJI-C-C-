#include "cipher.h"
#include "tests.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>


#define ARG_ERR "The program receives 1 or 4 arguments only.\n"
#define TEST_ERR "Usage: cipher test\n"
#define COMMAND_ERR "The given command is invalid.\n"
#define SHIFT_ERR "The given shift value is invalid.\n"
#define FILE_ERR "The given file is invalid.\n"
#define BASE 10
#define MAX_ARGS 5
#define MIN_ARGS 2
#define MAX_LINE 1024
/**
 * This function is used to check if the command is valid.
 */
 int valid_command(char command[])
{
     if (!strcmp(command,"cipher"))
     {
         return 1;
     }
    if (!strcmp(command,"decipher"))
    {
        return 1;
    }
    return 0;
}
/**
 * This function is used to check if a string can be converted to an integer
 */
int is_integer(char str[])
{
    if (!strcmp(str,"0"))
    {
        return 1;
    }
    long val = strtol(str, NULL, BASE);
    char converted[BASE];
    sprintf(converted,"%ld",val);

    if (!strcmp(str,converted))
    {
        return 1;
    }

    return 0;
}

/**
 * This function checks the input validity from the CLI
 * Returns a number according to the error of the input
 */
int check_input(int argc, char *argv[])
{
    enum Errors
    {
        NUM_ARGUMENTS_ERROR = 1,
        NOT_TEST_ERROR,
        COMMAND_ERROR,
        SHIFT_VALUE_ERROR,
        FILE_ERROR

    };
    if (argc != MIN_ARGS && argc != MAX_ARGS)
    {
        return NUM_ARGUMENTS_ERROR;
    }
    if (argc == MIN_ARGS)
    {
        if (strcmp(argv[1],"test") != 0)
        {
            return NOT_TEST_ERROR;
        }
        else
        {
            return 0;
        }
    }
    if (!valid_command(argv[1]))
    {
        return COMMAND_ERROR;
    }
    if (!is_integer(argv[2]))
    {
        return SHIFT_VALUE_ERROR;
    }
    FILE *file = fopen(argv[3], "r");
    if (file == NULL)
    {
        return FILE_ERROR;
    }
    return 0;
}

/**
 * This function prints the error message according to the error
 */
int print_error(int error)
{
    enum Errors
    {
        NUM_ARGUMENTS_ERROR = 1,
        NOT_TEST_ERROR,
        COMMAND_ERROR,
        SHIFT_VALUE_ERROR,
        FILE_ERROR
    };
    if (error == NUM_ARGUMENTS_ERROR)
    {
        fprintf(stderr,ARG_ERR);
        return EXIT_FAILURE;
    }
    if (error == NOT_TEST_ERROR)
    {
        fprintf(stderr,TEST_ERR);
        return EXIT_FAILURE;
    }
    if (error == COMMAND_ERROR)
    {
        fprintf(stderr,COMMAND_ERR);
        return EXIT_FAILURE;
    }
    if (error == SHIFT_VALUE_ERROR)
    {
        fprintf(stderr,SHIFT_ERR);
        return EXIT_FAILURE;
    }
    if (error == FILE_ERROR)
    {
        fprintf(stderr,FILE_ERR);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/**
 * This function check if all the tests have passed
 */
int check_tests()
{
    int total = 0;
    total = total + test_cipher_non_cyclic_lower_case_positive_k();
    total = total + test_cipher_cyclic_lower_case_special_char_positive_k();
    total = total +
            test_cipher_non_cyclic_lower_case_special_char_negative_k();
    total = total + test_cipher_cyclic_lower_case_negative_k();
    total = total + test_cipher_cyclic_upper_case_positive_k();
    total = total + test_decipher_non_cyclic_lower_case_positive_k();
    total = total + test_decipher_cyclic_lower_case_special_char_positive_k();
    total = total +
            test_decipher_non_cyclic_lower_case_special_char_negative_k();
    total = total + test_decipher_cyclic_lower_case_negative_k();
    total = total + test_decipher_cyclic_upper_case_positive_k();
    if (total)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int main (int argc, char *argv[])
{
    int valid_input = check_input(argc,argv);
    if (valid_input)
    {
        return print_error(valid_input);
    }
    char *command = argv[1];
    if (!strcmp(command,"test"))
    {
        return check_tests();
    }
    long k_value = strtol(argv[2],NULL,BASE);
    char *input_file_path = argv[3];
    char *output_file_path = argv[4];
    FILE *input_f = fopen(input_file_path,"r");
    FILE *output_f = fopen(output_file_path,"w");
    if (!output_f)
    {
        fclose(input_f);
        fprintf(stderr,FILE_ERR);
        return EXIT_FAILURE;
    }
    if (!strcmp(command,"cipher"))
    {
        char line[MAX_LINE];
        while (fgets (line,MAX_LINE,input_f))
        {
            cipher(line,k_value);
            fprintf(output_f,line);
        }
        fclose(input_f);
        fclose(output_f);
        return EXIT_SUCCESS;
    }
    if (!strcmp(command,"decipher"))
    {
        char line[MAX_LINE];
        while (fgets (line,MAX_LINE,input_f))
        {
            decipher(line,k_value);
            fprintf(output_f,line);
        }
        fclose(input_f);
        fclose(output_f);
        return EXIT_SUCCESS;
    }
}
