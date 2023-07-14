#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define R 6371.00

//23_dirA.txt 23_dirB.txt
//sve funcije u .c, a prototipove u .h
//proveravaj greske ARG_GRESKA, MEM_GRESKA, DAT_GRESKA


typedef struct polje {
	int brStajalista;
	char nazivStajalista[257];
	double lon;
	double lat;
	int zona;

}Polje;

typedef struct elem {
	Polje* podaci;
	struct elem* sledeci;
	struct elem* prethodni;

} Elem;

double rastojanje(double lat1, double lat2, double lon1, double lon2) {
	double t1, t2, d;

	t1 = pow(sin(((lat1 * 3.14) / 180 - (lat2 * 3.14) / 180) / 2), 2);
	t2 = pow(sin(((lon1 * 3.14) / 180 - (lon2 * 3.14) / 180) / 2), 2);
	d = 2 * R * asin(sqrt(t1 + t2 * cos((lat1 * 3.14) / 180) * cos((lat2 * 3.14) / 180)));
	return d;
}

//fja koja cita podatke o stajalistu iz fajla pa u polje, null ako ne ucita
Polje * ucitaj(FILE * fajl) {
	char c;
	char pom1[257];
	char* pom2="%d!%[^!]!%lf!%lf!%d\n";
	Polje* A;
	A = calloc(1, sizeof(Polje));

	//pom1 = A->nazivStajalista;
	if (fscanf(fajl, pom2, &A->brStajalista, pom1, &A->lon, &A->lat, &A->zona) == 6) {
			return A;
	}
	else {
		free(A);
		return NULL;
	}
	

	/*while ((c = fgetc(fajl)) != '!') {
		if (c == EOF) break;
		*pom1++ = c;
	}
	if (c == EOF) {
		free(A);
		return NULL;
	}
	*pom1 = '\0';

	fscanf(fajl, "%lf", &A->lat);
	fgetc(fajl);

	fscanf(fajl, "%lf", &A->lon);
	fgetc(fajl);

	fscanf(fajl, "%d", &A->zona);*/

	
}

//fje iz polja u listu, svaki smer svoju
Elem* formiraj(FILE * fajl) {
	Elem* prvi = NULL;
	Elem* zadnji = NULL;

	while (1) {
		Polje* A = ucitaj(fajl);
		if (A == NULL) return prvi;

		Elem * elem = calloc(1, sizeof(Elem));
		//elem->podaci = A;
		elem->podaci = calloc(1, sizeof(Polje));
		memcpy(elem->podaci, A, sizeof(Polje));

		elem->sledeci = NULL;

		if (prvi == NULL) {
			elem->prethodni = NULL;
		}
		else {
			elem->prethodni = zadnji;
		}

		if (zadnji == NULL) {
			prvi = elem;
		}
		else {
			zadnji->sledeci = elem;
		}
		zadnji = elem;
	
	
	
		free(A);
	}
	return prvi;

}

//od dve liste, formira listu sa razdaljinama i imenima
Elem* nova(Elem * prviA, Elem * prviB) {
	Elem* novPrvi = NULL, * novZadnji = NULL, * elem = NULL;
	for (Elem* i = prviA; i != NULL; i = i->sledeci) {
		for (Elem* j = prviB; j != NULL; j = j->sledeci) {
			if (!strcmp(i->podaci->nazivStajalista, j->podaci->nazivStajalista)) {
				elem = calloc(1, sizeof(Elem));
				//printf("%s\n",i->podaci->nazivStajalista);
				elem->podaci = calloc(1, sizeof(Polje));
				strcpy(elem->podaci->nazivStajalista, i->podaci->nazivStajalista);
				elem->podaci->zona = i->podaci->zona;
				elem->podaci->lon = rastojanje(i->podaci->lat, j->podaci->lat, i->podaci->lon, j->podaci->lon);

				elem->sledeci = NULL;

				if (novPrvi == NULL) {
					elem->prethodni = NULL;
				}
				else {
					elem->prethodni = novZadnji;
				}

				if (novZadnji == NULL) {
					novPrvi = elem;
				}
				else {
					novZadnji->sledeci = elem;
				}
				novZadnji = elem;
			}

		}

	}
	return novPrvi;
}
//formiranje izlazne datoteke 23_station.txt
//po formatu naziv stajalista!udaljenost!zona, stajalista sorted
void ispisi(Elem * prvi, char* ime) {
	char pom[257];
	double d;
	int x;
	for (Elem* i = prvi; i != NULL; i = i->sledeci) {
		for (Elem* j = i; j != NULL; j = j->sledeci) {
			if (strcmp(i->podaci->nazivStajalista, j->podaci->nazivStajalista) > 0) {
				strcpy(pom, i->podaci->nazivStajalista);
				strcpy(i->podaci->nazivStajalista, j->podaci->nazivStajalista);
				strcpy(j->podaci->nazivStajalista, pom);
				d = i->podaci->lon;
				i->podaci->lon = j->podaci->lon;
				j->podaci->lon = d;
				x = i->podaci->zona;
				i->podaci->zona = j->podaci->zona;
				j->podaci->zona = x;

			}

		}

	}
	FILE* out = fopen(ime, "w");
	for (Elem* k = prvi; k != NULL; k = k->sledeci) {
		fprintf(out, "%s!%.2lf!%d\n", k->podaci->nazivStajalista, k->podaci->lon, k->podaci->zona);


	}

	fclose(out);

}
void printuj(Elem * prvi) {
	for (Elem* trenutni = prvi; trenutni != NULL; trenutni = trenutni->sledeci) {
		printf("%s \n", trenutni->podaci->nazivStajalista);
	}

}

//fja za oslobadjanje mem
void oslobodi(Elem * prvi) {
	Elem* trenutni = prvi;
	while (trenutni != NULL) {
		Elem* stari = trenutni;
		trenutni->prethodni = NULL;
		free(trenutni->podaci);
		trenutni = trenutni->sledeci;
		free(stari);

	}
}

int main(int argc, char** argv) {
	int i = 1;
	if (argc <= 1) {
		printf("ARG_GRESKA");
		return 0;
	}
	while (argv[i] != '\0') {
		Elem* prviHed, * drugiHed, * konacniHed;

		char s1[100] = "", s2[100] = "", s3[50] = "_dirA.txt", s4[50] = "_dirB.txt";
		strcat(s1, argv[i]); strcat(s1, s3);
		strcat(s2, argv[i]); strcat(s2, s4);

		char s5[100] = "", s6[50] = "_station.txt";
		strcat(s5, argv[i]); strcat(s5, s6);

		FILE* fajl1 = fopen(s1, "r");
		if (!fajl1) {
			printf("DAT_GRESKA");
			return(0);
		}
		FILE* fajl2 = fopen(s2, "r");
		if (!fajl2) {
			printf("DAT_GRESKA");
			return(0);
		}

		prviHed = formiraj(fajl1);
		drugiHed = formiraj(fajl2);
		//printuj(prviHed);
		//printuj(drugiHed);

		konacniHed = nova(prviHed, drugiHed);

		ispisi(konacniHed, s5);

		fclose(fajl1);
		fclose(fajl2);

		oslobodi(prviHed);
		oslobodi(drugiHed);
		oslobodi(konacniHed);


		_CrtDumpMemoryLeaks();
		i++;
	}

	return 0;
}