#pragma once

#include <windows.ui.notifications.h>

namespace InteractiveNotifications {
	HRESULT RegisterAppForNotificationSupport();
	HRESULT InstallShortcut(_In_ PCWSTR shortcutPath, _In_ PCWSTR exePath);
	HRESULT RegisterComServer(_In_ PCWSTR exePath);

	HRESULT RegisterActivator();
	void UnregisterActivator();
	void silentActivation();

	// Sample stuff - I'm not sure that the toast stuff needs to be here
	HRESULT SendTestToast();

	// Sanity check
	double Add(double a, double b);
	HRESULT CreateToastXml(
		_In_ ABI::Windows::UI::Notifications::IToastNotificationManagerStatics* toastManager,
		_COM_Outptr_ ABI::Windows::Data::Xml::Dom::IXmlDocument** xml);

	HRESULT CreateToast(
		_In_ ABI::Windows::UI::Notifications::IToastNotificationManagerStatics* toastManager,
		_In_ ABI::Windows::Data::Xml::Dom::IXmlDocument* xml
	);
}

extern "C" {
	__declspec(dllexport) void RegisterForNotificationSupport();
	__declspec(dllexport) void RegisterActivator();
	__declspec(dllexport) void UnregisterActivator();
	__declspec(dllexport) void SendTestToast();
}