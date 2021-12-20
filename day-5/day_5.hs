import System.IO  
import Control.Monad



data P a
  = Get (Char -> P a)
  | Look (String -> P a)
  | Fail
  | Result a (P a)
  | Final [(a,String)]
  deriving Functor

main :: IO ()
main = do
--    helloFile <- openFile "day-5-input.txt" ReadMode
--    hasLine <- hIsEOF helloFile
--    firstLine <- if not hasLine
--                 then hGetLine helloFile
--                 else return "empty"
    contents <- readFile "day-5-input.txt"
    let fileLines = lines contents
    f <- 
    map f fileLines