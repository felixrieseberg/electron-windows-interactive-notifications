const ffi = require('ffi')
const lib = ffi.Library('../../InteractiveNotifications/Debug/InteractiveNotifications', {
    'CRegisterForNotificationSupport': ['string', []]
})

console.log(lib)
console.log(lib.CRegisterForNotificationSupport())
