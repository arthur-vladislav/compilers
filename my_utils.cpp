#include <iostream>
#include <string.h>
#include <vector>
#include <stdarg.h>
#include <typeinfo>

using namespace std;

template<typename T>

void print(T first, ...) { // Imprime n strings separadas por espaço e põe uma quebra de linha no fim
    va_list args;
    T str;

    str=first;
    va_start(args, first);
    do {
        cout << str << ' ';
        str = va_arg(args, T);
    } while (str != NULL);
    va_end(args);
    cout << endl;
}

int main(int argc, char const *argv[])
{
	print(0, 1, NULL);
	return 0;
}
