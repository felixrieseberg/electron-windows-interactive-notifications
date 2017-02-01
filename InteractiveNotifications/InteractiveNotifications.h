// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the INTERACTIVENOTIFICATIONS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// INTERACTIVENOTIFICATIONS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef INTERACTIVENOTIFICATIONS_EXPORTS
#define INTERACTIVENOTIFICATIONS_API __declspec(dllexport)
#else
#define INTERACTIVENOTIFICATIONS_API __declspec(dllimport)
#endif

#include <string>
#include <windows.ui.notifications.h>

namespace InteractiveNotifications {
	INTERACTIVENOTIFICATIONS_API HRESULT RegisterAppForNotificationSupport(PCWSTR shortcut, PCWSTR appId);
	INTERACTIVENOTIFICATIONS_API HRESULT InstallShortcut(_In_ PCWSTR shortcutPath, _In_ PCWSTR exePath, PCWSTR appId);

	INTERACTIVENOTIFICATIONS_API HRESULT RegisterComServer();
	INTERACTIVENOTIFICATIONS_API HRESULT RegisterActivator();
	INTERACTIVENOTIFICATIONS_API void UnregisterActivator();
	INTERACTIVENOTIFICATIONS_API std::string ws2utf8hex(const std::wstring&);
	INTERACTIVENOTIFICATIONS_API std::wstring s2ws(const std::string&);
}