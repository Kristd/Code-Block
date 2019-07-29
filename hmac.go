package main

import (
	"crypto/hmac"
	"crypto/sha1"
	"encoding/hex"
	"fmt"
)

func main() {
	message := []byte("appid1methodpush_msg_to_uidmsgtype401timestamp1558100703uidlist[50020843]")
	key := []byte("ae2cd3b8c57842b4895d6661057c66d3")
	mac := hmac.New(sha1.New, key)
	mac.Write(message)

	result1 := mac.Sum(nil)
	fmt.Println("mac.Sum:", result1)

	result2 := hex.EncodeToString(result1)
	fmt.Println("EncodeToString:", result2)
}
