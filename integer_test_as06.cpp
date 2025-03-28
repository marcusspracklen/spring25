#include <cassert>
#include <cmath>
#include "cs19_integer.h"
 
using namespace cs19s25;

int main() {
  assert(Integer{"0"} == Integer{"0"});
  assert(Integer{"2"} + Integer{"2"} == Integer{"4"});
  assert(static_cast<std::string>(Integer{"40"} + Integer{"2"}) == "42");
  assert(static_cast<double>(Integer{"40"} + Integer{"2"}) == 42);
  assert(Integer{"129047388211554320500759944742247699075"} +
             Integer{"9696595087158552526553345481980971093"} ==
         Integer{"138743983298712873027313290224228670168"});
  assert(std::abs(static_cast<double>(Integer{"12345678901234567"}) - 1.2345679e+16) < 1e9);
}