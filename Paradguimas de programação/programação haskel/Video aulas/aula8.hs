
--select_pri nomes
nomes :: (String, String, String)
nomes = ("arara","mesa","rato")

select_pri (x, _, _) = x
select_sec (_, y, _) = y
select_ter (_, _, z) = z