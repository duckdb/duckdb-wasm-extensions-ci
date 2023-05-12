#pragma once
#include "spatial/common.hpp"
#include "spatial/core/geometry/geometry_factory.hpp"
#include "spatial/geos/geos_wrappers.hpp"
namespace spatial {

namespace geos {


struct GEOSFunctionLocalState : FunctionLocalState {
public:
	GeosContextWrapper ctx;
	core::GeometryFactory factory;

public:
	explicit GEOSFunctionLocalState(ClientContext &context);
	static unique_ptr<FunctionLocalState> Init(ExpressionState &state, const BoundFunctionExpression &expr,
	                                           FunctionData *bind_data);
	static unique_ptr<FunctionLocalState> InitCast(CastLocalStateParameters &parameters);
	static GEOSFunctionLocalState &ResetAndGet(ExpressionState &state);
	static GEOSFunctionLocalState &ResetAndGet(CastParameters &parameters);
};

} // namespace core

} // namespace spatial