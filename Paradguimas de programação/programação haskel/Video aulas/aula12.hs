--função para verificar se duas listas são gêmeas
--casos bases
--se vazia, se a primeira vazia e a segunda não, e o inverso
comp_listas :: [Int] -> [Int] -> Bool
comp_listas [] [] = True
comp_listas [] _ = False
comp_listas _ [] = False
comp_listas (a:b) (c:d) | (a == c) = comp_listas b d -- percorre toda a lista para verificar se os elementos são iguais
                        | otherwise = False -- caso dois elementos forem diferentes