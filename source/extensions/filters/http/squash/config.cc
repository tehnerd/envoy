#include "extensions/filters/http/squash/config.h"

#include "envoy/config/filter/http/squash/v2/squash.pb.validate.h"
#include "envoy/registry/registry.h"

#include "common/protobuf/protobuf.h"
#include "common/protobuf/utility.h"

#include "extensions/filters/http/squash/squash_filter.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Squash {

Http::FilterFactoryCb SquashFilterConfigFactory::createFilterFactoryFromProtoTyped(
    const envoy::config::filter::http::squash::v2::Squash& proto_config, const std::string&,
    Server::Configuration::FactoryContext& context) {

  SquashFilterConfigSharedPtr config = std::make_shared<SquashFilterConfig>(
      SquashFilterConfig(proto_config, context.clusterManager()));

  return [&context, config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
        std::make_shared<SquashFilter>(config, context.clusterManager()));
  };
}

/**
 * Static registration for the squash filter. @see RegisterFactory.
 */
REGISTER_FACTORY(SquashFilterConfigFactory, Server::Configuration::NamedHttpFilterConfigFactory);

} // namespace Squash
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
