Gramática Linguagem L

- S  ->  
  - {D ;} “main” { C }+ “end” 

- C ->   
  - “readln” “(“ id “)” “;”<sup>2</sup> | 
  - “write” “(” E<sup>1</sup> {“,” E<sup>1</sup>}“)” “;” | 
  - “writeln” “(” E { “,” E } “)” “;”<sup>1.1</sup> | 
  - “while” “(” E “)”<sup>3</sup> (C | “begin” {C} “end”) |
  - “if” “(“ E “)”<sup>4</sup> “then” (C | “begin” {C} “end”) [ else”(C | “begin” {C} “end”)] | 
  - id “=” E “;”<sup>5</sup> | “;”       

- D ->   
  - (“int” | “boolean” | “byte” | “string”) id D1 <sup>6</sup>| 
  - “const” id “=” [“-”] constante_valor 

- D1 ->   
  - “=” E<sup>7</sup> D2  | D2

- D2 ->   
  - {“,” id [ “=” E ] }

- E ->    
  - E1 [ (“<” | “>” | “!=” | “==” | “>=” | “<=”) E1 ]

- E1 ->   
  - [“+” | “-”] E2 { ( “+” | “-” | “or”) E2 }

- E2  ->  
  - E3 {(“*” | “/” | “and”) E3}

- E3  ->  
  - “not” E3 |  
  - “(“ E “)” | 
  - id | 
  - constante_valor


<sup>1</sup>: imprime E.val

<sup>1.1</sup>: imprime '\n'

<sup>2</sup>: ID.val := valor_lido

<sup>3</sup>: repita enquanto E.val == True: se E.tipo != Boolean então ERRO senão comandos

<sup>4</sup>: se E.tipo == booleano então {se E.val == True então comandos senao [comandos]} senão ERRO

<sup>5</sup>: se id.tipo == E.tipo então: {id.val := E.val} senao ERRO

<sup>6</sup>: id.tipo := A.tipo; D1 := A.tipo; se D1.classe != vazio então: id.val := D1.val; D1.tipo = A.tipo

<sup>5</sup>: se id.tipo == E.tipo então: {id.val := E.val} senao ERRO