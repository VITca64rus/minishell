#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include<readline/history.h>
#include <unistd.h>

void ft_builtins(char *str, char **env)
{
	if (!strcmp(str, "exit"))
	{
		free(str);
		exit(0);
	}
	else if (!strncmp(str, "echo ", 5))
	{
		if (!strncmp(str, "echo -n ", 8))
			write(1, &str[8], strlen(&str[8]));
		else
		{
			write(1, &str[5], strlen(&str[5]));
			write(1, "\n", 1);
		}
	}
	else if (!strcmp(str, "env"))
	{
		while (*env)
		{
			write(1, *env, strlen(*env));
			write(1, "\n", 1);
			env++;
		}
	}
}

int main(int argc, char **argv, char **env)
{
	char	*str;

	while(1)
	{
		str = NULL;
		str = readline("\033[32mminishell> \033[0m");
		if (str)
		{
			if (*str)
				add_history(str);
			ft_builtins(str, env);
			//another operation next
			free(str);
		}
		else
			break;
	}
	write(1, "\n", 1);
}
