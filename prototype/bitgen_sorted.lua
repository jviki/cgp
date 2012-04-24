local base = {
	[0xaaaaaaaa] = 0xfffffffe,
	[0xcccccccc] = 0xfffefee8,
	[0xf0f0f0f0] = 0xfee8e880,
	[0xff00ff00] = 0xe8808000,
	[0xffff0000] = 0x80000000
}

function derive_output(vec)
	local result = {}

	for _, v in ipairs(vec) do
		if v == 0xffffffff then
			table.insert(result, 1, v)
		elseif base[v] ~= nil then
			table.insert(result, base[v])
		end
	end

	local rest = #vec - #result
	for i = 1, rest do
		table.insert(result, 0)
	end

	return result
end

local inputs = arg[1] and tonumber(arg[1]) or 8
local vec = {}

for line in io.lines() do
	local num = tonumber(string.match(line, "0x%x+"))
	
	table.insert(vec, num)
	
	if #vec == inputs then
		for _, v in ipairs(derive_output(vec)) do
			print(string.format("0x%08x", v))
		end

		vec = {}
	end
end
