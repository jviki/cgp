#! /bin/bash

INPUTS=8
BWIDTH=32

gen_inputs()
{
	echo "gen_inputs" > /dev/stderr
	time lua bitgen2.lua $INPUTS
}

sort_inputs()
{
	echo "sort_inputs" > /dev/stderr
	time (lua bittrans.lua $BWIDTH $INPUTS | lua bitsort.lua $BWIDTH $INPUTS | lua bittrans.lua $INPUTS $BWIDTH l)
}

gen_sorted()
{
	echo "gen_sorted" > /dev/stderr
	time lua bitgen_sorted.lua $INPUTS
}

if [ -n "$1" ]; then
	INPUTS="$1"
	shift
fi
if [ -n "$1" ]; then
	BWIDTH="$1"
	shift
fi

FILE_INPUTS=inputs.$INPUTS"_"$BWIDTH
FILE_SORTED=sorted.$INPUTS"_"$BWIDTH
FILE_OUTPUTS=outputs.$INPUTS"_"$BWIDTH

gen_inputs > $FILE_INPUTS
gen_sorted < $FILE_INPUTS > $FILE_SORTED
sort_inputs < $FILE_INPUTS > $FILE_OUTPUTS

if diff $FILE_SORTED $FILE_OUTPUTS > /dev/null; then
	echo "OK"
else
	echo "Failed"
fi
