#include <iostream>
#include <string>
#include <fstream>
std::string lines[11];
void affich(std::string tab[], int start, int end, int h)
{
    int i;
    i = -1;
    while (++i < h)
        lines[i].append(tab[i], start, end - start);
}

int main(int ac, char **av)
{
	if(ac !=2)
	{
		std::cout<<"problem in number of argument!\n";
		exit(1);
	}
    int l = 12;
    int h = 6;
    std::string str = av[1];
    std::string tab[11];
    std::ifstream file;
    file.open("Art.txt");
    int i = 0;
    for (i = 0; i < h; i++)
       std::getline(file, tab[i]);
    i = 0;
    while (i < str.length())
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            affich(tab, (str[i] - 'A') * l, (str[i] - 'A') * l + l, h);
        else if (str[i] >= 'a' && str[i] <= 'z')
            affich(tab, (str[i] - 'a') * l, (str[i] - 'a') * l + l, h);
        else
            affich(tab, (26) * l, (26) * l + l, h);
        i++;
    }
    i = 0;
    while (i < h)
        std::cout << lines[i++]<<std::endl;
}
