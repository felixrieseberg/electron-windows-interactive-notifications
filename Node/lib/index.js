const ffi = require('ffi');
const lib = ffi.Library('../../InteractiveNotifications/Debug/InteractiveNotifications', {
    'CRegisterForNotificationSupport': ['void', []]
});


console.log(lib);