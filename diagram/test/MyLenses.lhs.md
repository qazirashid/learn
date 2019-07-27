Lenses
=======

Haskell Lense library is quite useful when working with Records.
Haskell origin syntax for working with Records is quite verbose.
With lenses compact code can be written to work with Records.


Example in ghci:

$ ghci>
Prelude> :module + Control.Lens
Prelude Control.Lens> (1,2,3) ^. _2
2
Prelude Control.Lens> (1,20,3) ^. _2
20
Prelude Control.Lens> :t (^.)
(^.) :: s -> Getting a s a -> a
Prelude Control.Lens> (3,7,11) &2 .~ 13
Prelude Control.Lens> (3,7,11) & _2 .~ 13
(3,13,11)
Prelude Control.Lens> let x=(3,7,11)
Prelude Control.Lens> view _2 x
7
Prelude Control.Lens> view _3 x
11
Prelude Control.Lens> set _3 13 x
(3,7,13)
Prelude Control.Lens> view _3 x
11
Prelude Control.Lens> let y = set _3 13 x
Prelude Control.Lens> y
(3,7,13)


Making Lenses for User Defined Records

When a record is user defined using keyword 'data', lenses for it can be easily made by using function 'makeLenses' in Control.Lens
Then all lens operations become availalbe on the user defined Records. 
```Haskell
> {-# LANGUAGE TemplateHaskell #-}
> module MyLenses where
> import Control.Lens
> data Record = Record { _field1 :: Int, _field2 :: Int} deriving (Show)


> makeLenses ''Record
```
Lense operations
-----------------


