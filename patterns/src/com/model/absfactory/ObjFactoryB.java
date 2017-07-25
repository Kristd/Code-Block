package com.model.absfactory;

public class ObjFactoryB implements IFactory {
	public Object ProdObject() {
		return new ObjectB();
	}
}
