package main 

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func getFileString(fileName string) (string, error) {
	contents, err := ioutil.ReadFile(fileName)
	if err != nil {
		fmt.Printf("[ERROR] Failed to read file: %s\n", err)
		return "", err
	}

	return string(contents), nil
}

func stripString(str string) string {
	strippedStr := str

	strippedStr = strings.Replace(strippedStr, RED_START_CHAR, "", -1)
	strippedStr = strings.Replace(strippedStr, BLUE_START_CHAR, "", -1)
	strippedStr = strings.Replace(strippedStr, CYAN_START_CHAR, "", -1)
	strippedStr = strings.Replace(strippedStr, YELLOW_START_CHAR, "", -1)
	strippedStr = strings.Replace(strippedStr, RED_END_CHAR, "", -1)
	strippedStr = strings.Replace(strippedStr, BLUE_END_CHAR, "", -1)
	strippedStr = strings.Replace(strippedStr, CYAN_END_CHAR, "", -1)
	strippedStr = strings.Replace(strippedStr, YELLOW_END_CHAR, "", -1)

	return strippedStr
}

