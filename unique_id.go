package main

import (
	"fmt"
	"os"
	"sort"
	"strconv"
)

func id(x1, y1, x2, y2, w, h uint64) uint64 {
	return ((y1*w+x1)*w+x2)*h + y2
}

func decrypt(i, w, h uint64) (x1, y1, x2, y2 uint64) {
	y2 = i % h
	c := (i - y2) / h
	x2 = c % w
	c = (c - x2) / w
	x1 = c % w
	y1 = (c - x1) / w
	return
}

func checkConsistency(c map[uint64]bool) {
	n := uint64(len(c))
	inc := false
	for i := uint64(0); i < n; i++ {
		if _, e := c[i]; !e {
			fmt.Printf("Inconsistency: item c[%d] does not exist.\n", i)
			inc = true
		}
	}
	if !inc {
		fmt.Println("Collection is consistent.")
	}
}

type v_uint64 []uint64

func (v v_uint64) Len() int           { return len(v) }
func (v v_uint64) Swap(i, j int)      { v[i], v[j] = v[j], v[i] }
func (v v_uint64) Less(i, j int) bool { return v[i] < v[j] }
func printIndices(c map[uint64]bool) {
	v := make(v_uint64, len(c))
	var j int
	for i, _ := range c {
		v[j] = i
		j++
	}
	sort.Sort(v)
	fmt.Println("Collection indices:")
	var l int
	for i := range v {
		fmt.Printf("  index [%d] exists\n", v[i])
		if v[i] == 0 {
			l++
		}
	}
	fmt.Printf("There are %d and there should be %d indices.\n", len(c), len(v)-l+1)
}

func cmp(x1, y1, x2, y2, p1, p2, q1, q2 uint64) bool {
	return x1 == p1 && y1 == p2 && x2 == q1 && y2 == q2
}

func subRects(w, h int) int {
	return w * (w + 1) * h * (h + 1) / 4
}

func main() {
	if len(os.Args) != 3 {
		fmt.Printf("Usage %s w h\n  w - image width\n  h - image height\n", os.Args[0])
		return
	}
	w, _ := strconv.Atoi(os.Args[1])
	h, _ := strconv.Atoi(os.Args[2])
	n := w * h
	var conf int
	var sq int

	u := make(map[uint64]bool)
	for i := 0; i < n; i++ {
		y, x := i/w, i%w
		for l := y; l < h; l++ {
			for j := x; j < w; j++ {
				v := id(uint64(x), uint64(y), uint64(j), uint64(l), uint64(w), uint64(h))
				_, e := u[v]
				p, q, r, s := decrypt(v, uint64(w), uint64(h))
				if e || !cmp(uint64(x), uint64(y), uint64(j), uint64(l), p, q, r, s) {
					fmt.Printf("Conflict! (x1, y1, x2, y2) = (%d, %d, %d, %d) = %d <=> "+
						"(%d, %d, %d, %d)\n", x, y, j, l, v, p, q, r, s)
					conf++
				}
				u[v] = true
				sq++
			}
		}
	}
	nsq := subRects(w, h)
	var str string
	if conf == 0 {
		str = fmt.Sprintf("No conflicts!")
	} else {
		str = fmt.Sprintf("Found %d conflicts!", conf)
	}
	fmt.Printf("Result: %d stored instances. Should be %d instances.\nEquals? %v\n%s\n", sq, nsq,
		nsq == sq, str)
	//checkConsistency(u)
	printIndices(u)
}
