#include <iostream>
#include <stdexcept>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/mod_inverse.hpp>
#include "ecc.h"
#include "utils.h"
#include "misc.h"
#include "sha256.h"
#include "hmac.h"

using namespace std;
//namespace mp = boost::multiprecision;

void testIfPointsOnCurve() {
  try {
    FieldElementPoint p2 = FieldElementPoint(
      FieldElement(17, 223), FieldElement(56, 223), FieldElement(0, 223), FieldElement(7, 223)
    );
  } catch (const invalid_argument& ia) {
    cerr << "p2: Invalid argument: " << ia.what() << endl;
  }

  try {
    FieldElementPoint p3 = FieldElementPoint(
      FieldElement(200, 223), FieldElement(119, 223), FieldElement(0, 223), FieldElement(7, 223)
    );
  } catch (const invalid_argument& ia) {
    cerr << "p3: Invalid argument: " << ia.what() << endl;
  }

  try {
    FieldElementPoint p4 = FieldElementPoint(
      FieldElement(1, 223), FieldElement(193, 223), FieldElement(0, 223), FieldElement(7, 223)
    );
  } catch (const invalid_argument& ia) {
    cerr << "p4: Invalid argument: " << ia.what() << endl;
  }
  
  try {
    FieldElementPoint p5 = FieldElementPoint(
      FieldElement(42, 223), FieldElement(99, 223), FieldElement(0, 223), FieldElement(7, 223)
    );
  } catch (const invalid_argument& ia) {
    cerr << "p5: Invalid argument: " << ia.what() << endl;
  }
}


void testFieldElementPointAddition() {
  cout << "testFieldElementPointAddition()" << endl;
  int prime = 223;
  
  FieldElement a = FieldElement(0, prime);
  FieldElement b = FieldElement(7, prime);

  FieldElement x1;
  FieldElement y1;
  FieldElement x2;
  FieldElement y2;

  x1 = FieldElement(192, prime);
  y1 = FieldElement(105, prime);
  x2 = FieldElement(17, prime);
  y2 = FieldElement(56, prime);
  FieldElementPoint p1 = FieldElementPoint(x1, y1, a, b);
  FieldElementPoint p2 = FieldElementPoint(x2, y2, a, b);
  cout << (p1 + p2).to_string() << endl;

  x1 = FieldElement(170, prime);
  y1 = FieldElement(142, prime);
  x2 = FieldElement(60, prime);
  y2 = FieldElement(139, prime);
  cout << (FieldElementPoint(x1, y1, a, b) + FieldElementPoint(x2, y2, a, b)).to_string() << endl;

  x1 = FieldElement(47, prime);
  y1 = FieldElement(71, prime);
  x2 = FieldElement(17, prime);
  y2 = FieldElement(56, prime);
  cout << (FieldElementPoint(x1, y1, a, b) + FieldElementPoint(x2, y2, a, b)).to_string() << endl;

  x1 = FieldElement(143, prime);
  y1 = FieldElement(98, prime);
  x2 = FieldElement(76, prime);
  y2 = FieldElement(66, prime);
  cout << (FieldElementPoint(x1, y1, a, b) + FieldElementPoint(x2, y2, a, b)).to_string() << endl;

}

void findOrderOfGroup() {
  int prime = 223;
  FieldElement a = FieldElement(0, prime);
  FieldElement b = FieldElement(7, prime);
  FieldElement x = FieldElement(15, prime);
  FieldElement y = FieldElement(86, prime);

  FieldElementPoint p = FieldElementPoint(a, b);
  FieldElementPoint orig = FieldElementPoint(x, y, a, b);
  int order = 0;
  while (order == 0 || p.infinity()  == false) {
    p += orig;
    order ++;
  }
  cout << "Order of the group generated by " << orig.to_string() << " is: "<< order << endl;
}

void testFieldElementPointScalarMultiplication() {
  cout << "testFieldElementPointScalarMultiplication()" << endl;
  int prime = 223;
  FieldElement a = FieldElement(0, prime);
  FieldElement b = FieldElement(7, prime);

  FieldElement x1;
  FieldElement y1;
  FieldElement x2;
  FieldElement y2;

  x1 = FieldElement(192, prime);
  y1 = FieldElement(105, prime);
  FieldElementPoint p1 = FieldElementPoint(x1, y1, a, b);
  cout << "(" << x1.to_string() << ", " << y1.to_string() << "): " << (p1 + p1).to_string() << " == " << (p1 * 2).to_string() << endl;

  x1 = FieldElement(143, prime);
  y1 = FieldElement(98, prime);
  p1 = FieldElementPoint(x1, y1, a, b);
  cout << "(" << x1.to_string() << ", " << y1.to_string() << "): " << (p1 + p1).to_string() << " == " << (p1 * 2).to_string() << endl;

  x1 = FieldElement(47, prime);
  y1 = FieldElement(71, prime);
  p1 = FieldElementPoint(x1, y1, a, b);
  cout << "(" << x1.to_string() << ", " << y1.to_string() << "): " << (p1+p1).to_string() << " == " << (p1 * 2).to_string() << endl;
  cout << "(" << x1.to_string() << ", " << y1.to_string() << "): " << (p1+p1+p1+p1).to_string() << " == " << (p1 * 4).to_string() << endl;
  cout << "(" << x1.to_string() << ", " << y1.to_string() << "): " << (p1+p1+p1+p1+p1+p1+p1+p1).to_string() << " == " << (p1 * 8).to_string() << endl;
  cout << "(" << x1.to_string() << ", " << y1.to_string() << "): " << (p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1+p1).to_string() << " == " << (p1 * 21).to_string() << endl;

  x1 = FieldElement(15, prime);
  y1 = FieldElement(86, prime);
  p1 = FieldElementPoint(x1, y1, a, b);
  cout << (p1 * 7).to_string() << endl;
  cout << (p1 + p1 + p1 + p1 + p1 + p1 + p1).to_string() << endl;
  cout << (p1 * 8).to_string() << endl;
  cout << (p1 + p1 + p1 + p1 + p1 + p1 + p1 + p1).to_string() << endl;
}

void testSecp256k1() {
  cout << "testSecp256k1()" << endl;
  int512_t gx{"0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798"}; // string-based constructor
  int512_t gy{"0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8"};  
  // gx and gy are the coordinates of point g, which is the generator point, i.e., we add g to itself over and over again.
  int512_t prime = pow((int512_t)2, 256) - pow((int512_t)2,32) - 977;
  int512_t order{"0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141"};
  // If we add g "order" number of times to itself, we get point at infinity;
  // If we add g "order + 1" number of times to itself, we get g again!
  FieldElementPoint g = FieldElementPoint(
    FieldElement(gx, prime), FieldElement(gy, prime), FieldElement(0, prime), FieldElement(7, prime)
  );
  cout << (g * order).to_string(true) << endl;
  cout << (g * order + g).to_string(true) << endl;
}

void testS256SubClass() {
  cout << "testS256SubClass()" << endl;
  S256Element x = S256Element((int512_t)"0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798");
  S256Element y = S256Element((int512_t)"0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8");
  S256Element a = S256Element((int512_t)0);
  S256Element b = S256Element((int512_t)7);
  int512_t order{"0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141"};
  FieldElementPoint g = FieldElementPoint(x, y, a, b);
  cout << (g * order).to_string(true) << endl;
  cout << (g * order + g).to_string(true) << endl;

  S256Point p1 = S256Point(x, y);
  S256Point p2 = S256Point();
  cout << p1.to_string() << endl;
  cout << (p1 * order).to_string() << endl;
  cout << (p1 * order + p1).to_string() << endl;
  cout << p2.to_string() << endl;
}

void testS256Verification() {
  cout << "testS256Verification()" << endl;
  S256Point p1 = S256Point(
    (int512_t)"0x04519fac3d910ca7e7138f7013706f619fa8f033e6ec6e09370ea38cee6a7574",
    (int512_t)"0x82b51eab8c27c66e26c858a079bcdf4f1ada34cec420cafc7eac1a42216fb6c4"
  );
  Signature sig1 = Signature(
    (int512_t)"0x37206a0610995c58074999cb9767b87af4c4978db68c06e8e6e81d282047a7c6",
    (int512_t)"0x8ca63759c1157ebeaec0d03cecca119fc9a75bf8e6d0fa65c841c8e2738cdaec"
  );
  cout << p1.verify((int512_t)"0xbc62d4b80d9e36da29c16c5d4d9f11731f36052c72401a76c23c0fb5a9b74423",sig1) << endl;

  S256Point p2 = S256Point(
    (int512_t)"0x887387e452b8eacc4acfde10d9aaf7f6d9a0f975aabb10d006e4da568744d06c",
    (int512_t)"0x61de6d95231cd89026e286df3b6ae4a894a3378e393e93a0f45b666329a0ae34"
  );
  Signature sig2 = Signature(
    (int512_t)"0xac8d1c87e51d0d441be8b3dd5b05c8795b48875dffe00b7ffcfac23010d3a395",
    (int512_t)"0x68342ceff8935ededd102dd876ffd6ba72d6a427a3edb13d26eb0781cb423c4"
  );
  Signature sig3 = Signature(
    (int512_t)"0xeff69ef2b1bd93a66ed5219add4fb51e11a840f404876325a1e8ffe0529a2c",
    (int512_t)"0xc7207fee197d27c618aea621406f6bf5ef6fca38681d82b2f06fddbdce6feab6"
  );
  cout << p2.verify((int512_t)"0xec208baa0fc1c19f708a9ca96fdeff3ac3f230bb4a7ba4aede4942ad003c0f60",sig2) << endl;
  cout << p2.verify((int512_t)"0x7c076ff316692a3d7eb3c3bb0f8b1488cf72e1afcd929e29307032997a838a3d",sig3) << endl;
}

void testSHA256() {
  cout << "testSHA256()" << endl;
  unsigned char input[] = { 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21 }; // Hello world!
  for (int i = 0; i < sizeof(input); i++){
    cout << input[i];
  }
  cout << endl;

  unsigned char output[SHA256_HASH_SIZE];

  cal_sha256_hash(input, sizeof(input), output);
  cout << bytes_to_hex_string(output, sizeof(output), false) << endl;
}

void testBytesToInt512() {
  cout << "testBytesToInt512()" << endl;
  unsigned char input[] = { 0xff, 0x00 };
  cout << get_int512_from_bytes(input, sizeof(input), true) << endl;
}

void testSignatureCreation() {
  cout << "testSignatureCreation()" << endl;

  unsigned char secretChars[] = {'m', 'y', ' ', 's', 'e', 'c', 'r', 'e', 't' };
  unsigned char secretBytes[SHA256_HASH_SIZE];
  cal_sha256_hash(secretChars, sizeof(secretChars), secretBytes);
  cal_sha256_hash(secretBytes, SHA256_HASH_SIZE, secretBytes);
  int512_t secret = get_int512_from_bytes(secretBytes, SHA256_HASH_SIZE);

  unsigned char msgChars[] = {'m', 'y', ' ', 'm', 'e', 's', 's', 'a', 'g', 'e' };
  unsigned char msgHashBytes[SHA256_HASH_SIZE];
  cal_sha256_hash(msgChars, sizeof(msgChars), msgHashBytes);
  cal_sha256_hash(msgHashBytes, SHA256_HASH_SIZE, msgHashBytes);
  int512_t msgHash = get_int512_from_bytes(msgHashBytes, SHA256_HASH_SIZE);

  S256Point p = G * secret;
  int512_t k = 1234567890;
  int512_t r = (G * k).x().num();
  int512_t kInv = boost::integer::mod_inverse(k, G.order());
  int512_t sig = (int512_t)((int1024_t)(msgHash + secret * r) * kInv % G.order());
  cout << "p: " << p.to_string() << endl;
  cout << "msgHash: " << hex << msgHash << endl;
  cout << "r: " << hex << r << endl;
  cout << "sig: " << sig << endl;


  ECDSAKey pk = ECDSAKey(secretBytes, sizeof(secretBytes));
  cout << "ECDSAKey.get_deterministic_k(): " << hex
       << pk.get_deterministic_k(msgHashBytes, sizeof(msgHashBytes)) << endl;
  cout << "Note: the correct k should be fa4c6b87c29398c5022557788697f68dd3e2d39744355d18f47e4b91c69abad0" << endl;
  cout << "ECDSAKey.sign(): " << pk.sign(msgHashBytes, sizeof(msgHashBytes)).to_string() << endl;;
}

void testHMACSHA256() {
  cout << "testHMACSHA256()" << endl;
  unsigned char key[] = { 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21 }; // Hello world!
  unsigned char data[] = { 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64 }; // Hello world
  unsigned char output[SHA256_HASH_SIZE];
  hmac_sha256(key, sizeof(key), data, sizeof(data), output);
  cout << bytes_to_hex_string(output, sizeof(output), false) << endl;
}

int main() {
  testIfPointsOnCurve();
  cout << endl;
  testFieldElementPointAddition();
  cout << endl;
  findOrderOfGroup();
  cout << endl;
  testFieldElementPointScalarMultiplication();
  cout << endl;
  testSecp256k1();
  cout << endl;
  testS256SubClass();
  cout << endl;
  testS256Verification();
  cout << endl;
  testSHA256();
  cout << endl;
  testBytesToInt512();
  cout << endl;
  testSignatureCreation();
  cout << endl;
  testHMACSHA256();
  return 0;
}
