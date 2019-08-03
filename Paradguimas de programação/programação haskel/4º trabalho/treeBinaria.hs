--Marco Aurelio Monteiro Lima
--0022933
data ArvBin = Nulo | Vertice Int ArvBin ArvBin

arv = (Vertice 1
				(Vertice 2
                         (Vertice 4 Nulo Nulo) (Vertice 5 Nulo Nulo))
                (Vertice 3
                         Nulo (Vertice 6 Nulo Nulo)))

--4,2,5,1,3,6
em_ordem :: ArvBin -> [Int]
em_ordem Nulo = []
em_ordem (Vertice num esq dir) = em_ordem esq ++ [num] ++ em_ordem dir

--4,5,2,1,3,6
pos_ordem :: ArvBin -> [Int]
pos_ordem Nulo = []
pos_ordem (Vertice num esq dir) = pos_ordem esq ++ pos_ordem dir ++ [num]

--1,2,4,5,3,6
pre_ordem :: ArvBin -> [Int]
pre_ordem Nulo = []
pre_ordem (Vertice num esq dir) = [num] ++pre_ordem esq ++ pre_ordem dir