function int2bits(v, width)
	local bits = {}

	while v > 0 do
		table.insert(bits, 1, v % 2)
		v = math.floor(v / 2)
	end

	local rest = (width or #bits) - #bits
	for i = 1, rest do
		table.insert(bits, 1, 0)
	end

	return bits
end

function bits2int(bits)
		local v = 0
		local f = 1

		for i = #bits, 1, -1 do
			if bits[i] ~= 0 then
				v = v + f
			end

			f = f * 2
		end

		return v
end

local width  = arg[1] and tonumber(arg[1]) or 32
local inputs = arg[2] and tonumber(arg[2]) or  8
local lineno = 0

for line in io.lines() do
	local num = tonumber(string.match(line, "(0x%x+)"))
	local bits = int2bits(num, inputs)

	table.sort(bits)
	print(string.format("0x%08x", bits2int(bits)))
end
