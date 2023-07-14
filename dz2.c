#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {

	int m, n, i, br = 0, br2 = 0;
	char** mat, c, niz[200];

	scanf_s("%d %d\n", &m, &n);
	if (m != n || m < 1 || n < 1) return 0;
	mat = malloc(m * sizeof(char*));
	if (mat == NULL) { printf("MEM_GRESKA"); return 0; }
	for (i = 0; i < m; i++) {
		*(mat + i) = malloc(n * sizeof(char));
		if (*(mat + i) == NULL) { printf("MEM_GRESKA"); return 0; }
	}

	while (1) {
		for (i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				scanf_s("%c", *(mat + i) + j);
				getchar();
			}
		}

		for (i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				c = j != n - 1 ? ' ' : '\n';
				printf("%c%c", *(*(mat + i) + j), c);
			}

		printf("HORIZONTALNO\n");
		for (i = 0; i < m; i++) {
			br = 0;
			for (int j = 0; j < n; j++) {
				if (*(*(mat + i) + j) == '*' || *(*(mat + i) + j) == '_') {
					if (br == 0) continue;

					br2 = 0;
					for (int k = 0; k < br; k++) {
						if (*(niz + k) != *(niz + br - k - 1)) {
							br2++;
							break;
						}
					}

					if (br2 == 0) {
						for (int n = 0; n < br; n++) {
							printf("%c", *(niz + n));
							if (n == br - 1) putchar('\n');
						}
					}

					br = 0;
				}
				else {
					niz[br] = *(*(mat + i) + j);
					br++;
				}
			}
			if (br == 0) continue;
			br2 = 0;
			for (int k = 0; k < br; k++) {
				if (niz[k] != niz[br - k - 1]) {
					br2++;
					break;
				}
			}

			if (br2 == 0) {
				for (int n = 0; n < br; n++) {
					printf("%c", niz[n]);
					if (n == br - 1) putchar('\n');
				}
			}
		}

		printf("VERTIKALNO\n");
		for (int j = 0; j < n; j++) {
			br = 0;
			for (i = 0; i < m; i++) {

				if (*(*(mat + i) + j) == '*' || *(*(mat + i) + j) == '_') {
					if (br == 0) continue;

					br2 = 0;
					for (int k = 0; k < br; k++) {
						if (*(niz + k) != *(niz + br - k - 1)) {
							br2++;
							break;
						}
					}

					if (br2 == 0) {
						for (int n = 0; n < br; n++) {
							printf("%c", *(niz + n));
							if (n == br - 1) putchar('\n');
						}
					}

					br = 0;
				}
				else {
					niz[br] = *(*(mat + i) + j);
					br++;
				}
			}

			if (br == 0) continue;
			br2 = 0;
			for (int k = 0; k < br; k++) {
				if (niz[k] != niz[br - k - 1]) {
					br2++;
					break;
				}
			}

			if (br2 == 0) {
				for (int n = 0; n < br; n++) {
					printf("%c", niz[n]);
					if (n == br - 1) putchar('\n');
				}
			}
		}

		printf("DIJAGONALNO\n");
		//glavna
		br = 0;
		for (int j = 0; j < n; j++) {
			if (*(*(mat + j) + j) == '*' || *(*(mat + j) + j) == '_') {
				if (br == 0) continue;

				br2 = 0;
				for (int k = 0; k < br; k++) {
					if (*(niz + k) != *(niz + br - k - 1)) {
						br2++;
						break;
					}
				}

				if (br2 == 0) {
					for (int n = 0; n < br; n++) {
						printf("%c", *(niz + n));
						if (n == br - 1) putchar('\n');
					}
				}

				br = 0;
			}
			else {
				niz[br] = *(*(mat + j) + j);
				br++;
			}
		}

		if (br == 0) goto l1 ;
			br2 = 0;
			for (int k = 0; k < br; k++) {
				if (niz[k] != niz[br - k - 1]) {
					br2++;
					break;
				}
			}

			l1:if (br2 == 0) {
				for (int n = 0; n < br; n++) {
					printf("%c", niz[n]);
					if (n == br - 1) printf("\n");
				}
			}
		
		//sporedna
		br = 0;
		for (int s = 0; s < n; s++) {
			if (*(*(mat + n - s - 1) + s) == '*' || *(*(mat + n - s - 1) + s) == '_') {
				if (br == 0) continue;

				br2 = 0;
				for (int k = 0; k < br; k++) {
					if (*(niz + k) != *(niz + br - k - 1)) {
						br2++;
						break;
					}}

				if (br2 == 0) {
					for (int n = 0; n < br; n++) {
						printf("%c", *(niz + n));
						if (n == br - 1) putchar('\n');
					}}

				br = 0;
			}
			else {
				niz[br] = *(*(mat + n - s - 1) + s);
				br++;
				}

		}
		if (br == 0) goto l2;
			br2 = 0;
			for (int k = 0; k < br; k++) {
				if (niz[k] != niz[br - k - 1]) {
					br2++;
					break;
				}
			}

			l2:if (br2 == 0) {
				for (int n = 0; n < br; n++) {
					printf("%c", niz[n]);
					if (n == br - 1) putchar('\n');
				}
			}
		

		break;
	}

	for (i = 0; i < m; i++)
		free(*(mat + i));
	free(mat);

	return 0;
}