const addon = require('bindings')('notifications_bindings');
const ToastNotification = require('electron-windows-notifications').ToastNotification;

console.log(addon);

const shortcutPath = 'Microsoft\\Windows\\Start Menu\\lol.lnk';
const appId = 'com.felix.test';

addon.unregisterActivator();
