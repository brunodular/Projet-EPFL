#include <cmath> //pour abs
#include "../inc/constantes.h"

bool est_zero(double x,double eps) {
  return (std::abs(x) < eps);
}
