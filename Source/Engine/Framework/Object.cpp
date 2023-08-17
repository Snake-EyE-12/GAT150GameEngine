#include "Object.h"
namespace cg
{
	void Object::Read(const rapidjson::Value& value) {
		READ_DATA(value, name);
		
	}
}