#ifndef JWT_RS256_H
#define JWT_RS256_H

#include <Arduino.h>
#include <mbedtls/base64.h>
#include <mbedtls/base64.h>
#include <mbedtls/pk.h>
#include <mbedtls/sha256.h>
#include <mbedtls/error.h>

struct ParsedToken
{
  String header;
  String payload;
  String signature;
  String data;
};

class JWT_RS256
{
public:
  JWT_RS256();

  String base64URLDecode(String input);
  bool verifyRS256Signature(String data, String signature);
  bool tokenIsValid(String token);
  String getToken();
  ParsedToken parseToken(String token);
  char *rsa_public_key;

private:
  String token;
};

#endif // JWT_RS256_H