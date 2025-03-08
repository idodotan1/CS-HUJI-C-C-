//
// Created by idodo on 10/07/2024.
//
#include "Dense.h"

Matrix Dense::operator()(const Matrix& input) const
{
    return (*_ActivationFunction)(_weights*input+_bias);
}