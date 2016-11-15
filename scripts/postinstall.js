const path = require('path')
const fs = require('fs')

const from = path.join(__dirname, '..', 'dll', process.arch, 'InteractiveNotifications.dll')
const to = path.join(__dirname, '..', 'build', 'Release', 'InteractiveNotifications.dll')

fs.createReadStream(from).pipe(fs.createWriteStream(to))

