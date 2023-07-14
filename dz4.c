#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct elem {
	char* ime;
	int hh1;
	int mm1;
	int hh2;
	int mm2;
	int min;
	struct elem* sledeci;
} Elem;

Elem* ucitaj() {
	Elem* prvi = NULL;
	Elem* poslednji = NULL;
	int i = 0, hh1, mm1, hh2, mm2, min;
	char* ime;
	ime = calloc(2000, sizeof(char));
	char c;
	while (1) {
		i = 0;
		c = getchar();
		while (1) {
			c = getchar(); if (c == '\n')break;
			ime[i] = c;
			i++;
			if (c == ' ') break;
		}
		if (c == '\n')break;
		ime[i - 1] = '\0';
		ime = realloc(ime, i * sizeof(char));

		Elem * elem = calloc(1, sizeof(Elem));
		elem->ime = malloc(strlen(ime) + 1);
		strcpy(elem->ime, ime);
		scanf("%d", &hh1); elem->hh1 = hh1;
		getchar();
		scanf("%d", &mm1);  elem->mm1 = mm1;
		getchar();
		scanf("%d", &hh2);  elem->hh2 = hh2;
		getchar();
		scanf("%d", &mm2);  elem->mm2 = mm2;
		getchar();
		scanf("%d", &min);  elem->min = min;
		elem->sledeci = NULL;

		if (poslednji == NULL) {
			prvi = elem;
		}
		else {
			poslednji->sledeci = elem;
		}
		poslednji = elem;

	}
	free(ime);
	return prvi;
}

void ispisi(Elem * prvi) {
	for (Elem* trenutni = prvi; trenutni != NULL; trenutni = trenutni->sledeci) {
		printf("%s ", trenutni->ime);
		printf("%02d:%02d-%02d:%02d %d\n", trenutni->hh1, trenutni->mm1, trenutni->hh2, trenutni->mm2, trenutni->min);
	}

}

Elem* napraviNovu(Elem * prvi, int pocetak) {
	Elem* head = NULL;
	Elem* last = NULL;
	int i = 0, hh1, mm1, hh2, mm2, min, dol;

	for (Elem* trenutni = prvi; trenutni != NULL; trenutni = trenutni->sledeci) {
		int x1 = pocetak * 60, x2 = (pocetak + 8) * 60, x3 = (trenutni->hh1) * 60 + trenutni->mm1, x4 = (trenutni->hh2) * 60 + trenutni->mm2, duz = trenutni->min;
		if (x1 >= x3 && x4 >= x2 && x4 - x1 >= duz) {
			//1.
			Elem* nova = calloc(1, sizeof(Elem));
			nova->ime = trenutni->ime;
			nova->hh1 = trenutni->hh1;
			nova->hh2 = trenutni->hh2;
			nova->mm1 = trenutni->mm1;
			nova->mm2 = trenutni->mm2;
			nova->min = trenutni->min;

			nova->sledeci = NULL;
			if (last == NULL) {
				head = nova;
			}
			else {
				last->sledeci = nova;
			}
			last = nova;
			continue;
		}
		if (x1 >= x3 && x2 >= x4 && x4 - x1 >= duz) {
			//2.
			Elem* nova = calloc(1, sizeof(Elem));
			nova->ime = trenutni->ime;
			nova->hh1 = trenutni->hh1;
			nova->hh2 = trenutni->hh2;
			nova->mm1 = trenutni->mm1;
			nova->mm2 = trenutni->mm2;
			nova->min = trenutni->min;

			nova->sledeci = NULL;
			if (last == NULL) {
				head = nova;
			}
			else {
				last->sledeci = nova;
			}
			last = nova;
			continue;
		}
		if (x3 >= x1 && x2 >= x4 && x4 - x3 >= duz) {
			//3.
			Elem* nova = calloc(1, sizeof(Elem));
			nova->ime = trenutni->ime;
			nova->hh1 = trenutni->hh1;
			nova->hh2 = trenutni->hh2;
			nova->mm1 = trenutni->mm1;
			nova->mm2 = trenutni->mm2;
			nova->min = trenutni->min;

			nova->sledeci = NULL;
			if (last == NULL) {
				head = nova;
			}
			else {
				last->sledeci = nova;
			}
			last = nova;
			continue;
		}
		if (x3 >= x1 && x4 >= x2 && x2 - x3 >= duz) {
			//4.
			Elem* nova = calloc(1, sizeof(Elem));
			nova->ime = trenutni->ime;
			nova->hh1 = trenutni->hh1;
			nova->hh2 = trenutni->hh2;
			nova->mm1 = trenutni->mm1;
			nova->mm2 = trenutni->mm2;
			nova->min = trenutni->min;

			nova->sledeci = NULL;
			if (last == NULL) {
				head = nova;
			}
			else {
				last->sledeci = nova;
			}
			last = nova;
			continue;
		}

	}

	return head;
}

void oslobodi(Elem * prvi) {
	Elem* trenutni = prvi;
	while (trenutni != NULL) {
		Elem* stari = trenutni;
		trenutni = trenutni->sledeci;
		free(stari->ime);
		free(stari);
	}

}


int main() {
	int trajanje;
	scanf("%d", &trajanje);
	Elem* prvi = ucitaj();

	ispisi(prvi);

	Elem* drugi = napraviNovu(prvi, trajanje);

	ispisi(drugi);

	oslobodi(prvi);
	oslobodi(drugi);
	//printf("%d\n", dol);
	//printf("%s\n", ime);
	//printf("%d:%02d-%d:%02d %d", hh1, mm1, hh2, mm2, min);
	return 0;
}