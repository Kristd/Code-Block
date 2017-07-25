package com.model.decorator;

public class Component implements IBase {
	
	@Override
	public void Show() {
		System.out.print("Base component show.\n");
	}
}
