package main

import (
	"fmt"
	"gonum.org/v1/gonum/stat/distuv"
	"os"
	"strconv"
)

func main() {
	if len(os.Args) < 4 {
		fmt.Printf("Returns the probability of a value in a Gaussian given mean and standard deviation."+
			"\nUsage: %s x mu sigma p\n"+
			"  x     - value\n"+
			"  mu    - mean\n"+
			"  sigma - standard deviation\n"+
			"  p     - precision display (digits)\n", os.Args[0])
		os.Exit(1)
	}
	x, e := strconv.ParseFloat(os.Args[1], 64)
	if e != nil {
		fmt.Printf("Value '%s' invalid. Requires floating point.\n", os.Args[1])
	}
	mu, e := strconv.ParseFloat(os.Args[2], 64)
	if e != nil {
		fmt.Printf("Mean '%s' invalid. Requires floating point.\n", os.Args[2])
	}
	sigma, e := strconv.ParseFloat(os.Args[3], 64)
	if e != nil {
		fmt.Printf("Standard deviation '%s' invalid. Requires floating point.\n", os.Args[3])
	}
	p := 5
	if len(os.Args) > 4 {
		p, e = strconv.Atoi(os.Args[4])
		if e != nil {
			fmt.Printf("Precision '%s' invalid. Requires integer.\n", os.Args[4])
		}
	}

	g := distuv.Normal{mu, sigma, nil}
	fmt.Printf("Pr(X=%.*f) =  %.*f\nln(Pr(X=%.*f)) = %.*f\n", p, x, p, g.Prob(x), p, x, p, g.LogProb(x))
}
