const fs = require('fs')
const path = require('path')

function replaceSync (file, find, replace) {
  const contents = fs.readFileSync(file, 'utf8')
  const newContents = contents.replace(find, replace)

  if (newContents === contents) return false

  fs.writeFileSync(file, newContents, 'utf8')
  return true
}

function getAppPackage () {
  const cwd = process.cwd()
  const ends = cwd.indexOf('node_modules\\.staging')
  let package = null

  if (ends > 0) {
    try {
      package = require(path.join(cwd.slice(0, ends), 'package.json'))
    } catch (e) {
      // no-op
    }
  } else {
    try {
      package = require(path.join(process.cwd(), 'package.json'))
    } catch (e) {
      // no-op
    }
  }

  return package
}

module.exports = { replaceSync, getAppPackage }
