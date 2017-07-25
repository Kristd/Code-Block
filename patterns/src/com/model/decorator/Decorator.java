package com.model.decorator;

public class Decorator extends Phone {
	private Phone object;
	
	public void setDecorator(Phone object) {
		this.object = object;
	}
	
	public void Show() {
		object.Show();
		System.out.print("dec");
	}
}
