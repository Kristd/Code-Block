package com.model.absfactory;

public class AppleFactory implements IFactory {
	public IProduct PhoneProd() {
		return new ApplePhone();
	}

	public IProduct TabletProd() {
		return new AppleTablet();
	}
}
