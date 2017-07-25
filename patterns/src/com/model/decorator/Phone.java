package com.model.decorator;

public class Phone {
	private String name;
	
	public Phone(String name) {
		this.name = name;
	}
	
	public void Show() {
		System.out.print("i am a " + name);
	}
}
