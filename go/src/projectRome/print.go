package main 

import (
	"fmt"
	"io/ioutil"
	"strings"
)

const CLR = "\x1B[0m"
const RED = "\x1B[31;1m"
const BLUE = "\x1B[34;1m"
const CYAN = "\x1B[36;1m"

const RED_START_CHAR = "{"
const BLUE_START_CHAR = "<"
const CYAN_START_CHAR = "("

const RED_END_CHAR = "}"
const BLUE_END_CHAR = ">"
const CYAN_END_CHAR = ")"

func PrintRaw(fileName string) {
	rawStr, err := getFileString(fileName)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(rawStr)
	}
}

func PrintWithColor(fileName string) {
	rawStr, err := getFileString(fileName)
	if err != nil {
		fmt.Println(err)
	} else {
		colorStr := colorizeString(rawStr)
		fmt.Println(colorStr)
	}
}

func getFileString(fileName string) (string, error) {
	contents, err := ioutil.ReadFile(fileName)
	if err != nil {
		fmt.Printf("[ERROR] Failed to read file: %s\n", err)
		return "", err
	}

	return string(contents), nil
}

func colorizeString(str string) string {
	colorStr := str

	//fmt.Println(colorStr) // debugging print statements along the way

	colorStr = strings.Replace(colorStr, RED_START_CHAR, RED, -1)
	//fmt.Println(colorStr)
	colorStr = strings.Replace(colorStr, RED_END_CHAR, CLR, -1)
	//fmt.Println(colorStr)
	colorStr = strings.Replace(colorStr, BLUE_START_CHAR, BLUE, -1)
	//fmt.Println(colorStr)
	colorStr = strings.Replace(colorStr, BLUE_END_CHAR, CLR, -1)
	//fmt.Println(colorStr)
	colorStr = strings.Replace(colorStr, CYAN_START_CHAR, CYAN, -1)
	//fmt.Println(colorStr)
	colorStr = strings.Replace(colorStr, CYAN_END_CHAR, CLR, -1)
	//fmt.Println(colorStr)

	return colorStr
}
