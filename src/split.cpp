#include "Lincludes.hpp"

void free_2d(char **arr)
{
	int i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	arr = NULL;
}

char *remove_newline(char *str)
{
	int len = strlen(str);
	char *nova = (char *)malloc(sizeof(len) + 1);
	int i = -1;
	int j = -1;
	while (str[++i])
	{
		if (str[i] != '\n' && str[i] != '\r')
			nova[++j] = str[i];
	}
	while (++j <= len)
		nova[j] = '\0';
	return (nova);
}

int	string_counter(char *str, char c)
{
	int	i;
	int	ver;
	int	count;

	i = 0;
	ver = 1;
	count = 0;
	while (str[i])
	{
		while (str[i] != '\0' && str[i] == c)
		{
			i++;
			ver = 1;
		}
		if (str[i] != '\0' && str[i] != c && ver == 1)
		{
			i++;
			count++;
			ver = 0;
		}
		else if (str[i] != c && str[i] != 0)
			i++;
	}
	return (count);
}

char	*word(char *str, int *ptr_i, char c)
{
	int		i;
	int		n;
	int		k;
	char	*word;

	i = *ptr_i;
	n = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
		n++;
	}
	word = (char *)malloc(sizeof(char) * (n + 1));
	if (!word)
		return (NULL);
	i = i - n;
	k = 0;
	while (str[i] != '\0' && str[i] != c)
		word[k++] = str[i++];
	word[k] = '\0';
	*ptr_i = i;
	return (word);
}

char	**ft_split(char *s, char c)
{
	int		count;
	int		i;
	int		w;
	char	**arr;

	count = string_counter(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr[count] = NULL;
	i = 0;
	w = 0;
	while (w < count && s[i])
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			arr[w] = word(s, &i, c);
			w++;
		}
		i++;
	}
	std::cout << "SPLIT 4"  << std::endl;
	return (arr);
}