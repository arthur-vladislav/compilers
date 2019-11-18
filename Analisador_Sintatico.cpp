#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "alexa.cpp"
#include "DICIONARIO.h"
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

retorno_lexico tok;
Analisador_Lexico alexa("teste.l");
//static int present_line = 1;
//static 

void Init(char* nome) {
	char c;
	ifstream arq(nome);
	ofstream file("temp.l", ios_base::binary | ios_base::out);
	do {
		arq >> noskipws >> c;
		if (!arq.eof()) file << c;
	} while(!arq.eof());
	arq.close();
	file.close();
	alexa.open("temp.l");
}

void procedimento_S(){

	while (tok.TOKEN == T_INTEGER || tok.TOKEN == T_BOOLEAN || tok.TOKEN == T_BYTE || tok.TOKEN == T_STRING ||  tok.TOKEN == T_CONST) {
	
		procedimento_D();
		marry_token(T_SEMICOLON);

	}//fim while

	marry_token(T_MAIN);

	do {

		procedimento_C();
	
	} while (tok.TOKEN == T_READLN || tok.TOKEN == T_WRITE || tok.TOKEN == T_WRITELN || tok.TOKEN == T_WHILE || tok.TOKEN == T_IF || tok.TOKEN == T_ID || tok.TOKEN == T_SEMICOLON); //fim do.while

	marry_token(T_END);

}//fim S

void procedimento_C() {

	if (tok.TOKEN == T_READLN) {

		marry_token(T_READLN);
		marry_token(T_OPEN_PARENTESIS);
		marry_token(T_ID);
		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_SEMICOLON);

	
	}//fim if

	else if (tok.TOKEN == T_WRITE) {

		marry_token(T_WRITE);
		marry_token(T_OPEN_PARENTESIS);

		procedimento_E();

		while (tok.TOKEN == T_COMMA) {

			marry_token(T_COMMA);
			procedimento_E();

		}//fim while

		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_SEMICOLON);

	
	}//fim if

	else if (tok.TOKEN == T_WRITELN) {

		marry_token(T_WRITELN);
		marry_token(T_OPEN_PARENTESIS);

		procedimento_E();

		while (tok.TOKEN == T_COMMA) {

			marry_token(T_COMMA);
			procedimento_E();

		}//fim while

		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_SEMICOLON);


	}//fim if

	else if (tok.TOKEN == T_WHILE) {

		marry_token(T_WHILE);
		marry_token(T_OPEN_PARENTESIS);
		procedimento_E();
		marry_token(T_CLOSE_PARENTESIS);
		if (tok.TOKEN == T_BEGIN) {

			marry_token(T_BEGIN);

			while (tok.TOKEN == T_READLN || tok.TOKEN == T_WRITE || tok.TOKEN == T_WRITELN || tok.TOKEN == T_WHILE || tok.TOKEN == T_IF || tok.TOKEN == T_ID || tok.TOKEN == T_SEMICOLON) {
			
				procedimento_C();

			}//fim shile

			marry_token(T_END);
		
		}//fim if

		else {
		
			procedimento_C();

		}//fim else
	
	}//fim if

	else if (tok.TOKEN == T_IF) {

		marry_token(T_IF);
		marry_token(T_OPEN_PARENTESIS);
		procedimento_E();
		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_THEN);

		if (tok.TOKEN == T_BEGIN) {

			marry_token(T_BEGIN);

			while (tok.TOKEN == T_READLN || tok.TOKEN == T_WRITE || tok.TOKEN == T_WRITELN || tok.TOKEN == T_WHILE || tok.TOKEN == T_IF || tok.TOKEN == T_ID || tok.TOKEN == T_SEMICOLON) {

				procedimento_C();

			}//fim shile

			marry_token(T_END);

		}//fim if

		else {

			procedimento_C();

		}//fim else

		if (tok.TOKEN == T_ELSE) {

			marry_token(T_ELSE);
	
			if (tok.TOKEN == T_BEGIN) {

				marry_token(T_BEGIN);

				while (tok.TOKEN == T_READLN || tok.TOKEN == T_WRITE || tok.TOKEN == T_WRITELN || tok.TOKEN == T_WHILE || tok.TOKEN == T_IF || tok.TOKEN == T_ID || tok.TOKEN == T_SEMICOLON) {
			
					procedimento_C();

				}//fim shile

				marry_token(T_END);
		
			}//fim if

			else {
		
				procedimento_C();

			}//fim else
		
		}//fim if
	
	}//fim else if

	else if (tok.TOKEN == T_ID) {

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

	if (tok.TOKEN == T_INTEGER) {
	
		marry_token(T_INTEGER);
		marry_token(T_NEW_ID);
		procedimento_D1();

	}//fim if

	else if (tok.TOKEN == T_BOOLEAN) {

		marry_token(T_BOOLEAN);
		marry_token(T_NEW_ID);
		procedimento_D1();

	
	}//fim if

	else if (tok.TOKEN == T_BYTE) {

		marry_token(T_BYTE);
		marry_token(T_NEW_ID);
		procedimento_D1();
	
	}//fim if

	else if (tok.TOKEN == T_STRING) {
	
		marry_token(T_STRING);
		marry_token(T_NEW_ID);
		procedimento_D1();

	}//fim if

	else if(tok.TOKEN == T_CONST){
	
		marry_token(T_CONST);
		marry_token(T_NEW_ID);
		marry_token(T_ASSIGN);
		if (tok.TOKEN == T_SUBTRACT) {

			marry_token(T_SUBTRACT);

		}//fim if
		marry_token(T_VALUE);

	}//fim else


}//fim D

void procedimento_D1() {

	if (tok.TOKEN == T_ASSIGN) {
	
		marry_token(T_ASSIGN);
		procedimento_E();
		procedimento_D2();


	}//fim if

	else {
	
		procedimento_D2();

	}//fim else

}//fim D1

void procedimento_D2() {

	while(tok.TOKEN == T_COMMA){

		marry_token(T_COMMA);
		marry_token(T_NEW_ID);
		if (tok.TOKEN == T_ASSIGN) {
		
			marry_token(T_ASSIGN);
			procedimento_E();

		}//fim if
	
	}//fim while

}//fim D2

void procedimento_E() {

	procedimento_E1();

	if (tok.TOKEN == T_LESSER_THAN || tok.TOKEN == T_GREATER_THAN || tok.TOKEN == T_NOT_EQUAL || tok.TOKEN == T_EQUALS || tok.TOKEN == T_GREATER_THAN_EQUAL || tok.TOKEN == T_LESSER_THAN_EQUAL ) {

		if (tok.TOKEN == T_LESSER_THAN) {

			marry_token(T_LESSER_THAN);
		
		}//fim if

		else if (tok.TOKEN == T_GREATER_THAN) {

			marry_token(T_GREATER_THAN);
		
		}//fim if

		else if (tok.TOKEN == T_NOT_EQUAL) {

			marry_token(T_NOT_EQUAL);
		
		}//fim if

		else if (tok.TOKEN == T_EQUALS) {

			marry_token(T_EQUALS);
		
		}//fim if

		else if (tok.TOKEN == T_GREATER_THAN_EQUAL) {

			marry_token(T_GREATER_THAN_EQUAL);
		
		}//fim if

		else {

			marry_token(T_LESSER_THAN_EQUAL);
		
		}//fim else

		procedimento_E1();
	
	}//fim if

}//fim E

void procedimento_E1() {

	if (tok.TOKEN == T_ADD || tok.TOKEN == T_SUBTRACT) {
	
		if (tok.TOKEN == T_ADD) {

			marry_token(T_ADD);
		
		}//fim if

		else {

			marry_token(T_SUBTRACT);
		
		}//fim else

	}//fim if

	procedimento_E2();

	while (tok.TOKEN == T_ADD || tok.TOKEN == T_SUBTRACT || tok.TOKEN == T_OR) {

		if (tok.TOKEN == T_ADD) {

			marry_token(T_ADD);

		}//fim if

		else if (tok.TOKEN == T_SUBTRACT){

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

	while (tok.TOKEN == T_MULTIPLY || tok.TOKEN == T_DIVIDE || tok.TOKEN == T_AND) {

		if(tok.TOKEN == T_MULTIPLY) {
		
			marry_token(T_MULTIPLY);

		}//fim if

		else if(tok.TOKEN == T_DIVIDE){

			marry_token(T_DIVIDE);
		
		}//fim if

		else {

			marry_token(T_AND);
		
		}//fim else

		procedimento_E3();
	
	}//fim while

}//fim E2

void procedimento_E3() {

	if (tok.TOKEN == T_NOT) {
	
		marry_token(T_NOT);
		procedimento_E3();
		
	}//fim if

	else if (tok.TOKEN == T_OPEN_PARENTESIS) {
	
		marry_token(T_OPEN_PARENTESIS);
		procedimento_E();
		marry_token(T_CLOSE_PARENTESIS);

	}//fim if

	else if (tok.TOKEN == T_ID) {
	
		marry_token(T_ID);

	}//fim if

	else {
	
		marry_token(T_VALUE);

	}//fim else

}//fim E3

int marry_token(int expected_token){

	// cout << "token esperado: " << expected_token << "	token: " << tok << endl; //DEBBUG

	if (tok.TOKEN != expected_token) {
		string msg = "TOKEN NAO ESPERADO";
		if (tok.TOKEN == LEX_ERROR) msg = "LEXEMA INVALIDO";
		if (tok.TOKEN == UNEXPECTED_EOF) msg = "EOF NAO ESPERADO";
		if (tok.TOKEN == INVALID_CHAR) msg = "CARACTERE INVALIDO"; 
		if (tok.TOKEN == T_ID && expected_token == T_NEW_ID) msg = "IDENTIFICADOR JA DECLARADO: " + tok.lexema;
		if (tok.TOKEN == T_NEW_ID && expected_token == T_ID) msg = "IDENTIFICADOR NAO DECLARADO: " + tok.lexema;
		cout << "linha " << alexa.line  << ": "<< msg << " [" << tok.TOKEN << "]" << endl;
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
