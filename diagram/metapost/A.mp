
		
prologues := 3;
outputformat := "svg";
outputtemplate := "%j-%c.svg";
beginfig(1);
	s = 20; a=100; b=100;
	bot z1 = (s,0); z5=z1 + (a,0);
	top z3 = (1/2[x1,x5],b);
	z4 - z2 = whatever * dir 20;
	0.5[y2,y4] = 2/3[y1,y3];
	z2 = whatever[z1,z3];
	z4 = whatever[z3,z5];
	draw z1..z3;
	draw z3..z5;
	draw z2..z4;

endfig;
end

