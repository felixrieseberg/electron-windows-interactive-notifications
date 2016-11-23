const fs = require('fs')

function replaceSync (file, find, replace) {
  const contents = fs.readFileSync(file, 'utf8')
  const newContents = contents.replace(find, replace)

  if (newContents === contents) return false

  fs.writeFileSync(file, newContents, 'utf8')
  return true
}

module.exports = { replaceSync }
