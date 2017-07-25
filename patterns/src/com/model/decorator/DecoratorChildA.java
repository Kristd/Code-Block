package com.model.decorator;

public class DecoratorChildA extends Decorator {

	public DecoratorChildA(IBase component) {
		super(component);
	}
	
	@Override
	public void Show() {
		System.out.print("Decorator child A begin.\n");
		super.Show();
		System.out.print("Decorator child A end.\n");
	}
}
