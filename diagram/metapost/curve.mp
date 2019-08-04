
		
prologues := 3;
outputformat := "svg";
outputtemplate := "%j.svg";
beginfig(1);
	z1 = (0,0);
	z2 = (20,90);
	z3 = (100,90);
	z4 = (100,0);
	draw z1{z2-z1}..{z4-z3}z4;
	draw z1..z2;
	draw z3..z4;
	z12 = 1/2[z1,z2]; z23=1/2[z2,z3]; z34=1/2[z3,z4];
	draw z12 .. z23;
	draw z23 .. z34;
	show z23;
	z123=0.5[z12,z23];
	z234=0.5[z23,z34];
	z1234=0.5[z123,z234];
	
	draw z123..z234;
	draw z1{z2-z1}..z1234{z234-z123};
	draw z1234{z234 -z123}..z4{z4-z3};

endfig;
end

