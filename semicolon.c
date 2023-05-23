#include "shell.h"
/**
 * execute_command_with_waitpid - .
 * @path: .
 * @av: .
 * @env: .
 * Return: void
 */
void execute_command_with_waitpid(char *path, char **av, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == ERROR)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(path, av, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * handle_semicolons - .
 * @line: .
 * Return: void
 */
void handle_semicolons(char *line)
{
	char *token;
	char *args[100];
	int i;

	token = strtok(line, ";"); /*split on semicolons*/
	while (token != NULL)
	{
		args[0] = strtok(token, " ");
		i = 0;
		while (args[i] != NULL && i < 99)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (i > 0)
		{
			execute_command_with_waitpid(args[0], args, NULL);
		}

		token = strtok(NULL, ";");
	}
}

/**
 * print_error - .
 * @program_name: .
 * @counter: .
 * @command: .
 * @type_of_error: .
 * Return: void
 */

void print_error(char *program_name, int counter,
		char *command, int type_of_error)
{
	char *counter_s;

	counter_s = num_to_char(counter);
	write(STDERR_FILENO, program_name, _strlen(program_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_s, _strlen(counter_s));
	write(STDERR_FILENO, ": ", 2);
	if (type_of_error == EXIT_ERROR)
		write(STDERR_FILENO, "exit", 4);
	else
		write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);
	if (type_of_error == NOT_FOUND)
		write(STDERR_FILENO, "not found\n", 10);
	else if (type_of_error == PERMISSION_DENIED)
		write(STDERR_FILENO, "Permission denied\n", 18);
	else if (type_of_error == EXIT_ERROR)
	{
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, command, _strlen(command));
		write(STDERR_FILENO, "\n", 1);
	}
	free(counter_s);
}


/**
 * print_cant_open - .
 * @program_name: .
 * @counter: .
 * @file_name: .
 * Return: void
 */
void print_cant_open(char *program_name, int counter, char *file_name)
{

	char *counter_s;

	counter_s = num_to_char(counter);
	write(STDERR_FILENO, program_name, _strlen(program_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_s, _strlen(counter_s));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "Can't open ", 11);
	write(STDERR_FILENO, file_name, _strlen(file_name));
	write(STDERR_FILENO, "\n", 1);
}
