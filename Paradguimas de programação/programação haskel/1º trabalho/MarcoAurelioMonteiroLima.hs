--Marco Aurélio Monteiro Lima

--ordenacao simples de listas

--Encontrar o menor elemento
menor :: [Int] -> Int --recebe uma lista e retorna o menor
menor [x] = x
menor (x:xs) | (x < menor xs) = x 
             | otherwise = menor xs

--remover o menor elemento da lista
remover :: [Int] -> [Int]
remover [] = []
remover (x:xs) | (x == (menor(x:xs))) = xs
               | otherwise = (x:remover xs)

--recupera o menor elemeno da primeira lista e concatena ao final da lista auxiliar
listaAux :: [Int] -> [Int] -> [Int]
listaAux lista [] = lista
listaAux lista (x:xs) = listaAux (lista++[menor (x:xs)]) (remover (x:xs))

--ordenar a lista
ordena :: [Int] -> [Int]
ordena [] = []
ordena l = listaAux [] l