# Windows Interactive Notifications, from Node

## Installation
> :warning: Please read these instructions carefully.

### A unique identifier for all apps
When a win32 desktop application sends an interactive toast notification, Windows checks if the start menu contains a shortcut to the sending binary. If that is the case, it will check the shortcut for the `System.AppUserModel.ToastActivatorCLSID` property. If that property is set, it will attempt to activate a COM component using the given CLSID. The CLSID needs to be defined at compile-time and needs to be unique. This property is in concept similar to the `AppUserModelId`.

For that reason, this module will either use a specified CLSID or generate a random CLSID during installation and print it to console. There are two ways to set the CLSID:

 - Using an environment variable `TOAST_ACTIVATOR_CLSID`
 - Using the `package.json` of your application

 ```json
 {
     "dependencies" :{
         ...
     },
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
     "dependencies" :{
         ...
     },
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

## License
MIT. Please see License for details.