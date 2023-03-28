#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool goodBoy = false;

int main(int argc, char** argv) {
	#ifdef __unix__
		goodBoy = true;
	#endif
	
	if (!goodBoy) {
		printf("use unix dumbass\n");
		exit(-1);
	}

	++argv, --argc;
	unsigned int randomValue;
	FILE* fptr;

	fptr = fopen("/dev/random", "r");
	fread(&randomValue, sizeof(randomValue), 1, fptr);
	fclose(fptr);

	if (argc == 1) {
		randomValue %= atoi(argv[0]) + 1;
	}
	if (argc == 2) {
		if (atoi(argv[1]) < atoi(argv[0])) {
			printf("fuck off\n");
			return 0;
		}
		randomValue %= (atoi(argv[1]) - atoi(argv[0])) + 1;
		randomValue += atoi(argv[0]);
	}
	printf("%u\n", randomValue);

	return 0;
}

