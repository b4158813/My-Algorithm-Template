package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

func solve(in *bufio.Reader, out *bufio.Writer) {
	var n int
	fmt.Fscan(in, &n)

	return
}

func run(_r io.Reader, _w io.Writer) {
	in := bufio.NewReader(_r)
	out := bufio.NewWriter(_w)
	defer out.Flush()

	cases := 1
	// fmt.Fscan(in, &cases)
	for curCase := 1; curCase <= cases; curCase++ {
		solve(in, out)
	}

	/* Uncomment before submitting if there are multi testcases */
	// leftData, _ := io.ReadAll(in)
	// if s := strings.TrimSpace(string(leftData)); s != "" {
	// 	panic("Unread data exists:\n" + s)
	// }
}

func main() { run(os.Stdin, os.Stdout) }
