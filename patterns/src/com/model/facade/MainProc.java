/**
 * 	外观模式
 * 	1）通过一个统一的接口交互
 * 	2）即使系统后台设计复杂，通过重新设计封装一个简单的交互接口，
 * 	   使前端调用后台功能变得简单易维护
 * 
 * */

package com.model.facade;

public class MainProc {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Facade facade = new Facade();
		facade.init();
	}
}
