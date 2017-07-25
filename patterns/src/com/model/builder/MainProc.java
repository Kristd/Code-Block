/*
 * 	建造模式
 * 	1）四个功能独立的角色builder, concrete builder, director, product
 * 	2）
 * 
 * 
 * 
 * */

package com.model.builder;

public class MainProc {

	public static void main(String[] args) {
		IProduct house;
		IProduct car;
		
		String item4house = new String("door, windows");
		String item4car = new String("door, wheel");
		
		Director dir;
		
		dir = new Director(new HouseBulider());
		house = dir.Produce(item4house);
		house.Show();
		
		dir = new Director(new CarBuilder());
		car = dir.Produce(item4car);
		car.Show();
	}

}
