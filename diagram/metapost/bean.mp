prologues := 3;
outputformat := "svg";
outputtemplate := "%j.svg";
beginfig(1);
	z0 = (0,0); 
	z1 = (0,100); label.lft("z1",z1);
	z2 = (100,100);label.top("z2",z2);
	z3 = (200,100); label.rt("z3",z3);
	z4 = (0,0);     label.top("z4",z4);
	z5 = (100,0);   label.top("z5",z5);
	z6 = (200,0);   label.top("z6",z6);
	pickup pencircle scaled 2;
	draw z5..z4..z1..z3..z6..cycle withcolor green;
	
	drawdot z1; drawdot z2; drawdot z3; drawdot z4; drawdot z5; drawdot z6;

	draw z5..z4..z1..z3..z6..z5 withcolor red;
endfig;
end

