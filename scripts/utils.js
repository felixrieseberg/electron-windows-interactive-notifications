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
  let package = null

  if (process.cwd()) {
    try {
      package = require(path.join(process.cwd(), 'package.json'))
    } catch (e) {
      // no-op
    }
  }

  return package
}

module.exports = { replaceSync, getAppPackage }
