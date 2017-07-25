package com.model.builder;

public class CarBuilder implements IBuilder {
	private IProduct car;
	
	@Override
	public IProduct GetResult() {
		return car;
	}

	@Override
	public void BuildProd(String item) {
		car = new Car();
		car.consStr(item);
	}
}
