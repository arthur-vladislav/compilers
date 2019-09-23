#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

char* start(ifstream &src) {
    string lexema;
    lexema = "";
    char* token;

    char c;
    src >> noskipws >> c;
    if (regex_match(&c, regex("(\d)"))) {
        lexema.append(&c);
        token = integer(src, lexema);
    }
    else if (regex_match(&c, regex("\w")) {
        lexema.append(&c);
        token = word(src, lexema);
    }
    else if (regex_match(&c, regex("\=")) {
        lexema.append(&c);
        token = equals(src, lexema);

    } 
    else if (regex_match(&c, regex("(<|>|!)")) {
        lexema.append(c);
        token = comparisons(src, lexema);
        switch (c)
        {
        case '>':
            token = maior(src, lexema);
            break;
        case '<':
            token = menor(src, lexema);
            break;
        case '!':
            token = diferente(src, lexema);
            break;
        default:
            token = "ERRO";
            break;
        }
    }
    else if (c == '/') {
        // TODO: Comentario ou divisao
    }

    else {
        switch (c)
        {
        case '(':
            token = '(';
            break;
        case ')':
            token = ')';
            break;
        case ',':
            token = ',';
            break;
        case ';':
            token = ';';
            break;
        case '+':
            token = '+';
            break;
        case '-':
            token = '-';
            break;
        case '*':
            token = '*';
            break;
        case '{':
            token = '{';
            break;
        case '}':
            token = '}';
            break;
        default:
            token = "ERRO";
            break;
        }
    }

}

char* integer(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;

    if ( regex_match(lexema, regex("(0)")) && c == 'h'){
        lexema.append(&c);
        src >> noskipws >> c;
        if (!regex_match(&c, regex("[a-fA-F]"))) return "ERRO";
        lexema.append(&c);
        src >> noskipws >> c;
        if (!regex_match(&c, regex("[a-fA-F]"))) return "ERRO";
        lexema.append(&c);
        return "Hexadecimal";

    }
    while(regex_match(&c, regex("\d"))) {
        lexema.append(&c);
        src >> noskipws >> c;
    }
    src.seekg(-1, ios::cur);
    return "Int";
}

char* word(ifstream &src, string lexema){
    char c;
    src >> noskipws >> c;
    while (regex_match(&c, regex("\w"))) {
        lexema.append(c);
        src >> noskipws >> c;
    }
    // match tabela de símbolos para palavras reservadas
    src.seekg(-1, ios::cur);
    return "LEXEMA";
}

char* equals(ifstream & src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (c == '=') {
        lexema.append(&c);
        return 'IGUALDADE';
    }
    src.seekg(-1, ios::cur);
    return "ATRIBUICAO";
}

char* maior(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (regex_match(&c, regex("\="))) {
        lexema.append(c);
        return ">=";
    }
    src.seekg(-1, ios::cur);
    return "MAIOR"
}

char* menor(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (regex_match(&c, regex("\="))) {
        lexema.append(c);
        return "<=";
    }
    src.seekg(-1, ios::cur);
    return "MENOR";
}

char* diferente(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (regex_match(&c, regex("\="))) {
        lexema.append(c);
        return "!=";
    }
    return "ERRO";
}