
		
prologues := 3;
outputformat := "svg";
outputtemplate := "%j.svg";
beginfig(1);
	z0 = (0,0);
	z1 = (60,40);
	z2 = (40,90);
	z3 = (10,70);
	z4 = (30,50);
	
	for d=0 step 10 until 120:
		draw (0,0){dir 60}..{dir -d}(6cm,0);
	endfor;
	for d=0 step -10 until -90:
		draw (0,0){dir 60}..{dir -d}(6cm,0);
	endfor;

endfig;
end

