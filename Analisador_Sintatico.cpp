// Analisador_Sintatico.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "alexa.cpp"
#include "DICIONARIO.h"
//#include "alexa.cpp"
using namespace std;

//DEFININDO FUNCOES
int marry_token(int expected_token);
void procedimento_S();
void procedimento_C();
void procedimento_D();
void procedimento_D1();
void procedimento_D2();
void procedimento_E();
void procedimento_E1();
void procedimento_E2();
void procedimento_E3();

void Init(char* arq);

int tok;
Analisador_Lexico alexa("teste.l");
//static int present_line = 1;
//static 

void Init(char* nome) {
	char c;
	ifstream arq(nome);
	ofstream file("temp.l", ios_base::binary | ios_base::out);
	do {
		arq >> noskipws >> c;
		file << c;
	} while(!arq.eof());
	arq.close();
	file.close();
	alexa.open("temp.l");
}

void procedimento_S(){

	while (tok == T_INTEGER || tok == T_BOOLEAN || tok == T_BYTE || tok == T_STRING ||  tok == T_CONST) {
	
		procedimento_D();
		marry_token(T_SEMICOLON);

	}//fim while

	marry_token(T_MAIN);

	do {

		procedimento_C();
	
	} while (tok == T_READLN || tok == T_WRITE || tok == T_WRITELN || tok == T_WHILE || tok == T_IF || tok == T_ID || tok == T_SEMICOLON); //fim do.while

	marry_token(T_END);

}//fim S

void procedimento_C() {

	if (tok == T_READLN) {

		marry_token(T_READLN);
		marry_token(T_OPEN_PARENTESIS);
		marry_token(T_ID);
		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_SEMICOLON);

	
	}//fim if

	else if (tok == T_WRITE) {

		marry_token(T_WRITE);
		marry_token(T_OPEN_PARENTESIS);

		procedimento_E();

		while (tok == T_COMMA) {

			marry_token(T_COMMA);
			procedimento_E();

		}//fim while

		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_SEMICOLON);

	
	}//fim if

	else if (tok == T_WRITELN) {

		marry_token(T_WRITELN);
		marry_token(T_OPEN_PARENTESIS);

		procedimento_E();

		while (tok == T_COMMA) {

			marry_token(T_COMMA);
			procedimento_E();

		}//fim while

		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_SEMICOLON);


	}//fim if

	else if (tok == T_WHILE) {

		marry_token(T_WHILE);
		marry_token(T_OPEN_PARENTESIS);
		procedimento_E();
		marry_token(T_CLOSE_PARENTESIS);
		if (tok == T_BEGIN) {

			marry_token(T_BEGIN);

			while (tok == T_READLN || tok == T_WRITE || tok == T_WRITELN || tok == T_WHILE || tok == T_IF || tok == T_ID || tok == T_SEMICOLON) {
			
				procedimento_C();

			}//fim shile

			marry_token(T_END);
		
		}//fim if

		else {
		
			procedimento_C();

		}//fim else
	
	}//fim if

	else if (tok == T_IF) {

		marry_token(T_IF);
		marry_token(T_OPEN_PARENTESIS);
		procedimento_E();
		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_THEN);

		if (tok == T_BEGIN) {

			marry_token(T_BEGIN);

			while (tok == T_READLN || tok == T_WRITE || tok == T_WRITELN || tok == T_WHILE || tok == T_IF || tok == T_ID || tok == T_SEMICOLON) {

				procedimento_C();

			}//fim shile

			marry_token(T_END);

		}//fim if

		else {

			procedimento_C();

		}//fim else

		if (tok == T_ELSE) {

			marry_token(T_ELSE);
	
			if (tok == T_BEGIN) {

				marry_token(T_BEGIN);

				while (tok == T_READLN || tok == T_WRITE || tok == T_WRITELN || tok == T_WHILE || tok == T_IF || tok == T_ID || tok == T_SEMICOLON) {
			
					procedimento_C();

				}//fim shile

				marry_token(T_END);
		
			}//fim if

			else {
		
				procedimento_C();

			}//fim else
		
		}//fim if
	
	}//fim else if

	else if (tok == T_ID) {

		marry_token(T_ID);
		marry_token(T_ASSIGN);
		procedimento_E();
		marry_token(T_SEMICOLON);

	}//fim if

	else {
		
		marry_token(T_SEMICOLON);

	}//fim else


}//fim C

void procedimento_D() {

	if (tok == T_INTEGER) {
	
		marry_token(T_INTEGER);
		marry_token(T_ID);
		procedimento_D1();

	}//fim if

	else if (tok == T_BOOLEAN) {

		marry_token(T_BOOLEAN);
		marry_token(T_ID);
		procedimento_D1();

	
	}//fim if

	else if (tok == T_BYTE) {

		marry_token(T_BYTE);
		marry_token(T_ID);
		procedimento_D1();
	
	}//fim if

	else if (tok == T_STRING) {
	
		marry_token(T_STRING);
		marry_token(T_ID);
		procedimento_D1();

	}//fim if

	else if(tok == T_CONST){
	
		marry_token(T_CONST);
		marry_token(T_ID);
		marry_token(T_ASSIGN);
		if (tok == T_SUBTRACT) {

			marry_token(T_SUBTRACT);

		}//fim if
		marry_token(T_VALUE);

	}//fim else


}//fim D

void procedimento_D1() {

	if (tok == T_ASSIGN) {
	
		marry_token(T_ASSIGN);
		procedimento_E();
		procedimento_D2();


	}//fim if

	else {
	
		procedimento_D2();

	}//fim else

}//fim D1

void procedimento_D2() {

	while(tok == T_COMMA){

		marry_token(T_COMMA);
		marry_token(T_ID);
		if (tok == T_ASSIGN) {
		
			marry_token(T_ASSIGN);
			procedimento_E();

		}//fim if
	
	}//fim while

}//fim D2

void procedimento_E() {

	procedimento_E1();

	if (tok == T_LESSER_THAN || tok == T_GREATER_THAN || tok == T_NOT_EQUAL || tok == T_EQUALS || tok == T_GREATER_THAN_EQUAL || tok == T_LESSER_THAN_EQUAL ) {

		if (tok == T_LESSER_THAN) {

			marry_token(T_LESSER_THAN);
		
		}//fim if

		else if (tok == T_GREATER_THAN) {

			marry_token(T_GREATER_THAN);
		
		}//fim if

		else if (tok == T_NOT_EQUAL) {

			marry_token(T_NOT_EQUAL);
		
		}//fim if

		else if (tok == T_EQUALS) {

			marry_token(T_EQUALS);
		
		}//fim if

		else if (tok == T_GREATER_THAN_EQUAL) {

			marry_token(T_GREATER_THAN_EQUAL);
		
		}//fim if

		else {

			marry_token(T_LESSER_THAN_EQUAL);
		
		}//fim else

		procedimento_E1();
	
	}//fim if

}//fim E

void procedimento_E1() {

	if (tok == T_ADD || tok == T_SUBTRACT) {
	
		if (tok == T_ADD) {

			marry_token(T_ADD);
		
		}//fim if

		else {

			marry_token(T_SUBTRACT);
		
		}//fim else

	}//fim if

	procedimento_E2();

	while (tok == T_ADD || tok == T_SUBTRACT || tok == T_OR) {

		if (tok == T_ADD) {

			marry_token(T_ADD);

		}//fim if

		else if (tok == T_SUBTRACT){

			marry_token(T_SUBTRACT);

		}//fim if

		else {
		
			marry_token(T_OR);

		}//fim else

		procedimento_E2();
	
	}//fim while

}//fim E!


void procedimento_E2() {

	procedimento_E3();

	while (tok == T_MULTIPLY || tok == T_DIVIDE || tok == T_AND) {

		if(tok == T_MULTIPLY) {
		
			marry_token(T_MULTIPLY);

		}//fim if

		else if(tok == T_DIVIDE){

			marry_token(T_DIVIDE);
		
		}//fim if

		else {

			marry_token(T_AND);
		
		}//fim else

		procedimento_E3();
	
	}//fim while

}//fim E2

void procedimento_E3() {

	if (tok == T_NOT) {
	
		marry_token(T_NOT);
		procedimento_E3();
		
	}//fim if

	else if (tok == T_OPEN_PARENTESIS) {
	
		marry_token(T_OPEN_PARENTESIS);
		procedimento_E();
		marry_token(T_CLOSE_PARENTESIS);

	}//fim if

	else if (tok == T_ID) {
	
		marry_token(T_ID);

	}//fim if

	else {
	
		marry_token(T_VALUE);

	}//fim else

}//fim E3

int marry_token(int expected_token){

	// cout << "token esperado: " << expected_token << "	token: " << tok << endl; //DEBBUG

	if (tok != expected_token) {
		string msg = "TOKEN NAO ESPERADO";
		if (tok == LEX_ERROR) msg = "LEXEMA INVALIDO";
		if (tok == UNEXPECTED_EOF) msg = "EOF NAO ESPERADO";
		if (tok == INVALID_CHAR) msg = "CARACTERE INVALIDO"; 
		cout << "linha " << alexa.line  << ": "<< msg << " [" << tok << "]" << endl;
		exit(0);

	}//fim if

	tok = alexa.start();

}//fim marry_token


int main(int argc, char* args[]){

	Init(args[1]);

	tok = alexa.start();
	procedimento_S();

	if (!alexa.entrada.eof()) {

		cout << "FINAL DE ARQUIVO ESPERADO" << endl;
		alexa.close();
		return 1;
	
	}//fim if
    
	alexa.close();

}//fim main
