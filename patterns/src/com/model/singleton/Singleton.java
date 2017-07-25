package com.model.singleton;

public class Singleton {
	private static Singleton m_instance = null;
	private static Object mutex = new Object();
	
	private Singleton(){}
	
	public static Singleton GetInstance() {
		if(null == m_instance) {
			synchronized(mutex) {
				if(null == m_instance) {
					m_instance = new Singleton();
				}
			}
		}
		
		return m_instance;
	}
	
	public void Show() {
		System.out.print("i am singleton");;
	}
}
