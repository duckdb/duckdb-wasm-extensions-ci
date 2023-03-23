#pragma once
#include "geo/common.hpp"
#include "geo/core/geometry/geometry_factory.hpp"
#include "geo/geos/geos_wrappers.hpp"
namespace geo {

namespace geos {


struct GEOSFunctionLocalState : FunctionLocalState {
public:
	GeosContextWrapper ctx;
	core::GeometryFactory factory;

public:
	explicit GEOSFunctionLocalState(ClientContext &context);
	static unique_ptr<FunctionLocalState> Init(ExpressionState &state, const BoundFunctionExpression &expr,
	                                           FunctionData *bind_data);
	static unique_ptr<FunctionLocalState> InitCast(ClientContext &context);
	static GEOSFunctionLocalState &ResetAndGet(ExpressionState &state);
	static GEOSFunctionLocalState &ResetAndGet(CastParameters &parameters);
};

} // namespace core

} // namespace geo