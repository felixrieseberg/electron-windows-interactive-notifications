const path = require('path')
const fs = require('fs')

const from86 = path.join(__dirname, '..', 'Release')
const to86 = path.join(__dirname, '..', 'dll', 'ia32')

const from64 = path.join(__dirname, '..', 'x64', 'Release')
const to64 = path.join(__dirname, '..', 'dll', 'x64')

fs.createReadStream(from86).pipe(fs.createWriteStream(to86))
fs.createReadStream(from64).pipe(fs.createWriteStream(to64))
