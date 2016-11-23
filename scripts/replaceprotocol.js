/*
  Some methods taken from https://github.com/kelektiv/node-uuid/blob/master/uuid.js
*/

const path = require('path')
const fs = require('fs')
const {replaceSync} = require('./utils')

const DEFINED_PROTOCOL = /slack:\/\//gi

function replaceProtocol () {
  const newProtocol = process.env.TOAST_ACTIVATOR_PROTOCOL
  const cppFile = path.join(__dirname, '..', 'InteractiveNotifications', 'InteractiveNotifications.cpp')

  console.log(`\n##### ToastActivator Protocol #############################`)
  console.log(`DLLs will be compiled with the following launch protocol:`)
  console.log(newProtocol)
  console.log(`###########################################################\n`)

  replaceSync(cppFile, DEFINED_PROTOCOL, newProtocol)
}

module.exports = replaceProtocol
