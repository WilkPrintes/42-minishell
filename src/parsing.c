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

int	full_size(char *ptr)
{
	int	i;
	int	size;
	int	trigger;

	i = 0;
	size = 0;
	trigger = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 || ptr[i] == 39)
		{
			size++;
			i++;
			while (ptr[i] != 34 && ptr[i] != 39)
				i++;
		}
		else if (ptr[i] == ' ')
			size++;
		i++;
	}
	return (size);
}

void	how_to_parse(char *ptr, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ito.metod = malloc(size * sizeof(int));
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 || ptr[i] == 39)
		{
			ito.metod[j++] = 1;
			i++;
			while (ptr[i] != 34 && ptr[i] != 39)
				i++;
		}
		else if (ptr[i] == ' ')
			ito.metod[j++] = 0;
		i++;
	}
}

// Até aqui funciona como planejado

char *do_parse(char **ptr, int mode)
{

	if (mode == 0)
	{

		*ptr = ft_strdup(ft_strchr(*ptr, 34));
	}
	else if (mode == 1)
	{

		*ptr = ft_strdup(ft_strchr(*ptr, 34));
	}

}

char	**slow_parsing(char *ptr, int size)
{
	int		i;
	int		j;
	char	**parsed;

	i = 0;
	j = 0;
	how_to_parse(ptr, size);
	while (size != 0)
	{
		parsed[j] = do_parse(&ptr, ito.metod[j]);
		j++;
		size--;
	}
	return (parsed);
}


int	main(void)
{
	int		i;
	int		size;
	char	*ptr;

	ptr = readline("teste: ");
	if (have_quotes(ptr) == -1)
	{ write(2, "error\n", 6); return (1);}
	else if (have_quotes(ptr) == 1)
	{
		size = full_size(ptr);
		ito.pars = malloc ((size + 1) * sizeof(char *));
		ito.pars = slow_parsing(ptr, size);
	}
	else
		ito.pars = ft_split(ptr, ' ');
	for (i=0; i != -1; i++)
	{
		if (ito.pars[i] == NULL)
			break;
		printf("%s\n", ito.pars[i]);
	}
	free_this(ito.pars);
	free(ptr);
	return (0);
}
