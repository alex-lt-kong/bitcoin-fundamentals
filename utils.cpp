#include <arpa/inet.h>
#include <assert.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random.hpp>

#include "utils.h"

using namespace boost::multiprecision;
using namespace std;

int512_t get_int512_from_bytes(
  const unsigned char* input_bytes, const size_t input_len, const bool bytes_in_big_endian
) {

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

void get_bytes_from_int256(const int256_t input_int, const bool bytes_in_big_endian, unsigned char* output_bytes) {

  const size_t INT256_SIZE = 32;
  memcpy(output_bytes, &input_int, INT256_SIZE);
  // htonl(47) == 47 means the CPU is big endian, otherwise little endian
  if ((htonl(47) == 47) != bytes_in_big_endian) {
    // That is, the CPU's endianness is different from the desired endianness
    reverse(output_bytes, output_bytes + INT256_SIZE);      
  }
}

bool fermat_primality_test(const int512_t input, const int iterations) {  
  if (input <= 1) {
    return false;
  }

  boost::random::random_device gen;
  boost::random::uniform_int_distribution<uint512_t> ui(1, (uint512_t)(input - 1));
  int512_t x = -1;
  for (int i = 0; i < iterations; i++) {
    x = (int512_t)ui(gen);

    if (powm(x, input - 1, input) != 1) {
      return false;
    }
  }
  return true;
}

char* encode_bytes_to_base58_string(
  const unsigned char* input_bytes, const size_t input_len, const bool bytes_in_big_endian, size_t* output_len
) {
  *output_len = ceil(input_len * 1.36565823);
  int zero_count = 0;
  while (zero_count < input_len && input_bytes[zero_count] == 0)
		++zero_count; // This is not strictly needed in the current implementation, but let's keep it anyway...
	/*
	 * How do we get the size in advance? We can consider it this way--In base58 encoding, we use 58 characters to encode
	 * bytes (or bits), how many bits can be represented by one character? It is log(2)58 ≈ 5.8579 bits.
	 * Is it possible for base58 character to present 6 bits? No, 2^6 = 64, that is to say, characters will be exhausted
	 * before 0b11 1111 can be encoded.
	 * Since 1 byte = 8 bits, there are (input_len * 8) bits to be represented. Therefore, we need:
	 * (input_len * 8) / log(2)58 = (input_len * log(2)256) / log(2)58 = input_len * log(58)256 ≈ input_len * 1.36565823
	 * Then we round it up.
	 */
  int512_t num = get_int512_from_bytes(input_bytes, input_len, bytes_in_big_endian);
	char* buf = (char*)calloc(*output_len, 1);
  int idx = *output_len - 1;
  static const char b58_table[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
  while (num > 0) {
    buf[idx--] = b58_table[(char)(num % 58)];
    num /= 58;    
  }

  if (zero_count > 0) { assert (zero_count == idx); }
  while (idx > 0) {
    buf[idx--] = b58_table[0];
  }
  return buf;
}