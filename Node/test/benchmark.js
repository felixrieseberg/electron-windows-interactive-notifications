const perfy = require('perfy')
const isQuietHours = require('../lib/index').getIsQuietHours
const {Key, windef} = require('windows-registry')

const iterations = process.argv[2] || 100000

// Surpress windows-registry's dumb logs
const log = console.log
console.log = function () {}

function getIsQuietHoursThis () {
  isQuietHours()
}

function getIsQuietHoursWinReg () {
  const QUIET_HOURS_REGISTRY_KEY = 'NOC_GLOBAL_SETTING_TOASTS_ENABLED'

  try {
    let settingsKey = new Key(
      windef.HKEY.HKEY_CURRENT_USER,
      'Software\\Microsoft\\Windows\\CurrentVersion\\Notifications\\Settings',
      windef.KEY_ACCESS.KEY_READ
    )

    settingsKey.getValue(QUIET_HOURS_REGISTRY_KEY)
  } catch (error) {
    return false
  }
}

function measureThisTime () {
  perfy.start('this')
  for (let i = 0; i < iterations; i++) {
    getIsQuietHoursThis()
  }

  return perfy.end('this').time
}

function measureWinRegTime () {
  perfy.start('winreg')
  for (let i = 0; i < iterations; i++) {
    getIsQuietHoursWinReg()
  }

  return perfy.end('winreg').time
}

// Fight!
log(`Reading the quiet hours setting ${iterations} times:`)

const thisTime = measureThisTime()
const wrTime = measureWinRegTime()

log(`With this addon:                 ${thisTime}`)
log(`With windows-registry:           ${wrTime}`)
