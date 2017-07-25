package com.model.builder;

public class HouseBulider implements IBuilder {
	private IProduct house;
	
	@Override
	public void BuildProd(String item) {
		house = new House();
		house.consStr(item);
	}

	@Override
	public IProduct GetResult() {
		return house;
	}
}
