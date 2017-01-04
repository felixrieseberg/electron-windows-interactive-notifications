# Respond to Interactive Notifications, from Node or Electron
This project allows you to respond to Windows interactive notifications. Interactive notifications allow the user to interact with the notification by entering data. In order to receive that data, your application will need to register a COM component with the operating system.

> :memo: To send notifications from Electron, take a look at [`electron-windows-notifications`](https://github.com/felixrieseberg/electron-windows-notifications)

# Installation
> :warning: Please read these instructions carefully.

### A unique identifier for all apps
When a win32 desktop application sends an interactive toast notification, Windows checks if the start menu contains a shortcut to the sending binary. If that is the case, it will check the shortcut for the `System.AppUserModel.ToastActivatorCLSID` property. If that property is set, it will attempt to activate a COM component using the given CLSID. The CLSID needs to be defined at compile-time and needs to be unique. This property is in concept similar to the `AppUserModelId`.

For that reason, this module will either use a specified CLSID or generate a random CLSID during installation and print it to console. There are two ways to set the CLSID:

 - Using an environment variable `TOAST_ACTIVATOR_CLSID`
 - Using the `package.json` of your application

 ```json
 {
     "dependencies": { },
     "interactive-notifications": {
         "toast-activator-clsid": "B23D2B18-8DD7-403A-B9B7-152B40A1478C"
     }
 }
```

For that reason, this module compiles either using a set environment variable, a property `"windows-notifications": { "toastActivatorCLSID": "YOUR_ID" }`,  or will generate a unique CLSID during installation. In both cases it will print to the console which CLSID was used.

### The protocol to launch
To start your application, this module uses protocol links (like `spotify://` or `slack://`). Define the protocol that will be compiled into the dll using one of the following two methods:

 - Using an environment variable `TOAST_ACTIVATOR_PROTOCOL`
 - Using the `package.json` of your application

 ```json
 {
     "dependencies": { },
     "interactive-notifications": {
         "protocol": "myapp://"
     }
 }
 ```

## Example Installation

```
$env:TOAST_ACTIVATOR_PROTOCOL="myapp://"
$env:TOAST_ACTIVATOR_CLSID="B23D2B18-8DD7-403A-B9B7-152B40A1478C"
npm install --save windows-interactive-notifications
```

# Usage
This module contains only three methods relevant to you:

## `registerAppForNotificationSupport(shortcutPath, appId)`
In order to receive interactive notification activations, your application must have a shortcut in the Start Menu. That shortcut needs to contain two values in its `propertyStore`: A `System.AppUserModel.ToastActivatorCLSID` and a `System.AppUserModel.Id`. You don't have to use this module to set the shortcut, but it is offered for your convenience. Since the CLSID needs to be hardcoded at compile-time, it is not a parameter (see installation for more details).

Example
```javascript
const {registerAppForNotificationSupport} = require('windows-interactive-notifications')
const shortcutPath = 'Microsoft\\Windows\\Start Menu\\MyApp.lnk'
const appId = 'com.squirrel.mycompany.myapp'

registerAppForNotificationSupport(shortcutPath, appId)
```

## `registerActivator()`
Use this method to enable the activator. It registers the COM component with Windows. Call it before sending a notification. Calling it multiple times has no downside.

## `unregisterActivator()`
Use this method to disable the activator. It unregisters the COM component with Windows.

## Example Usage
Once you have registered your application for notification support (either using your own shortcut creation method or the one given in this module), register the activator.

This module will communicate with your application using protocol links. You might know about `mailto:` - and how you can tell an email application to create a new email draft by calling `mailto:someone@example.com?subject=This%20is%20the%20subject`. Well, this module works the same way: During installation, you defined your applications protocol. It is up to you to ensure that your app can actually receive those links. To debug this behavior, feel free to just use `Windows Run` (open it with `Windows + R`).

The app will activate your app in the following format:

```
<Protocol><Toast Arguments>&userData=[{"key":"value"}]
```

So, for a notification that contains the following template, your app would be called with the following URI:

```xml
<actions>
  <input id="message" type="text" placeHolderContent="Type a reply" />
  <action hint-inputId="message" activationType="background" content="Reply" arguments="message/?user=123" />
</actions>
```

```
myapp://message/?user=123&userData=[{"key":"message","value":"Hello"}]
```

This module does super-basic escaping. Spaces are turned into `%20`, doublequotes (`"`) are turned into `%22`. Ironically though, Unicode is supported.

# License
MIT. Please see License for details.
