#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

#define LARGO 50

enum nodo_state {BUSY,EMPTY,DELETED};

struct hash_node {
    char * key;
    void * value;
    enum nodo_state state;
} typedef hash_node_t;

struct hash {
    hash_node_t * hash_array;
    size_t length;
    size_t busy_space;
};

int hash_function(const char *key_string){
    return (int)strlen(key_string);
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){

    hash_t * hash = malloc(sizeof(hash_t));
    if(hash==NULL)return NULL;
    hash->length = LARGO;
    hash->busy_space = 0;
    hash_node_t * hash_array = malloc(sizeof(hash_node_t) * hash->length);

    // Inicializo todos los nodos en EMPTY.
    for(int i = 0; i< hash->length ; i++){
        hash_array[i].state = EMPTY;
    }
    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {

    char * key_copy = malloc(sizeof(char[strlen(clave)]));
    strcpy(key_copy,clave);

    int hashed_key = hash_function(key_copy);

    for(int i = hashed_key ; hashed_key < hash->length; i++) {
        if(hash->hash_array[i].state == EMPTY) {
            hash->hash_array[i].key = key_copy;
            hash->hash_array[i].value = dato; //*dato
            hash->hash_array[i].state = BUSY;
            return true;
        }
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            hash->hash_array[i].value = dato;
            return true;
        }
    }
    for(int i = 0; i < hashed_key; i++) {
        if(hash->hash_array[i].state == EMPTY) {
            hash->hash_array[i].key = key_copy;
            hash->hash_array[i].value = dato; //*dato
            hash->hash_array[i].state = BUSY;
            return true;
        }
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            hash->hash_array[i].value = dato;
            return true;
        }
    }
    return false;
}

size_t hash_cantidad(const hash_t *hash){
    return hash->busy_space;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
    int hashed_key = hash_function(clave);

    for(int i = hashed_key ; hashed_key < hash->length; i++) {
        if(hash->hash_array[i].state == EMPTY) {
            return NULL;
        }
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            return hash->hash_array[i].value;
        }
    }
    for(int i = 0; i < hashed_key; i++) {
        if(hash->hash_array[i].state == EMPTY) {
            return NULL;
        }
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            return hash->hash_array[i].value;
        }
    }
    return NULL;
}

void *hash_borrar(hash_t *hash, const char *clave){
    int hashed_key = hash_function(clave);

    for(int i = hashed_key ; hashed_key < hash->length; i++) {
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            return hash_array[i].key = NULL;
            return hash_array[i].value = NULL;
            return hash_array[i].state = DELETED;
        }
    }
    for(int i = 0; i < hashed_key; i++) {
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            return hash_array[i].key = NULL;
            return hash_array[i].value = NULL;
            return hash_array[i].state = DELETED;
        }
    }
}

bool hash_pertenece(const hash_t *hash, const char *clave){
    int hashed_key = hash_function(key_copy);

    for(int i = hashed_key ; hashed_key < hash->length; i++) {
        if(hash->hash_array[i].state == EMPTY) {
            return false;
        }
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            return true;
        }
    }
    for(int i = 0; i < hashed_key; i++) {
        if(hash->hash_array[i].state == EMPTY) {
            return false;
        }
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            return true;
        }
    }
    return false;
}

void hash_destruir(hash_t *hash){
  return;
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
  return NULL;
}

bool hash_iter_avanzar(hash_iter_t *iter){
  return NULL;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
  return NULL;
}

bool hash_iter_al_final(const hash_iter_t *iter){
  return NULL;
}

void hash_iter_destruir(hash_iter_t* iter){
  return;
}
