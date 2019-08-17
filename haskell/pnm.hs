module Pnm where
import qualified Data.ByteString.Lazy.Char8 as L8
import qualified Data.ByteString.Lazy as L
import Data.Char (isSpace)
import Data.Int (Int64)
import Data.Word (Word8)

data Greymap = Greymap{
    greyWidth :: Int,
    greyHeight:: Int,
    greyMax   :: Int,
    greyData  :: L.ByteString
}deriving(Eq)

instance Show Greymap where
    show (Greymap w h m _) = "GreyMap Image: Width="++show w ++ " Hieght="++show h ++ " Max Gray=" ++ show m ++ " + Binary Data" 

matchHeader :: L.ByteString -> L.ByteString -> Maybe L.ByteString
matchHeader prefix str 
    |L8.isPrefixOf prefix str = Just (L8.dropWhile isSpace (L.drop (L.length prefix) str))
    |otherwise                = Nothing

dropSpaces :: L.ByteString -> Maybe L.ByteString
dropSpaces bs = let bsr = L8.dropWhile isSpace bs
                 in if (L.null bsr) 
                    then Nothing
                    else Just bsr 

getNat :: L.ByteString -> Maybe (Int, L.ByteString)
getNat s = case (L8.readInt s) of 
                Nothing -> Nothing
                Just (num, rest) 
                   | num <= 0  -> Nothing
                   | otherwise -> Just (fromIntegral num, rest) 

getBytes :: Int -> L.ByteString -> Maybe (L.ByteString, L.ByteString)
getBytes n str = let count = fromIntegral n
                     both@(prefix,rest) = L.splitAt count str
                 in if (L.length prefix < count)
                     then Nothing
                     else Just both

(>>?) :: Maybe a-> (a -> Maybe b) -> Maybe b
Nothing >>? _ = Nothing
Just v  >>? f = f v

--parseP52 :: L.ByteString -> Maybe (Greymap, L.ByteString)
parseP52 s = 
    matchHeader (L8.pack "P5") s  >>? 
    dropSpaces                    >>?
    getNat                        >>?
    \(width, bs) -> dropSpaces bs >>?
    getNat                        >>?
    \(height, bs) ->dropSpaces bs >>?
    getNat                         >>?
    \(maxGrey,bs) -> getBytes 1 bs >>? --drop this byte after maxGrey. It is not part of binary streem
    \(something, bs) -> getBytes (width * height) bs >>?
    \(bitmap, something) -> Just (Greymap width height maxGrey bitmap,something)                                            
-- Monads help reduce boilerplace. Many functions that take a type a and return a monadic value (Maybe b), can be chained using monad operators.
-- This helps to clean the code.
-- We can parse a ByteString into an algebriac type using the this type of code. But there is a better way. 
-- In this case we haven't kep track of any parser state. if we want to keep track now, it will required modification in the long chain glued together using monad operators.
-- There should be a better way to introduce changes and keep track of parser state.
myfun :: Int -> Int -> [Char]
myfun 5 7 = "5 and 7"
myfun 5 x | x == 2 = "5 and 2"
          |otherwise = "5 and somethin"
myfun x y | x == 9 = "9 and something"
          | otherwise =  "No patten matched this one. so it is a catch All situation" 


prepareData :: L.ByteString
prepareData = L.pack (map toEnum [1..255]) 

genSpace :: L.ByteString
genSpace  = L.pack (map toEnum [9..20])

genImage  = L8.pack "P5\r\n\t 2 2 2 255  blah blah blah blah" 


data ParseState = ParseState{ inputByteString :: L.ByteString, currentOffset :: Int64}deriving(Show)

newtype Parser a = Parser { runParser :: ParseState -> Either String (a, ParseState)}

-- We introduce a new type Parse a, that is basically a function. the function can take a parsestate and can either fail (resulting in a String with error message) or it can pass
-- resulting in a tuple with first element of type a and second element of type ParseState

-- Identity Parser is a parser that takes a type a and returns a Parse of type a.

idParserMaker :: t -> Parser t
idParserMaker a = Parser (\s -> Right (a,s))

parse :: Parser t -> L.ByteString -> Either String t
-- parse is a function, that takes (a parser parameterised by type t) and an input for consumption by the  parser.
-- parse first constructs a parseState from the provided input for parsing by (ParseState targetInput 0). 
-- It then asks the parser to run its internal runParse fuction on the ParseState. (runParser targetParser inputState)
-- runParse will run on the ParseState and will either fail resulting in a String
-- or it will pass resulting in a tuple (t, ParseState). We will then extract t out of the tuple and use it as result of the parse.

parse targetParser targetInput = case runParser targetParser (ParseState targetInput 0) of
                                      Left errorString -> Left errorString
                                      Right (result, _) -> Right result

changeOffset :: ParseState -> Int64 -> ParseState
changeOffset pState newOffset = pState {currentOffset = newOffset}


parserForGettingParseState :: Parser ParseState
-- getParseState makes a parser that will return the current parseState. 
-- The reason we want to make a parser just for getting current state is that we want to chain parsers together.
-- then getting current parse state is justa link in the chain just like all other links which are parsers

parserForGettingParseState = Parser {runParser = (\state -> Right (state, state))} 

parserForPuttingParseState :: ParseState -> Parser ()
-- putParseState makes a parser that doesn't do much. It only function is to wrap the given parse state into a parse result so that the parseState can be used in parser chains

parserForPuttingParseState st = Parser {runParser =(\x -> Right ((),st))}
-- We are making a lot of parsers that provide output in form of tuples. 

(==>) :: Parser t1 -> (t1 -> Parser t2) -> Parser t2
-- (==>) is an operator that chains parsers. It takes a parser of type t1 AND a parserMaker of type t2.
-- then it returns a parser of type t2.

parsert1 ==> parserMakert2 = Parser chainMaker  -- Make a new parser. Note chaineMaker must be a lambda function that takes a type t1 and returns a parser for that type.
    where chainMaker inputState = case runParser parsert1 inputState of
                                    Left errString -> Left errString
                                    Right (t1, intermediateState) -> runParser (parserMakert2 t1) intermediateState
-- Note that ==> returns a parser that is effectively a chain of two parsers.
-- The first parser is given direcly on the left side of ==>. the second parser is not given directly, instead of parserMakser is given on the right side of ==>
-- thus job of ==> is not simply apply first parser, apply second parser and be done.
-- Instead it is a parserMaker. it will produce a parser. when producedParser is applied to a ParseState, then parsert1 is applied directly to ParseState.
-- Once parsert1 has been applied, then its output is taken and parserMaksert2 is asked to make a parsert2. 
-- Then parsert2 is applied to ParseState. 

-- the pattern is this
-- Monadic value (chain operator) MonadMaker = gives a binary operator that takesa monadic value on LeftSide and a MonadMaker on the right side.

byteParser :: Parser Word8
-- byteParser is is a parser that output a byte if it is succefull or fails.
byteParser = parserForGettingParseState ==> byteParserMaker

byteParserMaker :: ParseState -> Parser Word8
byteParserMaker st = Parser {runParser = (\st -> Right ((toEnum 2), st) )}

byteParserMaker' st = let byteString = inputByteString st
                          offset     = currentOffset st
                          newOffset  = offset + 1
                          w          = L.uncons byteString
                      in if (w == Nothing)
                         then Parser {runParser = (\x -> Left "Expected a Word8, but byteStream was empty")}
                         else let Just (w8, remByteString) = w
                              in Parser {runParser = (\x -> Right(w8, ParseState remByteString newOffset))}
                            

             
             
 
    


