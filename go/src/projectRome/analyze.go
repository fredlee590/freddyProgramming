package main

import (
	"fmt"
	"strings"
)

func AnalyzeCount(fileName string, maxCombo, threshold int) error {
	rawStr, err := getFileString(fileName)
	if err != nil {
		return err
	} else {
		strippedStr := stripString(rawStr)
		for i := 0; i < maxCombo; i++ {
			comboStr := fmt.Sprintf("%.3d", i)
			count := strings.Count(strippedStr, comboStr)
			if count > threshold {
				fmt.Printf("%s: %d (%c)\n", comboStr, count, i)
			}
		} 
	}
	return nil
}
