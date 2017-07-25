package com.model.template;

public class MainProc {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Message msg = new Message();
		Handler emailHandler = new EmailHandler();
		Handler timingHandler = new TimingHandler();
		
		emailHandler.ProcessMail(msg);
		timingHandler.ProcessMail(msg);
	}

}
