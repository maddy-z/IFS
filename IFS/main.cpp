#include <cstdio>
#include <cstdlib>

#include "IFS.h"
#include "image.h"
#include "vector.h"
#include "matrix.h"

// Global Arguments Got by argv in the main.

char *input_file = NULL;
char *output_file = NULL;
char *depth_file = NULL;

int width = 100;
int height = 100;
int iters = 0;
int points = 0;

// ------------------------------------------------------
// ------------------------------------------------------

int main(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) 
	{
		if (!strcmp(argv[i], "-input")) {
			i++; assert (i < argc);
			input_file = argv[i];
		} 
		else if (!strcmp(argv[i], "-size")) {
			i++; assert (i < argc);
			width = atoi(argv[i]);
			i++;
			assert (i < argc);
			height = atoi(argv[i]);
		} 
		else if (!strcmp(argv[i], "-output")) {
			i++; assert (i < argc);
			output_file = argv[i];
		}
		else if (!strcmp(argv[i], "-iters")) {
			i++; assert (i < argc); 
			iters = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-points")) {
			i++; assert (i < argc);
			points = atoi(argv[i]);
		}
		else {
			printf ("whoops error with command line argument %d: '%s'\n", i, argv[i]);
			assert(0);
		}
	}

	Image image(width, height);

	IFS demo(input_file);
	demo.printIFS();
	demo.fractalRendering(image, points, iters, output_file);

	// system("pause");
	return 0;
}