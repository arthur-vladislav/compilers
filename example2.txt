/* Erro token nao esperado */

byte b = 0h3;
boolean c = 8 or 5;
boolean b = 8 and 5;
integer n = 5;
integer m = n + 5;
boolean naoTerminou;
const MAXITER = 10;
string nome;
/* Programa Principal */
main
	write('Digite seu nome: ');
	readln(nome);
	naoTerminou=true;
	n=0;
	c = b and b;
	while (naoTerminou) begin
		writeln('Ola'' ',nome);
		n=n+1;
		n++;
		naoTerminou=n<MAXITER;
	end
	while(true == true);
end
