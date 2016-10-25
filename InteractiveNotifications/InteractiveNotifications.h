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

#include <windows.ui.notifications.h>

namespace InteractiveNotifications {
	class InteractiveNotificationsManager
	{
	public:
		static INTERACTIVENOTIFICATIONS_API HRESULT RegisterAppForNotificationSupport();
		static INTERACTIVENOTIFICATIONS_API HRESULT InstallShortcut(_In_ PCWSTR shortcutPath, _In_ PCWSTR exePath);
		static INTERACTIVENOTIFICATIONS_API HRESULT RegisterComServer(_In_ PCWSTR exePath);

		static INTERACTIVENOTIFICATIONS_API HRESULT RegisterActivator();
		static INTERACTIVENOTIFICATIONS_API void UnregisterActivator();
		
		// Sample stuff - I'm not sure that the toast stuff needs to be here
		static INTERACTIVENOTIFICATIONS_API HRESULT SendTestToast();

		// Sanity check
		static INTERACTIVENOTIFICATIONS_API double Add(double a, double b);
	private:
		static INTERACTIVENOTIFICATIONS_API HRESULT CreateToastXml(
			_In_ ABI::Windows::UI::Notifications::IToastNotificationManagerStatics* toastManager,
			_COM_Outptr_ ABI::Windows::Data::Xml::Dom::IXmlDocument** xml);

		static INTERACTIVENOTIFICATIONS_API HRESULT CreateToast(
			_In_ ABI::Windows::UI::Notifications::IToastNotificationManagerStatics* toastManager,
			_In_ ABI::Windows::Data::Xml::Dom::IXmlDocument* xml
		);
	};
}