--operação de and
andi :: Bool -> Bool -> Bool
andi False _ = False
andi _ False = False
andi True True = True