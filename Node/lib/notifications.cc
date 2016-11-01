#include <node.h>
#include <v8.h>

#include "../../InteractiveNotifications/stdafx.h"
#include "../../InteractiveNotifications/InteractiveNotifications.cpp"
#include <malloc.h>
#include <windows.h>
#include <stdio.h>

using namespace v8;

typedef void (__stdcall *f_funci)();

void Method(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);



  InteractiveNotifications::Add();

  args.GetReturnValue().Set(Boolean::New(isolate, true));
}

void Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  exports->Set(String::NewFromUtf8(isolate, "start"),
      FunctionTemplate::New(isolate, Method)->GetFunction());
}

NODE_MODULE(quiethours, Init)