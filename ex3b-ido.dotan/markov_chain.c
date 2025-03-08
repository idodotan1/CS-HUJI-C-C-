#include "markov_chain.h"

/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */
int get_random_number(int max_number)
{
    return rand() % max_number;
}

#include "markov_chain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */

Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr)
{
    Node* current = markov_chain->database->first;
    while (current!=NULL)
    {
        if (!markov_chain->comp_func(current->data->data,data_ptr))
        {
            return current;
        }
        current = current->next;
    }
    return current;
}

Node* add_to_database(MarkovChain *markov_chain, void *data_ptr)
{
    Node* in_chain = get_node_from_database(markov_chain,data_ptr);
    if (in_chain)
    {
        return in_chain;
    }
    MarkovNode *new_markov = malloc(sizeof(MarkovNode));
    if (!new_markov)
    {
        return NULL;
    }
    void *new_data = markov_chain->copy_func(data_ptr);
    if (!new_data)
    {
        free(new_markov);
        return NULL;
    }
    new_markov->data = new_data;
    new_markov->frequency_list = NULL;
    new_markov->frequency_list_length = 0;
    new_markov->total_frequencies = 0;
    if (add(markov_chain->database,new_markov))
    {
        markov_chain->free_data(new_data);
        markov_chain->free_data(new_markov->data);
        free(new_markov);
        return NULL;
    }
    return markov_chain->database->last;
}

int add_node_to_frequency_list(MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain)
{
    int length = first_node->frequency_list_length;
    for (int i = 0; i < length; i++)
    {
        if (!markov_chain->comp_func(first_node->frequency_list[i]
        .markov_node->data,
                    second_node->data))
        {
            first_node->frequency_list[i].frequency++;
            first_node->total_frequencies++;
            return EXIT_SUCCESS;
        }
    }
    MarkovNodeFrequency *temp = realloc(first_node->frequency_list,
                                        (length+1)*sizeof
                                                (MarkovNodeFrequency));
    if (!temp) {
        return EXIT_FAILURE;
    }
    first_node->frequency_list = temp;
    MarkovNodeFrequency new_markov_node_frequency = {second_node,1};
    first_node->frequency_list[length] = new_markov_node_frequency;
    first_node->frequency_list_length++;
    first_node->total_frequencies++;
    return EXIT_SUCCESS;
}

void free_markov_chain(MarkovChain ** ptr_chain)
{
    if (ptr_chain == NULL || *ptr_chain == NULL)
    {
        return;
    }
    MarkovChain *chain = *ptr_chain;
    Node *current = chain->database->first;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        if (current->data != NULL) {
            if (current->data->frequency_list != NULL)
            {
                free(current->data->frequency_list);
            }
            chain->free_data(current->data->data);
            free(current->data);
        }
        free(current);
        current = next;
    }
    free(chain->database);
    free(chain);
    *ptr_chain = NULL;

}

MarkovNode* get_first_random_node(MarkovChain *markov_chain)
{
    int rand_num;
    int chain_len = markov_chain->database->size;
    if (!chain_len)
    {
        return NULL;
    }
    while(true)
    {
        rand_num = get_random_number(chain_len);
        Node *current = markov_chain->database->first;
        for (int i = 0; i < rand_num; i++)
        {
            current = current->next;
        }
        if (!markov_chain->is_last(current->data))
        {
            return current->data;
        }
    }
}

MarkovNode* get_next_random_node(MarkovNode *cur_markov_node)
{
    if (!cur_markov_node->frequency_list_length)
    {
        return NULL;
    }
    int total_frequencies = cur_markov_node->total_frequencies;
    int rand_num = get_random_number(total_frequencies);
    int current_node = 0;
    int current_frequencies = cur_markov_node->frequency_list[0].frequency;
    for (int i = 0; i <= rand_num; i++)
    {
        if (i >= current_frequencies)
        {
            current_node++;
            current_frequencies +=
                    cur_markov_node->frequency_list[current_node].frequency;
        }
    }
    return cur_markov_node->frequency_list[current_node].markov_node;
}

void generate_random_sequence(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
    markov_chain->print_func(first_node->data);
    MarkovNode* next = get_next_random_node(first_node);
    int i = 1;
    while (next && i < max_length)
    {
        i++;
        markov_chain->print_func(next->data);
        next = get_next_random_node(next);
    }
}

