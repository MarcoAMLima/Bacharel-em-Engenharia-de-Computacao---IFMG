{-ordenação de lista
função ordenação
Essa função vai ordenar uma lista de forma crescente
caso base se tiver só um elemento na lista retorno o elemento
linha 12 se a cabeça da lista for menor que as proximas chamadas de função para a cauda lista retorne a cabeça da lista-}

lista :: [Int]
lista = [3,456,5,69,7,8,21,44,32]

--capturar o menor elemento
get_menor :: [Int] -> Int
get_menor [x] = x
get_menor (x:xs) | (x < get_menor xs) = x
                 | otherwise = get_menor xs

--remover o menor elemento da lista
-- linha 21 para que caia no case base nós mandamos formar uma nova lista
-- linha 20 se a cabeça da lista for menor que o menor da lista retorna a cauda
remove_menor :: [Int] -> [Int]
remove_menor [] = []
remove_menor (x:xs) | (x == (get_menor(x:xs))) = xs
                    | otherwise = (x:remove_menor xs)

--recupera o menor elemento e adiciona ele ao final da lista recusirvamente
aux_ordena :: [Int] -> [Int] -> [Int]
aux_ordena lista_ordenada [] = lista_ordenada
aux_ordena lista_ordenada (x:xs) = aux_ordena (lista_ordenada++[get_menor (x:xs)]) (remove_menor (x:xs))

ordena :: [Int] -> [Int]
ordena [] = []
ordena lista = aux_ordena [] lista