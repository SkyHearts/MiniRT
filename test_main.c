#include <stdio.h>
#include <stdlib.h>

double ft_atof(char *num)
{
	int		sign;
	double	whole;
	double	decimal;
	char	*tmp;

	tmp = num;
	sign = 1;
	if (tmp[0] == '-')
	{
		sign *= -1;
		tmp++;
	}
	whole = atoi(tmp);
	while (*tmp != '.' && *tmp)
		tmp++;
	decimal = atoi(++tmp);
	while (decimal > 1)
		decimal /= 10;
	return (sign * (whole + decimal));
}


int main()
{
	char r[] = "0.2";
	char f[] = "255";

	printf("ratio: %f\n", ft_atof(r));
	printf("dec: %f\n", ft_atof(f));
}