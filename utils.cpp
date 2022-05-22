#include <assert.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random.hpp>

#include "utils.h"

using namespace boost::multiprecision;
using namespace std;

int512_t get_int512_from_bytes(const unsigned char* input_bytes, const size_t input_len, const bool bytes_in_big_endian) {

  int512_t result = 0;
  
  assert (input_len <= 64);
  // 64 bytes * 8 = 512bit, can't use sizeof(int512_t) here, int512_t's size could be greater than 64 bytes
  assert (CHAR_BIT == 8); 

  if (bytes_in_big_endian == false) {
    for (int i = input_len; i >= 0; i--) {
      result = (result << 8) + input_bytes[i];
    }
  } else {
    for (int i = 0; i < input_len; i++) {
      result = (result << 8) + input_bytes[i];      
    }
  }
  return result;
}

bool fermat_primality_test(int512_t input, int iterations) {
  boost::random::random_device gen;
  boost::random::uniform_int_distribution<uint512_t> ui(1, (uint512_t)input);
  int512_t x = -1;
  if (input == 1) {
    return false;
  }
  for (int i = 0; i < iterations; i++) {
    x = (int512_t)ui(gen);

    if (powm(x, input - 1, input) != 1) {
      return false;
    }
  }
  return true;
}