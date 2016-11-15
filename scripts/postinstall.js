const fs = require('fs-extra')
const path = require('path')

const from = path.join(__dirname, 'dll', process.arch, 'InteractiveNotifications.dll')
const to = path.join(__dirname, 'build', 'Release')

fs.copySync(from, to)
