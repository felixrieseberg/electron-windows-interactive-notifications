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

namespace InteractiveNotifications {
	class InteractiveNotificationsManager
	{
	public:
		INTERACTIVENOTIFICATIONS_API HRESULT RegisterAppForNotificationSupport();
		INTERACTIVENOTIFICATIONS_API HRESULT InstallShortcut(_In_ PCWSTR shortcutPath, _In_ PCWSTR exePath);
		INTERACTIVENOTIFICATIONS_API HRESULT RegisterComServer(_In_ PCWSTR exePath);

		INTERACTIVENOTIFICATIONS_API HRESULT RegisterActivator();
		INTERACTIVENOTIFICATIONS_API void UnregisterActivator();

		// Returns a + b
		static INTERACTIVENOTIFICATIONS_API double Add(double a, double b);

		// Returns a * b
		static INTERACTIVENOTIFICATIONS_API double Multiply(double a, double b);

		// Returns a + (a * b)
		static INTERACTIVENOTIFICATIONS_API double AddMultiply(double a, double b);
	};
}