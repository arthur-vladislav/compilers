#include <iostream>
#include <string>
#include "alexa.cpp"
#include "my_utils.cpp"

using namespace std;\

// void print(T str) {
// 	cout << str << endl;
// }

int main(int argc, char* args[])
{
	// char c;
	// ifstream arq("teste.l");
	// ofstream file("temp.l", ios_base::binary | ios_base::out);
	// Analisador_Lexico alex("temp.l");

	// do {
	// 	arq >> noskipws >> c;
	// 	file << c;
	// } while(!arq.eof());
	// arq.close();
	// file.close();
	// do {
	// 	print(alex.start());
	// } while (!alex.entrada.eof());
	// alex.entrada.close();
	// remove("temp.l");
	print(args[1]);
}