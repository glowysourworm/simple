#pragma once

#include <string>
#include <typeinfo>

namespace simple
{
	struct simpleType
	{
	public:

		simpleType(const std::type_info& typeInfo)
		{
			_name = new std::string(typeInfo.name());
		}
		simpleType(const simpleType& type)
		{
			_name = new std::string(type.getName());
		}
		~simpleType()
		{
			delete _name;
		}
		void operator=(const simpleType& type)
		{
			delete _name;
			_name = new std::string(type.getName());
		}
		bool operator==(const simpleType& type) const
		{
			return *_name == type.getName();
		}
		bool operator!=(const simpleType& type) const
		{
			return *_name != type.getName();
		}
		std::string getName() const
		{
			return *_name;
		}

	private:

		std::string* _name;
	};
}
