local seq = {
	0, 1, 1, 2, 1, 2, 2, 3
}

function gen(off)
	local vec = {}

	for i = 1, 4 do
		vec[i] = seq[i] + off
	end

	for i = 5, 8 do
		vec[i] = seq[i] + off
	end

	for i = 5, 8 do
		vec[i + 4] = seq[i] + off
	end

	for i = 5, 8 do
		vec[i + 8] = seq[i] + off + 1
	end

	return vec
end

for i = 1, 8 do
	for _, v in ipairs(gen(i - 1)) do
		io.stdout:write(string.format("%d ", v))
	end
	print("")
end
