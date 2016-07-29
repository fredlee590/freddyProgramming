package main

import (
	"fmt"
	"os"
)

func main() {
	if len(os.Args) != 3 {
		fmt.Println("Need exactly two arguments: to describe file name")
		fmt.Println("1) File name of cipher text")
		fmt.Println("2) Command to execute")
		fmt.Println("Exiting!")
		os.Exit(1)
	}

	fmt.Println("=====================================================================================")
	fmt.Printf("Beginning a run of %s, the cipher analysis tool, with the following parameters.\n", os.Args[0])
	fileName := os.Args[1]
	command := os.Args[2]
	fmt.Printf("File name: %s\n", fileName)
	fmt.Printf("Command: %s\n", command)
	fmt.Println("=====================================================================================")

	fmt.Println()

	// validate file name
	if _, err := os.Stat(fileName); err != nil {
		fmt.Printf("Failed to stat file %s:\n(%s)\n", fileName, err)
		os.Exit(2)
	}

	// validate command
	switch command {
	case "print-raw":
		fmt.Println("Printing raw file.")
		PrintRaw(fileName)
	case "print":
		fmt.Println("Printing file with color markers parsed out.")
		PrintStripped(fileName)
	case "print-color":
		fmt.Println("Printing file with color applied.")
		PrintWithColor(fileName)
	case "analyze-count":
		fmt.Println("Counting numerical patterns")
		// TODO: make these options. For now change manually and recompile
		if err := AnalyzeCount(fileName, 130, 0); err != nil {
			fmt.Println("Failed to count common patterns")
			fmt.Println(err)
		}
	default:
		fmt.Println("Unknown command")
		os.Exit(3)
	}
}
