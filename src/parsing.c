#include "minishell.h"
#include <signal.h>

t_test ito;

void	free_this(char **str)
{
	int	i;

	i = 0;
	if (str == 0)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	have_quotes(char *ptr)
{
	int	val;
	int	i;

	val = 0;
	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 || ptr[i] == 39)
			val++;
		i++;
	}
	if (val % 2 != 0)
		return (-1);
	else if (val == 0)
		return (0);
	return (1);
}

void	fix_quotes(char *ptr)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 && trigger == 0)
			trigger = 34;
		else if (ptr[i] == 39 && trigger == 0)
			trigger = 39;
		else if (trigger != 0 && ptr[i] == 32)
			ptr[i] = 7;
		else if (ptr[i] == trigger)
			trigger = 0;
		i++;
	}
}

void	refix_quotes(char *ptr)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 && trigger == 0)
			trigger = 34;
		else if (ptr[i] == 39 && trigger == 0)
			trigger = 39;
		else if (trigger != 0 && ptr[i] == 7)
			ptr[i] = ' ';
		else if (ptr[i] == trigger)
			trigger = 0;
		i++;
	}
}

void redirect(char **pars)
{
	int	i;

	i = 0;
	while (pars[i] != NULL)
	{
		if (ft_strncmp(pars[i], ">", ft_strlen(pars[i])) == 0)
		{
			if (pars[i + 1] != NULL)
				dup2(open(pars[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777), 1);
		}
		else if (ft_strncmp(pars[i], ">>", ft_strlen(pars[i])) == 0)
		{
			if (pars[i + 1] != NULL)
				dup2(open(pars[i + 1], O_RDWR | O_CREAT | O_APPEND, 0777), 1);
		}
		else if (ft_strncmp(pars[i], "<", ft_strlen(pars[i])) == 0)
		{
			if (pars[i + 1] != NULL)
				dup2(open(pars[i + 1], O_RDONLY, 0777), 0);
		}
		i++;
	}
}

int parsing(char *ptr)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = have_quotes(ptr);
	if (quotes == -1)
		return (write(2, "error\n", 6));
	else if (quotes == 1)
		fix_quotes(ptr);
	ito.pars = ft_split(ptr, ' ');
	while (1)
	{
		if (ito.pars[i] == NULL)
			break;
		if (ft_strchr(ito.pars[i], 7) != NULL)
			refix_quotes(ito.pars[i]);
		i++;
	}
	redirect(ito.pars);
	return (0);
}
// Até aqui funciona como planejado

int	main(void)
{
	int		i;
	int		pid;
	int		size;
	char	*ptr;

	i = 0;
	ptr = readline("teste: ");
	parsing(ptr);
	pid = fork();
	if (pid == 0)
		command(getenv("PATH"), ito.pars[0]);
	else
		waitpid(pid, NULL, 0);
	free_this(ito.pars);
	free(ptr);
	return (0);
}
