#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LARGO 50

enum nodo_state {BUSY,EMPTY,DELETED};

struct hash { // Acá nos falta la funcion destruir.
    hash_node_t * hash_array;
    size_t length;
    size_t busy_space;
};

/// hola com etas
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
    hash->length = LARGO;
    hash->busy_space = 0;
    hash_node_t * hash_array = malloc(sizeof(hash_node_t) * hash->length);
    //inicializo todos los nodos en EMPTY.
    for(int i = 0; i< hash->length ; i++){
        hash_array[i]->state = EMPTY;
    }
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {

    char * key_copy = malloc(sizeof(char[strlen(clave)]));
    key_copy = strcpy(clave);

    //yo no haria ninguna copia ... guardaria el dato con *dato.

    int hashed_key = hash_function(key_copy);

    for(int i = hashed_key ; hashed_key < hash->length; i++) {
        if(hash->hash_array[i]->state == EMPTY) {
            hash->hash_array[i]->key = key_copy;
            hash->hash_array[i]->value = dato; //*dato
            hash->hash_array[i]->state = BUSY;
        }
        if(hash->hash_array[i]->state == BUSY && strcmp(clave,hash->hash_array[i]->key) == 0 ) {
            hash->hash_array[i]->value = dato;
        }
    }
}

size_t hash_cantidad(const hash_t *hash){
    return hash->busy_space;
}

void *hash_obtener(const hash_t *hash, const char *clave){ }

void *hash_borrar(hash_t *hash, const char *clave){ }

bool hash_pertenece(const hash_t *hash, const char *clave){ }

void hash_destruir(hash_t *hash){ }
