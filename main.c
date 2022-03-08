//natasha
#include <unistd.h>
#include <term.h>
#include <string.h>
#include <stdio.h>
#include "libft/libft.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}


int	main(int argc, char **argv, char **env)
{
	char			str[200];
	int				len;
	struct termios	term;
	char			*term_name = "xterm-256color"; //FIX_me for another term (env TERM=)

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);

	tgetent(0, term_name);
	tputs(save_cursor, 1, ft_putchar);
	while (strcmp(str, "\4"))
	{
		do
		{
			len = read(0, str, 100);
			str[len] = 0;
			if (!strcmp(str, "\e[A"))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				printf("previous\n");
			}
			else if (!strcmp(str, "\e[B"))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar); // FIX_ME - potential forbiden tigetstr
				printf("next\n");
			}
			else if (!strcmp(str, key_backspace) && !strcmp(str, "\177"))
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar); // FIX_ME - potential forbiden tgetstr
			}
			else
				write(1, str, len);
		} while (strcmp(str, "\n") && strcmp(str, "\4"));
	}
    return(0);
}
