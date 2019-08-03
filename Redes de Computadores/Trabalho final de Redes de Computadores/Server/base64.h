#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "base64.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <assert.h>

using namespace std;

size_t tamanho_buffer_decodificacao(const char *buffer){
    size_t tam = strlen(buffer), aux = 0;

    if(buffer[tam-1] == '=' && buffer[tam-2] == '=') aux = 2;
    else if(buffer[tam-1] == '=') aux = 1;

    return (tam*3)/4 - aux;
}


int codifica_base64(const char *buffer, size_t length, char **resultado){
    BIO *bio, *b64;
    BUF_MEM *bufferp;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, buffer, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferp);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);
    *resultado = (*bufferp).data;
    return 0;
}

int decodifica_base64(const char *dados_codificados, char **buffer, size_t *tam){
    BIO *bio, *b64;
    int decodeTam = tamanho_buffer_decodificacao(dados_codificados);
    *buffer = (char*)malloc(decodeTam+1);
    (*buffer)[decodeTam] = '\0';

    bio = BIO_new_mem_buf(dados_codificados, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    *tam = BIO_read(bio, *buffer, strlen(dados_codificados));
    assert(*tam == decodeTam);
    return 0;
}


#endif // BASE64_H_INCLUDED
