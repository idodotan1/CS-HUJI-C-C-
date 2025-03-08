//
// Created by idodo on 11/06/2024.
//
#include "markov_chain.h"
#include "string.h"
void test_add_node_to_frequency_list() {
    // Create nodes
    MarkovNode node1 = { .data = "node1", .frequency_list = NULL, .frequency_list_length = 0 };
    MarkovNode node2 = { .data = "node2", .frequency_list = NULL, .frequency_list_length = 0 };

    // Add node2 to node1's frequency list
    if (add_node_to_frequency_list(&node1, &node2) != EXIT_SUCCESS) {
        printf("Test failed: could not add node2 to node1's frequency list\n");
        return;
    }

    // Check the frequency list
    if (node1.frequency_list_length != 1 || strcmp(node1.frequency_list[0].markov_node->data, "node2") != 0 || node1.frequency_list[0].frequency != 1) {
        printf("Test failed: frequency list incorrect\n");
        return;
    }

    // Add node2 to node1's frequency list again
    if (add_node_to_frequency_list(&node1, &node2) != EXIT_SUCCESS) {
        printf("Test failed: could not add node2 to node1's frequency list a second time\n");
        return;
    }

    // Check the frequency list again
    if (node1.frequency_list_length != 1 || strcmp(node1.frequency_list[0].markov_node->data, "node2") != 0 || node1.frequency_list[0].frequency != 2) {
        printf("Test failed: frequency list incorrect after second addition\n");
        return;
    }

    printf("Test passed: add_node_to_frequency_list\n");
}
void test_free_database() {
    // Allocate and initialize a MarkovChain
    MarkovChain *chain = malloc(sizeof(MarkovChain));
    chain->database = malloc(sizeof(LinkedList));
    chain->database->first = malloc(sizeof(Node));
    chain->database->last = chain->database->first;

    // Create nodes
    MarkovNode *node1 = malloc(sizeof(MarkovNode));
    node1->data = strdup("node1");
    node1->frequency_list = NULL;
    node1->frequency_list_length = 0;
    chain->database->first->data = node1;
    chain->database->first->next = NULL;

    // Free the database
    free_database(&chain);

    // Check if the chain is correctly freed
    if (chain != NULL) {
        printf("Test failed: chain is not NULL after freeing\n");
        return;
    }

    printf("Test passed: free_database\n");
}

void test_get_node_from_database() {
    // Create and initialize a MarkovChain
    MarkovChain *chain = malloc(sizeof(MarkovChain));
    chain->database = malloc(sizeof(LinkedList));
    chain->database->first = NULL;
    chain->database->last = NULL;

    // Add nodes to the database
    Node *node1 = malloc(sizeof(Node));
    node1->data = malloc(sizeof(MarkovNode));
    node1->data->data = strdup("node1");
    node1->data->frequency_list = NULL;
    node1->data->frequency_list_length = 0;
    node1->next = NULL;
    chain->database->first = node1;
    chain->database->last = node1;

    Node *node2 = malloc(sizeof(Node));
    node2->data = malloc(sizeof(MarkovNode));
    node2->data->data = strdup("node2");
    node2->data->frequency_list = NULL;
    node2->data->frequency_list_length = 0;
    node2->next = NULL;
    chain->database->last->next = node2;
    chain->database->last = node2;

    // Test if we can get nodes from the database
    Node *found_node1 = get_node_from_database(chain, "node1");
    if (!found_node1 || strcmp(found_node1->data->data, "node1") != 0) {
        printf("Test failed: get_node_from_database for node1\n");
        return;
    }

    Node *found_node2 = get_node_from_database(chain, "node2");
    if (!found_node2 || strcmp(found_node2->data->data, "node2") != 0) {
        printf("Test failed: get_node_from_database for node2\n");
        return;
    }

    Node *not_found_node = get_node_from_database(chain, "node3");
    if (not_found_node) {
        printf("Test failed: get_node_from_database for node3\n");
        return;
    }

    printf("Test passed: get_node_from_database\n");

    // Free allocated memory
    free(node1->data->data);
    free(node1->data);
    free(node1);
    free(node2->data->data);
    free(node2->data);
    free(node2);
    free(chain->database);
    free(chain);

}
void test_add_to_database() {
    // Create and initialize a MarkovChain
    MarkovChain *chain = malloc(sizeof(MarkovChain));
    chain->database = malloc(sizeof(LinkedList));
    chain->database->first = NULL;
    chain->database->last = NULL;

    // Add nodes to the database
    Node *added_node1 = add_to_database(chain, "node1");
    if (!added_node1 || strcmp(added_node1->data->data, "node1") != 0) {
        printf("Test failed: add_to_database for node1\n");
        return;
    }

    Node *added_node2 = add_to_database(chain, "node2");
    if (!added_node2 || strcmp(added_node2->data->data, "node2") != 0) {
        printf("Test failed: add_to_database for node2\n");
        return;
    }

    // Try adding a node that already exists
    Node *added_node1_again = add_to_database(chain, "node1");
    if (!added_node1_again || strcmp(added_node1_again->data->data, "node1") != 0 || added_node1_again != added_node1) {
        printf("Test failed: add_to_database for node1 again\n");
        return;
    }

    printf("Test passed: add_to_database\n");

    // Free allocated memory
    free_database(&chain);
}
void run_tests() {
    test_add_node_to_frequency_list();
    test_free_database();
    test_get_node_from_database();
    test_add_to_database();
}

