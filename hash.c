#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

#define LARGO 100

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

int hash_function(const char *key_string, size_t tam){
    size_t aux = strlen(key_string);
    while (aux > tam) {
        aux -= tam;
    }
    return (int)aux;
}
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){

    hash_t * hash = malloc(sizeof(hash_t));
    if(hash==NULL) return NULL;
    hash->length = LARGO;
    hash->busy_space = 0;
    hash->hash_array = malloc(sizeof(hash_node_t) * hash->length);


    // Inicializo todos los nodos en EMPTY.
    for(int i = 0; i < hash->length; i++){
        hash->hash_array[i].state = EMPTY;
        hash->hash_array[i].key = NULL;
        hash->hash_array[i].value = NULL;
    }
    return hash;
}

hash_t *hash_crear_custom(hash_destruir_dato_t destruir_dato, size_t tam) {
        hash_t * hash = malloc(sizeof(hash_t));
        if(hash==NULL) return NULL;
        hash->length = tam;
        hash->busy_space = 0;
        hash_node_t * hash_array = malloc(sizeof(hash_node_t) * hash->length);
        hash->hash_array = hash_array;

        // Inicializo todos los nodos en EMPTY.
        for(int i = 0; i < hash->length; i++){
            hash->hash_array[i].state = EMPTY;
            hash->hash_array[i].key = NULL;
            hash->hash_array[i].value = NULL;
        }
        return hash;
}

void hash_copy(hash_t* old_hash, hash_t* new_hash) {
    for(int i = 0; i < old_hash->length ; i++){
        if(old_hash->hash_array[i].state == BUSY) {
            hash_guardar(new_hash, old_hash->hash_array[i].key, old_hash->hash_array[i].value);
        }
    }
    return;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    char * key_copy = malloc(sizeof(char[strlen(clave)+1]));
    strcpy(key_copy,clave);

    if(hash->busy_space == hash->length/2 ) {
        hash_t* new_hash = hash_crear_custom(NULL, hash->length * 2);
        hash_copy(new_hash, hash);
        hash->length = new_hash->length; //esto solucion bastante
        hash_destruir(hash);
        hash = new_hash;
    }

    int hashed_key = hash_function(clave, hash->length); //por lo que se le pasaba aca..

    for(int i = hashed_key ; i < hash->length; i++) {
        if(hash->hash_array[i].state == EMPTY) {
            hash->hash_array[i].key = key_copy;
            hash->hash_array[i].value = dato;
            hash->hash_array[i].state = BUSY;
            hash->busy_space++;
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
            hash->busy_space++;
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
    int hashed_key = hash_function(clave, hash->length);

    if(hash->busy_space == 0)
        return NULL;

    for(int i = hashed_key ; i < hash->length; i++) {
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
    int hashed_key = hash_function(clave, (int)hash->length);

    if(hash->busy_space == 0)
        return NULL;

    for(int i = hashed_key ; i < hash->length; i++) {
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            void* aux = hash->hash_array[i].value;
            free(hash->hash_array[i].key);
            hash->hash_array[i].key = NULL;
            hash->hash_array[i].value = NULL;
            hash->hash_array[i].state = DELETED;
            hash->busy_space--;
            return aux;
        }
    }
    for(int i = 0; i < hashed_key; i++) {
        if(hash->hash_array[i].state == BUSY && strcmp(clave,hash->hash_array[i].key) == 0 ) {
            void* aux = hash->hash_array[i].value;
            free(hash->hash_array[i].key);
            hash->hash_array[i].key = NULL;
            hash->hash_array[i].value = NULL;
            hash->hash_array[i].state = DELETED;
            hash->busy_space--;
            return aux;
        }
    }
    return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
    int hashed_key = hash_function(clave, (int)hash->length);

    if(hash->busy_space == 0)
        return false;

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

  free(hash->hash_array);
  free(hash);
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
