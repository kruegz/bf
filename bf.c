#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
	FILE *fr, *fw;

	if (argc < 2)
	{
		printf("%s\n", "Usage:\t./bf filename");
		printf("\t%s\n", "filename: A text file containing brainfuck code.");
		exit(1);
	}

	char const * file = argv[1];

	// Try to load file data
	fr = fopen(file, "r");
	fw = fopen("out.c", "w");

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

	fprintf(fw,"#include \"stdio.h\"\n\n");
	fprintf(fw,"int main()\n{\n");
	fprintf(fw,"char array[30000] = {0};\nchar *ptr=array;\n");

	char c;
	while (!feof(fr))
	{
		c = getc(fr);
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

	fprintf(fw, "return 0;\n}\n");

	fclose(fw);
	fclose(fr);

	printf("%s\n", "File successfully written to out.c");

	return 0;
}