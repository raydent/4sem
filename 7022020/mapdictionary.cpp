// shittymap.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
int main()
{
    std::ifstream input("(1) The Hunger Games.txt");
    std::map<std::string, int> m;
    std::string s;
    while (getline(input, s, ' ')) {
        std::transform(s.begin(), s.end(), s.begin(), tolower);
        while (s.size() != 0 && (s[s.size() - 1] < 'a' || s[s.size() - 1] > 'z')) {
            s.pop_back();
        }
        while (s.size() != 0 && (s[0] < 'a' || s[0] > 'z')) {
            s.erase(0);
        }
        if (s.size() != 0 && 'a' <= s[0] <= 'z') {
            m[s] += 1;
        }
    }
    std::map<int, std::vector<std::string>> m2;
    
    for (auto& i : m) {
        m2[i.second].push_back(i.first);
   }
    for (auto& i : m2) {
        std::cout << i.first << " ";
        for (auto& i2 : i.second) {
            std::cout << i2 << " ";
        }
        std::cout << std::endl;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
