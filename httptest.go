package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
)

func main() {
	value := url.Values{}

	value.Set("method", "push_msg_to_uid")
	value.Set("appid", "1")
	value.Set("msgtype", "401")
	value.Set("uidlist", "[50020843]")
	value.Set("timestamp", "")
	value.Set("sign", "")
	value.Set("message", `{"title":"MyTitle","desc":"MyDesc","payload":{"foregroundNotify_ctrl":2,"pushId":"1810000000000000001","pushTitle":"MyTestTitle","pushtext":"MyTestContent","skiplink":"yymobile://Channel/Live/54880976/54880976?tpl=16777217","skiptype":0,"type":1},"notification_ctrl":"1","notify_type":"1"}`)

	resp, err := http.PostForm("http://yypush.yy.com/v2/push_msg", value)

	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	fmt.Println("response Status:", resp.Status)
	fmt.Println("response Headers:", resp.Header)
	body, _ := ioutil.ReadAll(resp.Body)
	fmt.Println("response Body:", string(body))
}
