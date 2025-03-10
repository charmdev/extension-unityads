#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif


#include <hx/CFFI.h>
#include "UnityAdsEx.h"
#include <stdio.h>

using namespace unityads;

AutoGCRoot* unityAdsEventHandle = 0;

#ifdef IPHONE

static void unityads_set_event_handle(value onEvent)
{
	unityAdsEventHandle = new AutoGCRoot(onEvent);
}
DEFINE_PRIM(unityads_set_event_handle, 1);

static value unityads_init(value app_id, value testmode, value debugmode){
	init(val_string(app_id),val_bool(testmode),val_bool(debugmode));
	return alloc_null();
}
DEFINE_PRIM(unityads_init,3);

static value unityads_rewarded_show(value rewarded_placementid,value title, value msg){
	showRewarded(val_string(rewarded_placementid),val_string(title),val_string(msg));
	return alloc_null();
}
DEFINE_PRIM(unityads_rewarded_show,3);

static value unityads_canshow(value placementid){
	return alloc_bool(unityCanShow(val_string(placementid)));
}
DEFINE_PRIM(unityads_canshow,1);

#endif

extern "C" void unityads_main () {
	val_int(0); // Fix Neko init
	
}
DEFINE_ENTRY_POINT (unityads_main);

extern "C" int unityads_register_prims () { return 0; }

extern "C" void sendUnityAdsEvent(const char* type)
{
	printf("UnityAds Send Event: %s\n", type);
	value o = alloc_empty_object();
	alloc_field(o,val_id("type"),alloc_string(type));
	val_call1(unityAdsEventHandle->get(), o);
}
