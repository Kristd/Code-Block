package main

import (
	"fmt"
	"time"
)

func main() {
	//初始化断续器,间隔2s
	sign := make(chan byte, 1)
	var ticker *time.Ticker = time.NewTicker(5 * time.Second)

	go func() {
		for t := range ticker.C {
			fmt.Println("Tick at", t)
		}
	}()

	//time.Sleep(time.Second * 60) //阻塞，则执行次数为sleep的休眠时间/ticker的时间
	//ticker.Stop()
	<-sign
	fmt.Println("Ticker stopped")
}
