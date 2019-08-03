--Marco Aurélio Monteiro Lima
--RA:0022933

--push função para empilhar
--top função para retornar o topo da pilha
--pop remover o topo da pilha
--is_empty verificar se a pilha está vazia

push :: [Int] -> Int -> [Int]
push pilha x = pilha ++ [x]

top :: [Int] -> Int
top [x] = x
top (x:xs) = top xs

pop :: [Int] -> [Int]
pop [] = error "Não há o que desempilhar gênio!"
pop (x:xs) | (x == (top (x:xs))) = xs
           | otherwise = x:(pop xs)

is_empty :: [Int] -> Bool
is_empty vazio = if(vazio == []) then True
             else False