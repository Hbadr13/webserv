#include <iostream>
#include <vector>
// #include <pair
#include <map>
int main()
{
    std::vector<std::pair<int, int> > vet;

    vet.push_back(std::make_pair(1, 11));
    vet.push_back(std::make_pair(2, 22));
    vet.push_back(std::make_pair(3, 33));
    vet.push_back(std::make_pair(4, 44));
    vet.push_back(std::make_pair(5, 55));
    std::cout << vet[1].first; 
    return 0;

    std::cout << "size = " << vet.size() << std::endl;
    for (int i = 0; i < vet.size(); i++)
    {
        // var.insert(std::make_pair(i, i));
        std::cout << vet[i].first << std::endl;
    }
    return 0;
}