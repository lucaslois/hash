#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LARGO 50

enum nodo_state {BUSY,EMPTY,DELETED};

struct hash {
    hash_node_t * hash_array;
    size_t length;
    size_t busy_space;
};

struct hash_node {
    char * key;
    void * value;
    enum nodo_state state;
} typedef hash_node_t;

int hash_function(char *key_string){
    return strlen(key_string);
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){

    hash_t * hash = malloc(sizeof(hash_t));
    if(hash==NULL)return NULL;
    hash->length = 0;
    hash->busy = LARGO;
    hash_node_t * hash_array = malloc(sizeof(hash_node_t)*hash->length);
//continue here
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {

    char * key_copy = malloc(sizeof(char[strlen(clave)]));
    key_copy = strcpy(clave);

    //queda a definir si tenes que hacer una copia dinamca del dato (valor) y como...

    int hashed_key = hash_function(key_copy);

    for(int i = hashed_key ; hashed_key < hash->length; i++) {
        if(hash->hash_array[i]->state == EMPTY) {
            hash->hash_array[i]->key = key_copy;
            hash->hash_array[i]->value = dato;
            hash->hash_array[i]->state = BUSY;
        }
        if(hash->hash_array[i]->state == BUSY && strcmp(clave,hash->hash_array[i]->key) == 0 ) {
            hash->hash_array[i]->value = dato;
        }
    }
}
