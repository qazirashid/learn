
		
prologues := 3;
outputformat := "svg";
outputtemplate := "%j.svg";
beginfig(1);
	z0 = (0,0);
	z1 = (20,40);
	z2 = (100,60);
	z3 = (120,20);
	z4 = (30,50);
	fill z0..controls z1 and z2..z3--cycle;
	draw z0..z1;
	draw z2..z3;

endfig;
end

