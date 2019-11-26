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
void procedimento_D1(int operacao);
void procedimento_D2(int operacao);
void procedimento_E();
void procedimento_E1();
void procedimento_E2();
void procedimento_E3();
void semantico_ERRO_1(string id);
void semantico_ERRO_2(int valor_lido);
void semantico_ERRO_3(int pos_filho);
void semantico_ERRO_4(string id);
void semantico_ERRO_5(string id, int pos_filho);
void semantico_ERRO_6(string id);
void semantico_ERRO_9(int pos_procedimento, int operacao);
void semantico_ERRO_10(int pos_filho, int pos_filho_2);
void semantico_ERRO_11(int pos_procedimento, int pos_filho);
void semantico_ERRO_12(int operacao, int pos_filho);
void semantico_ERRO_13(int pos_procedimento, int operacao);
void semantico_ERRO_14(int pos_procedimento);
void semantico_1(int valor_lido);
//void semantico_5(bool boolean);
void semantico_6(string id);
void semantico_7(string identificador, int pos_filho);
void semantico_8(int operacao, string id);
void semantico_9(string id, int pos_filho);
void semantico_10(string id);
void semantico_11(int pos_procedimento, int pos_filho);
void semantico_12(string id, int pos_filho);
void semantico_13(int pos_procedimento, int pos_filho);
void semantico_14(int pos_procedimento, int pos_filho, int pos_filho_2, int operacao);
void semantico_15(int pos_procedimento);
void semantico_16(int pos_procedimento, int pos_filho);
void semantico_17(int pos_procedimento);
void semantico_18(int pos_procedimento, int pos_filho, int pos_filho_2, int operacao);
void semantico_19(int pos_procedimento);
void semantico_20(int pos_procedimento, int pos_filho, int operacao);
void semantico_21_A(int pos_procedimento, int pos_filho);
void semantico_21_B(int pos_procedimento, string id);
void semantico_21_C(int pos_procedimento, string id);
void semantico_22(string id, int pos_procedimento);

class Procedimento {

public:
	char classe; // v = variavel; c =const; b = blank
	int tipo;
	void* valor;
	int posicao;

	Procedimento() {}//fim Construtor

	Procedimento(int posicao) {

		this->posicao = posicao;

	}//fim Construtor

};


void Init(char* arq);
retorno_lexico tok;
Analisador_Lexico alexa("teste.l");
vector<Procedimento> procedimentos; //pilha de procedimentos em execução
bool fazer_semantico = true; // caso seja para fazer açoes semanticas
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

	int pos_procedimento, pos_filho, pos_filho_2, operacao;
	pos_procedimento = procedimentos.size();
	procedimentos.push_back(Procedimento(procedimentos.size()));
	string id;

	if (tok.TOKEN == T_READLN) {

		//int valor_lido;
		//string write_val = "";

		marry_token(T_READLN);
		marry_token(T_OPEN_PARENTESIS);
		id = tok.lexema;
		marry_token(T_ID);

		if (fazer_semantico) semantico_ERRO_1(id);
		if (fazer_semantico) semantico_ERRO_4(id);

		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_SEMICOLON);
		//cin >> valor_lido;
		//semantico_ERRO_2(valor_lido);
		//semantico_1(valor_lido);


	
	}//fim if

	else if (tok.TOKEN == T_WRITE) {

		marry_token(T_WRITE);
		marry_token(T_OPEN_PARENTESIS);
		procedimento_E();
		//if (fazer_semantico) write_val += to_string(E.val); //semantico_2

		while (tok.TOKEN == T_COMMA) {

			marry_token(T_COMMA);
			procedimento_E();
			// if (fazer_semantico) write_val += to_string(E.val); //semantico_2

		}//fim while

		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_SEMICOLON);
		// if (fazer_semantico) cout << write_val; //semantico_3
	
	}//fim if

	else if (tok.TOKEN == T_WRITELN) {

		marry_token(T_WRITELN);
		marry_token(T_OPEN_PARENTESIS);
		procedimento_E();
		// if (fazer_semantico) write_val += to_string(E.val); //semantico_2

		while (tok.TOKEN == T_COMMA) {

			marry_token(T_COMMA);
			procedimento_E();
			//if (fazer_semantico) write_val += to_string(E.val); //semantico_2

		}//fim while

		marry_token(T_CLOSE_PARENTESIS);
		marry_token(T_SEMICOLON);
		//if (fazer_semantico) cout << write_val << endl; //semantico_3 e semantico_4


	}//fim if

	else if (tok.TOKEN == T_WHILE) {
		int pos_filho;

		marry_token(T_WHILE);
		marry_token(T_OPEN_PARENTESIS);

		pos_filho = procedimentos.size();
		procedimento_E();
		if (fazer_semantico) semantico_ERRO_3(pos_filho);
		//if (fazer_semantico) semantico_5((*(bool*)procedimentos[pos_filho].valor));

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

		int pos_filho;

		marry_token(T_IF);
		marry_token(T_OPEN_PARENTESIS);

		pos_filho = procedimentos.size();
		procedimento_E();
		if (fazer_semantico) semantico_ERRO_3(pos_filho);
		//if (fazer_semantico) semantico_5(*(bool*)procedimentos[pos_filho].valor);


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
			//if (!fazer_semantico) semantico_5(true);
	
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

		id = tok.lexema;
		marry_token(T_ID);
		if (fazer_semantico) semantico_ERRO_1(id);
		if (fazer_semantico) semantico_ERRO_4(id);
		id = tok.lexema;

		marry_token(T_ASSIGN);

		pos_filho = procedimentos.size();
		procedimento_E();
		if (fazer_semantico) semantico_ERRO_5(id, pos_filho);
		//if (fazer_semantico) semantico_7(id, pos_filho);

		marry_token(T_SEMICOLON);

	}//fim if

	else {
		
		marry_token(T_SEMICOLON);

	}//fim else

	//semantico_5(true);

}//fim C

void procedimento_D() {
	
	int pos_procedimento, pos_filho, pos_filho_2, operacao;
	pos_procedimento = procedimentos.size();
	procedimentos.push_back(Procedimento(procedimentos.size()));
	string id;

	if (tok.TOKEN == T_INTEGER) {
	
		operacao = T_INTEGER;
		marry_token(T_INTEGER);
		id = tok.lexema;
		marry_token(T_NEW_ID);
		semantico_ERRO_6(id);
		semantico_8(operacao, id);
		pos_filho = procedimentos.size();
		procedimento_D1(operacao);
		semantico_ERRO_5(id, pos_filho);
		//semantico_9(id, pos_filho);

	}//fim if

	else if (tok.TOKEN == T_BOOLEAN) {

		operacao = T_BOOLEAN;
		marry_token(T_BOOLEAN);
		id = tok.lexema;
		marry_token(T_NEW_ID);
		semantico_ERRO_6(id);
		semantico_8(operacao, id);
		pos_filho = procedimentos.size();
		procedimento_D1(operacao);
		semantico_ERRO_5(id, pos_filho);
		//semantico_9(id, pos_filho);

	
	}//fim if

	else if (tok.TOKEN == T_BYTE) {

		operacao = T_BYTE;
		marry_token(T_BYTE);
		id = tok.lexema;
		marry_token(T_NEW_ID);
		semantico_ERRO_6(id);
		semantico_8(operacao, id);
		pos_filho = procedimentos.size();
		procedimento_D1(operacao);
		semantico_ERRO_5(id, pos_filho);
		//semantico_9(id, pos_filho);
	}//fim if

	else if (tok.TOKEN == T_STRING) {
	
		operacao = T_STRING;
		marry_token(T_STRING);
		id = tok.lexema;
		marry_token(T_NEW_ID);
		semantico_8(operacao, id);
		pos_filho = procedimentos.size();
		procedimento_D1(operacao);
		semantico_ERRO_5(id, pos_filho);
		//semantico_9(id, pos_filho);

	}//fim if

	else if(tok.TOKEN == T_CONST){
	
		marry_token(T_CONST);
		id = tok.lexema;
		marry_token(T_NEW_ID);
		semantico_ERRO_6(id);
		semantico_10(id);
		marry_token(T_ASSIGN);
		if (tok.TOKEN == T_SUBTRACT) {

			marry_token(T_SUBTRACT);

		}//fim if

		id = tok.lexema;
		marry_token(T_VALUE);
		semantico_21_C(pos_procedimento, id);
		semantico_22(id, pos_procedimento);

	}//fim else


}//fim D

void procedimento_D1(int operacao) {

	int pos_procedimento, pos_filho, pos_filho_2;
	pos_procedimento = procedimentos.size();
	procedimentos.push_back(Procedimento(procedimentos.size()));

	if (tok.TOKEN == T_ASSIGN) {
	
		marry_token(T_ASSIGN);
		pos_filho = procedimentos.size();
		procedimento_E();
		semantico_11(pos_procedimento, pos_filho);
		procedimento_D2(operacao);


	}//fim if

	else {
	
		procedimento_D2(operacao);

	}//fim else

}//fim D1

void procedimento_D2(int operacao) {

	string id;
	int pos_procedimento, pos_filho, pos_filho_2;
	pos_procedimento = procedimentos.size();
	procedimentos.push_back(Procedimento(procedimentos.size()));

	while(tok.TOKEN == T_COMMA){

		marry_token(T_COMMA);
		id = tok.lexema;
		marry_token(T_NEW_ID);
		semantico_ERRO_6(id);
		semantico_8(operacao, id);
		if (tok.TOKEN == T_ASSIGN) {
		
			marry_token(T_ASSIGN);
			pos_filho = procedimentos.size();
			procedimento_E();
			semantico_ERRO_5(id, pos_filho);

		}//fim if
	
	}//fim while

}//fim D2

void procedimento_E() {

	int pos_procedimento, pos_filho,pos_filho_2, operacao;
	pos_procedimento = procedimentos.size();
	procedimentos.push_back(Procedimento(procedimentos.size()));
	

	pos_filho = procedimentos.size();
	procedimento_E1();
	semantico_13(pos_procedimento, pos_filho);

	if (tok.TOKEN == T_LESSER_THAN || tok.TOKEN == T_GREATER_THAN || tok.TOKEN == T_NOT_EQUAL || tok.TOKEN == T_EQUALS || tok.TOKEN == T_GREATER_THAN_EQUAL || tok.TOKEN == T_LESSER_THAN_EQUAL ) {

		operacao = tok.TOKEN;

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

		semantico_ERRO_9(pos_filho, operacao);

		pos_filho_2 = procedimentos.size();
		procedimento_E1();
		semantico_ERRO_10(pos_filho, pos_filho_2);
		semantico_14(pos_procedimento, pos_filho, pos_filho_2, operacao);
	
	}//fim if

}//fim E

void procedimento_E1() {

	int pos_procedimento, pos_filho, pos_filho_2, operacao;
	pos_procedimento = procedimentos.size();
	procedimentos.push_back(Procedimento(procedimentos.size()));

	if (tok.TOKEN == T_ADD || tok.TOKEN == T_SUBTRACT) {
	
		if (tok.TOKEN == T_ADD) {

			marry_token(T_ADD);
		
		}//fim if

		else {

			marry_token(T_SUBTRACT);
			semantico_15(pos_procedimento);
		
		}//fim else	

	}//fim if

	pos_filho = procedimentos.size();
	procedimento_E2();
	semantico_ERRO_11(pos_procedimento, pos_filho);
	semantico_16(pos_procedimento, pos_filho);

	while (tok.TOKEN == T_ADD || tok.TOKEN == T_SUBTRACT || tok.TOKEN == T_OR) {

		operacao = tok.TOKEN;

		if (tok.TOKEN == T_ADD) {

			marry_token(T_ADD);

		}//fim if

		else if (tok.TOKEN == T_SUBTRACT){

			marry_token(T_SUBTRACT);

		}//fim if

		else {
		
			marry_token(T_OR);
			semantico_17(pos_procedimento);

		}//fim else

		semantico_ERRO_12(operacao, pos_filho);
		pos_filho_2 = procedimentos.size();
		procedimento_E2();
		semantico_ERRO_10(pos_filho, pos_filho_2);

		semantico_18(pos_procedimento, pos_filho, pos_filho_2, operacao);
	
	}//fim while

}//fim E()


void procedimento_E2() {

	int pos_procedimento, pos_filho, pos_filho_2, operacao;
	pos_procedimento = procedimentos.size();
	procedimentos.push_back(Procedimento(procedimentos.size()));

	pos_filho = procedimentos.size();
	procedimento_E3();
	semantico_13(pos_procedimento, pos_filho);

	while (tok.TOKEN == T_MULTIPLY || tok.TOKEN == T_DIVIDE || tok.TOKEN == T_AND) {

		operacao = tok.TOKEN;

		if(tok.TOKEN == T_MULTIPLY) {
		
			marry_token(T_MULTIPLY);

		}//fim if

		else if(tok.TOKEN == T_DIVIDE){

			marry_token(T_DIVIDE);
		
		}//fim if

		else {

			marry_token(T_AND);
			semantico_19(pos_procedimento);
		
		}//fim else
	
		semantico_ERRO_13(pos_procedimento, operacao);

		pos_filho_2 = procedimentos.size();
		procedimento_E3();

		semantico_ERRO_10(pos_filho, pos_filho_2);
		//semantico_20(pos_procedimento, pos_filho, aux);
	
	}//fim while

}//fim E2

void procedimento_E3() {
	
	string id;
	int pos_procedimento, pos_filho, pos_filho_2, operacao;
	pos_procedimento = procedimentos.size();
	procedimentos.push_back(Procedimento(procedimentos.size()));

	if (tok.TOKEN == T_NOT) {
	
		marry_token(T_NOT);
		pos_filho = procedimentos.size();
		procedimento_E3();
		semantico_ERRO_14(pos_filho);
		semantico_21_A(pos_procedimento, pos_filho);
		
	}//fim if

	else if (tok.TOKEN == T_OPEN_PARENTESIS) {
	
		marry_token(T_OPEN_PARENTESIS);
		pos_filho = procedimentos.size();
		procedimento_E();
		semantico_21_A(pos_procedimento, pos_filho);
		marry_token(T_CLOSE_PARENTESIS);

	}//fim if

	else if (tok.TOKEN == T_ID) {
	
		id = tok.lexema;
		marry_token(T_ID);
		semantico_21_B(pos_procedimento, id);

	}//fim if

	else {
	
		id = tok.lexema;
		marry_token(T_VALUE);
		semantico_21_C(pos_procedimento, id);

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

void semantico_ERRO_1(string id) {

	if (alexa.table.eh_palavra_reservada_bool(id) == false) {

		cout << alexa.line << ":" << "identificador não declarado " << " [" << id << "]" << endl;
		exit(0);

	}//fim if

	if(alexa.table.symbols.at(id).tipo == TYPE_BOOLEAN) {

		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);
	
	}//fim if
	

}//

/*
void semantico_ERRO_2(int valor_lido) {

	if (alexa.table.symbols.at(tok.lexema).tipo != valor_lido.tipo) {
	
		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);
	
	}//fim if


}*/

void semantico_ERRO_3(int pos_filho) {

	if (procedimentos[pos_filho].tipo != TYPE_BOOLEAN) {

		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);
	
	}//fim if


}//

void semantico_ERRO_4(string id) {

	if (alexa.table.symbols.at(id).classe != 'v') {

		cout << alexa.line << ":" << "classe de identificador incompativel " << " [" << id << "]" << endl;

		exit(0);

	}//fim if

}//

/*
void semantico_ERRO_5(int tipo_id, int pos_filho) {

	if (!(tipo_id == TYPE_INTEGER && procedimentos[pos_filho].tipo == TYPE_BYTE) &&
		(tipo_id != procedimentos[pos_filho].tipo)) {
	
		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);
	
	}//fim if


}//
*/

void semantico_ERRO_5(string id, int pos_filho){

	if ((!(alexa.table.symbols.at(id).tipo == TYPE_INTEGER && procedimentos[pos_filho].tipo == TYPE_BYTE)) &&
		(alexa.table.symbols.at(id).tipo != procedimentos[pos_filho].tipo)) {

		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);

	}//fim if


}//

void semantico_ERRO_6(string id) {

	if(alexa.table.eh_palavra_reservada_bool(id)) {

		cout << alexa.line << ":" << "identificador ja declarado " << " [" << id << "]" << endl;
		exit(0);
	
	}//fim if

}//

void semantico_ERRO_9(int pos_procedimento, int operacao) {

	if ((operacao == T_LESSER_THAN || operacao == T_GREATER_THAN || operacao == T_LESSER_THAN_EQUAL || operacao == T_GREATER_THAN_EQUAL) &&
		(procedimentos[pos_procedimento].tipo == TYPE_STRING || procedimentos[pos_procedimento].tipo == TYPE_BOOLEAN)) {
	
		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);
	
	}//fim if

}//



void semantico_ERRO_10(int pos_filho, int pos_filho_2) {

	if ((!(procedimentos[pos_filho].tipo == TYPE_INTEGER && procedimentos[pos_filho_2].tipo == TYPE_BYTE)) &&
		(!(procedimentos[pos_filho].tipo == TYPE_BYTE && procedimentos[pos_filho_2].tipo == TYPE_INTEGER)) &&
		(procedimentos[pos_filho].tipo != procedimentos[pos_filho_2].tipo)){

		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);
	
	}//fim if

}//

void semantico_ERRO_11(int pos_procedimento, int pos_filho) {

	if (procedimentos[pos_procedimento].tipo == TYPE_INTEGER && (procedimentos[pos_filho].tipo != TYPE_INTEGER && procedimentos[pos_filho].tipo != TYPE_BYTE)){

		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);

	}//fim if

}//

void semantico_ERRO_12(int operacao, int pos_filho) {


	switch (operacao){

	case T_ADD: if (procedimentos[pos_filho].tipo == TYPE_BOOLEAN) {
	
			cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
			exit(0);
		}//fim if
		break;
	case T_SUBTRACT: if (procedimentos[pos_filho].tipo == TYPE_BOOLEAN || procedimentos[pos_filho].tipo == TYPE_STRING) {
	
			cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
			exit(0);
	
		}//fim if
		break;

	case T_OR:if (procedimentos[pos_filho].tipo == TYPE_STRING) {

		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);

	
		}//fim if
		break;

	default:
		break;
	}//fim switch

}//

void semantico_ERRO_13(int pos_procedimento, int operacao) {
	
	if((operacao == T_MULTIPLY || operacao == T_DIVIDE) &&
		(procedimentos[pos_procedimento].tipo == TYPE_STRING || procedimentos[pos_procedimento].tipo == TYPE_BOOLEAN)) {

	    cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
	    exit(0);


	}//fim if

	else if (procedimentos[pos_procedimento].tipo == TYPE_STRING) {

		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);
	
	}//fim else if

}//

void semantico_ERRO_14(int pos_procedimento) {

	if (procedimentos[pos_procedimento].tipo != TYPE_BOOLEAN) {

		cout << alexa.line << ":" << "tipos incompatíveis. " << endl;
		exit(0);
	
	}//fim if

}//

/*
void semantico_1(int valor_lido) {
	
	alexa.table.add_valor(tok.lexema, valor_lido);

}*/

/*
void semantico_5(int boolean) {

	fazer_semantico = boolean;

}//
*/

/*
void semantico_7(string identificador, int pos_filho) {

	alexa.table.symbols.at(identificador).valor = procedimentos[pos_filho].valor;

}//
*/

void semantico_8(int operacao, string id){

	alexa.table.add_id(id, 'v', operacao);

}//

void semantico_9(string id, int pos_filho) {

	alexa.table.symbols.at(id).valor = procedimentos[pos_filho].valor;

}//

void semantico_10(string id) {

	alexa.table.add_id(id, 'c', 0);

}//

void semantico_11(int pos_procedimento, int pos_filho) {

	procedimentos[pos_procedimento].tipo = procedimentos[pos_filho].tipo;
	//procedimentos[pos_procedimento].valor = procedimentos[pos_filho].valor;

}//

void semantico_12(string id, int pos_filho) {
	
	//alexa.table.symbols.at(id).valor = procedimentos[pos_filho].valor;

}//

void semantico_13(int pos_procedimento, int pos_filho) {

	procedimentos[pos_procedimento].tipo = procedimentos[pos_filho].tipo;

}//


void semantico_14(int pos_procedimento, int pos_filho, int pos_filho_2, int operacao){

	procedimentos[pos_procedimento].tipo = TYPE_BOOLEAN;


}//


void semantico_15(int pos_procedimento) {

	procedimentos[pos_procedimento].tipo = TYPE_INTEGER;

}//

void semantico_16(int pos_procedimento, int pos_filho) {

	if (procedimentos[pos_procedimento].tipo == TYPE_INTEGER) {
	
		procedimentos[pos_filho].tipo == TYPE_INTEGER;

	}//fim if

}//

void semantico_17(int pos_procedimento) {

	procedimentos[pos_procedimento].tipo = TYPE_BOOLEAN;

}//


void semantico_18(int pos_procedimento, int pos_filho, int pos_filho_2, int operacao) {

	if ((procedimentos[pos_filho].tipo == TYPE_INTEGER && procedimentos[pos_filho_2].tipo == TYPE_BYTE) ||
		(procedimentos[pos_filho].tipo == TYPE_BYTE && procedimentos[pos_filho_2].tipo == TYPE_INTEGER)){

		procedimentos[pos_procedimento].tipo = TYPE_INTEGER;

	}//fim if
	else {
	
		procedimentos[pos_procedimento].tipo = procedimentos[pos_filho_2].tipo;

	}//fim else

}//

void semantico_19(int pos_procedimento){

	procedimentos[pos_procedimento].tipo = TYPE_BOOLEAN;

}//

/*
void semantico_20(int pos_procedimento, int pos_filho, int operacao){

	switch (operacao) {

	case T_MULTIPLY: procedimentos[pos_procedimento].valor = alexa.table.add_valor(*(int*)procedimentos[pos_procedimento + 1].valor * *(int*)procedimentos[pos_filho].valor);
		break;

	case T_ADD:  procedimentos[pos_procedimento].valor = alexa.table.add_valor((int)(*(int*)procedimentos[pos_procedimento + 1].valor + *(int*)procedimentos[pos_filho].valor));
		break;

	case T_AND:  if (procedimentos[pos_procedimento].tipo == TYPE_INTEGER || procedimentos[pos_procedimento].tipo == TYPE_BYTE) {
			  procedimentos[pos_procedimento].valor = alexa.table.add_valor(*(int*)procedimentos[pos_procedimento + 1].valor && *(int*)procedimentos[pos_filho].valor);
			}//fim if

			else {

			procedimentos[pos_procedimento].valor = alexa.table.add_valor(*(bool*)procedimentos[pos_procedimento + 1].valor && *(bool*)procedimentos[pos_filho].valor);

			}
			  break;
	}//fim switch


}//
*/

void semantico_21_A(int pos_procedimento, int pos_filho) {

	procedimentos[pos_procedimento].tipo = procedimentos[pos_filho].tipo;
	//procedimentos[pos_procedimento].valor = procedimentos[pos_filho].valor;

}//

void semantico_21_B(int pos_procedimento, string id) {

	procedimentos[pos_procedimento].tipo = alexa.table.symbols.at(id).tipo;
	//procedimentos[pos_procedimento].valor = alexa.table.symbols.at(id).valor;


}//

void semantico_21_C(int pos_procedimento, string id) {

	//STRING
	if (id[0] = '\'') {

		procedimentos[pos_procedimento].tipo = TYPE_STRING;
		//procedimentos[pos_procedimento].valor = alexa.table.add_valor(lexema);
	
	}//

	//BOOLEAN
	else if (id[0] == 't' || id[0] == 'f') {

		procedimentos[pos_procedimento].tipo = TYPE_BOOLEAN;
		//procedimentos[pos_procedimento].valor = alexa.table.symbols.at(lexema).valor;

	}//

	//BYTE
	else if(id[1] == 'h') {

		if(id.length() == 3) {

			switch (id[3]) {

			case '0':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(0);
				break;

			case '1': procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(1);
				break;

			case '2':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(2);
				break;

			case '3':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(3);
				break;

			case '4':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(4);
				break;

			case '5':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(5);
				break;

			case '6':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(6);
				break;

			case '7':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(7);
				break;

			case '8':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(8);
				break;

			case '9':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(9);
				break;

			case 'A': procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(10);
					break;

			case 'a': procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(10);
				break;

			case 'B': procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(11);
				break;

			case 'b':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				procedimentos[pos_procedimento].valor = alexa.table.add_valor(11);
				break;

			case 'C':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(12);
				break;

			case 'c':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(12);
				break;

			case 'D':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(13);
				break;

			case 'd':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(13);
				break;

			case 'E':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(14);
				break;

			case 'e':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(14);
				break;

			case 'F':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(15);
				break;

			case 'f':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(15);
				break;

			default: break;

			}//fim switch
		
		}//fim if

		else {

			int valor_byte = 0;
			/*
			switch (lexema[4]) {

			case '0': break;

			case '1': valor_byte += 1;
				break;

			case '2':valor_byte += 2;
				break;


			case '3':valor_byte += 3;
				break;


			case '4':valor_byte += 4;
				break;


			case '5':valor_byte += 5;
				break;


			case '6':valor_byte += 6;
				break;


			case '7':valor_byte += 7;
				break;


			case '8':valor_byte += 8;
				break;


			case '9':valor_byte += 9;
				break;


			case 'A': valor_byte += 10;
				break;


			case 'a': valor_byte += 10;
				break;


			case 'B': valor_byte += 11;
				break;


			case 'b':valor_byte += 11;
				break;


			case 'C':valor_byte += 12;
				break;


			case 'c':valor_byte += 12;
				break;


			case 'D':valor_byte += 13;
				break;


			case 'd':valor_byte += 13;
				break;


			case 'E':valor_byte += 14;
				break;


			case 'e':valor_byte += 14;
				break;


			case 'F':valor_byte += 15;
				break;


			case 'f':valor_byte += 15;
				break;

			default: break;

			}
			*/

			switch (id[3]) {

			case '0':procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case '1': valor_byte += 16;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case '2':valor_byte += 32;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case '3':valor_byte += 48;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case '4':valor_byte += 64;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case '5':valor_byte += 80;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case '6':valor_byte += 96;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case '7':valor_byte += 112;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case '8':valor_byte += 128;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case '9':valor_byte += 144;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'A': valor_byte += 160;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'a': valor_byte += 160;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'B': valor_byte += 176;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'b':valor_byte += 176;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'C':valor_byte += 192;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'c':valor_byte += 192;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'D':valor_byte += 208;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'd':valor_byte += 208;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'E':valor_byte += 224;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'e':valor_byte += 224;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'F':valor_byte += 240;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			case 'f':valor_byte += 240;
				procedimentos[pos_procedimento].tipo = TYPE_BYTE;
				//procedimentos[pos_procedimento].valor = alexa.table.add_valor(valor_byte);
				break;

			default: break;

			}//fim switch

		}//fim else

	}//fim else if

	//INTEIRO
	else {

		int inteiro = stoi(id);

		procedimentos[pos_procedimento].tipo = TYPE_INTEGER;
		//procedimentos[pos_procedimento].valor = alexa.table.add_valor(inteiro);		
	
	}//fim else

}//

void semantico_22(string id, int pos_procedimento) {

	alexa.table.symbols.at(id).tipo = procedimentos[pos_procedimento].tipo;
	//alexa.table.symbols.at(id).valor = procedimentos[pos_filho].valor;

}//


int main(int argc, char* args[]) {

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
