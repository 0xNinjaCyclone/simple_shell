#include "shell.h"

/*will edit betty soon*/
/**
 * get_av_with_flags_helper - .
 * @token: .
 * @status: .
 * Return: .
*/

char *get_av_with_flags_helper(char *token, int status)
{
	char *var, *cmd;

	if ( !token )
		return NULL;

	if (_strcmp("$$", token) == 0)
		cmd = get_process_id();
	else if (_strcmp("$?", token) == 0)
		cmd = get_status(status);
	else if ((token[0] == '$') && (token[1]))
	{
		var = _getenv(&token[1]);
		if (var)
			cmd = _strdup(var);
		else
			cmd = _strdup("");
	}
	else
		cmd = _strdup(token);

	return (cmd);
}
/**
 * get_av_with_flags - .
 * @line: .
 * @status: .
 * Return: .
 */
char **get_av_with_flags(char *line, int status)
{
	char *line_cpy, *token, **av, *var, *cmd;
	int i = 0, j, c_count;

	handle_comments(line);
	if (line[0] == '\0')
		return (NULL);
	line_cpy = _strdup(line);
	if (line_cpy == NULL)
		return (NULL); /*can't cpy*/
	
	token = TOK_D;
	c_count = char_count(line_cpy, ' ');
	for ( ; i < (int) strlen(line_cpy); i++ ) 
		for ( j = 0; j < (int) strlen(token); j++ )
			if ( line_cpy[i] == token[j] ) {
				c_count++;
				break;
			}
			
	i ^= i;
	token = _strtok(line_cpy, TOK_D);
	
	cmd = get_av_with_flags_helper(token, status);
	if ( !cmd )
		return NULL;

	av = malloc((c_count + 1) * sizeof(char *));
	if ( !av ) {
		free( cmd );
		return NULL;
	}

	av[i++] = cmd;
	while (token != NULL)
	{
		token = _strtok(NULL, TOK_D);
		if (token != NULL)
		{
			if (_strcmp("$$", token) == 0)
				cmd = get_process_id();
			else if (_strcmp("$?", token) == 0)
				cmd = get_status(status);
			else if ((token[0] == '$') && (token[1]))
			{
				var = _getenv(&token[1]);
				if (var)
					cmd = _strdup(var);
				else
					cmd = _strdup("");
			}
			else
				cmd = _strdup(token);
			av[i++] = cmd;
		}
	}
	av[i] = NULL;
	free(line_cpy);
	return (av);
}
/**
 * exit_check - .
 * @nread: .
 * @exit_cmd: .
 * Return: void
 */
void exit_check(int nread, char *exit_cmd)
{
	if (nread == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (_strcmp(exit_cmd, "exit") == 0)
	{
		exit(0);
	}
	if (_strcmp(exit_cmd, "exit") == 0)
	{
		exit(0);
	}
}

/**
 * _getenv - .
 * @name: .
 * Return: .
 */

char *_getenv(char *name)
{
	int i = 0, j = 0;

	if (name == NULL)
		return (NULL);
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] != '=')
		{
			if (environ[i][j] != name[j])
				break;
			if (environ[i][j] == name[j] && (environ[i][j + 1] == '='))
				return (&environ[i][_strlen(name) + 1]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/**
 * char_count - .
 * @str: .
 * @c: .
 * Return: .
 */

unsigned int char_count(char *str, char c)
{
	unsigned int count = 0;

	while (*str != '\0')
	{
		if (*str != c && *(str + 1) == c)
			count++;
		str++;
	}
	return (count + 1);
}
