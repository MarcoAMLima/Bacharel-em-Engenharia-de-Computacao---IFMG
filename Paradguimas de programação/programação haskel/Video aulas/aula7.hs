--soma de tuplas, tuplas não podem ser modificadas
func :: (Int,Int) -> (Int, Int) -> (Int, Int)
func (a,b) (c,d) = (a+c , b+d)