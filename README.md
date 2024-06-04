# JWT_RS256 Verification Library

This library provides functionality for verifying JWT (JSON Web Token) signatures using the RS256 algorithm. The library is implemented in C++ for use in Arduino projects.

## Contents

- [Installation](#installation)
- [Usage](#usage)
- [API](#api)
- [Example](#example)
- [License](#license)

## Installation

1. Clone this repository or download the source code.
2. Add the `jwt_rs256.h` and `jwt_rs256.cpp` files to your Arduino project.
3. Ensure you have the mbedTLS library installed in your Arduino environment.

## Usage

1. Include the library in your Arduino sketch:

```cpp
#include "JWT_RS256.h"
```

2. Set the RSA public key that will be used to verify the tokens:

```cpp
const char* rsa_public_key = "-----BEGIN PUBLIC KEY-----\n...\n-----END PUBLIC KEY-----";

JWT_RS256 jwt;
jwt.rsa_public_key = rsa_public_key;
```

3. Verify the validity of a JWT token:

```cpp
String token = "your.jwt.token.here";
bool isValid = jwt.tokenIsValid(token);

if (isValid) {
  Serial.println("Token is valid!");
} else {
  Serial.println("Token is invalid.");
}
```

## API

### Public Methods

- **JWT_RS256()**: Constructor for the JWT_RS256 class.
- **String base64URLDecode(String input)**: Decodes a Base64URL encoded string.
  - **Parameters**:
    - `input` (String): The Base64URL encoded string to decode.
  - **Returns**:
    - `String`: The decoded string.

- **bool verifyRS256Signature(String data, String signature)**: Verifies the RS256 signature of the given data.
  - **Parameters**:
    - `data` (String): The data to verify.
    - `signature` (String): The RS256 signature to verify against.
  - **Returns**:
    - `bool`: `true` if the signature is valid, `false` otherwise.

- **bool tokenIsValid(String token)**: Verifies if the given token is valid.
  - **Parameters**:
    - `token` (String): The JWT token to verify.
  - **Returns**:
    - `bool`: `true` if the token is valid, `false` otherwise.

- **String getToken()**: Returns the current token.
  - **Returns**:
    - `String`: The current token.

- **ParsedToken parseToken(String token)**: Parses the given token into its header, payload, and signature components.
  - **Parameters**:
    - `token` (String): The JWT token to parse.
  - **Returns**:
    - `ParsedToken`: A structure containing the header, payload, signature, and data parts of the token.

### Data Structures

- **ParsedToken**: A structure that holds the header, payload, signature, and data parts of a parsed token.
  - **Members**:
    - `String header`: The decoded header of the token.
    - `String payload`: The decoded payload of the token.
    - `String signature`: The decoded signature of the token.
    - `String data`: The concatenated header and payload used for signature verification.


## Example
```cpp
#include "JWT_RS256.h"

// Your RSA public key
const char* rsa_public_key = "-----BEGIN PUBLIC KEY-----\n...\n-----END PUBLIC KEY-----";

JWT_RS256 token_manager;

void setup() {
  Serial.begin(9600);

  token_manager.rsa_public_key = rsa_public_key;

  String token = "your.jwt.token.here";
  bool isValid = token_manager.tokenIsValid(token);

  if (isValid) {
    Serial.println("Token is valid!");
  }
}

void loop() {
  // Your code here
}
```

## License

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
