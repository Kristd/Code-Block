package com.model.facade;

public class Facade {
	private Sms 	sms;
	private Email 	email;
	
	public Facade() {
		sms 	= new Sms();
		email 	= new Email();
	}
	
	public boolean init() {
		boolean ret = false;
		
		if(sms.init() && email.init()) {
			ret = true;
		}
		
		return ret;
	}
}
