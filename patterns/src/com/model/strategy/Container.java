package com.model.strategy;

public class Container {
	private IStrategy m_strategy;
	
	void setStrategy(IStrategy strategy) {
		this.m_strategy = strategy;
	}
	
	void RunStrategy() {
		m_strategy.Show();
	}
}
