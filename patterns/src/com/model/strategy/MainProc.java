/*
 * 	����ģʽ
 * 	1��container��װ����ҵ���߼���ʹ����ĵ���ҵ��ӿ�һ��
 * 	2��containerͳһ���ص��õĽӿڣ��ı�ҵ���߼�����Ҫ�ı����Ľӿ�
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
