-- 1 retornar o maior item de uma lista
maior :: [Int] -> Int
-- caso tenha apenas um elemento retorna ele
maior [x] = x
--verifica se a cabeça é maior que a cauda
maior (x:xs) | (x > maior xs) = x
             | otherwise = maior xs

-- 2 verificar se um item está presente na lista - presente ()

--presente :: Eq b => ([b],b) -> Bool
--presente ([],_) = False
--presente ((x:xs), y) = if x == y then True else presente (xs, y)

presente :: [Int] -> Int -> Bool
presente [] _ = False
presente (x:xs) n | x == n = True
                  | otherwise = presente xs n

-- 3 verificar se os elementos da lista são pares
pares :: [Int] -> Bool
pares [] = True
pares (x:xs) | (mod x 2 == 0) = pares xs
             | otherwise = False