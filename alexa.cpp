#include "symbols.cpp"
#include "DICIONARIO.h"
#include <regex>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

extern tabela_simbolos table;

int number(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;

    if (regex_match(lexema, regex("(0)")) && c == 'h') {
        lexema.append(&c);
        src >> noskipws >> c;
        if (!regex_match(&c, regex("[0-9a-fA-F]"))) return 0;
        lexema.append(&c);
        src >> noskipws >> c;
        if (!regex_match(&c, regex("[0-9a-fA-F]"))) return 0;
        lexema.append(&c);
        return T_VALUE;
    }

    while(regex_match(&c, regex("\d"))) {
        lexema.append(&c);
        src >> noskipws >> c;
    }
    src.seekg(-1, ios::cur); // devolve c
    return T_VALUE;
}

int words(ifstream &src, string lexema){
    char c;
    src >> noskipws >> c;
    while (regex_match(&c, regex("(\w|\d|_)"))) {
        lexema.append(&c);
        src >> noskipws >> c;
    }
    
    int token = table.eh_palavra_reservada(lexema);
    if (token == 101) {
        table.add_id(lexema);
    }
    src.seekg(-1, ios::cur);
    return token;
}

int equals(ifstream & src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (c == '=') {
        lexema.append(&c);
        return T_EQUALS;
    }
    src.seekg(-1, ios::cur);
    return T_ATRIBUICAO;
}

int greater_than(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (c == '=') {
        lexema.append(&c);
        return T_GREATER_THAN_EQUAL;
    }
    src.seekg(-1, ios::cur);
    return T_GREATER_THAN;
}

int lesser_than(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (c == '=') {
        lexema.append(&c);
        return T_LESSER_THAN_EQUAL;
    }
    src.seekg(-1, ios::cur);
    return T_LESSER_THAN;
}

int not_equal(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (c == '=') {
        lexema.append(&c);
        return T_NOT_EQUAL;
    }
    return LEX_ERROR;
}

void comments(ifstream &src, int &line) {
    char c;
    src >> noskipws >> c;
    while(true) {
        if (c == '\n') line++;
        if (c == '*') {
            src >> noskipws >> c;
            if (c == '/') break;
        }
        src >> noskipws >> c;
    }
}

int start(ifstream &src, int &line) {
    string lexema;
    lexema = "";
    int token;

    char c;
    src >> noskipws >> c;
    while (c == ' ' || c == '\n' || c == '\t') {
        if (c == '\n') line++;
        if (c == '/') { // comentario ou divisao
            src >> noskipws >> c;
            if (c == '*') {
                comments(src, line);
            }
            else return T_DIVIDE; // divisão
        }
        src >> noskipws >> c;
    }
    if (regex_match(&c, regex("\d"))) {
        lexema.append(&c);
        token = number(src, lexema);
    }
    else if (regex_match(&c, regex("\w"))) {
        lexema.append(&c);
        token = words(src, lexema);
    }
    else if (c == '_') {
        lexema.append(&c);
        src >> noskipws >> c;
        while (c == '_') {
            lexema.append(&c);
            src >> noskipws >> c;
        }
        if (regex_match(&c, regex("\d|\w"))){
            lexema.append(&c);
            token = words(src, lexema);
        }
        else return LEX_ERROR;
    }
    else if (c == '=') {
        lexema.append(&c);
        token = equals(src, lexema);

    } 
    else if (regex_match(&c, regex("(<|>|!)"))) {
        lexema.append(&c);
        switch (c) {
            case '>':
                token = greater_than(src, lexema);
                break;
            case '<':
                token = lesser_than(src, lexema);
                break;
            case '!':
                token = not_equal(src, lexema);
                break;
            default:
                token = LEX_ERROR;
                break;
        }
    }
    else {
        switch (c) {
            case '(':
                token = T_OPEN_PARENTESIS;
                break;
            case ')':
                token = T_CLOSE_PARENTESIS;
                break;
            case ',':
                token = T_COMMA;
                break;
            case ';':
                token = T_SEMICOLON;
                break;
            case '+':
                token = T_ADD;
                break;
            case '-':
                token = T_SUBTRACT;
                break;
            case '*':
                token = T_MULTIPLY;
                break;
            default:
                token = LEX_ERROR;
                break;
        }
    }
    return token;
}