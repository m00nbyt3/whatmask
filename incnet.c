#include <stdio.h>
#include <stdlib.h>

void	calcmask(int level, int mask);
int		*cidrconv(int cidr);
void	error(char *err);

int	main(int argc, char **argv)
{
	char	*element;
	int		level[4];
	int		*cidr;
	int		i;
	int		j;
	int		k;

	if (argc < 2)
		error("Invalid argument");
	if (argv[1][0] == '/')
	{
		cidr = cidrconv(atoi(&argv[1][1]));
		calcmask(cidr[1], cidr[0]);
		return (0);
	}
	i = 0;
	k = 0;
	element = malloc(4 * sizeof(char));
	while (argv[1][i] && k < 4)
	{
		j = 0;
		while (argv[1][i] != '.' && argv[1][i])
		{
			if (j > 2)
				error("Argument not a subnet mask");
			element[j] = argv[1][i];
			i++;
			j++;
		}
		element[j] = 0;
		level[k] = atoi(element);
		k++;
		if (argv[1][i])
			i++;
	}
	i = -1;
	while (++i < k)
	{
		if (level[i] != 255 || i == 3)
		{
			calcmask(i, level[i]);
		}
	}
	return(0);
}

void	calcmask(int level, int mask)
{
	int	sum;
	int	div;

	sum = 0;
	div = 256;
	while (sum != mask && div != 1)
	{
		div /= 2;
		sum += div;
	}
	//div *= 2; 
	printf("Total IPs: %d\n", div);
	printf("Usable IPs: %d\n\n", div - 2);
	printf("Network IDs:\n");
	sum = 0;
	while (sum < 256)
	{
		printf("%d - ", sum);
		sum += div;
		printf("%d\n", sum - 1);
	}
}

int	*cidrconv(int cidr)
{
	int	i;
	int	*mask;
	int	sum;

	i = -1;
	mask = malloc(2 * sizeof(int));
	*mask = 0;
	*(mask + 1) = 0;
	sum = 256;
	while(++i != cidr)
	{
		sum /= 2;
		(*mask) += sum;
		if (sum == 1)
		{
			sum = 256;
			*mask = 0;
			(*(mask + 1))++;
		}
	}
	return (mask);
}

void	error(char *err)
{
	printf("%s\n", err);
	exit(1);
}