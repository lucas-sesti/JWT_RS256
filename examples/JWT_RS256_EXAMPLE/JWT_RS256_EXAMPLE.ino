#include <JWT_RS256.h>

JWT_RS256 token_manager;

const char *rsa_public_key = "-----BEGIN PUBLIC KEY-----\n...\n-----END PUBLIC KEY-----";

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting JWT_RS256 example...");

  token_manager.rsa_public_key = rsa_public_key;

  String token = "your.jwt.token.here";
  bool isValid = token_manager.tokenIsValid(token);

  if (isValid)
  {
    Serial.println("Token is valid");
  }
}

void loop() {}