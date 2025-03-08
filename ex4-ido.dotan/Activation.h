// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
typedef Matrix activation_func(const Matrix&);
namespace activation
{
   activation_func relu;
   activation_func softmax;
}









#endif //ACTIVATION_H