// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense
{
private:
    Matrix _weights;
    Matrix _bias;
    activation_func* _ActivationFunction;
public:
    Dense(const Matrix& weights, const Matrix& bias, activation_func*
    ActivationFunction):_weights(weights),_bias(bias),_ActivationFunction
    (ActivationFunction){}
    Matrix get_weights() const {return _weights;}
    Matrix get_bias() const {return _bias;}
    activation_func* get_activation() const {return _ActivationFunction;}
    Matrix operator()(const Matrix& input) const;
};










#endif //DENSE_H