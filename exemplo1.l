byte y = 0hff;
integer x;
boolean z = true;
/*huehuehuehue*/

main
	
	readln(x);

	while(z)
	begin
		if(x <= 5) then x = y; 
		else z = false; 
		x = 0h05;
		x = z; /* ERRO */
	end
end
