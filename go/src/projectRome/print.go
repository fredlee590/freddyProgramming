package main 

import (
	"fmt"
	"regexp"
	"strings"
	"strconv"
)

const CLR = "\x1B[0m"
const RED = "\x1B[31;1m"
const BLUE = "\x1B[34;1m"
const CYAN = "\x1B[36;1m"
const YELLOW = "\x1B[33;1m"

const RED_START_CHAR = "{"
const BLUE_START_CHAR = "<"
const CYAN_START_CHAR = "("
const YELLOW_START_CHAR = "+"

const RED_END_CHAR = "}"
const BLUE_END_CHAR = ">"
const CYAN_END_CHAR = ")"
const YELLOW_END_CHAR = "-"

func PrintRaw(fileName string) {
	rawStr, err := getFileString(fileName)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(rawStr)
	}
}

func PrintStripped(fileName string, oneline bool) {
	rawStr, err := getFileString(fileName)
	if err != nil {
		fmt.Println(err)
	} else {
		strippedStr := stripString(rawStr)
		if oneline {
			strippedStr = strings.Replace(strippedStr, "\n", "", -1)
		}
		fmt.Println(strippedStr)
	}
}

func PrintWithColor(fileName string, oneline bool) {
	rawStr, err := getFileString(fileName)
	if err != nil {
		fmt.Println(err)
	} else {
		colorStr := colorizeString(rawStr)
		if oneline {
			colorStr = strings.Replace(colorStr, "\n", "", -1)
		}
		fmt.Println(colorStr)
	}
}

func PrintChars(fileName, color string) {
	rawStr, err := getFileString(fileName)
	if err != nil {
		fmt.Println(err)
	} else {
		var startChar string
		var endChar string
		oneLineStr := strings.Replace(rawStr, "\n", "", -1)
		switch color {
		case "blue":
			startChar = BLUE_START_CHAR
			endChar = BLUE_END_CHAR
		case "cyan":
			startChar = CYAN_START_CHAR
			endChar = CYAN_END_CHAR
		case "yellow":
			startChar = YELLOW_START_CHAR
			endChar = YELLOW_END_CHAR
		case "red":
			startChar = RED_START_CHAR
			endChar = RED_END_CHAR
		default:
			fmt.Println("Unknown color")
			return
		}

		oneLineStr = strings.Replace(oneLineStr, fmt.Sprintf("%s%s", endChar, startChar), "", -1)

		re := regexp.MustCompile(fmt.Sprintf("\\%s[0-9a-z]+\\%s", startChar, endChar))
		colorChars := re.FindAllString(oneLineStr, -1)
		allChars := ""
		for _, c := range colorChars {
			ch := strings.Replace(c, startChar, "", -1)
			ch = strings.Replace(ch, endChar, "", -1)
			allChars += ch
		}

		fmt.Println(allChars)

		curChar := ""
		for i, c := range allChars {
			curChar += fmt.Sprintf("%c", c)
			if i % 3 == 2 {
				curInt, _ := strconv.Atoi(curChar)
				fmt.Printf("%c", curInt)
				curChar = ""
			}
		}

		fmt.Println()
	}
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
	colorStr = strings.Replace(colorStr, YELLOW_START_CHAR, YELLOW, -1)
	//fmt.Println(colorStr)
	colorStr = strings.Replace(colorStr, YELLOW_END_CHAR, CLR, -1)
	//fmt.Println(colorStr)

	return colorStr
}
