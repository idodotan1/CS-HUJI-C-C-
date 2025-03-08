//
// Created by idodo on 10/07/2024.
//
#define INPUT_ROWS 748
#define NUM_LAYERS 4
#define OUTPUT_VECTOR 10
#include "MlpNetwork.h"
MlpNetwork::MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE])
        :_layers{
        Dense(weights[0], biases[0],
              activation::relu),
        Dense(weights[1], biases[1],
              activation::relu),
        Dense(weights[2], biases[2],
              activation::relu),
        Dense(weights[3], biases[3],
              activation::softmax)
}
{}


digit MlpNetwork :: operator()(const Matrix& input) const
{
    Matrix vector = input;
    for (int i = 0; i < NUM_LAYERS; i++)
    {
        vector = _layers[i](vector);
    }
    float max_prob = vector[0];
    unsigned int max_index = 0;
    for (int i = 1; i < OUTPUT_VECTOR; i++)
    {
        if (vector[i] > max_prob)
        {
            max_prob = vector[i];
            max_index = i;
        }
    }
    digit result = {max_index,max_prob};
    return result;
}
