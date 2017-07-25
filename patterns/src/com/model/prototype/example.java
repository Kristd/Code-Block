package com.model.prototype;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

/*****************************************
*	原型模式中的拷贝分为"浅拷贝"和"深拷贝":
*	浅拷贝: 对值类型的成员变量进行值的复制,对引用类型的成员变量只复制引用,不复制引用的对象.
*	深拷贝: 对值类型的成员变量进行值的复制,对引用类型的成员变量也进行引用对象的复制.
******************************************/

public class example {
	/*****************
	*	实例一:浅拷贝
	******************/
	public class PrototypeEx1 implements Cloneable {
		private String name;

		public String getName() {
			return name;
		}

		public void setName(String name) {
			this.name = name;
		}

		public Object clone() {
			try {
				return super.clone();
			} 
			catch (CloneNotSupportedException e) {   
				e.printStackTrace();
				return null;
			}
		} 
	}

	public class TestMain1 {
		public void main(String[] args) {
			PrototypeEx1 orgObj = new PrototypeEx1();
			orgObj.setName("original object");
			
			PrototypeEx1 cpObj = (PrototypeEx1)orgObj.clone();
			orgObj.setName("copy object");
			  
			System.out.println("original object:" + orgObj.getName());
			System.out.println("cloned object:" + cpObj.getName());
		}
	}
	/**********************************	
	*  	结果:
	*	original object:changed object1
	*	cloned object:original object
	***********************************/

	/*****************
	*	实例二: 浅拷贝
	******************/
	public class VarObjEx2 {
		private String name;

		public String getName() {
			return name;
		}

		public void setName(String name) {
			this.name = name;
		}
	}
	
	public class PrototypeEx2 implements Cloneable {
		private String id;
		private VarObjEx2 varObj;
		
		public String getId() {
			return id;
		}

		public void setId(String id) {
			this.id = id;
		}
	 
		public VarObjEx2 getVarObj() {
			return varObj;
		}

		public void setVarObj(VarObjEx2 varObj) {
			this.varObj = varObj;
		}

		public Object clone(){ 
			try {
				return super.clone();
			} 
			catch (CloneNotSupportedException e) {
				e.printStackTrace();
				return null;
			}  
		}
	}
	
	public class TestMain2 {
		public void main(String[] args) {
			VarObjEx2 var = new VarObjEx2();
			
			var.setName("original var");
			PrototypeEx2 orgObj = new PrototypeEx2();
			orgObj.setId("original object");
			orgObj.setVarObj(var);
		  
			PrototypeEx2 copyObj = (PrototypeEx2)orgObj.clone();
			copyObj.setId("copy object");
			copyObj.getVarObj().setName("copy var");
		  
			System.out.println("original object id:" + orgObj.getId());
			System.out.println("original object name:" + orgObj.getVarObj().getName());
		  
			System.out.println("cloned object id:" + copyObj.getId());
			System.out.println("cloned object name:" + copyObj.getVarObj().getName());
		}
	}
	/****************************************
	*	结果:
	*	original object id:test1
	*	original object name:changed object
	*	cloned object id:testCopy
	*	cloned object name:changed object
	*****************************************/

	/*****************
	*	实例三: 深拷贝
	******************/
	public class VarObjEx3 implements Cloneable {
		private String name;

		public String getName() {
			return name;
		}

		public void setName(String name) {
			this.name = name;
		}

		public Object clone() {
			try { 
				return super.clone();
			} 
			catch (CloneNotSupportedException e) {   
				e.printStackTrace();
				return null;
			}
		} 
	}

	public class PrototypeEx3 implements Cloneable {
		private String id;
		private VarObjEx3 var;
	 
		public String getId() {
			return id;
		}

		public void setId(String id) {
			this.id = id;
		}

		public VarObjEx3 getVarObj() {
			return var;
		}

		public void setVarObj(VarObjEx3 var) {
			this.var = var;
		}

		public Object clone(){
			PrototypeEx3 ret = null;
			
			try {
				ret = (PrototypeEx3)super.clone();
				ret.var = (VarObjEx3)this.var.clone();
				return ret;
			} 
			catch (CloneNotSupportedException e) {
				e.printStackTrace();
				return null;
			}  
		}
	}

	public class TestMain3 {
		public void main(String[] args) {
			VarObjEx3 var = new VarObjEx3();
			var.setName("original var");
			
			PrototypeEx3 orgObj = new PrototypeEx3();
			orgObj.setId("original object");
			orgObj.setVarObj(var);
		  
			PrototypeEx3 copyObj = (PrototypeEx3)orgObj.clone();
			copyObj.setId("copy object");
			copyObj.getVarObj().setName("copy var");
		  
			System.out.println("original object id:" + orgObj.getId());
			System.out.println("original object name:" + orgObj.getVarObj().getName());
		  
			System.out.println("cloned object id:" + copyObj.getId());
			System.out.println("cloned object name:" + copyObj.getVarObj().getName());
		}
	}
	/******************************************
	*	结果:
	*	original object id:test1
	*	original object name:original object
	*	cloned object id:testCopy
	*	cloned object name:changed object
	*******************************************/
	
	
	//实例四: 利用串行化来做深复制
	//把对象写道流里的过程是串行化(Serialization)过程;把对象从流中读出来是并行化(Deserialization)过程. 写在流里的是对象的一个拷贝,然后再从流里读出来重建对象.
	public class PrototypeSe implements Serializable {
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		private String name;

		public String getName() {
			return name;
		}

		public void setName(String name) {
			this.name = name;
		}
	}

	public class NewPrototypeSe implements Serializable {
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		private String id;
	 
		public String getId() {
			return id;
		}

		public void setId(String id) {
			this.id = id;
		}

		private PrototypeSe prototype;
	 
		public PrototypeSe getPrototype() {
			return prototype;
		}

		public void setPrototype(PrototypeSe prototype) {
			this.prototype = prototype;
		}
	 
		public Object deepClone(){
			try {
				ByteArrayOutputStream bo = new ByteArrayOutputStream();
				ObjectOutputStream oo = new ObjectOutputStream(bo);   
				oo.writeObject(this);   
	   
				ByteArrayInputStream bi = new ByteArrayInputStream(bo.toByteArray());
				ObjectInputStream oi = new ObjectInputStream(bi);
				return oi.readObject(); 
			} 
			catch (IOException | ClassNotFoundException e) {
				e.printStackTrace();
				return null;
			}
		}
	}

	public class TestDeepClone {
		public void main(String[] args) {
			PrototypeSe po = new PrototypeSe();
			po.setName("test1");
			NewPrototypeSe se = new NewPrototypeSe();
			se.setPrototype(po);
	  
			NewPrototypeSe deepClone = (NewPrototypeSe)se.deepClone();
			deepClone.getPrototype().setName("test2");
	  
	  	System.out.println("original name:" + se.getPrototype().getName());
	  	System.out.println("cloned name:" + deepClone.getPrototype().getName());
		}
	}
	/*	
		结果:
		original name:test1
		cloned name:test2
	*/
}
