--verificar o comprimento de uma lista
--caso a lista esteja vazia
size_list [] = 0
--caso a lista não esteja vazia
--x é a cabeça da lista, xs a cauda
--conta a cabeça, corto ela e passo o resto da lista para continuar
size_list (x:xs) = 1 + size_list xs