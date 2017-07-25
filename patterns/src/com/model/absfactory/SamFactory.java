package com.model.absfactory;

public class SamFactory implements IFactory {
	public IProduct PhoneProd() {
		return new SamPhone();
	}

	public IProduct TabletProd() {
		return new SamTablet();
	}
}
