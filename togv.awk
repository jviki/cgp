{
	W   = $1
	H   = $2
	ALL = W * H
	IN  = $3
	OUT = $4
	FIN = $5
	FOUT = $6

	LEN = 1 + FIN

	print "# " $0

	print "digraph chromo" NR " {"
	print "# " W "x" H " = " ALL
	print "# " IN ", " OUT
	print "# " FIN ", " FOUT
	print "# " NF

	FIRST = 7

	for(i = 0; i < IN; ++i)
		print "i" i " [shape=circle, regular=1, style=filled, fillcolor=yellow];"

	color = "blue"
	for(i = 0; i < ALL; ++i) {
		if(i % H == 0)
			color = color == "blue"? "green" : "blue"
		printf "n%d [shape=box, style=filled, fillcolor=%s];\n", i, color
	}

	for(i = 0; i < OUT; ++i)
		print "o" i " [shape=circle, regular=1, style=filled, fillcolor=red];"

	for(i = 0; i < H; ++i) {
		print "subgraph r" i " {"
		cindex = i
		
		for(j = 0; j < W; ++j) {
			s = FIRST + (i * LEN) + (j * H * LEN)
			print_cell(s, cindex + (j * H))
		}

		print "}"
	}

	OFFSET = NF - OUT + 1

	for(i = 0; i < OUT; ++i) {
		src = what_input($(OFFSET + i))
		dst = "o" i
		label = $(OFFSET + i) " to o" i 
		print src " -> " dst "[label=\"" label "\"];"
	}

	print "overlap = false;"
	print "label = \"chromosome " NR "\";"
	print "}"
}

# c ... offset of a cell
# i ... id of cell
function print_cell(c, i)
{
	f = $c

	if(f == -1) {
		print "# skipped n" i
		return
	}

	print "# " c, i, f
	print "n" i "[label=\"n" i "::" f "\"];"
	
	for(fi = 1; fi <= FIN; ++fi) {
		src = what_input($(c + fi))
		dst = "n" i
		label = $(c + fi) " to n" i "/" (fi - 1)
		print src " -> " dst " [label = \"" label "\"];" 
	}
}

# i ... index of input
function what_input(i)
{
	if(i < IN)
		return "i" i
	else
		return sprintf("n%d", ((i - IN) / FOUT))
}
