#include "shell.h"

/*
    betty
*/
void check_file(char *file)
{
    struct stat fileStat;
    
    
    if (stat(file, &fileStat) == 0) {
        printf("File Size: %ld bytes\n", fileStat.st_size);
        printf("File Permissions: %o\n", fileStat.st_mode);
        printf("File Inode: %lu\n", fileStat.st_ino);
        

    
        if (S_ISREG(fileStat.st_mode)) {
            printf("File is a regular file.\n");
        }

        if (S_ISDIR(fileStat.st_mode)) {
            printf("File is a directory.\n");
        }
    } else {
        printf("Failed to retrieve file information.\n");
    }
}

char *get_command_from_file(char *file)
{
    return file;
}

char **get_commands(int mode, char *file_name)
{
    char ** lines;
    if(mode == NON_INTERACTIVE_PIPED)
    {
        lines = piped_non_interactive();
    }
    
    else if (mode == NON_INTERACTIVE_FILE)
    {

        lines = file_non_interactive(file_name);
    }
	return lines;
}


char **piped_non_interactive()
{
    char b[2048], *text, **lines;
    ssize_t bytesRead;
    size_t totalchar = 0;
    while ((bytesRead = read(STDIN_FILENO, b, 2048)) > 0) 
    {
        totalchar += bytesRead;
    }
    if (bytesRead == -1) 
    {
        perror("read");
        exit(ERROR);
    }
    b[totalchar - 1] = '\0';
    text = malloc(sizeof(char) * (totalchar));
    if(!text)
        return (NULL);
    
    text = _strdup(b);
    if(text)
        lines = text_to_vector(text);
    return (lines);
}

char **text_to_vector(char *text)
{
    char *token, *cmd, *text_cpy;
    char **lines;
    int i = 0;
    unsigned int c_count;
    
    text_cpy = _strdup(text);
    if (text_cpy == NULL)
        return (NULL);
    
    
    c_count = char_count(text_cpy, '\n');
    lines = malloc(c_count * sizeof(char *));
    token = strtok(text_cpy, "\n");
    cmd = _strdup(token);
    lines[i++] = cmd;
    while (token != NULL)
    {
        token = strtok(NULL, "\n");
        if (token != NULL)
        {
            cmd = _strdup(token);
            lines[i++] = cmd;
        }

    }
    free(text);
    return (lines);


}
char **file_non_interactive(char *file_name)
{
    struct stat fileStat;
    char *text, **lines;
    int file_descriptor;
    size_t letters;

    if (stat(file_name, &fileStat) != -1) 
    {
        if (S_ISREG(fileStat.st_mode)) 
        {
            
             file_descriptor = open(file_name, O_RDONLY);
             if (file_descriptor  == -1)
		        exit(ERROR);
            text = malloc((fileStat.st_size + 1) * sizeof(char));
            if(!text)
                return (NULL);
            letters = read(file_descriptor, text, fileStat.st_size);
            if((int) letters == -1)
            {
                perror("read");
            }
            close(file_descriptor);
            
            text[letters - 1] = '\0';
            if(text)
            lines = text_to_vector(text);
            return (lines);
        } 
        else 
        {   
            printf("The file is not a regular file\n");
        }
    }
    else
    {
        /*todo print error*/
        printf("The file is a regular file\n");
        exit(ERROR);
    }

    return (NULL);
}
