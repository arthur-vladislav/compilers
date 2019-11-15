#include <unordered_map>
#include <iostream>
#include "DICIONARIO.h"
using namespace std;

class tabela_simbolos{

private:
  unordered_map<string, int> symbols;
  unordered_map<string, string> constantes;
  int posicao;

public:
  tabela_simbolos(){
    this->symbols["const"]=1;
    this->symbols["integer"]=2;
    this->symbols["byte"]=3;
    this->symbols["string"]=4;
    this->symbols["while"]=5;
    this->symbols["if"]=6;
    this->symbols["else"]=7;
    this->symbols["and"]=8;
    this->symbols["or"]=9;
    this->symbols["not"]=10;
    this->symbols["="]=11;
    this->symbols["=="]=12;
    this->symbols["("]=13;
    this->symbols[")"]=14;
    this->symbols["<"]=15;
    this->symbols[">"]=16;
    this->symbols["!="]=17;
    this->symbols[">="]=18;
    this->symbols["<="]=19;
    this->symbols[","]=20;
    this->symbols["+"]=21;
    this->symbols["-"]=22;
    this->symbols["*"]=23;
    this->symbols["/"]=24;
    this->symbols[";"]=25;
    this->symbols["begin"]=26;
    this->symbols["end"]=27;
    this->symbols["then"]=28;
    this->symbols["readln"]=29;
    this->symbols["write"]=30;
    this->symbols["writeln"]=31;
    this->symbols["main"]=32;
    this->symbols["boolean"]=33;
    this->symbols["true"]=34;
	  this->constantes["true"] = "boolean";
    this->symbols["false"]=34;
	  this->constantes["false"] = "boolean";
    this->symbols["id"]=35;

    this->posicao = 36;

  }//fim construtor


  int eh_palavra_reservada(string string){

    for (auto it = symbols.cbegin(); it != symbols.cend(); ++it)
        if(string == (*it).first) return (*it).second;

    return T_NEW_ID;
  }// fim eh_palavra_reservada

  void add_id(string id) {

    this->symbols[id] = 35;

  }//fim add_id

  void add_valor(string valor){

    this->symbols[valor] = 34;
	this->constantes[valor] = "integer";

  }//fim add_valor

  void add_string(string string){

    this->symbols[string] = 34;
	this->constantes[string] = "string";

  }//fim add_string

    void print_tabela(){
      //debbug
      for (auto it = symbols.cbegin(); it != symbols.cend(); ++it)
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
	  for (auto it = constantes.cbegin(); it != constantes.cend(); ++it)
		  cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;

    }//fim print_tabela



};//fim classe tabela_simbolos

//int main(){
//
//   /*map<string, int> m;
//   m["hello"] = 23;
//   // check if key is present
//   if (m.find("hello") != m.end())
//     cout << "map contains key\n";
//   // retrieve
//   cout << m["hello"] << '\n';
//   map<string, int>::iterator i = m.find("hello");
//   assert(i != m.end());
//   cout << "Key: " << i->first << " Value: " << i->second << '\n';
//   return 0;
//   */
//tabela_simbolos symbols;
//symbols.add_tipo("42");//instancia da tabela_simbolos
 //   symbols.print_tabela();
//   bool r = symbols.eh_palavra_reservada("while");
//   cout << r << endl;
//   r = symbols.eh_palavra_reservada("hu3");
//   cout << r << endl;
//}//fim main()
