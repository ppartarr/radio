package main

import (
	"encoding/csv"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"strconv"
	"strings"

	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/plotutil"
	"gonum.org/v1/plot/vg"
)

func main() {
	// open data file
	file, err := os.Open("data.csv")
	if err != nil {
		log.Fatal(err.Error())
	}
	defer file.Close()

	// create plot
	p := plot.New()

	// customize plot
	p.Title.Text = "Radio Frequency Data Stream"
	p.X.Label.Text = "Timestamp (ms)"
	p.Y.Label.Text = "Buffer size (bytes)"

	// read from csv
	csvReader := csv.NewReader(file)
	records, err := csvReader.ReadAll()

	points := make(plotter.XYs, len(records))
	for index, record := range records {

		if err != nil {
			log.Fatal(err)
		}

		// parse timestamp & buffer size
		fmt.Println(record)
		timestamp, err := strconv.ParseFloat(record[0], 64)
		if err != nil {
			fmt.Println(err.Error())
		}

		bufferString := strings.Split(record[1], " ")
		bufferSize, err := strconv.ParseFloat(bufferString[1], 64)
		if err != nil {
			fmt.Println(err.Error())
		}

		// add points to graph
		points[index].X = timestamp
		points[index].Y = bufferSize // buffer length
	}

	err = plotutil.AddLinePoints(p,
		"RF 433MHz received buffer size (in bytes)",
		points,
	)

	if err != nil {
		panic(err)
	}

	// Save the plot to a PNG file.
	if err = p.Save(4*vg.Inch, 4*vg.Inch, filepath.Join("received"+".png")); err != nil {
		panic(err)
	}
}
