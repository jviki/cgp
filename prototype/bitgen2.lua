function bitgen2_init(k)
	local vec = {
		0xaaaaaaaa,
		0xcccccccc,
		0xf0f0f0f0,
		0xff00ff00,
		0xffff0000
	}

	for i = #vec + 1, k do
		table.insert(vec, 0x00000000)
	end

	return vec
end

function bitgen2_2tok(vec, k)
	local flip = true

	for i = 6, k do
		if not flip then
			break
		end

		if flip and vec[i] == 0x00000000 then
			flip = false
			vec[i] = 0xffffffff
		elseif flip and vec[i] == 0xffffffff then
			flip = true
			vec[i] = 0x00000000
		end
	end

	return vec
end

local K = arg[1] and tonumber(arg[1]) or 8
local vec = bitgen2_init(K)

for i = 1, 2 ^ K / 32 do
	for j = 1, K do
		print(string.format("0x%08x", vec[j]))
	end

	vec = bitgen2_2tok(vec, K)
end
