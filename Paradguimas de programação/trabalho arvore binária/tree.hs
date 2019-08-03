--Marco Aurélio Monteiro Lima, RA:0022933
--Pâmela Evelyn Carvalho, RA: 0015669

-- I try


data ArvBin = Nulo | No Int ArvBin ArvBin

arv = (No 1 
        (No 2 
            (No 4 Nulo Nulo) (No 5 Nulo Nulo))
        (No 3 
            (No 6 Nulo Nulo) Nulo))

em_ordem :: ArvBin -> [Int]
em_ordem Nulo = []
em_ordem (No num esq dir) = (em_ordem esq) ++ [num] ++ (em_ordem dir)

pre_ordem :: ArvBin -> [Int]
pre_ordem  Nulo = []
pre_ordem  (No num esq dir) = [num] ++ (pre_ordem  esq) ++ (pre_ordem  dir)

pos_ordem :: ArvBin -> [Int]
pos_ordem Nulo = []
pos_ordem (No num esq dir) = (pos_ordem esq) ++ (pos_ordem dir) ++ [num]

-- passa um elemento e uma sub arvore a esq ou dir
inserir :: Ord a=> a -> ArvBin -> ArvBin
inserir x Nulo = (No x Nulo Nulo)
inserir x (No y esq dir)
            | x==y = No y esq dir
            | x<y = No y (inserir x esq) dir
            | x>y = No y esq (inserir x dir )

--função auxiliar para encontrar o elemento mais a esquerda passando uma sub arvore
mais_esq :: ArvBin -> a
mais_esq (No x Nulo _) = x
mais_esq (No _ esq _) = mais_esq esq

remover :: Ord a => a -> ArvBin -> ArvBin
remover x Nulo = Nulo
remover x (No y esq dir)
            | x==y = dir
remover x (No y esq Nulo)
            | x==y = esq
remover x (No y esq dir)
            | x<y = No y (remover x esq) dir
            | x>y = No y esq (remover x dir)
            | x==y = let z = mais_esq dir
                in No z esq (remover z dir)