#include "utils.h"
#include <stdio.h>

//Creamos la función strLen que nos permitirá contar el largo de una palabra. Para implementarla, decidimos crear un ciclo for que recorra cada posición/carácter de la palabra y con una variable llamada len fuimos sumando cada una de ellas para llegar al largo total. 
int strLen(char*src){
	int len=0;
	for (int i=0;src[i]!= '\0';i++) {
		len=len+1;
	}
	return len;
}
	
//La función strDup genera una copia de una cadena de caracteres. Tomando como entrada un puntero a una cadena de caracteres (src), calcula su longitud utilizando la función strLen para luego solicitar la memoria deseada (que sea equivalente). Así, copia caracter por caracter, mediante un ciclo, en la nueva variable d, la cual al ser retornada devolverá una copia, es decir, un puntero a la nueva cadena duplicada. 
char* strDup(char*src) {
	int largo= strLen(src);
	char*d= (char*)malloc(sizeof(char)*(largo+1));
	for(int i=0;i<=largo;i++){
		d[i]=src[i];
	}
	return d;
}

//Creamos una nueva estructura, inicializando todas sus claves/campos (first, totalkeys ,totalwords) en nulo (es decir, en 0).
struct keysPredict* keysPredictNew () {
	struct  keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));
	kt->first =0;
	kt->totalKeys = 0;
	kt->totalWords = 0;
	return kt;
	
}

//Para agregar una palabra a la estructura creada en keysPredict usamos la función keysPredictAddWord. Esta función se fijará si la palabra está vacía y sino ingresa a un ciclo while con la condición variable i menor a su largo (ya calculado con strLen). En él, recorre cada carácter, buscando su posición en la lista. Si el carácter no está presente (no existe), creamos un nuevo nodo y se agrega a la lista. En tal caso, si el carácter existe, avanza al siguiente. Si el último nodo marca el final de una palabra (end == 1) no se realiza ninguna acción adicional. De lo contrario, se duplica la palabra y se actualizan los contadores. 
void keysPredictAddWord(struct keysPredict* kt, char* word) {
    struct node* curr= kt->first;
	struct node* prev = 0; 
	int largoPalabra = strLen(word);
	int contador =0;
	int i = 0;
	
	if (largoPalabra==0){  // Si la palabra está vacía, no se realiza ninguna operación
		return;
	}

	while(i<largoPalabra){ // ciclo para recorrer cada carácter de la palabra y agregarla al trie
		if (curr==0){
			curr = addSortedNewNodeInLevel(&(curr), word[i]); 
			if (prev==0){
				kt->first=curr;  
			} 
			else{
				prev->down=curr; // Conecta el nodo previo con el nuevo nodo.
			}
			kt->totalKeys++;
		}
		else{ // Buscamos si el carácter ya existe en el nivel actual
			struct node* res=findNodeInLevel(&(curr),word[i]);
			if(res==0){ // Si no se encuentra, crea un nuevo nodo.
				struct node* vr = addSortedNewNodeInLevel(&(curr), word[i]); 
				// Conecta el nodo previo con el nuevo nodo en caso de que exista un nodo previo.
				
				if(prev!=0){
				prev->down= curr;
				}
				else{
					kt-> first = vr;
				}
				curr= findNodeInLevel(&(curr),word[i]); // Avanza al siguiente carácter.
				kt->totalKeys++;
			}
			else{
				curr=res; // Si el carácter existe, solamente avanza en el trie
				contador++;
			}
		}
		prev=curr; // Actualizamos prev al nodo actual.
		curr=curr->down; // Avanzamos al siguiente nivel de nodos 
		i++;
	}
	if (prev->end == 1 && contador == largoPalabra){ // Si la palabra ya está completa en el trie, no se agrega devueltaa
		return;
	}
	else{
		prev->word=strDup(word);
		kt->totalWords++;
		prev-> end = 1;
	}
}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {
    struct node* curr = kt->first;  
    struct node* prev = 0;
    int largoPalabra = strLen(word);  //calculamos la longitud de la palabra llamando a la funcion strLen que creamos antes
    int i = 0;
	
	if (largoPalabra==0){ // Si la palabra está vacía, no hacemos ninguna operación.
		return;
	}

    while (i <= largoPalabra && curr != 0) { // Recorremos cada carácter de la palabra en el trie hasta llegar a la última letra o hasta que no hayan coincidencias.
        struct node* res = findNodeInLevel(&(curr), word[i]);  // Busca el nodo correspondiente al carácter actual.

        if (res == 0) {
            // Si no se encuentra un nodo correspondiente, la palabra no existe en el trie
            return;
        }

        prev = res;
        curr = res->down;
        i++;
		// Avanza al siguiente nodo.
    }

	// Verifica si se llegó al nodo final de la palabra y si este nodo está marcado como el fin de una palabra.
    if (prev != 0 && prev->end == 1) {
        prev->end = 0;  
        free(prev->word);  
        prev->word = 0;  
        kt->totalWords--;  
    }
}


// Esta función busca una palabra en el árbol de predicción de teclas (keysPredict).
// La función recorre la estructura de nodos, nivel por nivel, para verificar si la palabra existe.
// Si la palabra se encuentra y está marcada como el final de una palabra válida, devuelve el nodo correspondiente, si no, decuelve 0.
struct node* keysPredictFind(struct keysPredict* kt, char* word) {
    struct node* find = kt->first;          
    int largoPalabra = strLen(word); // Calcula la longitud de la palabra llamando a la funcion strLen creada antes

	// Recorre cada carácter de la palabra en la estructura
    for (int i = 0; i < largoPalabra; i++) {
        find = findNodeInLevel(&find,word[i]); // Busca el nodo correspondiente al carácter actual.
        if (find == 0) {
            return 0; // Si el carácter no existe en la estructura de nodos, quiere decir que la palabra no está presente, entonces se retorna 0.
        }
		
		if(i != largoPalabra - 1){
			find = find->down; // Si no es el último carácter, baja al siguiente nivel de nodos
		}
    }
	

    if (find->end == 1) { // Verificamos si el nodo final representa el final de una palabra en la estructura de nodos
        return find; // devolvemos el nodo final si es una palabra válida
	}
    
    return 0;
}


void agregarPalabra(struct node* n, char** res, int *pos){ 
    if (n==0) return; // Si el nodo es nulo, no hace nada.

    if (n->end==1){ // Si el nodo actual marca el final de una palabra (marcada con end =1), se duplica la palabra y se guarda en el arreglo de resultados.
        res[(*pos)]=strDup(n->word);
        (*pos)++; // incrementamos la posición en el arreglo de resultados
    }
	// ahora llamamos recursivamente para procesar el nodo de abajo y luego el nodo siguiente
    agregarPalabra(n->down, res, pos);
    agregarPalabra(n->next, res, pos);
}

	
char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {
    struct node* n=kt->first;
    struct node* prev=0;
    char** vacio=0; //creamos un arreglo vacio para usarlo despues en uno de los casos
    int largo=strLen(partialWord);
    int i=0;
    *wordsCount=0;

    while (i<largo){ // aca recorremos cada carácter del prefijo en la estructura de nodos
        n=findNodeInLevel(&n, partialWord[i]); // busca el nodo correspondiente al carácter actual
        if (n==0){
            return vacio; // si la funcion no encuentra un nodo para el carácter actual, el prefijo no está en la estructura de nodos, entonces devuelve un arreglo vacío
        }   

        if (n->down !=0){ // avanzamos al siguiente nivel si hay nodos
            prev=n;
            n=n->down;
            i++;
        }
    }
    *wordsCount= contarPalabras(n); // Cuenta las palabras a partir del último nodo del prefijo
	int pos=0;
    
    if(prev!=0 && prev->end==1){ // Si el prefijo es una palabra válida, incrementamos el conteo de palabras
		(*wordsCount)++;
    }
	char** res= (char**)malloc(sizeof(char)*(*wordsCount));
	if (res==0){
		*wordsCount=0;
		return 0;
	}
	if(prev!=0 && prev->end==1){ // si el prefijo es una palabra, la agregamos al arreglo de resultados
		res[pos]=strDup(prev->word);
		(pos)++;
	}
    agregarPalabra(n, res, &pos);
    return res;  
}


int contarPalabras(struct node* n){ // Función auxiliar para contar todas las palabras en el "subárbol" de un nodo
	// Recursivamente cuenta palabras en los niveles descendentes y en los nodos siguientes
    if (n==0) return 0; 
    int contador=0;
    if (n->end==1){ // incrementamos el contador si el nodo actual marca el final de una palabra
         contador++;
     }
	// llamamos recursivamente para contar palabras en el nodo descendente y en el nodo siguiente
    contador+= contarPalabras(n->down);
    contador+= contarPalabras(n->next);

    return contador;
}

void keysPredictListAllRec(struct node* n, char** lista, int* contador){ //creamos la funcion recursiva
    if (n == 0) return; 
    if (n->end == 1){
        lista[*contador] = strDup(n->word); 
        (*contador)++; 
    }

    // hacemos las llamadas recursivas a la funcion 
    keysPredictListAllRec(n->down, lista, contador);
    keysPredictListAllRec(n->next, lista, contador);
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {
    if(kt==0 || kt->first == 0){ // Verifica si el trie está vacío o si el primer nodo es nulo.
        *wordsCount = 0;
        return 0;
    }
    *wordsCount = 0;
    struct node* nodo = kt->first;
    printf("wc: %d\n", *wordsCount);
    *wordsCount = contarPalabras(nodo); // Cuenta el número total de palabras en la estructura de nodos
    printf("wc: %d\n", *wordsCount);
    char** palabras = (char**) malloc((*wordsCount) * sizeof(char)); // creamos la lista
    if (palabras == 0) { // hacemos esto por si falla la memoria, nos aseguramos de que `wordsCount` sea cero y devuelva 0.
        *wordsCount = 0; 
        return 0;
    }
    int cantidad = 0; 
    keysPredictListAllRec(nodo, palabras, &cantidad); 
    return palabras;
}

void keysPredictDelete(struct keysPredict* kt) {
	if (kt == 0) return; // verificamos si el trie es nulo, en cuyo caso no hay nada que eliminar.
	borrararreglodenodos(kt->first);
	free(kt);
}

void keysPredictPrint(struct keysPredict* kt) {
	printf("--- Predict --- Keys: %i Words: %i\n", kt->totalKeys, kt->totalWords);
	keysPredictPrintAux(kt->first, 0);
	printf("---\n");
}


void keysPredictPrintAux(struct node* n, int level) {
    if(!n) return;
    struct node* current = n;
    while(current) {
        for(int i=0; i<level;i++) printf(" |   ");
        if(current->end) {
            printf("[%c]\n",current->character);
        } else  {
            printf(" %c \n",current->character);
        }
        keysPredictPrintAux(current->down, level+1);
        current = current->next;
    }
}

// FUNCIONES AUXILIARES

struct node* findNodeInLevel(struct node** list, char character) {
    struct node* p = *list; // inicializamos el puntero `p` en el inicio de la lista de nodos
    while(p != 0){ // recorremos la lista de nodos en el nivel actual
        if(p->character == character){
            return p; // devolvemos el nodo si encuentra el carácter buscado
        }
        p = p->next; // Avanza al siguiente nodo en el nivel
    }
    return 0;
}

struct node* addSortedNewNodeInLevel(struct node** list, char character) {
	struct node* nuevoNodo = (struct node*)malloc(sizeof(struct node));
    nuevoNodo->character = character;
    nuevoNodo->next = 0;
    nuevoNodo->end = 0;
    nuevoNodo->word = 0;
    nuevoNodo->down = 0;

    if (*list == 0){ // Si la lista está vacía, asigna el nuevo nodo como el primer elemento
        *list = nuevoNodo;
        return *list;
    }
    if ((*list)->character > character){ 
        nuevoNodo->next = *list;
        *list = nuevoNodo;
        return *list;
	}

    struct node* actual = *list; // Puntero para recorrer la lista.
    struct node* anterior = 0;	// Puntero para mantener la referencia al nodo anterior

    while(actual != 0 && actual->character < character){
        anterior = actual;
        actual = actual->next;
	}
	
	if (actual != 0 && actual->character == character) {
        free(nuevoNodo); 
        return *list;
    }
	
	// Inserta el nuevo nodo en la posición ordenada
    anterior->next = nuevoNodo;
    nuevoNodo->next = actual;

    return *list; 
}


void borrararreglodenodos(struct node*n){
	if(n==0){ // caso base, si el nodo es nulo, no hace nada
		return;
	}
	borrararreglodenodos(n->next); // llamamos recursivamente para liberar el siguiente nodo en el mismo nivel
	borrararreglodenodos(n->down); // Llamamos recursivamente para liberar el nodo descendente
	
	if (n->word!=0){ // liberamos la memoria de la palabra almacenada, si existe
		free(n->word);
	}
	free(n);
}	
	
void deleteArrayOfWords(char** words, int wordsCount){
	if (words==NULL){ // Si el arreglo de palabras es nulo, no hace nada
		return;
	}
	
	for (int i=0; i<wordsCount;i++){  // recorremos cada palabra en el areglo y libera su memoria
		free(words[i]);
	}
	
	free(words); // liberamos la memoria del arreglo de palabras
}
	
	

	
