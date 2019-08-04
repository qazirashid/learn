prologues := 3;
outputformat := "svg";
outputtemplate := "%j.svg";
beginfig(1);
	z1 = (0,100); label.lft("z1",z1);
	z2 = (100,100);label.top("z2",z2);
	z3 = (200,100); label.rt("z3",z3);
	z4 = (0,0);     label.top("z4",z4);
	z5 = (100,0);   label.top("z5",z5);
	z6 = (200,0);   label.top("z6",z6);
	pickup pencircle scaled 2;
	drawdot z1; drawdot z2; drawdot z3; drawdot z4; drawdot z5; drawdot z6;
	fill z5..z4..z1..z3..z6..cycle withcolor red;
	z0 = (x2, 0.5[y1,y4]);
        for k=1 upto 6:
		z'[k]=0.2[z[k],z0];
	endfor
	unfill z'5..z'4..z'1..z'3..z'6..cycle;	
        for k=1 upto 6:
		z''[k]=0.4[z[k],z0];
	endfor
	fill z''5..z''4..z''1..z''3..z''6..cycle withcolor green;	

        for k=1 upto 6:
		z'r[k]=0.6[z[k],z0];
	endfor
	unfill z'r5..z'r4..z'r1..z'r3..z'r6..cycle;	
        for k=1 upto 6:
		z'p[k]=0.8[z[k],z0];
	endfor
	fill z'p5..z'p4..z'p1..z'p3..z'p6..cycle withcolor blue;	
endfig;
end

