#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
	    fprintf(stderr, "Error : You must specify a directory\n");
	    return 1;
    }
    DIR* FD;
    struct dirent* in_file;
    FILE    *entry_file;
    char    buffer[BUFSIZ];
    char *line = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;

    char *directory = argv[1];
    strcat(directory, "/");

    //lineSize = getline(&line, &len, stdin);
    while (lineSize != -1)
    {
	    /* Scanning the in directory */
	    if (NULL == (FD = opendir (argv[1]))) 
	    {
		fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));

		return 1;
	    }
	    while ((in_file = readdir(FD))) 
	    {

    		char *line = NULL;
		if (!strcmp (in_file->d_name, ".") || !strcmp (in_file->d_name, ".."))
		    continue;

                char entry_path[4096];
		strcpy(entry_path,directory);
		strcat(entry_path,in_file->d_name);

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
    return 0;
}
