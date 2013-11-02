#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Component.h"

class Object{
public:
	void update(){
		for(auto& i : components){
			i.second->update();
		}
	}

	void addComponent(std::shared_ptr<Component> component){
		components[component->getKeyString()] = component;
		component->object = this;
	}

	bool hasComponent(std::string key) const{
		return components.find(key) != components.end();
	}

	std::shared_ptr<Component> getComponent(std::string key){
		auto com = components.find(key);
		return com != components.end() ? com->second : std::shared_ptr<Component>();
	}

	template<class T>
	std::shared_ptr<T> getComponentAs(std::string key){
		auto com = getComponent(key);
		return std::dynamic_pointer_cast<T>(com);
	}

protected:
	std::unordered_map<std::string, std::shared_ptr<Component>> components;
};
