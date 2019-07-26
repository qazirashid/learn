# Current Thoughts
In the past few days, I have been looking for tools to create visual illustrations/animations for teaching/conveying ideas.

I wouldn't want to rely on a commercial tool that I cannot see under the hood and experiment with it.

So I'll build myself a tool to that. That will be a good learning excercise as well as I'll get a tool that I can tweak and tune.

It will be foolish to try to invent the wheel, so first step is to go looking for tools that are already out there and can be tweaked.
## Search for pieces
### Cairo 
Starting from the low end of the spectrum, there are various C libraries for rendering 2-D graphics on various backend.
One very popular is the 'cairo' library. 
<https://cairographics.org/> 
I have just scratched the surface of cairo, so can't comment much at this stage. 
using cairo from C/C++ seems a tedium, although it offers all the flexibility. 
There are bindings for Python, which can be useful if the tool is written in python. 
But so far I am hesitating to go with python. python is loosly typed. It is a great lanuage, but not my first choice.

## Tex, pdfTex, luatex, Latex
Tex/Latex are great for typesetting. 
Tikz-pgf <https://ctan.org/pkg/pgf?lang=en> seems a nice tool for drawing graphics especially for engineering graphics. 
It can also typeset mathemtical formulas so math looks elegant. 

So I have been reading about Tex and Tikz. Their output is very elegant and beautiful. but Tikz syntax is a bit of worry. 
I want to be able to treat graphics elements as objects. Tikz provides functionlity to draw them but I don't know how can I programatically manipulate objects before drawing them.

The reason I want to manipulate graphics objects before they are drawn on a surface is that I want to be able to parameterize the graphics.
Then these parameterized graphics objects are used to instantiate tikz scripts in  sequence such that we build a graphical movie frame by frame.
To be able to specify changes between frames, I think it will be very difficult to just rely on Tikz. 

#LuaTex, what is that?
So Tex was written by Donald E. Knuth around 1980s. It is a great software for typesetting.
Tex output to a dvi file that is device independant (excellent engineering idea). Then DVI can be converted to any backend of intered, e.g., pdf, ps.
Later someone wrote pdfTex, which was basically Tex but output was pdf. 
Then some people thought they don't have access to internals of Tex, so they wrote Luatex. It is basically Tex with an embedded Lua interpreter. 
So lua interpertor gives access to internals of Tex and thus user can tweak and tune it. 
I don't have time to play with it but it is an interesting line of learning. 
Is it beneficial though? I don't know. My thought is that Tex does provide a shell escape in the form of **\write18**, which can be used to practically embed the output of any program into Tex input token stream. So what more will LuaTex do. I don't know at this stage. 


## Do Graphics Backends matter?
So graphics can be output in PS, PDF, JPEG, PNG, SVG, DVI etc. Does the back end matter?
Probably not, because there are excellent tools that can transform output from one back end to another. 
ImageMajik provides a lot of tools that 'convert' between file formats.
There will be others as well that I haven't come acros as yet. 


## Haskell Diagram package
I have been reading a lot of Haskell on and off for the pas few years. It is a great lanuage but it is very difficult to get grasp on.
I haven't been able to fully understand the philosophy of haskell, so I have played with it and everytime discovered new things.
So when thinking of doing graphics, I thought, how will haskell do it? Even if I can't use it, it will give me ideas and those ideas will be useful in any other programming lanuage.
and I found somebody has been working on it and have built an excellent library 'Diagrams' for almost the same goal that I have.
So I decided that I'll play with it. 
<http://hackage.haskell.org/package/diagrams>
Their website <https://archives.haskell.org/projects.haskell.org/diagrams/> has very good resources to getting started. 

