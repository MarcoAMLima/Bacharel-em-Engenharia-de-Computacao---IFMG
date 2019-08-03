--Marco Aurélio Monteiro Lima
--RA:0022933

--queue função para enfilheirar
--front função para retornar a frente da fila
--desqueue desinfileirar a frente
--is_empty verificar se a fila está vazia

queue :: [Int] -> Int -> [Int]
queue fila x = fila ++ [x]

front :: [Int] -> Int
front [x] = x
front [] = error "fila vazia"
front (x:xs) = x

desqueue :: [Int] -> [Int]
desqueue [] = error "Não há o que desinfileirar gênio"
desqueue (x:xs) = xs

is_empty :: [Int] -> Bool
is_empty vazio = if(vazio == []) then True
                 else False
