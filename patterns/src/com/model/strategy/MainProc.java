/*
 * 	策略模式
 * 	1）container封装具体业务逻辑，使对外的调用业务接口一致
 * 	2）container统一返回调用的接口，改变业务逻辑不需要改变具体的接口
 * 
 * */

package com.model.strategy;

public class MainProc {

	public static void main(String[] args) {
		Container container = new Container();
		container.setStrategy(new StrategyA());
		container.RunStrategy();
	}

}
