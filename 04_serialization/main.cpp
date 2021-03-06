#include "ecc.h"
#include "utils.h"
#include "misc.h"
#include "sha256.h"
#include "hmac.h"
#include <sstream>

void test_uncompressed_sec_format() {
  cout << "test_uncompressed_sec_format():" << endl;
  uint8_t private_key_bytes3[] = { 0x0d, 0xea, 0xdb, 0xee, 0xf1, 0x23, 0x45 };
  ECDSAKey pk3 = ECDSAKey(private_key_bytes3, sizeof(private_key_bytes3));
  uint8_t* sec = pk3.public_key().get_sec_format(false);
  for (int i = 0; i < (32 * 2 + 1); ++i)
    cout << hex << setfill('0') << setw(2) << (int)sec[i] << "";
  cout << endl;
  free(sec);
}

void test_compressed_sec_format() {
  cout << "test_compressed_sec_format():" << endl;
  uint8_t private_key_bytes3[] = { 0x0d, 0xea, 0xdb, 0xee, 0xf5, 0x43, 0x21 };
  ECDSAKey pk3 = ECDSAKey(private_key_bytes3, sizeof(private_key_bytes3));
  uint8_t* sec = pk3.public_key().get_sec_format(true);
  for (int i = 0; i < (32 + 1); ++i)
    cout << hex << setfill('0') << setw(2) << (int)sec[i] << "";
  cout << endl;
  free(sec);
}


void test_der_sig_format() {
  cout << "test_der_sig_format():" << endl;
  Signature sig = Signature(
    (int512_t)"0x37206a0610995c58074999cb9767b87af4c4978db68c06e8e6e81d282047a7c6",
    (int512_t)"0x8ca63759c1157ebeaec0d03cecca119fc9a75bf8e6d0fa65c841c8e2738cdaec"
  );
  uint8_t* der;
  size_t output_len;
  der = sig.get_der_format(&output_len);
  cout << "Function result: ";
  for (int i = 0; i < output_len; ++i)
    cout << hex << setfill('0') << setw(2) << (int)der[i] << "";
  cout << endl;
  cout << "Expected result: "
       << "3045022037206a0610995c58074999cb9767b87af4c4978db68c06e8e6e81d282047a7c6022100"
       << "8ca63759c1157ebeaec0d03cecca119fc9a75bf8e6d0fa65c841c8e2738cdaec" << endl;
  free(der);
}


void test_base58() {
  cout << "test_base58():" << endl;
  uint8_t input0[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21};
  // Hello World!
  
  char* output = nullptr;
  output = encode_bytes_to_base58_string(input0, sizeof(input0), true);
  cout << "Function result: " << output << "\n"
       << "Expected result: 2NEpo7TZRRrLZSi2U" << endl;
  free(output);

  char input1[] = "The quick brown fox jumps over the lazy dog.";
  output = encode_bytes_to_base58_string((uint8_t*)input1, strlen(input1), true);
  cout << "Function result: " << output << "\n"
       << "Expected result: USm3fpXnKG5EUBx2ndxBDMPVciP5hGey2Jh4NDv6gmeo1LkMeiKrLJUUBk6Z" << endl;
  free(output);

  uint8_t input2[] = {
    0x7c, 0x07, 0x6f, 0xf3, 0x16, 0x69, 0x2a, 0x3d, 0x7e, 0xb3, 0xc3, 0xbb, 0x0f, 0x8b, 0x14, 0x88, 
    0xcf, 0x72, 0xe1, 0xaf, 0xcd, 0x92, 0x9e, 0x29, 0x30, 0x70, 0x32, 0x99, 0x7a, 0x83, 0x8a, 0x3d
  };
  output = encode_bytes_to_base58_string(input2, sizeof(input2), true);
  cout << "Function result: " << output << "\n"
       << "Expected result: 9MA8fRQrT4u8Zj8ZRd6MAiiyaxb2Y1CMpvVkHQu5hVM6" << endl;
  free(output);

  uint8_t input3[] = {
    0xef, 0xf6, 0x9e, 0xf2, 0xb1, 0xbd, 0x93, 0xa6, 0x6e, 0xd5, 0x21, 0x9a, 0xdd, 0x4f, 0xb5, 0x1e,
    0x11, 0xa8, 0x40, 0xf4, 0x04, 0x87, 0x63, 0x25, 0xa1, 0xe8, 0xff, 0xe0, 0x52, 0x9a, 0x2c};
  output = encode_bytes_to_base58_string(input3, sizeof(input3), true);
  cout << "Function result: " << output << "\n"
       << "Expected result: 4fE3H2E6XMp4SsxtwinF7w9a34ooUrwWe4WsW1458Pd" << endl;
  free(output);

  uint8_t input4[] = {
    0xc7, 0x20, 0x7f, 0xee, 0x19, 0x7d, 0x27, 0xc6, 0x18, 0xae, 0xa6, 0x21, 0x40, 0x6f, 0x6b, 0xf5, 
    0xef, 0x6f, 0xca, 0x38, 0x68, 0x1d, 0x82, 0xb2, 0xf0, 0x6f, 0xdd, 0xbd, 0xce, 0x6f, 0xea, 0xb6
  };
  output = encode_bytes_to_base58_string(input4, sizeof(input4), true);
  cout << "Function result: " << output << "\n"
       << "Expected result: EQJsjkd6JaGwxrjEhfeqPenqHwrBmPQZjJGNSCHBkcF7" << endl;
  free(output);

  uint8_t input5[] = { 0x00, 0x00, 0x28, 0x7f, 0xb4, 0xcd };
  output = encode_bytes_to_base58_string(input5, sizeof(input5), true);
  cout << "Function result: " << output << "\n"
       << "Expected result: 111233QC4 (questionable)" << endl;
  free(output);
}

void test_base58_checksum() {
  cout << "test_base58_checksum():" << endl;
  uint8_t input_bytes[] = {0xde, 0xad, 0xbe, 0xef};
  char* output = encode_base58_checksum(input_bytes, sizeof(input_bytes));
  cout << "Function result: " << output << "\n"
       << "Expected result: eFGDJPketnz" << endl;
  free(output);

  uint8_t input_bytes1[] = "Hello world!";
  output = encode_base58_checksum(input_bytes1, sizeof(input_bytes1)-1);
  cout << "Function result: " << output << "\n"
       << "Expected result: 9wWTEnNTWna86WmtFaRbXa" << endl;
  free(output);

  
  char input_bytes2[] = "The quick brown fox jumps over the lazy dog.";
  output = encode_base58_checksum((uint8_t*)input_bytes2, strlen(input_bytes2));
  cout << "Function result: " << output << "\n"
       << "Expected result: 46auvTd4NTVoJhFVnfh9reLsP21HQAQUFXCCBzNZjAPwQBRpaSp4aDLzWajGrqq21B" << endl;
  free(output);
}

void test_hash160_address() {
  cout << "test_hash160_address():" << endl;
  char* addr;

  ECDSAKey key = ECDSAKey(5002);
  addr = key.public_key().get_address(false, true);
  cout << "Function result: "<< addr << "\n"
       << "Expected result: mmTPbXQFxboEtNRkwfh6K51jvdtHLxGeMA" << endl;
  free(addr);

  ECDSAKey key2 = ECDSAKey((int512_t)2020 * 2020 * 2020 * 2020 * 2020);
  addr = key2.public_key().get_address(true, true);
  cout << "Function result: "<< addr << "\n"
       << "Expected result: mopVkxp8UhXqRYbCYJsbeE1h1fiF64jcoH" << endl;
  free(addr);

  uint8_t priv_key3[] = {0x01, 0x23, 0x45, 0xde, 0xad, 0xbe, 0xef};
  ECDSAKey key3= ECDSAKey(priv_key3, sizeof(priv_key3));
  addr = key3.public_key().get_address(true, false);
  cout << "Function result: "<< addr << "\n"
       << "Expected result: 1F1Pn2y6pDb68E5nYJJeba4TLg2U7B6KF1" << endl;
  free(addr);
}

void test_privkey_wif_address() {
  cout << "test_privkey_wif_address():" << endl;
  char* addr;

  ECDSAKey key = ECDSAKey(5003);
  addr = key.get_wif_private_key(true, true);
  cout << "Function result: "<< addr << "\n"
       << "Expected result: cMahea7zqjxrtgAbB7LSGbcQUr1uX1ojuat9jZodMN8rFTv2sfUK" << endl;
  free(addr);

  ECDSAKey key2 = ECDSAKey((int512_t)2021 * 2021 * 2021 * 2021 * 2021);
  addr = key2.get_wif_private_key(false, true);
  cout << "Function result: "<< addr << "\n"
       << "Expected result: 91avARGdfge8E4tZfYLoxeJ5sGBdNJQH4kvjpWAxgzczjbCwxic" << endl;
  free(addr);

  uint8_t priv_key3[] = {0x05, 0x43, 0x21, 0xde, 0xad, 0xbe, 0xef};
  ECDSAKey key3 = ECDSAKey(priv_key3, sizeof(priv_key3));
  addr = key3.get_wif_private_key(true, false);
  cout << "Function result: "<< addr << "\n"
       << "Expected result: KwDiBf89QgGbjEhKnhXJuH7LrciVrZi3qYjgiuQJv1h8Ytr2S53a" << endl;
  free(addr);
}

int main() {
  test_uncompressed_sec_format();
  cout << endl;
  test_compressed_sec_format();
  cout << endl;
  test_der_sig_format();
  cout << endl;
  test_base58();
  cout << endl;
  test_base58_checksum();
  cout << endl;
  test_hash160_address();
  cout << endl;
  test_privkey_wif_address();
  cout << endl;
}