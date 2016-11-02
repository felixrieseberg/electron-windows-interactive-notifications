#include <node.h>
#include <v8.h>
#include <nan.h>

#include "InteractiveNotifications.h"
#include <malloc.h>
#include <windows.h>
#include <stdio.h>

typedef void (__stdcall *f_funci)();

using v8::Integer;
using v8::Local;
using v8::String;

NAN_METHOD(RegisterAppForNotificationSupport)
{
	Nan::HandleScope scope;

	if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsString())
	{
		Nan::ThrowTypeError("Invalid arguments, expected arguments are: shortcut name[string], app id [string]");
		return;
	}
	
	Local<String> shortcutHandle = Nan::To<String>(info[0]).ToLocalChecked();
	Local<String> appIdHandle = Nan::To<String>(info[1]).ToLocalChecked();
	
	String::Value shortcutStringValue(shortcutHandle);
	String::Value appIdStringValue(appIdHandle);

	HRESULT hr = InteractiveNotifications::RegisterAppForNotificationSupport((PCWSTR)*shortcutStringValue, (PCWSTR)*appIdStringValue);
	
	if (hr != S_OK)
	{
		Nan::ThrowError(String::Concat(Nan::New<String>("RegisterAppForNotificationsSupport Failed with error code:").ToLocalChecked(),
			Nan::To<String>(Nan::New<Integer>(static_cast<int>(hr))).ToLocalChecked()));
		return;
	}
}

NAN_METHOD(RegisterActivator)
{
	Nan::HandleScope scope;

	InteractiveNotifications::RegisterActivator();
}

NAN_METHOD(UnregisterActivator)
{
	Nan::HandleScope scope;

	InteractiveNotifications::UnregisterActivator();
}

// TODO: Remove?
NAN_METHOD(SendTestToast)
{
	Nan::HandleScope scope;

	InteractiveNotifications::SendTestToast();
}

NAN_MODULE_INIT(init) {
  
  // TODO: Make sure that this is necesarry..
  HRESULT hr = CoInitializeEx(NULL, COINITBASE_MULTITHREADED);

  Nan::SetMethod(target, "registerAppForNotificationSupport", RegisterAppForNotificationSupport);
  Nan::SetMethod(target, "registerActivator", RegisterActivator);
  Nan::SetMethod(target, "unregisterActivator", UnregisterActivator);
  // TODO: Remove?
  Nan::SetMethod(target, "sendTestToast", SendTestToast);
}

NODE_MODULE(notifications_bindings, init)