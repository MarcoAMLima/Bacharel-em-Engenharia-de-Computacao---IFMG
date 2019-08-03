--definindo novos tipos de dados
type Nome = String
type Idade = Int
type Linguagem = String
type Pessoa = (Nome, Idade, Linguagem)

--FUNÇÃO DO TIPO PESSOA
pessoa :: Pessoa
pessoa = ("joao", 32, "C")

--função para retornar o primeiro elemento do meu tipo criado
my_fst :: Pessoa -> Nome
my_fst ( n, i, l) = n