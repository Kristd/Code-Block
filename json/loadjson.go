package main

import (
	"encoding/json"
	"fmt"
)

type JsonConfig struct {
	m  map[string]interface{}
	rb []byte
}

type Msg_Create_Request struct {
	Action string                   `json:"action"`
	Config []map[string]interface{} `json:"conf"`
	UserID int                      `json:"id"`
}

type KeyWord struct {
	Key   string
	Text  string
	Image string
}

type AutoReplyConf struct {
	GroupName string
	KeyWords  []KeyWord
}

func main() {
	jsondata := "{\"action\":\"create\",\"id\":6,\"conf\":[{\"group\":\"广东麻将\",\"keywords\":[{\"keyword\":\"游戏\",\"cotent\":\"http://qyq.xoyo.com/h5/\",\"img\":\"/data/pic_tmp/bf3/510/a68/2ab.gif\"},{\"keyword\":\"管理员\",\"cotent\":\"现在有事，私聊我，等下回复你\"}]},{\"group\":\"湖南麻将\"}]}"
	//var jm map[string]interface{}
	mc := &Msg_Create_Request{}
	if err := json.Unmarshal([]byte(jsondata), mc); err != nil {
		fmt.Println("err = ", err)
	} else {
		fmt.Println("mc =", mc)

		replies := make([]AutoReplyConf, len(mc.Config))

		for i := 0; i < len(mc.Config); i++ {
			replies[i].GroupName, _ = mc.Config[i]["group"].(string)
			sections, succ := mc.Config[i]["keywords"].([]interface{})
			if succ {
				replies[i].KeyWords = make([]KeyWord, len(sections))

				for j := 0; j < len(sections); j++ {
					section, succ := sections[j].(map[string]interface{})
					if succ {
						replies[i].KeyWords[j].Key, _ = section["keyword"].(string)
						fmt.Println("replies[i].KeyWords[j].Key =", replies[i].KeyWords[j].Key)
					}
				}
			}
		}

		fmt.Println("Group =", mc.Config[0]["group"])
		fmt.Println("keywords =", mc.Config[0]["keywords"])

		v, _ := mc.Config[0]["keywords"].([]interface{})
		//fmt.Println("v =", v[0])
		vv, ok := v[0].(map[string]interface{})
		if ok {
			fmt.Println("keyword =", vv["keyword"])
			fmt.Println("cotent =", vv["cotent"])
		} else {
			fmt.Println("failed")
		}
	}
}
