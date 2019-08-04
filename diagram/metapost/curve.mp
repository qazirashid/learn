
		
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
	draw z1{z2-z1}..z1234{z234-z123} withcolor green;
	draw z1234{z234 -z123}..z4{z4-z3} withcolor green;

	pickup pencircle xscaled 0.2pt yscaled 7pt rotated 30;
	draw z1..controls z2 and z3..z4 withcolor blue;
	pickup pencircle scaled 2;
	drawdot z1; drawdot z2; drawdot z3; drawdot z4;
	drawdot z23; drawdot z34; drawdot z12;
	drawdot z123; drawdot z1234; drawdot z234;

endfig;
end

