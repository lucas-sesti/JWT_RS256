#include "JWT_RS256.h"
#include <Arduino.h>
#include <mbedtls/base64.h>
#include <mbedtls/pk.h>
#include <mbedtls/sha256.h>
#include <mbedtls/error.h>

JWT_RS256::JWT_RS256(){};

String JWT_RS256::getToken()
{
  return this->token;
}

const char base64_url_alphabet[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'};

String JWT_RS256::base64URLDecode(String in)
{
  String out;
  int T[256];
  for (int i = 0; i < 256; i++)
    T[i] = -1;
  for (int i = 0; i < 64; i++)
    T[base64_url_alphabet[i]] = i;

  int val = 0, valb = -8;
  for (unsigned int i = 0; i < in.length(); i++)
  {
    unsigned char c = in[i];
    if (T[c] == -1)
      break;
    val = (val << 6) + T[c];
    valb += 6;
    if (valb >= 0)
    {
      out += (char)((val >> valb) & 0xFF);
      valb -= 8;
    }
  }
  return out;
}

bool JWT_RS256::verifyRS256Signature(String data, String signature)
{
  mbedtls_pk_context pk;
  mbedtls_pk_init(&pk);

  int ret = mbedtls_pk_parse_public_key(&pk, (const unsigned char *)this->rsa_public_key, strlen(this->rsa_public_key) + 1);
  if (ret != 0)
  {
    Serial.print("Failed to parse public key: ");
    Serial.println(ret);
    mbedtls_pk_free(&pk);
    return false;
  }

  unsigned char hash[32];
  mbedtls_sha256((const unsigned char *)data.c_str(), data.length(), hash, 0);

  ret = mbedtls_pk_verify(&pk, MBEDTLS_MD_SHA256, hash, sizeof(hash), reinterpret_cast<const unsigned char *>(signature.c_str()), signature.length());
  if (ret != 0)
  {
    Serial.print("Signature verification failed: ");
    Serial.println(ret);
    mbedtls_pk_free(&pk);
    return false;
  }

  mbedtls_pk_free(&pk);
  return true;
}

ParsedToken JWT_RS256::parseToken(String token)
{
  String parts[3];

  for (int i = 0; i < 3; i++)
  {
    int dotIndex = token.indexOf('.');
    String part = token.substring(0, dotIndex);

    parts[i] = part;
    token = token.substring(dotIndex + 1, token.length());
  }

  struct ParsedToken result = {this->base64URLDecode(parts[0]), this->base64URLDecode(parts[1]), this->base64URLDecode(parts[2]), parts[0] + "." + parts[1]};

  return result;
}

bool JWT_RS256::tokenIsValid(String token)
{
  ParsedToken parsedToken = this->parseToken(token);

  if (!this->verifyRS256Signature(parsedToken.data, parsedToken.signature))
  {
    Serial.println("Failed to verify signature");
    Serial.println(token);
    
    token.clear();
    return false;
  }

  return true;
}