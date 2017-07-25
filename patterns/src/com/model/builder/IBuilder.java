package com.model.builder;

public interface IBuilder {
	IProduct GetResult();
	void BuildProd(String item);
}
