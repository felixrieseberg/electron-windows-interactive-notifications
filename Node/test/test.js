const assert = require('assert')
const getIsQuietHours = require('../lib/index').getIsQuietHours
const isQuietHours = getIsQuietHours()

if (process.platform !== 'win32') {
    assert.strictEqual(isQuietHours, false)
} else {
    const ok = isQuietHours === false || isQuietHours === true
    assert.ok(ok, true)
}
