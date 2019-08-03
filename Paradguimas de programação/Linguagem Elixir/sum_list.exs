sum [2,3,4]
def sum([head | rest]) do
	head + sum(rest)
end