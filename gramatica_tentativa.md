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
  - E1<sup>d</sup> [ (“<” | “>” | “!=” | “==” | “>=” | “<=”<sup>e</sup>) E1<sup>f</sup><sup>g</sup> ]

- E1 ->   
  - [“+” | “-”] E2<sup>h</sup> { ( “+” | “-” | “or”) E2<sup>i</sup><sup>j</sup> }

- E2  ->  
  - E3<sup>k</sup> {(“*” | “/” | “and”<sup>e</sup>) E3<sup>l</sup><sup>m</sup>}

- E3  ->  
  - “not” E3.1<sup>o</sup> |  
  - “(“ E<sup>n</sup> “)” | 
  - id<sup>c</sup><sup>q</sup>| 
  - constante_valor<sup>P</sup>


<sup>1</sup>: imprime E.val

<sup>1.1</sup>: imprime '\n'

<sup>2</sup>: ID.val := valor_lido

<sup>3</sup>: repita enquanto E.val == True: se E.tipo != Boolean então ERRO senão comandos

<sup>4</sup>: se E.tipo == booleano então {se E.val == True então comandos senao [comandos]} senão ERRO

<sup>5</sup>: se id.tipo == E.tipo então: {id.val := E.val} senao ERRO

<sup>6</sup>: id.tipo := A.tipo; D1 := A.tipo; se D1.classe != vazio então: id.val := D1.val; D1.tipo = A.tipo

<sup>5</sup>: se id.tipo == E.tipo então: {id.val := E.val} senao ERRO

<sup>a</sup>: se id.classe != vazio então ERRO // unicidade 
senão id.classe = classe-const  // declaração

<sup>b</sup>: se id.classe != vazio então ERRO // unicidade 
senão id.classe = classe-var  // declaração

<sup>c</sup>: se id.classe = vazio então ERRO

<sup>d</sup>: E.tipo = E1.1.tipo

<sup>e</sup>: pegar operador  // pegar operador para comparação

<sup>f</sup>: se E1.1.tipo != E1.2.tipo então ERRO // tipos incompatíveis

<sup>g</sup>: se operador == ‘==’ OU `!=` então
se E1.1.tipo == string AND E1.2.tipo == string OU E1.1.tipo == inteiro AND E1.2.tipo == inteiro OU E1.1.tipo == bool AND E1.2.yipo == boolentão OK
          senão ERRO
        senão
  se E1.1.tipo != inteiro AND E1.2.tipo != inteiro então ERRO

<sup>h</sup>: E1.tipo = E2.1.tipo  // E’ recebe E’’

<sup>i</sup>: se E2.1.tipo != E2.2.tipo então ERRO  // tipos incompatíveis

<sup>j</sup>: se operador == or então
  Se E2.1.tipo != inteiro AND E2.1.tipo != string então ERRO
        senão
  se E1.1.tipo != inteiro AND E1.2.tipo != inteiro então ERRO 

<sup>k</sup>: E1.tipo = E3.tipo  // E’ recebe E’’

<sup>l</sup>: se E3.1.tipo != E3.2.tipo então ERRO  // tipos incompatíveis

<sup>m</sup>: se operador == and então
  Se E2.1.tipo != inteiro AND E2.1.tipo != string então ERRO
        senão
  se E1.1.tipo != inteiro AND E1.2.tipo != inteiro então ERRO 

<sup>n</sup>: E3.tipo = E.tipo

<sup>o</sup>: se E3.1.tipo = string então ERRO 
senão E3.tipo = E3.1.tipo 

<sup>p</sup>:  E3.tipo = VALORCONST.tipo

<sup>q</sup>:  E3.tipo = id.tipo