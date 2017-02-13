const fs = require('fs')
const path = require('path')

const CONFIG_FILE = path.join(__dirname, '.ewin-configured')

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

function getConfiguration() {
  return new Promise((resolve) => {
    fs.stat(CONFIG_FILE, (err, result) => resolve(!!(err || !result)))
  })
}

function setConfiguration(configuration) {
  fs.writeFileSync(CONFIG_FILE, JSON.stringify(configuration), { encoding: 'utf-8' })
}

module.exports = { replaceSync, getAppPackage, getConfiguration, setConfiguration }
