#define FILE_PATH_ERROR "Error: incorrect file path"
#define NUM_ARGS_ERROR "Usage: invalid number of arguments"

#define DELIMITERS " \n\t\r"

#include "stdbool.h"
#include "markov_chain.h"
#include "linked_list.h"
#include "stdio.h"
#include "string.h"

#define BASE 10
#define MAX_LINE 1000
#define MAX_TWEET_LENGTH 20
#define MIN_ARGS 4
#define MAX_ARGS 5


/**
 * This function is used to initialize a new markov chain and its functions
 * @return pointer to the new markov chain
 */
MarkovChain *initialize_markov_chain(copy_func_def copy_func,
                                     print_func_def
                                     print_func, comp_func_def comp_func,
                                     is_last_def is_last, free_data_def
                                     free_data) {
    MarkovChain *new_chain = malloc(sizeof(MarkovChain));
    if (!new_chain) {
        return NULL;
    }
    new_chain->database = malloc(sizeof(LinkedList));
    if (!new_chain->database) {
        free(new_chain);
        return NULL;
    }
    new_chain->database->first = NULL;
    new_chain->database->last = NULL;
    new_chain->database->size = 0;
    new_chain->comp_func = comp_func;
    new_chain->is_last = is_last;
    new_chain->print_func = print_func;
    new_chain->copy_func = copy_func;
    new_chain->free_data = free_data;
    return new_chain;
}

/**
 * This function checks if the input entered by the user is valid
 */
int valid_input(int argc, char *argv[]) {
    if (argc < MIN_ARGS || argc > MAX_ARGS) {
        printf(NUM_ARGS_ERROR);
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[3], "r"); // Try to open the file in read mode
    if (!file) {
        printf(FILE_PATH_ERROR);
        return EXIT_FAILURE;
    }
    fclose(file);
    return EXIT_SUCCESS;
}
/**
 * This function checks if the word ends a sentence
 * @param str the word we want to check
 * @return True if does and False otherwise
 */
bool end_of_sentence(const char *str) {
    int len = (int) strlen(str);
    if (len < 2) {
        return false;
    }
    return (str[len - 1] == '.');
}

/**
 * This function adds all the words to the database and frequency lists
 * @param fp the file to read the words from
 * @param words_to_read number of words to read(0 if there is no restriction)
 * @param markov_chain the markov chain to add the words to
 * @return 0 if successful and false otherwise
 */
int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain) {
    char line[MAX_LINE];
    bool word_limit = true;
    int words_counter = 0;
    char *word1 = NULL;
    char *word2 = NULL;
    while (fgets(line, sizeof(line), fp) && word_limit) {
        word1 = NULL;
        word2 = NULL;
        char *token = strtok(line, DELIMITERS);
        while (token != NULL) {
            if (word1 == NULL) {
                word1 = token;

            } else {
                word2 = token;
                Node *word1_node = add_to_database(markov_chain, word1);
                Node *word2_node = add_to_database(markov_chain, word2);
                if (!word1_node || !word2_node) {
                    return EXIT_FAILURE;
                }
                if (!end_of_sentence(word1)) {
                    if (add_node_to_frequency_list(word1_node->data,
                                                   word2_node->data,
                                                   markov_chain)) {
                        return EXIT_FAILURE;
                    }
                }
                word1 = word2;
                word2 = NULL;
            }
            words_counter++;
            if (words_counter == words_to_read) {
                word_limit = false;
                break;
            }
            token = strtok(NULL, DELIMITERS);
        }
    }
    return EXIT_SUCCESS;
}

/**
 * A function used to print a word
 * @param data a word to print
 */
void print_word(void *data) {
    char *word = (char *) data;
    printf(" %s", word);
}

/**
 * A function used to compare 2 words
 * @param first first word
 * @param second second word
 * @return 0 if the words equal, negative value if the first word is before
 * the second word and positive otherwise
 */
int compare_words(void *first, void *second) {
    return strcmp((char *) first, (char *) second);
}

/**
 * A function to copy a word to another word
 * @param data the word to copy
 * @return the copied word
 */
void *copy_word(void *data) {
    char *word = (char *) data;
    char *copy = malloc(strlen(word) + 1);
    if (!copy) {
        return NULL;
    }
    strcpy(copy, word);
    return copy;
}

/**
 * A function that checks if a node is the last one
 * @param data a node
 * @return true if it's the last node and false otherwise
 */
bool is_last_node(void *data) {
    MarkovNode *markov_node = (MarkovNode *) data;
    return markov_node->frequency_list_length == 0;
}

int main(int argc, char *argv[]) {
    if (valid_input(argc, argv)) {
        return EXIT_FAILURE;
    }
    unsigned int seed = (unsigned int) strtol(argv[1], NULL, BASE);
    srand(seed);
    int num_tweets = (int) strtol(argv[2], NULL, BASE);
    char *file_path = argv[3];
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf(FILE_PATH_ERROR);
        return EXIT_FAILURE;
    }
    int num_words = argc == MAX_ARGS ? (int) strtol(argv[4], NULL, BASE) : 0;
    MarkovChain *new_chain = initialize_markov_chain(copy_word, print_word,
                                                     compare_words,
                                                     is_last_node, free);
    if (!new_chain) {
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    if (fill_database(file, num_words, new_chain)) {
        free_markov_chain(&new_chain);
        fclose(file);
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < num_tweets + 1; i++) {
        printf("Tweet %d:", i);
        MarkovNode *first = get_first_random_node(new_chain);
        generate_random_sequence(new_chain, first, MAX_TWEET_LENGTH);
        printf("\n");

    }
    fclose(file);
    free_markov_chain(&new_chain);
    return EXIT_SUCCESS;

}


