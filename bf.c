#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
	// Setup write and read files
	FILE *fr, *fw;

	// Check arguments
	if (argc < 2)
	{
		printf("%s\n", "Usage:\t./bf filename");
		printf("\t%s\n", "filename: A text file containing brainfuck code.");
		exit(1);
	}

	// Get the filename
	char const * file = argv[1];

	// Try to load file data
	fr = fopen(file, "r");
	fw = fopen("out.c", "w");

	// Check file
	if (fr == NULL)
	{
		printf("%s\n", "Invalid file name.");
		exit(1);
	}
	if (fw == NULL)
	{
		printf("%s\n", "Error loading write file.");
		exit(1);
	}

	// Write headers
	fprintf(fw,"#include \"stdio.h\"\n\n");
	fprintf(fw,"int main()\n{\n");
	fprintf(fw,"char array[30000] = {0};\nchar *ptr=array;\n");
	
	// Get characters from the input file
	char c;
	while (!feof(fr))
	{
		c = getc(fr);
		// Write the appropriate statement to the file
		switch (c)
		{
			case '>':
				fprintf(fw, "++ptr;\n");
				break;
			case '<':
				fprintf(fw, "--ptr;\n");
				break;
			case '+':
				fprintf(fw, "++*ptr;\n");
				break;
			case '-':
				fprintf(fw, "--*ptr;\n");
				break;
			case '.':
				fprintf(fw, "putchar(*ptr);\n");
				break;
			case ',':
				fprintf(fw, "*ptr = getchar();\n");
				break;
			case '[':
				fprintf(fw, "while (*ptr)\n{\n");
				break;
			case ']':
				fprintf(fw, "}\n");
				break;
		}
	}

	// Write the closing statments
	fprintf(fw, "return 0;\n}\n");

	// Close the files
	fclose(fw);
	fclose(fr);

	// Print confirmation
	printf("%s\n", "File successfully written to out.c");

	return 0;
}
