#include "BaseClass.h"
#include "ClassFactory.h"
#include <string>
using namespace std;


typedef void* (*createObject)(void);

class ClassFactory {
private:
    map<string, createObject> m_classMap;
    ClassFactory() {};

public:
    void* getClassByName(string className) {
	map<string, createObject>::const_iterator iter;
	iter = m_classMap.find(className);
	if (iter == m_classMap.end()) {
	    return NULL;
	}
	else {
	    return iter->second();
	}
    }

    void registClass(string name, createObject method) {
        m_classMap.insert(pair<string, createObject>(name, method));
    }

    static ClassFactory& getInstance() {
	static ClassFactory m_factory;
        return m_factory;
    }
};

class Register {
public:
    Register(string className, createObject pCreateFn) {
        ClassFactory::getInstance().registClass(className, pCreateFn);
    }
};

#define REGISTER(className)                                             \
    className* getInstant##className() {                                \
        return new className;                                           \
    }                                                                   \
    Register g_creatorRegister##className(#className, (createObject)getInstant##className)

class BaseClass {
public:
    virtual void showInfo() = 0;
};

class DeviceA : public BaseClass {
public:
    void showInfo() {
        cout<<"I am Device A"<<endl;
    };
};
REGISTER(DeviceA);

class DeviceB : public BaseClass {
public:
    void showInfo() {
        cout<<"I am Device B"<<endl;
    };
};
REGISTER(DeviceB);


int Reflect() {
    string strDev[2] = {"DeviceA", "DeviceB"};

    BaseClass* ptrObj = (BaseClass*)ClassFactory::getInstance().getClassByName(strDev[0]);
    ptrObj->showInfo();
    return 0;
}

