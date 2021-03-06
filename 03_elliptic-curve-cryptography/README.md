### Sample output

```
testIfPointsOnCurve():
Expect (p1): NO exception thrown
Expect (p2): NO exception thrown
Expect (p3): exception WILL BE thrown
p3: Invalid argument: Point (200 (223), 119 (223)) not on the curve
Expect (p4): NO exception thrown
Expect (p5): exception WILL BE thrown
p5: Invalid argument: Point (42 (223), 99 (223)) not on the curve

testFieldElementPointAddition()
Result: FieldElementPoint(170, 142)_0_7 FieldElement(223)
Expect: FieldElementPoint(170, 142)_0_7 FieldElement(223)
Result: FieldElementPoint(220, 181)_0_7 FieldElement(223)
Expect: FieldElementPoint(220, 181)_0_7 FieldElement(223)
Result: FieldElementPoint(215, 68)_0_7 FieldElement(223)
Expect: FieldElementPoint(215, 68)_0_7 FieldElement(223)
Result: FieldElementPoint(47, 71)_0_7 FieldElement(223)
Expect: FieldElementPoint(47, 71)_0_7 FieldElement(223)

testFieldElementPointScalarMultiplication():
Result1: FieldElementPoint(49, 71)_0_7 FieldElement(223)
Result2: FieldElementPoint(49, 71)_0_7 FieldElement(223)
Expect:  FieldElementPoint(49, 71)_0_7 FieldElement(223)
Result1: FieldElementPoint(64, 168)_0_7 FieldElement(223)
Result2: FieldElementPoint(64, 168)_0_7 FieldElement(223)
Expect:  FieldElementPoint(64, 168)_0_7 FieldElement(223)
Result1: FieldElementPoint(36, 111)_0_7 FieldElement(223)
Result2: FieldElementPoint(36, 111)_0_7 FieldElement(223)
Expect:  FieldElementPoint(36, 111)_0_7 FieldElement(223)
Result1: FieldElementPoint(194, 51)_0_7 FieldElement(223)
Result2: FieldElementPoint(194, 51)_0_7 FieldElement(223)
Expect:  FieldElementPoint(194, 51)_0_7 FieldElement(223)
Result1: FieldElementPoint(116, 55)_0_7 FieldElement(223)
Result2: FieldElementPoint(116, 55)_0_7 FieldElement(223)
Expect:  FieldElementPoint(116, 55)_0_7 FieldElement(223)
Result1: FieldElementPoint(Infinity)_0_7 FieldElement(223)
Result2: FieldElementPoint(Infinity)_0_7 FieldElement(223)
Expect:  FieldElementPoint(Infinity)_0_7 FieldElement(223)
Result1: FieldElementPoint(Infinity)_0_7 FieldElement(223)
Result2: FieldElementPoint(Infinity)_0_7 FieldElement(223)
Expect:  FieldElementPoint(Infinity)_0_7 FieldElement(223)
Result1: FieldElementPoint(15, 86)_0_7 FieldElement(223)
Result2: FieldElementPoint(15, 86)_0_7 FieldElement(223)
Expect:  FieldElementPoint(15, 86)_0_7 FieldElement(223)

findOrderOfGroup():
Result: Order of the group generated by FieldElementPoint(15, 86)_0_7 FieldElement(223) is: 7
Expect: Order of the group generated by FieldElementPoint(15, 86)_0_7 FieldElement(223) is: 7

testSecp256k1():
Result: FieldElementPoint(Infinity)_0_7 FieldElement(fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f)
Expect: FieldElementPoint(Infinity)_0_7 FieldElement(fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f)
Result: FieldElementPoint(79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798, 483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)_0_7 FieldElement(fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f)
Expect: FieldElementPoint(79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798, 483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)_0_7 FieldElement(fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f)

testS256SubClass():
Result: FieldElementPoint(Infinity)_0_7 FieldElement(fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f)
Expect: FieldElementPoint(Infinity)_0_7 FieldElement(fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f)
Result: FieldElementPoint(79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798, 483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)_0_7 FieldElement(fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f)
Expect: FieldElementPoint(79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798, 483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)_0_7 FieldElement(fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f)
Result: S256Point(79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798, 483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)_0_7
Expect: S256Point(79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798, 483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)_0_7
Result: S256Point(Infinity)_0_7
Expect: S256Point(Infinity)_0_7
Result: S256Point(79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798, 483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)_0_7
Expect: S256Point(79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798, 483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)_0_7
Result: S256Point(Infinity)_0_7
Expect: S256Point(Infinity)_0_7

testS256Verification():
Result: 1
Expect: 1
Result: 1
Expect: 1
Result: 1
Expect: 1

testBytesToInt512():
Result: 65280
Expect: 65280
Result: 255
Expect: 255
Result: 3735928559
Expect: 3735928559
Result: 67482173399188229
Expect: 67482173399188229
Result: 0
Expect: 0
Result: 1123923222922975560859903
Expect: 1123923222922975560859903

testSignatureCreation():
Result: p: S256Point(028d003eab2e428d11983f3e97c3fa0addf3b42740df0d211795ffb3be2f6c52, 0ae987b9ec6ea159c78cb2a937ed89096fb218d9e7594f02b547526d8cd309e2)_0_7
Expect: p: S256Point(028d003eab2e428d11983f3e97c3fa0addf3b42740df0d211795ffb3be2f6c52, 0ae987b9ec6ea159c78cb2a937ed89096fb218d9e7594f02b547526d8cd309e2)_0_7
Result: msgHash: 231c6f3d980a6b0fb7152f85cee7eb52bf92433d9919b9c5218cb08e79cce78
Expect: msgHash: 231c6f3d980a6b0fb7152f85cee7eb52bf92433d9919b9c5218cb08e79cce78
Result: r: 2b698a0f0a4041b77e63488ad48c23e8e8838dd1fb7520408b121697b782ef22
Expect: r: 2b698a0f0a4041b77e63488ad48c23e8e8838dd1fb7520408b121697b782ef22
Result: sig: bb14e602ef9e3f872e25fad328466b34e6734b7a0fcd58b1eb635447ffae8cb9
Expect: sig: bb14e602ef9e3f872e25fad328466b34e6734b7a0fcd58b1eb635447ffae8cb9
Result: fa4c6b87c29398c5022557788697f68dd3e2d39744355d18f47e4b91c69abad0
Expect: fa4c6b87c29398c5022557788697f68dd3e2d39744355d18f47e4b91c69abad0
Result: Deterministic K: abef7a40d9bd76aef7ee7e733404ecfcd8041550a68625d7cc0608b0025038b1
Expect: Deterministic K: abef7a40d9bd76aef7ee7e733404ecfcd8041550a68625d7cc0608b0025038b1
Result: Signature(8eeacac05e4c29e793b5287ed044637132ce9ead7fded533e7441d87a8dc9c23, 36674f81f10c7fb347c1224bd546813ea24ada6f642c02f2248516e3aa8cb303)
Expect: Signature(8eeacac05e4c29e793b5287ed044637132ce9ead7fded533e7441d87a8dc9c23, 36674f81f10c7fb347c1224bd546813ea24ada6f642c02f2248516e3aa8cb303)

```