#include "markov_chain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */
int get_random_number(int max_number)
{
    return rand() % max_number;
}

Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr)
{
    Node* current = markov_chain->database->first;
    while (current!=NULL)
    {
        if (!strcmp(current->data->data,data_ptr))
        {
            return current;
        }
        current = current->next;
    }
    return current;
}

Node* add_to_database(MarkovChain *markov_chain, char *data_ptr)
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
    char *new_str = malloc(strlen(data_ptr)+1);
    if (!new_str)
    {
        free(new_markov);
        return NULL;
    }
    strcpy(new_str,data_ptr);
    new_markov->data = new_str;
    new_markov->frequency_list = NULL;
    new_markov->frequency_list_length = 0;
    new_markov->total_frequencies = 0;
   if (add(markov_chain->database,new_markov))
   {
       free(new_markov->data);
       free(new_markov);
       return NULL;
   }
    return markov_chain->database->last;
}

int add_node_to_frequency_list(MarkovNode *first_node, MarkovNode *second_node)
{
    int length = first_node->frequency_list_length;
    for (int i = 0; i < length; i++)
    {
        if (!strcmp(first_node->frequency_list[i].markov_node->data,
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

void free_database(MarkovChain ** ptr_chain)
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
            free(current->data->data);
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
        if (current->data->frequency_list_length)
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

void generate_tweet(MarkovNode *first_node, int max_length)
{
    printf("%s ",first_node->data);
    MarkovNode* next = get_next_random_node(first_node);
    int i = 1;
    while (next && i < max_length)
    {
        i++;
        if(next->frequency_list_length && i < max_length)
        {
            printf("%s ", next->data);
            next = get_next_random_node(next);
        }
        else
        {
            printf("%s",next->data);
            break;
        }
    }
}

