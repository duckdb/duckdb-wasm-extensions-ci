#pragma once
#include "spatial/common.hpp"

namespace spatial {

namespace core {

struct CoreTableFunctions {
public:
	static void Register(DatabaseInstance &db) {
		RegisterOsmTableFunction(db);
		RegisterShapefileTableFunction(db);
	}

private:
	static void RegisterOsmTableFunction(DatabaseInstance &db);
	static void RegisterShapefileTableFunction(DatabaseInstance &db);
};

} // namespace core

} // namespace spatial