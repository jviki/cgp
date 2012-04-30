#! /bin/sh

run_cgp()
{
	./cgp | awk 'BEGIN {S=0} /Generation/ {G=$2}
	                         /Success/ {S=1; for(i = 3; i <= NF; ++i)
	                           {printf("%d%s", $i, i == NF? "\n" : " ") >> "success.chr"}}
									 END {print S, G}'
}

run_many_cgp()
{
	if [ -z $1 ]; then
		echo "Missing argument: how many times to run cgp?" > /dev/stderr
		return 1
	fi

	for i in `seq 1 $1`; do run_cgp; done 
}

cgp_stat()
{
	awk '{S+=$1; T+=1; if($1) {G+=$2}} END {print S, (T - S), S == 0? -1 : (G / S)}'
}

for i in `seq 1 16`; do
	run_many_cgp $1 | cgp_stat
done
