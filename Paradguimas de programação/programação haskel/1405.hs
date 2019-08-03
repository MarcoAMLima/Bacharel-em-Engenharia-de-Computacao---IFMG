{---Tipos Algebricos

type Nome = String
type Cidade = String

data Pessoa = Programador Nome Cidade | Aluno Nome Cidade deriving(Show)

p1 = Programador "Fulano" "Bambui"
p2 = Aluno "Beltrano" "São Paulo"

is_programador :: Pessoa -> Bool
is_programador (Programador _ _) = True
is_programador _ = False

is_aluno :: Pessoa -> Bool
is_aluno (Aluno _ _) = True
is_aluno _ = False-}

--Operações com números complexos

type Re = Double
type Im = Double

data Complex = Complexo Re Im deriving(Show)

c1 = Complexo 10 10
c2 = Complexo 5 5

--Adição Escalar
adicao_complexa_e :: Complex -> Double -> Complex
adicao_complexa_e (Complexo a b) n = Complexo (a+n) (b+n)

--Adição Complexa
adicao_complexa :: Complex -> Complex -> Complex
adicao_complexa (Complexo x y) (Complexo a b) = Complexo (x+a) (y+b)


--Subtração escalar

--Subtração Complexa

--Multiplicação escalar

--Multiplicação Complexa

--Modulo ou Magnitude