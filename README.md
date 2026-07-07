CryptoLab
📖 Overview
CryptoLab is a collection of cryptographic algorithms and implementations written in C, C++, and Java.
It serves as a learning resource and practical toolkit for experimenting with classical and modern cryptography techniques.

The repository includes implementations of:

Classical ciphers (Caesar, Vigenère, Row/Column transposition)

Modular arithmetic utilities (GCD, Extended GCD, Modular Inverse)

Public‑key cryptosystems (RSA, ElGamal, ECC)

Digital signatures (RSA, ElGamal, DSSS)

Hashing algorithms (MD5, SHA‑512)

Symmetric encryption (SDES)

Chinese Remainder Theorem (CRT)

🚀 Features
Wide coverage: From basic number theory utilities to advanced cryptographic schemes.

Multi‑language support: Implementations in C, C++, and Java.

Educational focus: Code is structured to help students understand cryptographic concepts.

Modular design: Each algorithm is implemented in its own file for clarity.

📂 Repository Structure
Code
CryptoLab/
├── casear.c              # Caesar Cipher
├── vignere.c             # Vigenère Cipher
├── row_col.c             # Row/Column Transposition Cipher
├── gcd.c                 # Greatest Common Divisor
├── extendedgcd.c         # Extended Euclidean Algorithm
├── modular_inv.c         # Modular Inverse
├── crt.c                 # Chinese Remainder Theorem
├── rsa.c                 # RSA Cryptosystem
├── rsadigitalsign.cpp    # RSA Digital Signature
├── Elgamel.c             # ElGamal Cryptosystem
├── elgameldigitalsign.cpp# ElGamal Digital Signature
├── ecc.cpp               # Elliptic Curve Cryptography
├── digitalsgns.cpp       # Digital Signatures (general)
├── DSSS.cpp              # DSSS implementation
├── sdes.cpp              # Simplified DES
├── md5_sha512.java       # MD5 and SHA‑512 hashing
├── md5_sha512.class      # Compiled Java class
├── Main.java             # Example driver (Lab9)
└── .gitignore
🛠️ Getting Started
Prerequisites
C/C++ compiler (e.g., GCC, Clang)

Java JDK (for MD5/SHA‑512 implementations)

Compilation & Execution
Compile and run any algorithm individually:

bash
# Example: Compile and run RSA
gcc rsa.c -o rsa
./rsa

# Example: Compile and run Caesar Cipher
gcc casear.c -o caesar
./caesar

# Example: Run Java hashing
javac md5_sha512.java
java md5_sha512
📌 Example Usage
Caesar Cipher
text
Input: HELLO
Key: 3
Output: KHOOR
RSA
text
Enter prime numbers: 17, 19
Public key: (e, n)
Private key: (d, n)
Message: 42
Encrypted: <ciphertext>
Decrypted: 42
🧪 Testing
Each file can be compiled and tested independently.
For validation:

Compare outputs with known cryptographic examples.

Use small primes for RSA/ElGamal to verify correctness.

Check hash outputs against standard MD5/SHA‑512 tools.

🤝 Contributing
Contributions are welcome!

Fork the repo

Create a new branch (feature/new-algorithm)

Add your implementation or fix

Commit with a clear message (feat: add AES implementation)

Open a Pull Request

📜 License
This project currently has no explicit license.
If you plan to reuse or extend, please contact the repository owner.