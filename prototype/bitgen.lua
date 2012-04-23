function int2bits(v, width)
	local bits = {}

	while v > 0 do
		table.insert(bits, v % 2)
		v = math.floor(v / 2)
	end

	local rest = (width or #bits) - #bits
	for i = 1, rest do
		table.insert(bits, 0)
	end

	return bits
end

function reverse(t)
	local r = {}

	for i = #t, 1, -1 do
		table.insert(r, t[i])
	end

	return r
end

function bits2int(bits)
		local v = 0
		local f = 1

		for i = 1, #bits do
			if bits[i] ~= 0 then
				v = v + f
			end

			f = f * 2
		end

		return v
end

function asbits(value)
	if type(value) == "number" then
		return int2bits(b)
	elseif type(value) == "table" then
		return value
	elseif type(value) == "string" then
		return tonumber(value)
	end
end

function msb(value, width)
	local b = asbits(value)

	if b[width] ~= nil then
		return b[width]
	else
		return b[#b]
	end
end

function lsb(value)
	local b = asbits(value)
	return b[1]
end

function shift_msb_out(value, l)
	local b = asbits(value)
	local out = b[#b]

	for i = #b, 2, -1 do
		b[i] = b[i - 1]
	end

	b[1] = l or 0

	return b, out
end

function bits_ranges(bits, width)
	local ranges = {}
	local range = {}
	width = width or 8

	for i, v in ipairs(bits) do
		table.insert(range, v)

		if i % width == 0 then
			table.insert(ranges, range)
			range = {}
		end
	end

	return ranges
end

function bitgen_range(range, width)
	local data = {}

	for i = 0, range - 1 do
		table.insert(data, int2bits(i, width or 8))
	end

	return data
end

function bitgen_2tok(k, width)
	local vec = {}
	local dat = bitgen_range(2 ^ k, k)
	width = width or 8

	for i = 1, k do
		local bits = {}

		for _, d in ipairs(dat) do
			table.insert(bits, d[i])
		end

		vec[i] = {}
		for _, r in ipairs(bits_ranges(bits, width)) do
			table.insert(vec[i], bits2int(r))
		end
	end

	return vec
end

for _, v in ipairs(bitgen_2tok(9, 32)) do
	for i, d in ipairs(v) do
		io.stdout:write(string.format("0x%08x%s", d, i == #v and "" or " -> "))
	end

	print("")
end
