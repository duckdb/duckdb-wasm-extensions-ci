#include "spatial/common.hpp"
#include "spatial/core/types.hpp"
#include "spatial/geos/functions/scalar.hpp"
#include "spatial/geos/functions/common.hpp"
#include "spatial/geos/geos_wrappers.hpp"

#include "duckdb/parser/parsed_data/create_scalar_function_info.hpp"
#include "duckdb/common/vector_operations/unary_executor.hpp"
#include "duckdb/common/vector_operations/binary_executor.hpp"


namespace spatial {

namespace geos {

using namespace spatial::core;

static void IntersectionFunction(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &lstate = GEOSFunctionLocalState::ResetAndGet(state);
	BinaryExecutor::Execute<string_t, string_t, string_t>(args.data[0], args.data[1], result, args.size(), [&](string_t left, string_t right) {
		auto left_geom = lstate.factory.Deserialize(left);
		auto right_geom = lstate.factory.Deserialize(right);
		auto left_geos_geom = lstate.ctx.FromGeometry(left_geom);
		auto right_geos_geom = lstate.ctx.FromGeometry(right_geom);

		auto geos_result = left_geos_geom.Intersection(right_geos_geom);
		auto result_geom = lstate.ctx.ToGeometry(lstate.factory, geos_result.get());
		return lstate.factory.Serialize(result, result_geom);
	});
}

void GEOSScalarFunctions::RegisterStIntersection(ClientContext &context) {
	auto &catalog = Catalog::GetSystemCatalog(context);

	ScalarFunctionSet set("ST_Intersection");

	set.AddFunction(ScalarFunction({GeoTypes::GEOMETRY(), GeoTypes::GEOMETRY()}, GeoTypes::GEOMETRY(), IntersectionFunction, nullptr, nullptr, nullptr, GEOSFunctionLocalState::Init));

	CreateScalarFunctionInfo info(std::move(set));
	info.on_conflict = OnCreateConflict::ALTER_ON_CONFLICT;
	catalog.CreateFunction(context, info);
}

} // namespace spatials

} // namespace spatial
