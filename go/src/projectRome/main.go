package main

import (
	"fmt"
	"os"
)

func main() {
	if len(os.Args) != 3 {
		fmt.Println("FWIW, it worked! But I know this is terrible code. TODO: FIX EVERYTHING.")
		fmt.Println("Need exactly two arguments: to describe file name")
		fmt.Println("1) File name of cipher text. NOTE: This file needs the color delimiters!")
		fmt.Println("2) Command to execute. Options are")
		fmt.Println("   print")
		fmt.Println("   print-raw")
		fmt.Println("   print-oneline")
		fmt.Println("   print-color")
		fmt.Println("   print-red")
		fmt.Println("   print-yellow")
		fmt.Println("   print-blue")
		fmt.Println("   print-cyan")
		fmt.Println("   analyze-count")
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
		PrintStripped(fileName, false)
	case "print-oneline":
		fmt.Println("Printing file with color markers parsed out. One line.")
		PrintStripped(fileName, true)
	case "print-color":
		fmt.Println("Printing file with color applied.")
		PrintWithColor(fileName, false)
	case "print-oneline-color":
		fmt.Println("Printing file with color markers parsed out. One line.")
		PrintWithColor(fileName, true)
	case "print-cyan":
		fmt.Println("Printing only cyan characters.")
		PrintChars(fileName, "cyan")
	case "print-yellow":
		fmt.Println("Printing only yellow characters.")
		PrintChars(fileName, "yellow")
	case "print-blue":
		fmt.Println("Printing only blue characters.")
		PrintChars(fileName, "blue")
	case "print-red":
		fmt.Println("Printing only red characters.")
		PrintChars(fileName, "red")
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
