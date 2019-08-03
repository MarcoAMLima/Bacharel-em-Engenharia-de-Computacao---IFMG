--exe 1: verlista [2,3] [3,3]
verlista :: [Int] -> [Int] -> Bool
verlista [] [] = True
verlista [] _ = False
verlista _ [] = False
verlista (x:resto) (c:k) | (x == c) = verlista resto k
                         | otherwise = False

--exe 2: inv_lista [2,3] 
inv_lista :: [t] -> [t]
inv_lista [] = []
inv_lista (a:b) = (inv_lista b)++[a]
