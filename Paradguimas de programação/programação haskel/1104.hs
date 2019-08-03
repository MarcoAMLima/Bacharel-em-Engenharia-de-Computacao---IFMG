--Soma - soma 3
soma 0 = 0
soma 1 = 1
soma n = soma(n-1) + n

--Fatorial - fact 3
fact 0 = 1
fact n = fact(n-1) * n

--Fibonnci - fib 32
fib 0 = 0
fib 1 = 1
fib 2 = 1
fib n = fib(n-1) + fib(n-2)

--Guarda - guarda 0
guarda x | (x==0) = 0
         | (x==1) = 1
         | otherwise = -1

--AND (variavel anonima '_')
my_and :: Bool -> Bool -> Bool
my_and False _ = False
my_and _ False = False
my_and True True = True

--If else - letra 'a'
letra :: Char -> String
letra l =
         if l >= 'a' && l <= 'z'
         then "minusculo"
         else if l >= 'A' && l <= 'Z'
         then "maiusculo"
         else "Nao e uma letra do alfabeto"

-- Letra com guarda - letra2 'a'
letra2 :: Char -> String
letra2 c | c >= 'a' && c <= 'z' = "minusculo"
         | c >= 'A' && c <= 'Z' = "maiusculo"
         | otherwise = "Nenhum"

--Trabalhando comm tuplas - ponto (2,3) (3,2)
ponto :: (Int, Int) -> (Int, Int) -> (Int, Int)
ponto (a,b) (c,d) = (a+c,b+d)

--utilizando variaveis anonimas para recuperar os elementos das tuplas, nome
nome :: (String, Int, String)
nome = ("Fulano",10,"Ciclano")

-- segundo nome , recuperar uma posição da tupla
primeiro (x,_,_) = x
segundo (_,y,_) = y
terceiro (_,_,z) = z

--listas,
lista [] = 0
lista (x:xs) = 1 + lista xs

--função type do haskell
type Nome = String
type Idade = Int
type Telefone = String
type Pessoa(Nome, Idade, Telefone)

pessoa :: Pessoa
pessoa = ("Fulano", 10, "123")

--criar uma função para retornar o primeiro elemento  do tipo pessoa
fst2 :: Pessoa -> Int
fst2 (a,b,c) = b