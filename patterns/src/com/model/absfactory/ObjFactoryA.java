package com.model.absfactory;

public class ObjFactoryA implements IFactory {
	public Object ProdObject() {
		return new ObjectA();
	}
}
