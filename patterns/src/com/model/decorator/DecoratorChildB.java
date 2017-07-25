package com.model.decorator;

public class DecoratorChildB extends Decorator {
	
	public DecoratorChildB(IBase component) {
		super(component);
	}
	
	@Override
	public void Show() {
		System.out.print("Decorator child B begin.\n");
		super.Show();
		System.out.print("Decorator child B end.\n");
	}
}
