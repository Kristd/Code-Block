package com.model.template;

public abstract class Handler {
	private Message msg = new Message();
	
	abstract public void send();
	
	public void InQueue(Message msg) {
		System.out.print("put a message in queue.\n");;
	}
	
	public Message OutQueue() {
		System.out.print("get a message out of queue.\n");;
		return new Message();
	}
	
	public void ProcessMail(Message msg) {
		this.msg = msg;
		InQueue(this.msg);
		OutQueue();
		send();
	}
}
