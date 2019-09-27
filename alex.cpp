#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

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
            else return 0; // divisão
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
    else if (regex_match(&c, regex("="))) {
        lexema.append(&c);
        token = equals(src, lexema);

    } 
    else if (regex_match(&c, regex("(<|>|!)"))) {
        lexema.append(&c);
        switch (c)
        {
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
            token = 0;
            break;
        }
    }
    else {
        switch (c) {
            case '(':
                token = 0;
                break;
            case ')':
                token = 0;
                break;
            case ',':
                token = 0;
                break;
            case ';':
                token = 0;
                break;
            case '+':
                token = 0;
                break;
            case '-':
                token = 0;
                break;
            case '*':
                token = 0;
                break;
            case '{':
                token = 0;
                break;
            case '}':
                token = 0;
                break;
            case '/':
                token = 0;
                break;
            default:
                token = 0;
                break;
        }
    }
}

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
        return 0;
    }

    while(regex_match(&c, regex("\d"))) {
        lexema.append(&c);
        src >> noskipws >> c;
    }
    src.seekg(-1, ios::cur); // devolve c
    return 0;
}

int words(ifstream &src, string lexema){
    char c;
    src >> noskipws >> c;
    while (regex_match(&c, regex("\w"))) {
        lexema.append(&c);
        src >> noskipws >> c;
    }
    // match tabela de símbolos para palavras reservadas
    src.seekg(-1, ios::cur);
    return 0;
}

int equals(ifstream & src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (c == '=') {
        lexema.append(&c);
        return 0;
    }
    src.seekg(-1, ios::cur);
    return 0;
}

int greater_than(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (regex_match(&c, regex("="))) {
        lexema.append(&c);
        return 0;
    }
    src.seekg(-1, ios::cur);
    return 0;
}

int lesser_than(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (regex_match(&c, regex("="))) {
        lexema.append(&c);
        return 0;
    }
    src.seekg(-1, ios::cur);
    return 0;
}

int not_equal(ifstream &src, string lexema) {
    char c;
    src >> noskipws >> c;
    if (regex_match(&c, regex("="))) {
        lexema.append(&c);
        return 0;
    }
    return 0;
}

void comments(ifstream &src, int &line) {
    char c;
    src >> noskipws >> c;
    while(true) {
        if (c == '*') {
            src >> noskipws >> c;
            if (c == '/') break;
        }
    }
}