#include <JWT_RS256.h>

JWT_RS256 tokenManager;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting JWT_RS256 example...");

  tokenManager.rsa_public_key = "ADD_YOUR_RSA_PUBLIC_KEY";

  String token = "ADD_YOUR_TOKEN";
  bool isValid = tokenManager.tokenIsValid(token);

  if (isValid)
  {
    Serial.println("Token is valid");
  }
}

void loop() {}