#pragma once

class Object;

class Component abstract{
	friend class Object;
public:
	Component():object(nullptr){}
	virtual ~Component(){}
	virtual void update(){}
	virtual const std::string& getKeyString() const = 0;
	Object* getObject(){ return object; }
private:
	Object* object;
};
