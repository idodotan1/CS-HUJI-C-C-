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
//void print_markov_chain(const MarkovChain *markov_chain) {
//    if (markov_chain == NULL || markov_chain->database == NULL) {
//        printf("Markov chain or database is NULL.\n");
//        return;
//    }
//
//    const LinkedList *list = markov_chain->database;
//    const Node *current_node = list->first;
//
//    while (current_node != NULL) {
//        const MarkovNode *markov_node = current_node->data;
//        printf("MarkovNode:");
//        markov_chain->print_func(markov_node->data);
//        printf("\n");
//        printf("Total: %d\n",markov_node->total_frequencies);
//        for (int i = 0; i < markov_node->frequency_list_length; i++)
//        {
//            const MarkovNodeFrequency *frequency = &markov_node->frequency_list[i];
//            printf("  - FrequencyNode:");
//            markov_chain->print_func(frequency->markov_node->data);
//            printf(", Frequency: %d\n", frequency->frequency);
//        }
//
//        current_node = current_node->next;
//    }
//}
//void print_markov_chain(const MarkovChain *markov_chain) {
//    if (markov_chain == NULL || markov_chain->database == NULL) {
//        printf("Markov chain or database is NULL.\n");
//        return;
//    }
//
//    const LinkedList *list = markov_chain->database;
//    const Node *current_node = list->first;
//
//    while (current_node != NULL) {
//        const MarkovNode *markov_node = current_node->data;
//        printf("MarkovNode: %s\n", markov_node->data);
//        printf("Total: %d\n",markov_node->total_frequencies);
//        for (int i = 0; i < markov_node->frequency_list_length; i++)
//        {
//            const MarkovNodeFrequency *frequency = &markov_node->frequency_list[i];
//            printf("  - FrequencyNode: %s, Frequency: %d\n",
//                   frequency->markov_node->data, frequency->frequency);
//        }
//
//        current_node = current_node->next;
//    }
//}
/**
 * This function is used to initialize a new markov chain
 * @return pointer to the new markov chain
 */
MarkovChain *initialize_markov_chain() {
    MarkovChain *new_chain = malloc(sizeof(MarkovChain));
    if (!new_chain)
    {
        return NULL;
    }
    new_chain->database = malloc(sizeof(LinkedList));
    if (!new_chain->database)
    {
        free(new_chain);
        return NULL;
    }
    new_chain->database->first = NULL;
    new_chain->database->last = NULL;
    new_chain->database->size = 0;
    return new_chain;
}
/**
 * This function checks if the input entered by the user is valid
 */
int valid_input(int argc, char *argv[])
{
    if (argc < MIN_ARGS || argc > MAX_ARGS)
    {
        printf(NUM_ARGS_ERROR);
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[3], "r"); // Try to open the file in read mode
    if (!file)
    {
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
bool end_of_sentence(const char *str)
{
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
int fill_database(FILE *fp,int words_to_read,MarkovChain *markov_chain)
{
    char line[MAX_LINE];
    bool word_limit = true;
    int words_counter = 0;
    char *word1 = NULL;
    char *word2 = NULL;
    while (fgets(line, sizeof(line), fp) && word_limit)
    {
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
                                                   word2_node->data)) {
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


int main(int argc, char *argv[])
{
    if (valid_input(argc,argv))
    {
        return EXIT_FAILURE;
    }
    unsigned int seed = (unsigned int)strtol(argv[1],NULL,BASE);
    srand(seed);
    int num_tweets = (int) strtol(argv[2],NULL,BASE);
    char* file_path = argv[3];
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf(FILE_PATH_ERROR);
        return EXIT_FAILURE;
    }
    int num_words = argc == MAX_ARGS ? (int) strtol(argv[4],NULL,BASE) : 0;
    MarkovChain *new_chain = initialize_markov_chain();
    if (!new_chain)
    {
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    if(fill_database(file,num_words,new_chain))
    {
        free_database(&new_chain);
        fclose(file);
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < num_tweets+1; i++)
    {
        printf("Tweet %d: ",i);
        MarkovNode* first = get_first_random_node(new_chain);
        generate_tweet(first,MAX_TWEET_LENGTH);
        printf("\n");

    }
    fclose(file);
    free_database(&new_chain);
    return EXIT_SUCCESS;

}
