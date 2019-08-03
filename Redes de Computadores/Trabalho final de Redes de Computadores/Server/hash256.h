#ifndef HASH256_H_INCLUDED
#define HASH256_H_INCLUDED

#include <iostream>
#include <cstring>
#include <openssl/sha.h>
#include <cstdio>
using namespace std;


string encode_sha256(string text){
	const char *data = const_cast<char*>(text.c_str());
	unsigned char aux[SHA_DIGEST_LENGTH];

	SHA_CTX ctx;
	SHA_Init(&ctx);
	SHA_Update(&ctx, data, strlen(data));
	SHA_Final(aux, &ctx);

	char strresp[SHA_DIGEST_LENGTH*2+1];

	for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
		sprintf(&strresp[i*2], "%02x", (unsigned int)aux[i]);

	string resp(strresp);
	return resp;
}



#endif // HASH256_H_INCLUDED
