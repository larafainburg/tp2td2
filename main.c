#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
void predictAndPrintAll(struct keysPredict* kt, char* partialWord ) {
	char** words;
	int wordsCount;
	words = keysPredictRun(kt, partialWord, &wordsCount);
	printf("Predicts: %s = ", partialWord);
	for(int i=0; i<wordsCount; i++) {
		printf("%s,", words[i]);
	}
	printf("\n");
	deleteArrayOfWords(words, wordsCount);
}


void findAndPrintAll(struct keysPredict* kt, char* word ) {
	struct node* result = keysPredictFind(kt, word);
	printf("Find: %s = %i\n", word, result!=0);
}


int main() {
	//conjunto de casos de test que deben implementar:
	
	// caso de test de la funcion strLen
	int len = strLen("");
	printf("strDup(\"\") -> \"%i\"\n", len);
	printf("\n");
	
	int lenDos = strLen("a");
	printf("strDup(\"a\") -> \"%i\"\n", lenDos);
	printf("\n");
	
	int lenTres = strLen("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	printf("strDup(\"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\") -> \"%i\"\n", lenTres);
	printf("\n");
	
	
	// caso de test de la funcion strDup
	char* dup = strDup("");
	printf("strDup(\"\") -> \"%s\"\n", dup);
	free(dup);
	printf("\n");
	
	char* dupUno= strDup("a");
	printf("strDup(\"a\") -> \"%s\"\n", dupUno);
	free(dupUno);
	printf("\n");
	
	char* dupDos = strDup("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	printf("strDup(\"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\") -> \"%s\"\n", dupDos);
	free(dupDos);
	printf("\n");
	
	
	// keysPredict - crear un diccionario
	// CASOS GRANDES: DICCIONARIO DE 100 PALABRAS 
	struct keysPredict* diccionario = keysPredictNew();
	
	keysPredictAddWord(diccionario, "bosque");
	keysPredictAddWord(diccionario, "guitarra");
	keysPredictAddWord(diccionario, "montana"); 
	keysPredictAddWord(diccionario, "sol");
	keysPredictAddWord(diccionario, "tren");
	keysPredictAddWord(diccionario, "puerta");
	keysPredictAddWord(diccionario, "rio");
	keysPredictAddWord(diccionario, "cielo");
	keysPredictAddWord(diccionario, "laguna");
	keysPredictAddWord(diccionario, "nube");
	keysPredictAddWord(diccionario, "actuar");
	keysPredictAddWord(diccionario, "arena");
	keysPredictAddWord(diccionario, "camino");
	keysPredictAddWord(diccionario, "arbol"); 
	keysPredictAddWord(diccionario, "roca");
	keysPredictAddWord(diccionario, "playa");
	keysPredictAddWord(diccionario, "ciudad");
	keysPredictAddWord(diccionario, "cerveza");
	keysPredictAddWord(diccionario, "fuego");
	keysPredictAddWord(diccionario, "madera");
	keysPredictAddWord(diccionario, "noche");
	keysPredictAddWord(diccionario, "estrella");
	keysPredictAddWord(diccionario, "espacio");
	keysPredictAddWord(diccionario, "galaxia");
	keysPredictAddWord(diccionario, "planeta");
	keysPredictAddWord(diccionario, "luz");
	keysPredictAddWord(diccionario, "libro");
	keysPredictAddWord(diccionario, "ventana");
	keysPredictAddWord(diccionario, "mariposa");
	keysPredictAddWord(diccionario, "piedra");
	keysPredictAddWord(diccionario, "relampago"); 
	keysPredictAddWord(diccionario, "trueno");
	keysPredictAddWord(diccionario, "camisa");
	keysPredictAddWord(diccionario, "botella");
	keysPredictAddWord(diccionario, "barco");
	keysPredictAddWord(diccionario, "avion");
	keysPredictAddWord(diccionario, "nieve");
	keysPredictAddWord(diccionario, "helicoptero");
	keysPredictAddWord(diccionario, "peces");
	keysPredictAddWord(diccionario, "viento");
	keysPredictAddWord(diccionario, "bici");
	keysPredictAddWord(diccionario, "lagarto");
	keysPredictAddWord(diccionario, "cometa");
	keysPredictAddWord(diccionario, "tierra");
	keysPredictAddWord(diccionario, "mapa");
	keysPredictAddWord(diccionario, "musica"); 
	keysPredictAddWord(diccionario, "danza");
	keysPredictAddWord(diccionario, "paloma");
	keysPredictAddWord(diccionario, "luna");
	keysPredictAddWord(diccionario, "solsticio");
	keysPredictAddWord(diccionario, "calle");
	keysPredictAddWord(diccionario, "amigo");
	keysPredictAddWord(diccionario, "desierto");
	keysPredictAddWord(diccionario, "hielo");
	keysPredictAddWord(diccionario, "puente");
	keysPredictAddWord(diccionario, "cueva");
	keysPredictAddWord(diccionario, "espejo");
	keysPredictAddWord(diccionario, "murcielago"); 
	keysPredictAddWord(diccionario, "hoja");
	keysPredictAddWord(diccionario, "flor");
	keysPredictAddWord(diccionario, "hierba");
	keysPredictAddWord(diccionario, "monte");
	keysPredictAddWord(diccionario, "diamante");
	keysPredictAddWord(diccionario, "catarata"); 
	keysPredictAddWord(diccionario, "costa"); 
	keysPredictAddWord(diccionario, "amapola");
	keysPredictAddWord(diccionario, "roble");
	keysPredictAddWord(diccionario, "puno"); 
	keysPredictAddWord(diccionario, "desierto"); 
	keysPredictAddWord(diccionario, "piedra"); 
	keysPredictAddWord(diccionario, "musgo");
	keysPredictAddWord(diccionario, "mar");
	keysPredictAddWord(diccionario, "nave");
	keysPredictAddWord(diccionario, "constelacion"); 
	keysPredictAddWord(diccionario, "universo"); 
	keysPredictAddWord(diccionario, "aurora");
	keysPredictAddWord(diccionario, "ceniza");
	keysPredictAddWord(diccionario, "isla");
	keysPredictAddWord(diccionario, "rayo"); 
	keysPredictAddWord(diccionario, "cristal");
	keysPredictAddWord(diccionario, "volcan"); 
	keysPredictAddWord(diccionario, "bruma");
	keysPredictAddWord(diccionario, "gacela");
	keysPredictAddWord(diccionario, "charco"); 
	keysPredictAddWord(diccionario, "dragon"); 
	keysPredictAddWord(diccionario, "pluma");
	keysPredictAddWord(diccionario, "vidrio");
	keysPredictAddWord(diccionario, "humo");
	keysPredictAddWord(diccionario, "duna");
	keysPredictAddWord(diccionario, "avalancha");
	keysPredictAddWord(diccionario, "pueblo");
	keysPredictAddWord(diccionario, "colina");
	keysPredictAddWord(diccionario, "llama");
	keysPredictAddWord(diccionario, "tunel"); 
	keysPredictAddWord(diccionario, "molino");
	keysPredictAddWord(diccionario, "marino");
	keysPredictAddWord(diccionario, "cascada");
	keysPredictAddWord(diccionario, "tormenta");
	keysPredictAddWord(diccionario, "relampago");
	keysPredictAddWord(diccionario, "biblioteca");
	keysPredictAddWord(diccionario, "xilofono");
	
	
	//Borrar la mitad de las palabras del diccionario.
	//copiamos las primeras 50 palabras del diccionario que creamos antes y las borramos con keysPredictRemoveWord
	keysPredictRemoveWord(diccionario, "bosque");
	keysPredictRemoveWord(diccionario, "guitarra");
	keysPredictRemoveWord(diccionario, "montana"); 
	keysPredictRemoveWord(diccionario, "sol");
	keysPredictRemoveWord(diccionario, "tren");
	keysPredictRemoveWord(diccionario, "puerta");
	keysPredictRemoveWord(diccionario, "rio");
	keysPredictRemoveWord(diccionario, "cielo");
	keysPredictRemoveWord(diccionario, "laguna");
	keysPredictRemoveWord(diccionario, "nube");
	keysPredictRemoveWord(diccionario, "arena");
	keysPredictRemoveWord(diccionario, "camino");
	keysPredictRemoveWord(diccionario, "arbol"); 
	keysPredictRemoveWord(diccionario, "roca");
	keysPredictRemoveWord(diccionario, "playa");
	keysPredictRemoveWord(diccionario, "ciudad");
	keysPredictRemoveWord(diccionario, "cerveza");
	keysPredictRemoveWord(diccionario, "fuego");
	keysPredictRemoveWord(diccionario, "madera");
	keysPredictRemoveWord(diccionario, "noche");
	keysPredictRemoveWord(diccionario, "estrella");
	keysPredictRemoveWord(diccionario, "espacio");
	keysPredictRemoveWord(diccionario, "galaxia");
	keysPredictRemoveWord(diccionario, "planeta");
	keysPredictRemoveWord(diccionario, "luz");
	keysPredictRemoveWord(diccionario, "libro");
	keysPredictRemoveWord(diccionario, "ventana");
	keysPredictRemoveWord(diccionario, "mariposa");
	keysPredictRemoveWord(diccionario, "piedra");
	keysPredictRemoveWord(diccionario, "relampago"); 
	keysPredictRemoveWord(diccionario, "trueno");
	keysPredictRemoveWord(diccionario, "camisa");
	keysPredictRemoveWord(diccionario, "botella");
	keysPredictRemoveWord(diccionario, "barco");
	keysPredictRemoveWord(diccionario, "avion");
	keysPredictRemoveWord(diccionario, "nieve");
	keysPredictRemoveWord(diccionario, "helicoptero");
	keysPredictRemoveWord(diccionario, "peces");
	keysPredictRemoveWord(diccionario, "viento");
	keysPredictRemoveWord(diccionario, "bici");
	keysPredictRemoveWord(diccionario, "lagarto");
	keysPredictRemoveWord(diccionario, "cometa");
	keysPredictRemoveWord(diccionario, "tierra");
	keysPredictRemoveWord(diccionario, "mapa");
	keysPredictRemoveWord(diccionario, "musica"); 
	keysPredictRemoveWord(diccionario, "danza");
	keysPredictRemoveWord(diccionario, "paloma");
	keysPredictRemoveWord(diccionario, "luna");
	keysPredictRemoveWord(diccionario, "solsticio");
	keysPredictRemoveWord(diccionario, "calle");
	keysPredictRemoveWord(diccionario, "amigo");
	
	keysPredictPrint(diccionario);
	

	char letras[] = "abcdefghijklmnopqrstuvwxyz";
	char p[3]; 
	p[2] = '\0'; 
	
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			p[0] = letras[i];
			p[1] = letras[j];
			predictAndPrintAll(diccionario, p); 
		}
	}
	
	// CASOS CHICOS
	struct keysPredict* kt = keysPredictNew();
	
	// Armar un diccionar con las palabras “alfajor”, “canoa”, “rinoceronte”, “casa” y “rino”
	keysPredictAddWord(kt, "alfajor");
	keysPredictAddWord(kt, "canoa");
	keysPredictAddWord(kt, "rinoceronte");
	keysPredictAddWord(kt, "casa");
	keysPredictAddWord(kt, "rino");
	
	keysPredictPrint(kt);
	
	// Borrar la palabra “canoa” y agregar la palabra “pato”
	keysPredictRemoveWord(kt, "canoa");
	keysPredictAddWord(kt, "pato");
	
	// Predecir a partir “c”, “ca”, “casa” y “casas”	
	predictAndPrintAll(kt, "c");
	predictAndPrintAll(kt, "ca");
	predictAndPrintAll(kt, "casa");
	predictAndPrintAll(kt, "casas");
	
	keysPredictPrint(kt);
	
}

	
