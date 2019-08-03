--Nome: Marco Aurélio Monteiro Lima
--RA: 0022933

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
subtracao_complexa_e :: Complex -> Double -> Complex
subtracao_complexa_e (Complexo a b) n = Complexo (a-n) (b-n)

--Subtração Complexa
subtracao_complexa :: Complex -> Complex -> Complex
subtracao_complexa (Complexo x y) (Complexo a b) = Complexo (x-a) (y-b)

{---Multiplicação escalar
mult_complexa_e :: Complex -> Double -> Complex

--Multiplicação Complexa
mult_complexa :: Complex -> Complex -> Complex-}

--Modulo ou Magnitude
modulo :: Complex -> Double
modulo (Complexo x y) = Complexo sqrt((x^2)+(y^2))