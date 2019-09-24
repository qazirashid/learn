data MyType a = MN | MJ a deriving(Show, Eq)

double x = x + x
triple x = x + x + x
half x   = x/2

--idTest   x    | ((fmap id MN) == (id MN)) && (fmap id (MJ x) == id (MJ x)) = "PASS"
--              | otherwise = "Fail"
--idTest :: MyType a -> Bool

--idTest MN = (fmap id MN) == (id MN)
--idTest (MJ x) = (fmap id (MJ x)) == (id (MJ x))
   


instance Functor MyType where
    fmap fun vmt = case vmt of 
                    MN -> MN
                    MJ a -> MJ (fun a)

instance Applicative MyType where
    pure a = MJ a
    vmt <*> a = case vmt of 
                     MN -> MN
                     MJ f -> fmap f a
 
idTest :: (Functor x, Eq (x a)) => (x a) -> String
idTest x 
    | (fmap id x) == (id x) = "PASS"
    | otherwise = "FAIL"

