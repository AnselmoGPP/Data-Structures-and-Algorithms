// Creational patterns
#include "abstract_factory.hpp"
#include "builder.hpp"
#include "factory_method.hpp"
#include "object_pool.hpp"
#include "prototype.hpp"
#include "singleton.hpp"

// Structural patterns
#include "adapter_class.hpp"
#include "adapter_object.hpp"
#include "bridge.hpp"
#include "composite.hpp"
#include "decorator.hpp"
#include "facade.hpp"
#include "flyweight.hpp"
//#include "private_class_data.hpp"
#include "proxy.hpp"

// Behavioral patterns
#include "chain_of_responsability.hpp"
#include "command.hpp"
#include "interpreter.hpp"
#include "iterator.hpp"
#include "mediator.hpp"
#include "memento.hpp"
#include "null_object.hpp"
#include "observer.hpp"
#include "state.hpp"
#include "strategy.hpp"
#include "template_method.hpp"
#include "visitor.hpp"


int main()
{
	// Creational patterns
	test_abstract_factory();
	test_builder();
	test_factory_method();
	test_object_pool();
	test_prototype();
	test_singleton();

	// Structural patterns
	//test_adapter_class();
	//test_adapter_object();
	//test_bridge();
	//test_composite();
	//test_decorator();
	//test_facade();
	//test_flyweight();
	//test_private_class_data();
	//test_proxy();

	// Behavioral patterns
	//test_chain_of_responsability();
	//test_command();
	//test_interpreter();
	//test_iterator();
	//test_mediator();
	//test_memento();
	//test_null_object();
	//test_observer();
	//test_state();
	//test_strategy();
	//test_template_method();
	//test_visitor();

	std::cin.get();
}
