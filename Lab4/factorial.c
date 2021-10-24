#include <stdio.h>

int main(int argc, char const *argv[]) {

	int n = 8;		// n!(rad 5)
	int i = 1;		// outer loop variable (rad 12)
	int k = n + 1;	// outer loop compare constant (rad 11)
	int result = 1;	// result is always 1 or above (rad 10)

	while (i != k) {		// as long as i != k we're okay (rad 15)
		i++;				// increment i (rad 16)
		int product = 0;	// initialize product to 0 (rad 17)
		int j = 1;			// initialize inner loop var (rad 19)

		while (j != i) {	// as long as j != i we're okay(rad 22)
			j++;			// increment j (rad 23)
			product += result;	// do a1 = a1 + v0 (rad 24)

		}

		result = product; //(rad 27)
	}

	printf("result == %d\n", result);

	return 0;
}
