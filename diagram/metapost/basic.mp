
		
prologues := 3;
outputformat := "svg";
outputtemplate := "%j-%c.svg";
beginfig(1);
	o=0;
	b=100; a=100;
	top rt z1 = (o,b);
	top z2 = (a,b);
	top lft z3 = (2a,b);
	bot rt z4 = (o,o);
	bot z5 = (a,o);
	bot lft z6 = (2a, o);
	draw z1..z6;
	draw z2..z5;
	draw z3..z4;
	show 0.4[z2,z6];
endfig;
end

