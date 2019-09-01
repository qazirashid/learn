
var arrows = document.getElementById("arrows");
var circle = document.getElementById("circle");
var c2 = document.getElementById("circle");
var i=0;
var cy=0, cx=0;
var t=0, radscale=60;
var up=1;
var tmatrix = [1,0,0,1,0,0];
var tmatrixString=tmatrix.toString().replace(/,/g," ");
//To insert tmatrix as an attribute, we need to replace commas by space
function animation(){
    
    t=t+ 0.01 * Math.PI;
    if(t>2*Math.PI) t=0;
    if(t<Math.PI) up=1; else up=0;
    tmatrix[0] = Math.cos(t);
    tmatrix[1] = -1*Math.sin(t);
    tmatrix[2] = 1*Math.sin(t);
    tmatrix[3] = Math.cos(t);
    tmatrixString = "matrix(" + tmatrix.toString().replace(/,/g," ") + ")";
    arrows.setAttribute("transform", tmatrixString);
    
    cx = 500*Math.cos(t);
    cy = 500*Math.sin(t);    
    circle.setAttribute("cy", cy.toString());
    circle.setAttribute("cx", cx.toString());
    if(up==1) c2.setAttribute("r", (t*radscale).toString());
    else c2.setAttribute("r", radscale*(2*Math.PI-t));
    window.requestAnimationFrame(animation);
    
    
    
}

var animationid = window.requestAnimationFrame(animation);

