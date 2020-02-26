// teste_endereco.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
/*
Arthur Pereira
Henrique Schiess Pertussati
Ian Paixão
*/
#include <unordered_map>
#include <iostream>
#include <regex>
#include "DICIONARIO.h"
#include<vector>
#define NO_TYPE 0
#define TYPE_INTEGER 1
#define TYPE_BYTE 2
#define TYPE_BOOLEAN 3
#define TYPE_STRING 4
#define T_NEW_ID 101
typedef unsigned char BYTE;
using namespace std;


class ID {

public:

	char classe; // v = variavel; c =const; b = blank
	int token;
	int tipo;
	void* valor;

	ID() {

	}

	ID(char classe, int token, int tipo) {

		this->classe = classe;
		this->token = token;
		this->tipo = tipo;


	}//fim construtor

	void set_valor(void* valor) {

		this->valor = valor;

	}


};

class tabela_simbolos {

private:

public:

	unordered_map<string, ID> symbols;
	vector<int> valores_int;
	//vector<BYTE> valores_byte;
	vector<string> valores_string;
	vector<bool> valores_bool;
	string ultimo_adicionado;


	void add_valor(string id, int valor) {

		valores_int.push_back(valor);
		this->symbols[id].set_valor(&valores_int[valores_int.size() - 1]);


	}

	void* add_valor(int valor) {

		valores_int.push_back(valor);
		
		return &(valores_int[valores_int.size() - 1]);


	}

	void add_valor(string id, string valor) {

		valores_string.push_back(valor);
		this->symbols[id].set_valor(&valores_string[valores_string.size() - 1]);


	}

	void* add_valor(string valor) {

		valores_string.push_back(valor);

		return &(valores_string[valores_string.size() - 1]);


	}

	/*void add_valor(string id, bool valor) {

		valores_bool.push_back(valor);
		int pos = valores_bool.size() - 1;
		this->symbols[id].set_valor(&valores_bool[pos]);


	}*/

	/*
	void add_valor(string id, BYTE valor) {

		valores_byte.push_back(valor);
		this->symbols[id].set_valor(&valores_byte[valores_byte.size() - 1]);


	}
	*/

	tabela_simbolos() {
		this->symbols["const"] = ID('b', 1, NO_TYPE);
		this->symbols["integer"] = ID('b', 2, NO_TYPE);
		this->symbols["byte"] = ID('b', 3, NO_TYPE);
		this->symbols["string"] = ID('b', 4, NO_TYPE);
		this->symbols["while"] = ID('b', 5, NO_TYPE);
		this->symbols["if"] = ID('b', 6, NO_TYPE);
		this->symbols["else"] = ID('b', 7, NO_TYPE);
		this->symbols["and"] = ID('b', 8, NO_TYPE);
		this->symbols["or"] = ID('b', 9, NO_TYPE);
		this->symbols["not"] = ID('b', 10, NO_TYPE);
		this->symbols["="] = ID('b', 11, NO_TYPE);
		this->symbols["=="] = ID('b', 12, NO_TYPE);
		this->symbols["("] = ID('b', 13, NO_TYPE);
		this->symbols[")"] = ID('b', 14, NO_TYPE);
		this->symbols["<"] = ID('b', 15, NO_TYPE);
		this->symbols[">"] = ID('b', 16, NO_TYPE);
		this->symbols["!="] = ID('b', 17, NO_TYPE);
		this->symbols[">="] = ID('b', 18, NO_TYPE);
		this->symbols["<="] = ID('b', 19, NO_TYPE);
		this->symbols[","] = ID('b', 20, NO_TYPE);
		this->symbols["+"] = ID('b', 21, NO_TYPE);
		this->symbols["-"] = ID('b', 22, NO_TYPE);
		this->symbols["*"] = ID('b', 23, NO_TYPE);
		this->symbols["/"] = ID('b', 24, NO_TYPE);
		this->symbols[";"] = ID('b', 25, NO_TYPE);
		this->symbols["begin"] = ID('b', 26, NO_TYPE);
		this->symbols["end"] = ID('b', 27, NO_TYPE);
		this->symbols["then"] = ID('b', 28, NO_TYPE);
		this->symbols["readln"] = ID('b', 29, NO_TYPE);
		this->symbols["write"] = ID('b', 30, NO_TYPE);
		this->symbols["writeln"] = ID('b', 31, NO_TYPE);
		this->symbols["main"] = ID('b', 32, NO_TYPE);
		this->symbols["boolean"] = ID('b', 33, NO_TYPE);
		this->symbols["true"] = ID('c', 34, TYPE_BOOLEAN);
		this->symbols["false"] = ID('c', 34, TYPE_BOOLEAN);
		add_valor("true", true);
		add_valor("false", false);


		ultimo_adicionado = "false";

	}//fim construtor


	int eh_palavra_reservada(string string) {

		for (auto it = symbols.cbegin(); it != symbols.cend(); ++it)
			if (string == (*it).first) return (*it).second.token;

		return T_NEW_ID;
		//return 0;

	}// fim eh_palavra_reservada

	bool eh_palavra_reservada_bool(string string) {

		for (auto it = symbols.cbegin(); it != symbols.cend(); ++it)
			if (string == (*it).first) return true;

		return false;

	}// fim eh_palavra_reservada

	void add_id(string id, char classe, int tipo) {

		this->symbols[id] = ID(classe, 35, tipo);
		ultimo_adicionado = id;

	}//fim add_id


	/*
	void add_valor(string valor){

	  this->symbols[valor] = 34;
	  this->constantes[valor] = "integer";

	}//fim add_valor

	void add_string(string string){

	  this->symbols[string] = 34;
	  this->constantes[string] = "string";

	}//fim add_string
	*/
	void print_tabela() {
		//debbug
		for (auto it = symbols.cbegin(); it != symbols.cend(); ++it)
			cout << " [" << (*it).first << ':' << (*it).second.classe << ']' << endl;

	}//fim print_tabela



};//fim classe tabela_simbolos

/*
int main() {

	/*
	map<string, int> m;
	m["hello"] = 23;
	// check if key is present
	if (m.find("hello") != m.end())
	  cout << "map contains key\n";
	// retrieve
	cout << m["hello"] << '\n';
	map<string, int>::iterator i = m.find("hello");
	assert(i != m.end());
	cout << "Key: " << i->first << " Value: " << i->second << '\n';
	return 0;


tabela_simbolos symbols;
symbols.add_id("42", 'b', 0);//instancia da tabela_simbolos
symbols.print_tabela();
bool r = symbols.eh_palavra_reservada("while");
cout << r << endl;
r = symbols.eh_palavra_reservada("hu3");
cout << r << endl;
symbols.symbols.at(symbols.ultimo_adicionado) = ID('c', 35, TYPE_INTEGER);
symbols.print_tabela();
bool x = &symbols.symbols.at("true").valor;
bool* y = (bool*)symbols.symbols.at("true").valor;
//cout << &(symbols.symbols.at("true").valor) << endl;
cout << x << endl;
cout << &y << endl;

}
*/
