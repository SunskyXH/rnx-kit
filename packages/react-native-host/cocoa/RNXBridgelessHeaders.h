#if USE_BRIDGELESS

// clang-format off
#import "RNXFeatureMacros.h"
// clang-format on

#import <React/RCTSurfacePresenterBridgeAdapter.h>
#import <ReactCommon/RCTHost+Internal.h>
#import <ReactCommon/RCTHost.h>

#if USE_HERMES
#import <ReactCommon/RCTHermesInstance.h>
#else
#import <ReactCommon/RCTJscInstance.h>
#endif  // USE_HERMES

#ifdef USE_REACT_NATIVE_CONFIG
#import <react/config/ReactNativeConfig.h>
#endif  // USE_REACT_NATIVE_CONFIG

#ifdef USE_FEATURE_FLAGS
#import <react/featureflags/ReactNativeFeatureFlags.h>
#import <react/featureflags/ReactNativeFeatureFlagsDefaults.h>
#endif  // USE_FEATURE_FLAGS

#ifdef USE_CODEGEN_PROVIDER
#import <React/RCTComponentViewFactory.h>
#import <ReactCodegen/RCTThirdPartyComponentsProvider.h>
#endif  // USE_CODEGEN_PROVIDER

#if __has_include(<react/runtime/JSEngineInstance.h>)
using SharedJSRuntimeFactory = std::shared_ptr<facebook::react::JSEngineInstance>;
#else
using SharedJSRuntimeFactory = std::shared_ptr<facebook::react::JSRuntimeFactory>;
#endif  // __has_include(<react/runtime/JSEngineInstance.h>)

// For details, see
// https://github.com/facebook/react-native/commit/c3b0a8f1626939cf5c7b3864a5acf9d3dad26fb3
@interface RCTHost (Compatibility)
@property (nonatomic, readonly) RCTModuleRegistry *moduleRegistry;      // Introduced in 0.74
@property (nonatomic, readonly) RCTSurfacePresenter *surfacePresenter;  // Introduced in 0.74

// Introduced in 0.74
- (instancetype)initWithBundleURLProvider:(RCTHostBundleURLProvider)provider
                             hostDelegate:(id<RCTHostDelegate>)hostDelegate
               turboModuleManagerDelegate:
                   (id<RCTTurboModuleManagerDelegate>)turboModuleManagerDelegate
                         jsEngineProvider:(RCTHostJSEngineProvider)jsEngineProvider
                            launchOptions:(nullable NSDictionary *)launchOptions;

// Deprecated in 0.74
- (instancetype)initWithBundleURL:(NSURL *)bundleURL
                     hostDelegate:(id<RCTHostDelegate>)hostDelegate
       turboModuleManagerDelegate:(id<RCTTurboModuleManagerDelegate>)turboModuleManagerDelegate
                 jsEngineProvider:(RCTHostJSEngineProvider)jsEngineProvider;

- (RCTModuleRegistry *)getModuleRegistry;      // Deprecated in 0.74, and removed in 0.75
- (RCTSurfacePresenter *)getSurfacePresenter;  // Deprecated in 0.74, and removed in 0.75
@end

#ifdef USE_FEATURE_FLAGS

// https://github.com/facebook/react-native/blob/0.80-stable/packages/react-native/ReactCommon/react/featureflags/ReactNativeFeatureFlagsOverridesOSSStable.h
class RNXBridgelessFeatureFlags : public facebook::react::ReactNativeFeatureFlagsDefaults
{
public:
#ifdef USE_UNIFIED_FEATURE_FLAGS  // >= 0.77
    bool enableBridgelessArchitecture() override
    {
        return true;
    }
    bool enableFabricRenderer() override
    {
        return true;
    }
    bool useTurboModules() override
    {
        return true;
    }
    bool useNativeViewConfigsInBridgelessMode() override
    {
        return true;
    }
#if USE_VIEW_COMMAND_RACE_FIX  // 0.77
    bool enableFixForViewCommandRace() override
    {
        return true;
    }
#endif                                             // USE_VIEW_COMMAND_RACE_FIX
#if USE_UPDATE_RUNTIME_SHADOW_NODE_REFS_ON_COMMIT  // >= 0.79
    bool useShadowNodeStateOnClone() override
    {
        return true;
    }
#endif  // USE_UPDATE_RUNTIME_SHADOW_NODE_REFS_ON_COMMIT
#else   // < 0.77
    bool useModernRuntimeScheduler() override
    {
        return true;
    }

    bool enableMicrotasks() override
    {
        return true;
    }

    bool batchRenderingUpdatesInEventLoop() override
    {
        return true;
    }
#endif  // USE_UNIFIED_FEATURE_FLAGS
};
#endif  // USE_FEATURE_FLAGS

#elif USE_FABRIC

#import <React/RCTSurfacePresenterBridgeAdapter.h>
#import <react/config/ReactNativeConfig.h>

@class RCTHost;

#else

@class RCTHost;
@class RCTSurfacePresenterBridgeAdapter;

namespace facebook::react
{
    class EmptyReactNativeConfig
    {
    };
}  // namespace facebook::react

#endif  // USE_BRIDGELESS
