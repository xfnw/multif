#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    DIR* FD;
    struct dirent* in_file;
    FILE    *entry_file;
    char    buffer[BUFSIZ];
    char *line = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;
    int burst = 1;
    if (argc < 2)
    {
	    fprintf(stderr, "Error : You must specify a directory\n");
	    return 1;
    }
    if (argc >= 3)
	    burst = atoi(argv[2]);
    if (burst <= 0)
    {
	    fprintf(stderr, "Error : burst must be an integer greater than 0\n");
	    return 1;
    }

    char *directory = argv[1];
    strcat(directory, "/");
    /* Scanning the in directory */
    if (NULL == (FD = opendir (argv[1]))) 
    {
	fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));

	return 1;
    }

    while (lineSize != -1)
    {
	    while ((in_file = readdir(FD))) 
	    {

		if (!strcmp (in_file->d_name, ".") || !strcmp (in_file->d_name, ".."))
		    continue;

                char entry_path[4096];
		strcpy(entry_path,directory);
		strcat(entry_path,in_file->d_name);

		int c;
		for (c = 0; c < burst; c++) {
    			char *line = NULL;
			entry_file = fopen(entry_path, "a");
			if (entry_file == NULL)
			{
			    fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));

			    return 1;
			}

			lineSize = getline(&line, &len, stdin);
			if (lineSize == -1)
				return 0;

			fprintf(entry_file, line);

			/* When you finish with the file, close it */
			fclose(entry_file);
			free(line);
		}
	    }
	    rewinddir(FD);
    }
    return 0;
}
