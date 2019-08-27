
module Main where
import Control.Monad

cshow []          = ""
cshow (e:rList) = show (fst e) ++ "," ++ show (snd e) ++ "\n" ++ (cshow rList);


main = do 
       putStrLn preamble
       putStrLn beginDocument
       forM frameList (\(x,y) -> do
                                       putStrLn $ wrapTikz (curves x y))
       putStrLn endDocument  
mainStr a b = preamble ++ beginDocument ++ beginTikz ++ visOptions ++ beginData ++cshow (curves a b)  ++ endData++endTikz ++ endDocument; 

wrapTikz f = beginTikz ++ visOptions ++ beginData ++ cshow(f) ++ endData ++ endTikz

test = wrapTikz (curves 1 2)

makeParamList = zip (paramX) (paramY)
paramX = [1,1..]
paramY = [2,2.05..]
 
frameList = take numFrames makeParamList

numFrames = 60

genvis = cshow (take 50 $ curves 1 1)
 

calcPair f  x= (x, f x)

calcSin = map (calcPair sin) [0.0,0.05..2*pi]

curves a b = [(cos (a*t), sin (b*t)) | t<-[0.0,0.05..2*pi]] 

preamble :: String
preamble = "\\documentclass[tikz]{standalone}\n\\usepackage{tikz}\n\\usetikzlibrary{datavisualization}\n" 

beginDocument::String
beginDocument = "\\begin{document}\n"

endDocument :: String
endDocument = "\\end{document}\n"

beginTikz = "\\begin{tikzpicture}\n"
endTikz   ="\\end{tikzpicture}"

visOptions ="  \\datavisualization [xy Cartesian,visualize as smooth line]\n"
beginData = "    data{\n x,y\n"
endData   = "    };"
