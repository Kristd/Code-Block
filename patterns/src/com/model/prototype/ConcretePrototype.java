package com.model.prototype;

public class ConcretePrototype implements Prototype {
	
	public class Var implements Prototype{
		public Var clone() {
			try {
				return (Var) super.clone();
			} catch (CloneNotSupportedException e) {
				e.printStackTrace();
			}
			
			return null;
		}
	}
	
	public String Name;
	public Var var;
	
	@Override
	public ConcretePrototype clone() {
		ConcretePrototype ret;
		try {
			ret = (ConcretePrototype) super.clone();
			ret.var = this.var;
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		
		return null;
	}
}
