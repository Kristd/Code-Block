package com.model.builder;

public class Director {
	private IBuilder builder;
	
	public Director(IBuilder builder) {
		this.builder = builder;
	}
	
	public IProduct Produce(String item) {
		builder.BuildProd(item);
		return builder.GetResult();
	}
}
