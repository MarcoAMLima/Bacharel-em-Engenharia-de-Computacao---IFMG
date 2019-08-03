
#caso seja 10 uma das minhas variáveis
x = 3
y = 10
case 10 do
	^x -> "x é igual a 10"
	^y -> "y é igual a 10"
end

#cond
cond do
	2 + 2 == 5 ->
		"verdade 2 + 2 == 5 no seu mundo"
	2 * 2 == 3 ->
		"verdade 2 x 2 == 3 no seu universo"
	1 + 1 == 2 ->
		"verdade 1 + 1 == 2"
end

#estrutura SE
if String.valid?("HEllo") do
	"É uma string!"
else
	"Não é uma string"
end

#unless que a uma forma negativa do SE
unless is_integer("hello") do
	"Não é do tipo inteiro"
end

#função anonima
sum = fn (a,b) -> a + b end

#A & tarquigrafia
sum = &(&1 + &2)

#chamar essa função
sum.(2,3)
