#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//cita 1. red do entera, i vraca pokazivac na taj red 
char* readLine() {
	char* string = NULL, * cpystring = NULL, c;
	int i = 0;
	int size = 0, index=0;

	while (1) {
		c = getchar();
		if (c == '\n') break;
		if (size <= index) {
			size += sizeof(char);
			cpystring = realloc(string, size);
			if (!cpystring) {
				printf("MEM_GRESKA");
				/*free(string);
				string = NULL;
				break;*/
				exit(0);
			}
			string = cpystring;
		}
		string[index++] = c;
	}
	cpystring = realloc(string, size + 1);
	if (!cpystring) {
		printf("MEM_GRESKA");
		exit(0);
	}
	string = cpystring;
	string[index] = '\0';
	free(cpystring);
	if (index == 0) return NULL;
	return string;
}
//podela

//cita parove stringova i emojia, preko n broj redova
//char** readlines(int* n) {
//	char** reci = NULL, **pomreci = NULL, c;
//	int startreda = 1, i = 0;
//	int brReciVel = 0, size = 0, dvaN = 0;
//	/*while (1) {
//		while (1) {
//			c = getchar();
//			if (c == '\n') {
//				dvaN++;
//				if (dvaN == 2) break;
//				else continue;
//			}
//			if (size <= index) {
//				brReci += sizeof(char*);
//				size += sizeof(char);
//				pomreci = realloc(reci, size);
//				if (!pomreci) {
//					printf("MEM_GRESKA");
//					exit(0);
//				}
//				reci = pomreci;
//			}
//			pomreci[index++] = c;
//		}
//	}*/
//	/*while(1) {
//		c = getchar();
//		if (c == '\n') break;
//		if (startreda) {
//
//			startreda = 0;
//		}
//
//
//	}*/
//	while (1) {
//		brReciVel += sizeof(char*);
//		pomreci = realloc(reci, brReciVel);
//		if (!pomreci) {
//			printf("MEM_GRESKA");
//			exit(0);
//		}
//		reci = pomreci;
//		reci[i] = readLine();
//		if (reci[i] == NULL) goto kraj;
//		i++;
//		brReciVel++;
//	}
//	n = i;
//kraj:return reci;
//
//}

char* changeEmoticons(char* string, char** values, int n) {

}

int main() {
	char* string1, **mat;
	int brUnVr;
	string1 = readLine();
	if (string1 ==NULL) {
		printf("GRESKA\n");
		free(string1);
		return 0;
	}
	/*mat = readlines(&brUnVr);
	for (int i = 0; i < strlen(mat); i++) {
		printf("%s\n", mat[i]);
	}*/
	printf("%s\n", string1);
	free(string1);
	return 0;
}